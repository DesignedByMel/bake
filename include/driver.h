#pragma once

#include <iostream>
#include <string>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "ast/ast.h"
#include "codegen/director.h"
#include "ir/build_ir.h"
#include "ir/class_list.h"
#include "ir/ir_visitor.h"
#include "typecheck/symbol_node.h"
#include "typecheck/build_st.h"
#include "typecheck/symbol_table_print.h"
#include "typecheck/visitor_tc.h"
#include "typecheck/check_scope.h"

extern int yylineno;
extern int nelements;
extern FILE* yyin;
extern FILE* yyout;
extern bool printLex;
extern ClassList* ast;

int yylex(void);
int yyparse(void);
void help(char* cmd_name);
void yylex_destroy(void);
int perform_lex(string in_fname, bool print_lex);
void add_builtins();
void add_nums();

ClassStatement* buildObject();
ClassStatement* buildIO();
ClassStatement* buildString();
ClassStatement* buildBool();
ClassStatement* buildConvert();
FeatureOption* buildConvertFunc(string name);
