#include <iostream>
#include <map>

#include "matrix.h"
#include "innerLang.h"

using namespace std;

Matrix::Matrix(InnerLang * lang) {
    this->lang = lang;

    this->marker = &defaultMarker;

    buildColumns();

    printColumnValues();
}

/*
 * PRIVATE
 */

void Matrix::buildColumns() {
    string * innerValues = this->lang->getAllValues();
    
    this->column.insert(pair<string, int>(*(this->marker), 0));

    for (int i = 0; i < this->lang->getSize(); i++) {
	this->column.insert(pair<string, int>(innerValues[i], i+1));
    }
    
    this->row.insert(pair<string, int>(*(this->marker), 0));

    allocateMatrixMemory();
    
}

void Matrix::buildRows() {

}

void Matrix::allocateMatrixMemory() {
    int columnSize = this->column.size();

    this->matrix = new int * [columnSize];

    for (int i = 0; i < columnSize; i++) {
	int rowSize = this->row.size();
	this->matrix[i] = new int[rowSize];
    }
}

void Matrix::fillMatrixValues() {

}

/*
 * PUBLIC
 */

void Matrix::printColumnValues() {
    for (this->it = this->column.begin(); this->it != this->column.end(); this->it++)
	cout << this->it->second << ". " << this->it->first << endl;
}

int Matrix::returnActionNumber(string row, string column) {
    int rowNumber;
    int colNumber;

    this->it = this->row.find(row);
    rowNumber = this->it->second;

    this->it = this->column.find(column);
    colNumber = this->it->second;

    return this->matrix[rowNumber][colNumber];
}
