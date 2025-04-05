// CMSC 430 Compiler Theory and Design
// Project 4 Skeleton
// UMGC CITE
// Summer 2023

// This file contains the bodies of the type checking functions

#include <string>
#include <vector>
#include <limits>

using namespace std;

#include "types.h"
#include "listing.h"

void checkAssignment(Types lValue, Types rValue, string message) {
	if (lValue != MISMATCH && rValue != MISMATCH && lValue != rValue)
		appendError(GENERAL_SEMANTIC, "Type Mismatch on " + message);
}

Types checkWhen(Types true_, Types false_) {
	if (true_ == MISMATCH || false_ == MISMATCH)
		return MISMATCH;
	if (true_ != false_)
		appendError(GENERAL_SEMANTIC, "When Types Mismatch ");
	return true_;
}

Types checkSwitch(Types case_, Types when, Types other) {
	if (case_ != INT_TYPE)
		appendError(GENERAL_SEMANTIC, "Switch Expression Not Integer");
	return checkCases(when, other);
}

Types checkCases(Types left, Types right) {
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == NONE || left == right)
		return right;
	appendError(GENERAL_SEMANTIC, "Case Types Mismatch");
	return MISMATCH;
}

Types checkArithmetic(Types left, Types right) {
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == INT_TYPE && right == INT_TYPE)
		return INT_TYPE;
	if (left == REAL_TYPE || right == REAL_TYPE)
		return REAL_TYPE;
	appendError(GENERAL_SEMANTIC, "Integer Type Required");
	return MISMATCH;
}

Types checkNegation(Types unary){
	if (unary == MISMATCH)
		return MISMATCH;
	if (unary == REAL_TYPE)
		return REAL_TYPE;
	if (unary == INT_TYPE)
		return INT_TYPE;
	if (unary != REAL_TYPE && unary != INT_TYPE)
		appendError(GENERAL_SEMANTIC, "Arithmetic Operator Requires Numeric Types");
		return MISMATCH;
}

Types checkExponent(Types left, Types right){
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == INT_TYPE && right == INT_TYPE)
		return INT_TYPE;
	if (left == REAL_TYPE || right == REAL_TYPE)
		return REAL_TYPE;
	if (left != REAL_TYPE || left != INT_TYPE);
		appendError(GENERAL_SEMANTIC, "Arithmetic Operator Requires Numeric Types");
		return MISMATCH;
	if (right != REAL_TYPE || right != INT_TYPE);
		appendError(GENERAL_SEMANTIC, "Arithmetic Operator Requires Numeric Types");
		return MISMATCH;
}

Types checkRelational(Types left, Types right){
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == CHAR_TYPE && right == CHAR_TYPE)
		return CHAR_TYPE;
	if (left == CHAR_TYPE && right != left)
		appendError(GENERAL_SEMANTIC, "Character Literals Cannot be Compared to Numeric Expressions");
		return MISMATCH;
	if (right == CHAR_TYPE && left != right)
		appendError(GENERAL_SEMANTIC, "Character Literals Cannot be Compared to Numeric Expressions");
		return MISMATCH;
}

Types checkModulus(Types left, Types right){
	if (left != INT_TYPE || right != INT_TYPE)
		appendError(GENERAL_SEMANTIC, "Remainder Operator Requires Integer Operands");
		return MISMATCH;
	if (left == INT_TYPE && right == INT_TYPE)
		return INT_TYPE;
}

Types checkList(Types left, Types right){
	if (right == left)
		return right;
	if (left == NONE || left == right)
		return right;
	if (right != left)
		appendError(GENERAL_SEMANTIC, "List Element Types Do Not Match");
		return MISMATCH;
}

Types checkListType(Types left, Types right){
	if (left == NONE || left == right)
		return right;
	if (left != right)
		appendError(GENERAL_SEMANTIC, "List Type Does Not Match Element Types");
		return MISMATCH;
}

Types checkSubList(Types list){
	if (list != INT_TYPE)
		appendError(GENERAL_SEMANTIC, "List Subscript Must Be Integer");
		return MISMATCH;
	if (list == INT_TYPE)
		return list;
}

Types checkIfElse(Types left, Types middle, Types right){
	if (middle == NONE)
		return right;
	if (left != middle || left != right || middle != right)
		appendError(GENERAL_SEMANTIC, "If-Elsif-Else Type Mismatch");
		return MISMATCH;
}

Types checkFold(Types elements){
	if (elements != INT_TYPE)
		appendError(GENERAL_SEMANTIC, "Fold Requires A Numeric List");
		return MISMATCH;
	if (elements == INT_TYPE)
		return elements;
}
