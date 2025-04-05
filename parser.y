/* CMSC 430 Compiler Theory and Design
   Project 2 Skeleton
   UMGC CITE
   Summer 2023 

   Project 2 Parser */

%{
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "types.h"
#include "listing.h"
#include "symbols.h"

int yylex();
Types find(Symbols<Types>& table, CharPtr identifier, string tableName);
void yyerror(const char* message);

Symbols<Types> scalars;
Symbols<Types> lists;

%}

%define parse.error verbose

%union {
	CharPtr iden;
	Types type;
}

%token <iden> IDENTIFIER

%token <type> INT_LITERAL CHAR_LITERAL REAL_LITERAL HEX_LITERAL

%type <type> list expressions body type statements statement cases case expression
	term primary base variable function_header factor condition logical_operator
	elsif_clauses list_choice

%token ADDOP MULOP ANDOP RELOP OROP NOTOP MODOP EXPOP NEGOP ARROW

%token LPAREN RPAREN SEMICOLON COLON COMMA 

%token BEGIN_ CASE CHARACTER ELSE ELSIF END ENDSWITCH FUNCTION INTEGER IS LIST OF OTHERS
	RETURNS SWITCH WHEN ENDFOLD ENDIF FOLD IF LEFT RIGHT THEN REAL

%left ADDOP
%left MULOP MODOP 
%right EXPOP
%left ANDOP OROP 
%left NOTOP NEGOP 


%%

function: function_header variables body

variables: /* empty */ | variables variable

function_header: FUNCTION IDENTIFIER parameters_opt RETURNS type SEMICOLON
	| error SEMICOLON {$$ = MISMATCH;}
	;

parameters_opt: /* empty */ | parameters

variable: IDENTIFIER COLON type IS statement {checkAssignment($3, $5, "Variable Initialization"); scalars.insert($1, $3);}
	| IDENTIFIER COLON LIST OF type IS list SEMICOLON {$$= checkListType($5, $7); lists.insert($1, $5);}
	| error SEMICOLON {$$ = MISMATCH;}
	;

list: LPAREN expressions RPAREN {$$ = $2;}

expressions: /* empty */ {$$ = NONE;}
	| expression
	| expressions COMMA expression {$$ = checkList($1, $3);}
	;

parameters: parameter 
	| parameters COMMA parameter
	;

parameter: IDENTIFIER COLON type

type: INTEGER {$$ = INT_TYPE;} | REAL {$$ = REAL_TYPE;} | CHARACTER {$$ = CHAR_TYPE;}

body: BEGIN_ statements END SEMICOLON {$$ = $2;}
	| error SEMICOLON {$$ = MISMATCH;}

statements: statement | statements statement

statement: expression SEMICOLON
         | WHEN condition COMMA expression COLON expression SEMICOLON {$$ = checkWhen($4, $6);}
         | SWITCH expressions IS cases OTHERS ARROW statements ENDSWITCH SEMICOLON {$$ = checkSwitch($2, $4, $7);}
         | IF condition THEN statement elsif_clauses ELSE statement ENDIF SEMICOLON {$$ = checkIfElse($4, $5, $7);}
         | FOLD direction operator list_choice ENDFOLD SEMICOLON {$$ = checkFold($4);}	 
	;

elsif_clauses: /* empty */ {$$ = NONE;} | ELSIF condition THEN statement elsif_clauses {$$ = $4;}

cases: cases case {$$ = checkCases($1, $2);} |
       /* empty */ {$$ = NONE;}

case: CASE INT_LITERAL ARROW statement {$$ = $4;}
	| error SEMICOLON {$$ = MISMATCH;}
	;

direction: LEFT | RIGHT

operator: ADDOP | MULOP

list_choice: list | IDENTIFIER

condition: expression RELOP expression {$$ = checkRelational($1, $3);}
	 | condition logical_operator condition
         | LPAREN condition RPAREN 
         | NOTOP condition

logical_operator: 
	ANDOP | OROP

expression: term 
	| expression ADDOP term {$$ = checkArithmetic($1, $3);}

term: factor 
	| term MULOP factor {$$ = checkArithmetic($1, $3);}
	| term MODOP factor {$$ = checkModulus($1, $3);}

factor: base 
	| NEGOP factor {$$ = checkNegation($2);}

base: primary 
	| base EXPOP primary {$$ = checkExponent($1, $3);}

primary: INT_LITERAL 
       | REAL_LITERAL 
       | CHAR_LITERAL
       | HEX_LITERAL 
       | IDENTIFIER {$$ = find(scalars, $1, "Scalar");}
       | IDENTIFIER list {$$ = checkSubList($2); find(lists, $1, "List");}
       | LPAREN expression RPAREN {$$ = $2;}
	;

	

%%

Types find(Symbols<Types>& table, CharPtr identifier, string tableName) {
	Types type;
	if (!table.find(identifier, type)) {
		appendError(UNDECLARED, tableName + " " + identifier);
		return MISMATCH;
	}
	return type;
}

void yyerror(const char* message) {
	appendError(SYNTAX, message);
}

int main(int argc, char *argv[]) {
	firstLine();
	yyparse();
	lastLine();
	return 0;
} 
