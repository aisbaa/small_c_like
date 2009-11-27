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
    getNextState(3, 1, NULL);
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

char Syntax::makeAction() {
    char action = this->stream->getNextEntity()[0];
    return action;
}

void Syntax::fillMatrix() {
    MatrixValues newRecord;

    newRecord.newState = makeNumber();
    newRecord.state    = makeNumber();
    newRecord.term     = makeNumber();
    newRecord.action   = makeAction();
    
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

MatrixValues Syntax::findMatrix(int state, int term) {
    for (this->it = this->matrix.begin(); this->it < this->matrix.end(); this->it++) {
	MatrixValues matrix = *(this->it);
	if (matrix.state == state && matrix.term == term)
	    return matrix;
    }
}

int Syntax::getActionNumber(char action) {
    if (action == '-')
	return action_pop;
    if (action == '+')
	return action_push;
    if (action == '~')
	return action_reduction;
    return NULL;
}

/*
 * PUBLIC
 */

void Syntax::printMatrix() {
    for (this->it = this->matrix.begin(); this->it < this->matrix.end(); this->it++) {
	MatrixValues a = *(this->it);
	cout << a.newState << " ::= " 
	     << a.state    << " "
	     << a.term     << " "
	     << a.action   << endl;
    }
}

int Syntax::getNewState(int prev_state, int token) {
    MatrixValues matrix = findMatrix(prev_state, token);
    return matrix.state;
}

int Syntax::getNextState(int prev_state, int token, int * new_state) {
    MatrixValues matrix;
    int action;

    matrix = findMatrix(prev_state, token);
    action = getActionNumber(matrix.action);
    
    new_state = &matrix.state;

    return action;
}
