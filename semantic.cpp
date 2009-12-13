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
    const SemanticRule *semantic = getSemanticRule(-10);
    if (semantic) {
	//cout << semantic->action << endl;
	//OUTP * ou = semantic->output;
	//cout << ou->fromStack << endl;
    }
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
    //semanticRule->output = &outputs[0];
    semanticRule->outputs = outputs;

    return semanticRule;
}

/* 
 * Parser
 */

vector<OUTP> Semantic::makeOutp(vector<string> line) {
    vector<OUTP> outputs;
    OUTP outp;
    vector<string>::iterator it;
    int outputsSize;

    for (it = line.begin(); it < line.end(); it++) {

	if (*it != "$") {
	    outp.stuff = &(*it);
	    outp.fromStack = -1;
	    outputs.push_back(outp);
	}
	else {
	    outp.stuff = NULL;
	    it++;
	    outp.fromStack = stringToInt(*it);
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
    
    for ( it=this->semanticRuleMap.begin() ; it != this->semanticRuleMap.end(); it++ )
	cout << (*it).first << endl;
    
    return NULL;
}

