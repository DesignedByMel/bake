#pragma once

#include <string>
#include "ast/visitor.h"
#include "ast/node.h"
#include "ir/class_list.h"
#include "typecheck/symbol_node.h"

namespace ir {

  enum ScopeType{ANON, METHOD, CLASS};

  class BuildIR : bake_ast::Visitor {
  public:
    BuildIR(bake_ast::ClassList* ast_root);
    virtual ~BuildIR();

    ClassList* getClassList() { return classlist; }

    // Terminal nodes
    void visit(bake_ast::IntegerVal*);
    void visit(bake_ast::Int8Val*);
    void visit(bake_ast::Int64Val*);
    void visit(bake_ast::FloatVal*);
    void visit(bake_ast::StringVal*);
    void visit(bake_ast::BoolVal*);
    void visit(bake_ast::Id*);
    void visit(bake_ast::Type*);

    // Unary Operators
    void visit(bake_ast::LogicalNot*);
    void visit(bake_ast::BitNot*);
    void visit(bake_ast::Isvoid*);
    void visit(bake_ast::New*);

    // Binary Operators
    void visit(bake_ast::Plus*);
    void visit(bake_ast::Minus*);
    void visit(bake_ast::Multiply*);
    void visit(bake_ast::Divide*);
    void visit(bake_ast::LessThan*);
    void visit(bake_ast::LessThanEqual*);
    void visit(bake_ast::Equal*);
    void visit(bake_ast::Assign*);

    // Misc
    void visit(bake_ast::ExprList*);
    void visit(bake_ast::WhileLoop*);
    void visit(bake_ast::IfStatement*);
    void visit(bake_ast::LetStatement*);
    void visit(bake_ast::CaseStatement*);
    void visit(bake_ast::CaseList*);
    void visit(bake_ast::Case*);
    void visit(bake_ast::FormalDeclare*);
    void visit(bake_ast::ClassStatement*);
    void visit(bake_ast::ClassList*);
    void visit(bake_ast::Dispatch*);
    void visit(bake_ast::ListFormalDeclare*);
    void visit(bake_ast::Feature*);
    void visit(bake_ast::FeatureOption*);
    void visit(bake_ast::FeatureList*);

  private:
    void visitOutstring(bake_ast::Dispatch* n);
    void visitOutint(bake_ast::Dispatch* n);
    int reserveReg() { return reg_count++; } // Gets the current number of used virtual registers and increments the counter
    int getRegCount() { return reg_count++; } //  increments the counter and Gets the current number of used virtual registers

    ClassList* classlist;
    ClassDef* curr_class; // Reference to the current class being compiled
    Method*  curr_method; // Reference to the current method being compilerd
    BasicBlock* curr_bb;  // Reference to the current basic block being compiled

    // Current basic-hacky solution to the last minute problem of referencing hte ST in the IR
    ScopeType scopeFlag;                    // This flag tells us which of the next three to use
    typecheck::ClassNode* classNode;        // Use if in class scope
    typecheck::SymbolAnon* symbolAnon;      // Use if in a symbolAnon (i.e. case, let)
    typecheck::SymbolMethod* symbolMethod;  // Use if in method scope


    int reg_count = 0; // Number of virtual registers that have been created. The next register that should be created is reg_count + 1
    std::pair <int,RegisterType>  throwup; // Used to specify which register the result of an operation is stored in.
  };
}
