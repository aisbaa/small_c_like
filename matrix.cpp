#include <iostream>
#include <map>

#include "matrix.h"
#include "syntax.h"

using namespace std;

Matrix::Matrix(Syntax * syntax) {
    this->syntax = syntax;

    buildColumns();
    buildRows();
    allocateMatrixMemory(); 
    fillMatrixValues();

    this->syntax->printSyntaxValues();

    /*
    cout << "Columns: " << this->column.size() << endl;
    printColumnValues();
    cout << endl;

    cout << "Rows: " << this->row.size() << endl;
    printRowValues();
    cout << endl;

    cout << "Matrix:" << endl;
    printMatrix();
    cout << endl;
    */
    returnActionNumber(-2, 16);
}

/*
 * PRIVATE
 */

void Matrix::buildColumns() {
    for (int i = 0; i < this->syntax->getSize(); i++)
	if (this->column.find(this->syntax->getTerminal(i)) == this->column.end())
	    this->column.insert(pair<int, int>(this->syntax->getTerminal(i), i));
}

void Matrix::buildRows() {
    for (int i = 0; i < this->syntax->getSize(); i++)
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
	int first = this->syntax->getAugment(i);
	int second = this->syntax->getTerminal(i);

	if (first != 0 && second != 0) {
	    this->it = this->row.find(first);
	    
	    this->it = this->row.find(first);
	    int rowNum = this->it->second - 1;

	    this->it = this->column.find(second);
	    int colNum = this->it->second - 1;

	    this->matrix[rowNum][colNum] = this->syntax->getAugment(i);
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
	cout << this->it->first << ". " << this->it->second << endl;
}

void Matrix::printRowValues() {
    for (this->it = this->row.begin(); this->it != this->row.end(); this->it++)
	cout << this->it->first << ". " << this->it->second << endl;
}

int Matrix::returnActionNumber(int row, int column) {
    int rowNumber, colNumber;

    this->it = this->row.find(row);
    rowNumber = this->it->second;

    this->it = this->column.find(column);
    colNumber = this->it->second;

    cout << "(" << row << ", " << column << ") "
	 << rowNumber << " : " << colNumber 
	 << " => " << this->matrix[rowNumber][colNumber] 
	 << endl;

    return this->matrix[rowNumber][colNumber];
}
