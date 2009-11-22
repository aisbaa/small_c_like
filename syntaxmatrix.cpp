#include <iostream>
#include <fstream>
#include <map>

#include "syntaxmatrix.h"
#include "textstream.h"
#include "innerLang.h"

using namespace std;

SyntaxMatrix::SyntaxMatrix(string fileName, InnerLang * lang) {
    this->file   = new ifstream(fileName.c_str(), ios_base::in);
    this->stream = new TextStream(file);
    this->lang   = lang;

    this->delimeter = &defaultDelimeter;
    this->endOfRule = &defaultEndOfRule;

    parseAll();
    buildMatrix();
    /*
    cout << "Stulpeliai: " << endl;
    printTerminals();
    
    cout << endl << "Desiniosios taisykles: " << endl;
    printRows();
    
    cout << endl << "Matrica:" << endl;

    printMatrix();
    */
}

/*
 * PRIVATE
 */

void SyntaxMatrix::buildMatrix() {
    int columnSize = this->TerminalMap.size();
    int rowSize = this->RowMap.size();

    this->matrix = new int * [rowSize];
    for (int i = 0; i < rowSize; i++)
	this->matrix[i] = new int[columnSize];

    for (int i = 0; i < rowSize; i++) {
	for (int j = 0; j < columnSize; j++)
	    this->matrix[i][j] = NULL;
    }
}

string SyntaxMatrix::buildRule() {
    string rule = "<";
    string value;
    
    while (value != ">") {
	value = this->stream->getNextEntity();
	rule += value;
    }

    return rule;
}

string SyntaxMatrix::buildLeft() {
    string leftSide, value;

    while (value != *(this->delimeter) && this->file->good()) {
	value = this->stream->getNextEntity();
	if (value != *(this->delimeter))
	    leftSide += value;
    }

    return leftSide;
}

bool SyntaxMatrix::isDefinedTerminal(string value) {
    this->it = this->TerminalMap.find(value);

    if (this->it == this->TerminalMap.end())
	return true;

    return false;
}

bool SyntaxMatrix::isInnerLangValue(string value) {
    if (this->lang->getInnerLangValue(value) != 44)
	return true;
    return false;
}

void SyntaxMatrix::addTerminal(string value) {
    int index = this->TerminalMap.size();

    if (isDefinedTerminal(value))
	this->TerminalMap.insert(pair<string, int>(value, index++));
}

void SyntaxMatrix::parseAll() {
    int counter = 0;

    while (this->file->good()) {
	string rightValues = "";
	string value = "";

	buildLeft();

	while (value != *(this->endOfRule)) {
	    value = this->stream->getNextEntity();
	    if (value == "<")
		rightValues += buildRule();
	    else {
		if (isInnerLangValue(value)) {
		    addTerminal(value);
		    rightValues += value;
		    this->RowMap.insert(pair<string, int>(rightValues, counter));
		    counter++;
		}
	    }
	}
    }
}

void SyntaxMatrix::printTerminals() {
    for (this->it = this->TerminalMap.begin() ; this->it != this->TerminalMap.end(); this->it++)
	cout << this->it->second << ". " << this->it->first << endl;
}

void SyntaxMatrix::printRows() {
    for (this->it = this->RowMap.begin() ; this->it != this->RowMap.end(); this->it++)
	cout << this->it->first << endl;
}

void SyntaxMatrix::printMatrix() {
    int columnSize = this->TerminalMap.size();
    int rowSize = this->RowMap.size();

    for (int i = 0; i < rowSize; i++) {
	for (int j = 0; j < columnSize; j++)
	    cout << this->matrix[i][j] << " ";
	cout << endl;
    }    
}

/*
 * PUBLIC
 */

int SyntaxMatrix::getNumberByRow(string value) {
    this->it = this->RowMap.find(value);

    if (this->it == this->RowMap.end())
	return NULL;   

    return this->it->second;
}

int SyntaxMatrix::getNumberByColumn(string value) {
    this->it = this->TerminalMap.find(value);

    if (this->it == this->TerminalMap.end())
	return NULL;

    return this->it->second;
}

int ** SyntaxMatrix::getMatrix() {
    return this->matrix;
}

int SyntaxMatrix::getMatrixValue(int row, int column) {
    return this->matrix[row][column];
}
