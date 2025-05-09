// CMSC 430 Compiler Theory and Design
// Project 4 Skeleton
// UMGC CITE
// Summer 2023

// This file contains type definitions and the function
// prototypes for the type checking functions

typedef char* CharPtr;

enum Types {MISMATCH, INT_TYPE, CHAR_TYPE, REAL_TYPE, NONE};

void checkAssignment(Types lValue, Types rValue, string message);
Types checkWhen(Types true_, Types false_);
Types checkSwitch(Types case_, Types when, Types other);
Types checkCases(Types left, Types right);
Types checkArithmetic(Types left, Types right);
Types checkRelational(Types left, Types right);
Types checkExponent(Types left, Types right);
Types checkNegation(Types unary);
Types checkModulus(Types left, Types right);
Types checkList(Types left, Types right);
Types checkListType(Types left, Types right);
Types checkSubList(Types list);
Types checkIfElse(Types left, Types middle, Types right);
Types checkFold(Types elements);