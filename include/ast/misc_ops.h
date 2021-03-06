
#ifndef __THE_AWSOME__
#define __THE_AWSOME__

#include "node.h"
using namespace bake_ast;

namespace bake_ast {

  /*** WhileLoop ***/
  class WhileLoop : public Node {
  public:
    WhileLoop() : Node(WHILELOOP) { };
    WhileLoop(Node* c, Node* b);
    virtual ~WhileLoop();

    void setCond(Node* n) { this->cond = n; }
    Node* getCond() { return this->cond; }

    void setBody(Node* n) { this->body = n; }
    Node* getBody() { return this->body; }

    void accept(Visitor* v) { v->visit(this); }

  private:
    Node* cond;
    Node* body;
  };
  
  /*** Formal Declare: for method arguments and optional expression assignments ***/
  // this class also supports the optional expression assignment.
  class FormalDeclare : public Node {
  public:
    FormalDeclare() : Node(FORMALDECLARE) {};
    FormalDeclare(Id* i, Type* t, Node* e = nullptr);
    virtual ~FormalDeclare();

    Id* getID() { return this->id; }
    Type* getType() { return this->type; }
    Node* getExpr() { return this->expr; }

    void setID(Id* n) { id = n; }
    void setType(Type* n) { type = n; }
    void setExpr(Node* n) { expr = n; }

    void accept(Visitor* v) { v->visit(this); }

  private:
    Id* id;
    Type* type;
    Node* expr = nullptr;
  };

  /*** IfStatement ***/
  class IfStatement : public Node {
  public:
    IfStatement() : Node(IFSTATEMENT) {};
    IfStatement(Node* c, Node* b, Node* e);
    virtual ~IfStatement();

    void setCond(Node* n) { this->cond = n; }
    Node* getCond() { return this->cond; }

    void setBody(Node* n) { this->body = n; }
    Node* getBody() { return this->body; }

    void setElseBody(Node* n) { this->elseBody = n; }
    Node* getElseBody() { return this->elseBody; }

    void accept(Visitor* v) { v->visit(this); }

  private:
    Node* cond;
    Node* body;
    Node* elseBody;
  };

  /*** Case Statements ***/
  // this class also supports the optional expression assignment.
  class Case : public Node {
  public:
    Case() : Node(CASE) {};
    Case(Id* i, Type* t, Node* e);
    virtual ~Case();

    Id* getID() { return this->id; }
    Type* getType() { return this->type; }
    Node* getExpr() { return this->expr; }

    void setID(Id* n) { id = n; }
    void setType(Type* n) { type = n; }
    void setExpr(Node* n) { expr = n; }

    void accept(Visitor* v) { v->visit(this); }

  private:
    Id* id;
    Type* type;
    Node* expr;

  };
}

#endif
