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
    /*
    for (int i = 0; i < this->index; i++) {
	cout << this->syntax[i][0] << " ::= " << this->syntax[i][1] << " " << this->syntax[i][2] << endl;
    }
    */
}

/*
 * PRIVATE
 */

void Syntax::makeSyntax() {
    string leftValue, value;

    while (this->file->good()) {

	while (value != "::="  && this->file->good()) {
	    value = this->stream->getNextEntity();
	    if (value != "::=")
		leftValue += value;
	}

	if (convertToInteger(leftValue) > 0) {
	    this->syntax[this->index][0] = leftValue;
	    this->syntax[this->index][1] = this->stream->getNextEntity();
	    this->syntax[this->index][2] = "NULL";
	    this->index++;
	}

	if (convertToInteger(leftValue) < 0) {
	    string firstValue;
	    while (this->file->good() && !isNumber(value)) {
		value = this->stream->getNextEntity();
		firstValue += value;
	    }
	    this->syntax[this->index][0] = leftValue;
	    this->syntax[this->index][1] = firstValue;
	    this->syntax[this->index][2] = this->stream->getNextEntity();
	    this->index++;
	}
	leftValue = "";
	value = "";
    }

}

string Syntax::makeLeftValue() {
    string value, leftValue;
    
    value = this->stream->getNextEntity();
    while (value != this->delimiter && this->file->good()) {
	leftValue += value;
	value = this->stream->getNextEntity();
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

int Syntax::getSize() {
    return this->index;
}

string Syntax::getTerminal(int index) {
    string number = this->syntax[index][2];
    if (isNumber(number))
	return this->syntax[index][2];
    return "NULL";
}

string Syntax::getWord(int index) {
    return this->syntax[index][1];
}

string Syntax::getLeftValue(int index) {
    return this->syntax[index][0];
}
