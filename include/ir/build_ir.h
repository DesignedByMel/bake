#pragma once

#include "ast/visitor.h"
#include "ir/class_list.h"

namespace ir {
  class BuildIR : bake_ast::Visitor {
  public:
    BuildIR();

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
    ClassList* classes;
  };
}