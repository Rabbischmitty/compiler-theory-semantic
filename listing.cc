// CMSC 430 Compiler Theory and Design
// Project 1 Skeleton
// UMGC CITE
// Summer 2023

// This file contains the bodies of the functions that produces the 
// compilation listing

#include <cstdio>
#include <string>
#include <queue>

using namespace std;

#include "listing.h"

static int lineNumber;
static string error = "";
static int totalErrors = 0;
int lexicalErrors = 0;
int syntaxErrors = 0;
int semanticErrors = 0;
std::queue<std::string> errorQueue;

static void displayErrors();

void firstLine()
{
	lineNumber = 1;
	printf("\n%4d  ",lineNumber);
}

void nextLine()
{
	displayErrors();
	lineNumber++;
	printf("%4d  ",lineNumber);
}

int lastLine()
{
	printf("\r");
	displayErrors();
	printf("     \n");
	int totalErrors = lexicalErrors + syntaxErrors + semanticErrors;

    if (totalErrors == 0) {

        printf("Compiled Successfully\n\n");

    } else {

        printf("Lexical Errors %d\n", lexicalErrors);

		printf("Syntax Errors %d\n", syntaxErrors);

        printf("Semantic Errors %d\n\n", semanticErrors);

    }

    return totalErrors;

}
    
void appendError(ErrorCategories errorCategory, string message)
{
	string messages[] = { "Lexical Error, Invalid Character ", "",
		"Semantic Error, ", "Semantic Error, Duplicate ",
		"Semantic Error, Undeclared " };

    errorQueue.push(messages[errorCategory] + message);
    totalErrors++;
    if (errorCategory == LEXICAL) lexicalErrors++;
    else if (errorCategory == SYNTAX) syntaxErrors++;
    else if (errorCategory == GENERAL_SEMANTIC) semanticErrors++;
}

void displayErrors()
{
	while (!errorQueue.empty()) {
        printf("%s\n", errorQueue.front().c_str());
        errorQueue.pop();
    }
}
