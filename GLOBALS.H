/****************************************************/
/* File: globals.h                                  */
/* Global types and vars for C- scanner             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 6

typedef enum
    /* book-keeping tokens */
   {ENDFILE, ERROR,
    /* reserved words */
    IF, ELSE, INT, VOID, WHILE, RETURN,
    /* multicharacter tokens */
    ID, NUM,
    /* special symbols */
    ASSIGN,     /* =  */
    EQ,         /* == */
    NEQ,        /* != */
    LT,         /* <  */
    LE,         /* <= */
    GT,         /* >  */
    GE,         /* >= */
    PLUS,       /* +  */
    MINUS,      /* -  */
    TIMES,      /* *  */
    OVER,       /* /  */
    LPAREN,     /* (  */
    RPAREN,     /* )  */
    LBRACKET,   /* [  */
    RBRACKET,   /* ]  */
    LBRACE,     /* {  */
    RBRACE,     /* }  */
    SEMI,       /* ;  */
    COMMA       /* ,  */
   } TokenType;

extern FILE* source;
extern FILE* listing;
extern FILE* code;

extern int lineno;

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

typedef enum {StmtK, ExpK} NodeKind;
typedef enum {IfK, WhileK, ReturnK, AssignK, ReadK, WriteK} StmtKind;
typedef enum {OpK, ConstK, IdK} ExpKind;

typedef enum {Void, Integer, Boolean} ExpType;

#define MAXCHILDREN 3

typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
     union { StmtKind stmt; ExpKind exp;} kind;
     union { TokenType op;
             int val;
             char * name; } attr;
     ExpType type;
   } TreeNode;

extern int EchoSource;
extern int TraceScan;
extern int TraceParse;
extern int TraceAnalyze;
extern int TraceCode;
extern int Error;

#endif
