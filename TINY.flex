/******************************/
/* File: TINY.flex            */
/* Lex specification for C-   */
/******************************/

%{
#include "globals.h"
#include "util.h"
#include "scan.h"
#include "util.c"
char tokenString[MAXTOKENLEN+1];
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}({letter}|{digit})*
newline     \n
whitespace  [ \t]+

%option noyywrap

%%

"if"            { return IF; }
"else"          { return ELSE; }
"int"           { return INT; }
"void"          { return VOID; }
"while"         { return WHILE; }
"return"        { return RETURN; }
"=="            { return EQ; }
"!="            { return NEQ; }
"<="            { return LE; }
">="            { return GE; }
"<"             { return LT; }
">"             { return GT; }
"="             { return ASSIGN; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return OVER; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
";"             { return SEMI; }
","             { return COMMA; }
{number}        { return NUM; }
{identifier}    { return ID; }
{newline}       { lineno++; }
{whitespace}    { /* skip whitespace */ }
"/*"            { char c, prev = 0;
                  do
                  { prev = c;
                    c = input();
                    if (c == EOF) break;
                    if (c == '\n') lineno++;
                  } while (!(prev == '*' && c == '/'));
                }
.               { return ERROR; }

%%

TokenType getToken(void)
{ static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin  = fopen("tiny.txt", "r");
    yyout = fopen("result.txt", "w");
    listing = yyout;
  }
  currentToken = yylex();
  strncpy(tokenString, yytext, MAXTOKENLEN);

  fprintf(listing, "\t%d: ", lineno);
  printToken(currentToken, tokenString);

  return currentToken;
}

int main()
{
  printf("welcome to the C- flex scanner\n");
  while(getToken())
  {
    printf("a new token has been detected...\n");
  }
  return 1;
}
