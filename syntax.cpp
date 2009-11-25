#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>

#include "syntax.h"
#include "textstream.h"

using namespace std;

Syntax::Syntax(string fileName) {
    this->file   = new ifstream(fileName.c_str(), ios_base::in);
    this->stream = new TextStream(file);

    try {
	parseFile();  
    } catch (int) {
	cout << "nothing to read or else" << endl;
    } catch (const char *str) {
	cout << "cought exceptio::" << str << endl;
    } catch (...) {
	cout << "got excpetion" << endl;
    }

    printMatrix();
    getActionNumber(0, 1);
}

/*
 * PRIVATE
 */

void Syntax::parseFile() {
    while (this->file->good()) {
	fillMatrix();
    }
}

int Syntax::makeNumber() {
    string number, value;

    while (this->file->good() && !isNumber(value) && value != "0") {
	value = this->stream->getNextEntity();
	number += value;
    }

    return convertToInteger(number);
}

void Syntax::fillMatrix() {
    MatrixValues newRecord;

    newRecord.newState = makeNumber();
    newRecord.state    = makeNumber();
    newRecord.term     = makeNumber();
    
    this->matrix.push_back(newRecord);
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

void Syntax::printMatrix() {
    for (this->it = matrix.begin(); this->it < matrix.end(); this->it++) {
	MatrixValues a = *(this->it);
	cout << a.newState
	     << " ::= "
	     << a.state
	     << " "
	     << a.term
	     << endl;
    }
}

int Syntax::getActionNumber(int state, int term) {
    for (this->it = matrix.begin(); this->it < matrix.end(); this->it++) {
	MatrixValues a = *(this->it);
	if (a.state == state && a.term == term) {
	    cout << "getActionNumber("
		 << state
		 << ", "
		 << term
		 << ") => "
		 << a.newState
		 << endl;
	    return a.newState;
	}
    }
    return NULL;
}

int Syntax::getNextState(int prev_state, int token, int * new_state) {
    if (prev_state < 0)
	return action_reduction;
    if (prev_state > 0)
	return action_push;
    return action_pop;
}
