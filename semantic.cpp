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

    /* Testing */
    //SemanticRule *semantic = getSemanticRule(-10);
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
    semanticRule->tokenName       = block.thirdLine[0];
    semanticRule->innerLangValue  = stringToInt(block.thirdLine[1]);
    semanticRule->semanticValue   = stringToInt(block.thirdLine[2]);

    outputs = makeOutp(block.secondLine);

    semanticRule->output = &outputs[0];

    return semanticRule;
}

/* 
 * Parser
 */
vector<OUTP> Semantic::makeOutp(vector<string> line) {
    vector<OUTP> outputs;
    OUTP outp;
    int outputsSize;
    
    for (int i = 0; i < 8; i++) {
	if (line[i] != "$") {
	    outp.stuff = &line[i];
	    outp.fromStack = -1;
	    outputs.push_back(outp);
	}
	else {
	    outp.stuff = NULL;
	    i++;
	    outp.fromStack = stringToInt(line[i]);
	    outputs.push_back(outp);
	}
    }

    outputsSize = outputs.size();

    for (int i = 0; i < outputsSize; i++) {
	if ((i+1) < outputsSize)
	    outputs[i].next = &(outputs[i+1]);
	else
	    outputs[i].next = NULL;
    }

    return outputs;
}

string Semantic::makeValue() {
    string value = this->stream->getNextEntity();
    if (value == "-")
	return value += this->stream->getNextEntity();
    return value;
}

Block Semantic::getBlock() {
    Block block;
    
    block.firstLine  = getLineColumns(6);
    block.secondLine = getLineColumns(8);
    block.thirdLine  = getLineColumns(3);
   
    return block;
}

vector<string> Semantic::getLineColumns(int cols) {
    vector<string> columns;

    for (int i = 0; i < cols; i++)
	columns.push_back(makeValue());

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
    
    for ( it=this->semanticRuleMap.begin() ; it != this->semanticRuleMap.end(); it++ )
	cout << (*it).first << endl;

    return NULL;
}
