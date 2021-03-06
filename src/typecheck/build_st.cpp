#include "typecheck/build_st.h"
using namespace typecheck;

BuildST::BuildST() {
  curr_scope = new Groot(); // Create Groot (root of the symbol table tree)
}

/**
 * Add classes to the symbol tree
 */
void BuildST::visit(ClassList* classes) {
  for(auto child : classes->getChildren()) {
    child->accept(this);
  }
}

/**
 * Add the methods and members of classes to the symbol tree
 */
void BuildST::visit(ClassStatement* cls) {
  /** Add class to Groot **/
  ClassNode* nnode = new ClassNode(cls->cantExtend());
  nnode->setAst(cls);

  // Set class this inherits from 
  if(cls->getInheritType() != nullptr) {
    nnode->setSuper(*cls->getInheritType()->getName());
  }

  // Add new class to groot
  string class_name = *cls->getType()->getName();
  ((Groot*) curr_scope)->addClass(class_name, nnode);
  nnode->setName(class_name);

  // Set AST reference up so the new class scope can be easily found from the AST
  cls->setScope(nnode);

  // Forward visitor
  if(cls->getList() != nullptr) {
    curr_scope = nnode;
    cls->getList()->accept(this);
    curr_scope = curr_scope->getLexParent();
  }
}

/**
 * Forward the visitor down to the members of a feature list
 */
void BuildST::visit(FeatureList* list) {
  for(auto featureOpt : list->getList()) {
    if(featureOpt->getFeat() != nullptr) {
      featureOpt->getFeat()->accept(this);
    } else if(featureOpt->getForm() != nullptr) {
      featureOpt->getForm()->accept(this);
    } else {
      throw "Error: Neither formal or feature specified for FeatureOpt";
    }
  }
}

/**
 * Add a new attribute to the class, let scope, or method parameter list.
 */
void BuildST::visit(FormalDeclare* formal) {
  string name = *(formal->getID()->getName());
  string type = *(formal->getType()->getName());

  if(curr_scope->isA(CLASSNODE)) { // Add attribute to class
    ((ClassNode*) curr_scope)->addMember(name, type);
  } else if(curr_scope->isA(SYMBOLANON)) { // Add variable to LET block
    ((SymbolAnon*) curr_scope)->addMember(name, type);
  } else if(curr_scope->isA(SYMBOLMETHOD)) { // Add parameter to method
    ((SymbolMethod*) curr_scope)->addParam(name, type);
  }
}

/**
 * Add a new method to the class
 */
void BuildST::visit(Feature* feat) {
  // Get name and type info
  string name = *(feat->getID()->getName());
  string retType = *(feat->getType()->getName());

  // Create new method node
  SymbolMethod* method = new SymbolMethod();
  method->setRetType(retType); // Set return type

  // Add method to class
  ((ClassNode*) curr_scope)->addMethod(name, method);
  curr_scope = method;

  // Create reference from AST to symbol tree
  feat->setScope(method);

  /* Add parameters to the scope tree */
  if(feat->getList() != nullptr) {
    feat->getList()->accept(this);
  }

  feat->getExpr()->accept(this); // Forward to the method's expression.

  curr_scope = curr_scope->getLexParent();
}

/**
 * Forward visitor down to the parameters
 */
void BuildST::visit(ListFormalDeclare* paramList) {
  for(auto param : paramList->getList()) {
    param->accept(this);
  }
}

/**
 * Add a new let block to the method.
 */
void BuildST::visit(LetStatement* let) {
  /* Add the new let statement */
  SymbolAnon* sub = new SymbolAnon();

  if(curr_scope->isA(SYMBOLMETHOD)) {
    ((SymbolMethod*) curr_scope)->addMember(sub);
  } else if(curr_scope->isA(SYMBOLANON)) {
    ((SymbolAnon*) curr_scope)->addSub(sub);
  }

  let->setScope(sub);

  curr_scope = sub;
  let->getList()->accept(this); // Forward the visitor
  let->getExpr()->accept(this); // Forward to substatements

  curr_scope = curr_scope->getLexParent();
}

/**
 * Forward to children
 */
void BuildST::visit(ExprList* list) {
  for(auto child : list->getChildren()) {
    child->accept(this);
  }
}

/**
 * Forward to children
 */
void BuildST::visit(WhileLoop* loop) {
  loop->getCond()->accept(this);
  loop->getBody()->accept(this);
}

/**
 * Forward to children
 */
void BuildST::visit(IfStatement* if_state) {
  if_state->getCond()->accept(this);
  if_state->getBody()->accept(this);
  if_state->getElseBody()->accept(this);
}

/**
 * Forward to children
 */
void BuildST::visit(CaseStatement* case_state) {
  case_state->getExpr()->accept(this);
  case_state->getCaseList()->accept(this);
}

/**
 * Forward to children
 */
void BuildST::visit(CaseList* list) {
  for(auto el : list->getList()) {
    el->accept(this);
  }
}

/**
 * Each case works like a Let with only one new variable.
 */
void BuildST::visit(Case* case_item) {
  SymbolAnon* sub = new SymbolAnon();

  //Add this case's variable to scope.
  string name = *(case_item->getID()->getName());
  string type = *(case_item->getType()->getName());
  sub->addMember(name, type);

  if(curr_scope->isA(SYMBOLMETHOD)) {
    ((SymbolMethod*) curr_scope)->addMember(sub);
  } else if(curr_scope->isA(SYMBOLANON)) {
    ((SymbolAnon*) curr_scope)->addSub(sub);
  }

  curr_scope = sub;

  case_item->getExpr()->accept(this);

  curr_scope = curr_scope->getLexParent();
}
