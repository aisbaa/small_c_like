#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdlib.h>

#include "semantic.h"
#include "token.h"
#include "textstream.h"

using namespace std;

Semantic::Semantic(string fileName) {
    this->file   = new ifstream(fileName.c_str(), ios_base::in);
    this->stream = new TextStream(file);

    parse();
}

void Semantic::parse() {
    try {
	while (this->file->good()) {
	    Block block = getBlock();
	    SemanticRule *semanticRule = makeSemanticRule(block);
	    this->semanticRuleMap.insert( pair<int,SemanticRule *> (stringToInt(block.firstLine[0]), semanticRule) );
	}
    } catch (int err) {
	if (err != STREAM_IS_NOT_GOOD_FOR_READING) throw ;
    }
}

SemanticRule *Semantic::makeSemanticRule(Block block) {
    SemanticRule *semanticRule = new SemanticRule;
    vector<OUTP> outputs;

    semanticRule->action          = stringToInt(block.firstLine[1]);
    semanticRule->stackSize       = stringToInt(block.firstLine[2]);
    semanticRule->typeCheckValues = makeTypeCheckValues(block.firstLine);
    semanticRule->tokenName       = block.thirdLine[0];
    semanticRule->innerLangValue  = stringToInt(block.thirdLine[1]);
    semanticRule->semanticValue   = stringToInt(block.thirdLine[2]);

    semanticRule->outputs = block.secondLine;

    return semanticRule;
}

vector<int> Semantic::makeTypeCheckValues(vector<string> line) {
    vector<string>::iterator it;
    vector<int> typeCheckValues;

    for (it = line.begin()+2; it < line.end(); it++) {
	typeCheckValues.push_back(stringToInt(*it));
    }

    return typeCheckValues;
}

Block Semantic::getBlock() {
    Block block;
    
    block.firstLine  = getLineColumns();
    block.secondLine = getLineColumns();
    block.thirdLine  = getLineColumns();
   
    return block;
}

vector<string> Semantic::getLineColumns() {
    string line = this->stream->getWholeLine();
    string value;
    int pos = 0;
    vector<string> columns;

    while (line[pos] != '\0') {
	value = "";

	while (line[pos] != ' ' && line[pos] != '\0') {
	    value += line[pos];
	    pos++;
	}

	pos++;
	columns.push_back(value);
    }

    return columns;
}

int Semantic::stringToInt(string value) {
    return atoi(value.c_str());
}

/*
 * Public
 */

const SemanticRule * Semantic::getSemanticRule(int number) {
    map<int, SemanticRule *>::iterator it;

    it = this->semanticRuleMap.find(number);

    if (it != this->semanticRuleMap.end())
	return (*it).second;

    return NULL;
}

