#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "syntax.h"
#include "textstream.h"

using namespace std;

Syntax::Syntax(string fileName) {
    this->file   = new ifstream(fileName.c_str(), ios_base::in);
    this->stream = new TextStream(file);

    this->index = 0;

    this->delimiter = "::=";

    makeSyntax();
    
    printSyntaxValues();
}

/*
 * PRIVATE
 */

void Syntax::makeSyntax() {
    while (this->file->good()) {
	string leftValue = makeLeftValue();

	if (convertToInteger(leftValue) > 0)
	    makeWithOneRightValue(leftValue);

	if (convertToInteger(leftValue) < 0)
	    makeWithTwoRightValues(leftValue);
    }

}

void Syntax::makeWithOneRightValue(string leftValue) {
    this->syntax[this->index][0] = convertToInteger(leftValue);
    this->syntax[this->index][1] = convertToInteger(this->stream->getNextEntity());
    this->syntax[this->index][2] = NULL;
    this->index++;
}


void Syntax::makeWithTwoRightValues(string leftValue) {
    string firstValue, value;
    while (this->file->good() && !isNumber(value)) {
	value = this->stream->getNextEntity();
	firstValue += value;
    }
    this->syntax[this->index][0] = convertToInteger(leftValue);
    this->syntax[this->index][1] = convertToInteger(firstValue);
    this->syntax[this->index][2] = convertToInteger(this->stream->getNextEntity());
    this->index++;
}

string Syntax::makeLeftValue() {
    string value, leftValue;
    
    while (value != this->delimiter  && this->file->good()) {
	value = this->stream->getNextEntity();
	if (value != this->delimiter)
	    leftValue += value;
    }

    return leftValue;
}

bool Syntax::isNumber(string value) {
    if (atoi(value.c_str()))
	return true;
    return false;
}

int Syntax::convertToInteger(string value) {
    if (atoi(value.c_str()))
	return atoi(value.c_str());
    return NULL;
}

/*
 * PUBLIC
 */

void Syntax::printSyntaxValues() {
    for (int i = 0; i < this->index; i++)
	cout << this->syntax[i][0] 
	     << " ::= " 
	     << this->syntax[i][1] 
	     << " " 
	     << this->syntax[i][2] 
	     << endl;
}

int Syntax::getSize() {
    return this->index;
}

int Syntax::getTerminal(int index) {
    return this->syntax[index][2];
}

int Syntax::getAugment(int index) {
    return this->syntax[index][1];
}

int Syntax::getLeftValue(int index) {
    return this->syntax[index][0];
}
