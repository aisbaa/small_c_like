#include <iostream>
#include <map>

#include "matrix.h"
#include "innerLang.h"
#include "syntax.h"

using namespace std;

Matrix::Matrix(InnerLang * lang, Syntax * syntax) {
    this->lang   = lang;
    this->syntax = syntax;

    buildColumns();
    buildRows();
    allocateMatrixMemory(); 
    fillMatrixValues();

    //printColumnValues();
    //printRowValues();
    printMatrix();
    cout << "returnActionNumber(-1, 15) => " << returnActionNumber(-1, 15) << endl;
}

/*
 * PRIVATE
 */

void Matrix::buildColumns() {
    for (int i = 0; i < this->syntax->getSize(); i++)
	this->column.insert(pair<int, int>(this->syntax->getTerminal(i), i));
}

void Matrix::buildRows() {
    for (int i = 0; i < this->syntax->getSize()-1; i++)
	if (this->row.find(this->syntax->getAugment(i)) == this->row.end())
	    this->row.insert(pair<int, int>(this->syntax->getAugment(i), i));    
}

void Matrix::allocateMatrixMemory() {
    int rowSize = this->row.size();

    this->matrix = new int * [rowSize];

    for (int i = 0; i < rowSize; i++)
	this->matrix[i] = new int[this->column.size()];
}

void Matrix::fillMatrixValues() {
    int rowSize = this->row.size();

    for (int i = 0; i < rowSize; i++) {
	if (this->column.find(this->syntax->getLeftValue(i)) == this->column.end()) {
	    this->it = this->column.find(this->syntax->getTerminal(i));
	    this->matrix[i][(int)this->it->second] = this->syntax->getAugment(i);
	}
    }
}

/*
 * PUBLIC
 */

void Matrix::printMatrix() {
    int rowSize = this->row.size();
    int colSize = this->column.size();

    for (int i = 0; i < rowSize; i++) {
	for (int j = 0; j < colSize; j++)
	    cout << this->matrix[i][j] << "    ";
	cout << endl;
    }
}

void Matrix::printColumnValues() {
    for (this->it = this->column.begin(); this->it != this->column.end(); this->it++)
	cout << this->it->second << ". " << this->it->first << endl;
}

void Matrix::printRowValues() {
    for (this->it = this->row.begin(); this->it != this->row.end(); this->it++)
	cout << this->it->second << ". " << this->it->first << endl;
}

int Matrix::returnActionNumber(int row, int column) {
    int rowNumber, colNumber;

    this->it = this->row.find(row);
    rowNumber = this->it->second + 1;

    this->it = this->column.find(column);
    colNumber = this->it->second + 1;

    return this->matrix[rowNumber][colNumber];
}
