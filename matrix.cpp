#include <iostream>
#include <map>

#include "matrix.h"
#include "innerLang.h"
#include "syntax.h"

using namespace std;

Matrix::Matrix(InnerLang * lang, Syntax * syntax) {
    this->lang   = lang;
    this->syntax = syntax;

    this->marker = &defaultMarker;

    buildColumns();
    buildRows();
    allocateMatrixMemory(); 
    fillMatrixValues();

    //printColumnValues();
    //printRowValues();
    cout << "returnActionValue(\"3\", \"1\") => " << returnActionValue("-1", "15") << endl;
}

/*
 * PRIVATE
 */

void Matrix::buildColumns() {
    for (int i = 0; i < this->syntax->getSize(); i++) {
	string terminal = this->syntax->getTerminal(i);
	if (terminal != "NULL")
	    this->column.insert(pair<string, int>(terminal, i));
    }
}

void Matrix::buildRows() {
    /*
    for (int i = 0; i < 7; i++) {
	if (this->row.find(this->demoSyntax[i][1]) == this->row.end())
	    this->row.insert(pair<string, int>(this->demoSyntax[i][1], i));
    }
    */
    for (int i = 0; i < this->syntax->getSize()-1; i++) {
	string value = this->syntax->getWord(i);
	if (this->row.find(value) == this->row.end())
	    this->row.insert(pair<string, int>(value, i));
    }
    
}

void Matrix::allocateMatrixMemory() {
    int rowSize = this->row.size();
    this->matrix = new string * [rowSize];

    for (int i = 0; i < rowSize; i++) {
	int columnSize = this->column.size();

	this->matrix[i] = new string[columnSize];
    }
}

void Matrix::fillMatrixValues() {
    int rowSize = this->row.size();

    for (int i = 0; i < rowSize; i++) {
	if (this->column.find(this->syntax->getLeftValue(i)) == this->column.end()) {
	    this->it = this->column.find(this->syntax->getTerminal(i));
	    if (this->syntax->getTerminal(i) != "NULL")
		this->matrix[i][(int)this->it->second] = this->syntax->getWord(i);
	}
    }

    /*
    for (int i = 0; i < rowSize; i++) {
	if (this->column.find(this->demoSyntax[i][0]) == this->column.end()) {
	    this->it = this->column.find(this->demoSyntax[i][2]);
	    this->matrix[i][(int)this->it->second] = this->demoSyntax[i][0];
	}
    }
    */
}

/*
 * PUBLIC
 */

void Matrix::printColumnValues() {
    for (this->it = this->column.begin(); this->it != this->column.end(); this->it++)
	cout << this->it->second << ". " << this->it->first << endl;
}

void Matrix::printRowValues() {
    for (this->it = this->row.begin(); this->it != this->row.end(); this->it++)
	cout << this->it->second << ". " << this->it->first << endl;
}


int Matrix::returnActionNumber(string row, string column) {
    int rowNumber;
    int colNumber;

    this->it = this->row.find(row);
    rowNumber = this->it->second;

    this->it = this->column.find(column);
    colNumber = this->it->second;
    
    return 1;
    //return this->matrix[rowNumber][colNumber];
}

string Matrix::returnActionValue(string row, string column) {
    int rowNumber, colNumber;

    this->it = this->row.find(row);
    rowNumber = this->it->second;

    this->it = this->column.find(column);
    colNumber = this->it->second;

    return this->matrix[rowNumber][colNumber];
}
