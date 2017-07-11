#ifndef AST_H
#define AST_H

#include<stdlib.h>
#include<stdio.h>

#include"helpers.h"
#include"token.h"

/* stuff concerning the ASTs */

/*
each node is treated like a tree in and of itself
variables in the program will be pointers to a tree 
*/

/* AST NODE DEFINITIONS */

// AST node types
typedef enum {
	None,
	NumberNode,
	PlusNode,
	MinusNode,
	MultiplyNode,
	DivideNode,
	IdentifierNode,
	AssignmentNode,
	UnaryMinus
}
AST_Type;

// converts type to string for printing
char* AST_TypeRepr(AST_Type t);

/* 
name: basic node
description: "base class" for AST nodes
execution: not executed
*/
typedef struct {
	AST_Type type;
}
AST_Node;

/*
name: number node
description: ast node that holds/represents a number
execution: terminal; returns itself
*/
typedef struct {
	AST_Type type;
	double number;
}
AST_Number;

/*
name: binary operator node
description: node for binary operations
execution: execute left, execute right, return result of operation
*/
typedef struct {
	AST_Type type;
	AST_Node* left;
	AST_Node* right;
}
AST_BinOp;

/*
name: identifier node
description: node for identifiers; points to another tree (which may be a number etc.)
execution: execute the tree and return the result
*/
typedef struct {
	AST_Type type;
	AST_Node* tree;
	char* name;
}
AST_Identifier;

/*
name: assignment node
description: node for assignment
execution: changes left to point to the same tree as right, returns left.
*/
typedef struct {
	AST_Type type;
	AST_Identifier* left;
	AST_Node* right;
}
AST_Assignment;

/*
name: unary minus
description: unary minus
execution: unary minus
*/
typedef struct {
	AST_Type type;
	AST_Node* negate;
}
AST_UnaryMinus;

// AST Runtime Functions ============================================================

// defines execution of all ast node types
AST_Node* execute(AST_Node* root);

// frees an ast
/* this function is called when building an ast has failed */
void freeast(AST_Node* n);

// does runtime type checking and execution of binary op nodes (+-*/)
AST_Node* BinOpCheck(AST_Node* root);

// Building ASTs from the input tokens =============================================

/*
These functions try to use a rule in the grammar to build an ast.

The grammar is written below these function delcarations

if building the ast is successful;
	they will update the tlindex parameter
	and return a pointer to an ast for executing the rule.

if rule failed without error
	returns zero; and does not affect the tlindex parameter

if rule failed with error
	returns zero and sets tlindex to -1
*/
AST_Node* Statement(TokenArray* ta, int* tlindex);
AST_Node* TypeDefinition(TokenArray* ta, int* tlindex);
AST_Node* VariableDeclaration(TokenArray* ta, int* tlindex);
AST_Node* Expression(TokenArray* ta, int* tlindex);
AST_Node* Identifier(TokenArray* ta, int* tlindex);
AST_Node* Assignment(TokenArray* ta, int* tlindex);
AST_Node* FunctionDefinition(TokenArray* ta, int* tlindex);
//AST_Node* FunctionDefinitionParameters(TokenArray* ta, int* tlindex);
AST_Node* FunctionCall(TokenArray* ta, int* tlindex);
//AST_Node* FunctionCallParameters(TokenArray* ta, int* tlindex);
AST_Node* NumericExpression(TokenArray* ta, int* tlindex);
AST_Node* NumericTerm(TokenArray* ta, int* tlindex);
AST_Node* NumericFactor(TokenArray* ta, int* tlindex);
AST_Node* Number(TokenArray* ta, int* tlindex);

// returns a char* that represents this ast
void AST_FPrint(FILE* fp, AST_Node* tree);

/*
grammar:

statement:
	variable declaration ';'
	type def ';'
	expression ';'

variable decl : 
	typename followed by identifier
	typename then assignment

typedef:
	'class' identifier '{' statements '}'

expression:
	identifier
	assignment
	function def
	function call
	numeric expression

assignment:
	identifier '=' expression

function def:
	'func' '(' parameter declaration ')' '->' typename ':' '{' statements '}'

parameter declaration:
	variable declaration optionally followed by comma and then more variable declarations

function call:
	identifier '(' parameter list ')'

parameter list:
	expression optionally followed by comma and then more expressions

numeric expression:
	summation of terms

term:
	product/division of factors/divisors
	factor
	factor plus factor
	factor minus factor

factor:
	number
	identifier
	factor '^' factor
	'(' numeric expression ')' 

number : digit optionally followed by a . then more digit, optionally followed by the letter 'e' then ('+', '-', '') then more digit.
*/

#endif
