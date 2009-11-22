#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "rewritertool.h"
#include "textstream.h"

using namespace std;

RewriterTool::RewriterTool(string fileName) {
    this->file   = new ifstream(fileName.c_str(), ios_base::in);
    this->stream = new TextStream(file);
    
    this->delimiter = &defaultDelimiter;

    this->outFile = "test";

    this->index = -1;

    parseAll();

    writeToFile();
}

/*
 * PRIVATE
 */

void RewriterTool::parseAll() {
    string value;

    while (this->file->good()) {
	char c = this->file->get();
	
	if (isCharNumber(c)) {
	    while (!isWhitespace(c) && this->file->good() && c != '\n') {
		this->buffer += c;
		c = this->file->get();		
	    }
	    this->buffer += ' ';
	    if (c == '\n')
		this->buffer += '\n';
	}

	else if (c == '\n')
	    this->buffer += '\n';

	else {
	    if (!isWhitespace(c)) {
		while (!isWhitespace(c) && this->file->good() && c != '\n') {
		    value += c;
		    c = this->file->get();		
		}

		if (!isDelimiter(value))
		    valueIsWord(value);		
		else
		    this->buffer += *(this->delimiter);
		
		this->buffer += " ";

		value = "";
		
		if (c == '\n')
		    this->buffer += '\n';
	    }
	}
    }
}

void RewriterTool::valueIsWord(string value) {
    stringstream number;

    if (this->syntaxMap.find(value) == this->syntaxMap.end()) {
	this->syntaxMap.insert(pair<string, int>(value, this->index));	
	number << this->index;
	this->buffer += number.str();
	this->index--;
    }
    else {
	this->it = this->syntaxMap.find(value);
	number << this->it->second;
	this->buffer += number.str();
    }
}

bool RewriterTool::isDelimiter(string value) {
    if (value == *(this->delimiter))
	return true;
    return false;
}

bool RewriterTool::isWhitespace(char value) {
    if (value == ' ')
	return true;
    return false;
}

bool RewriterTool::isCharNumber(char value) {
    if (value >= '0' && value <= '9')
	return true;
    return false;
}

bool RewriterTool::isNumber(string value) {
    if (atoi(value.c_str()))
	return true;
    return false;
}

void RewriterTool::writeToFile() {
    ofstream outFile;

    outFile.open(this->outFile.c_str(), fstream::out);

    outFile << this->buffer;

    outFile.close();
}

int RewriterTool::convertToInteger(string value) {
    if (atoi(value.c_str()))
	return atoi(value.c_str());
    return NULL;
}
