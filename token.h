#ifndef TOKEN_H
#define TOKEN_H

/*
This file contains the definitions of all the stuff related to tokens and token arrays.
*/

#include"arrays.h"

// token ============================================================================
typedef struct {
	int pos;	// Position of token in buffer.
	char* data;	// token data
	char* type;	// token type
} Token;

// creates a token
Token* NewToken(Token* t, Token T)
{
	t->pos = T.pos;
	t->data = T.data;
	t->type = T.type;
	return t;
}

// deletes a token.
void Token_Free(Token* t)
{
	free(t->data);
	free(t->type);
	free(t);
}

// returns a char* that represents this token
char* Token_Repr(Token* t)
{
	int reprStrLen = strlen("Token(, '')\n") + strlen(t->data) + strlen(t->type) + 1;
	char* reprStr = (char*) malloc(reprStrLen);
	sprintf(reprStr, "Token(%s, \'%s\')\n", t->type, t->data);
	
	return reprStr;
}

// compare data of two tokens
int Token_Dcmp(Token* a, Token* b)
{
	return !strcmp(a->data, b->data);
}

// compare type of two tokens
int Token_Tcmp(Token* a, Token* b)
{
	return !strcmp(a->type, b->type);
}

// check type of a token
int Token_isType(Token* t, char* type)
{
	return !strcmp(t->type, type);
}

// check data of a token
int Token_isData(Token* t, char* data)
{
	return !strcmp(t->data, data);
}

// token array ======================================================================

CompleteArrayDefinition(TokenArray, Token, tokens);

#endif
