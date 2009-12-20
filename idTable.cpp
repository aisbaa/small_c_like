#include "idTable.h"

int IdTable::getNextFunctParamSemantic() {
  Params * list = this -> checkStack.top().checking -> list;
  Params::iterator it;
  int step = 0;
  for (
       it =  list -> begin();
       it != list -> end();
       it++
       )
      if (step == this -> checkStack.top().step)
        break;
      else
        step++;

  this -> checkStack.top().step++;
  return it -> second;
}

/*
 * Huge method
 */
bool IdTable::checkSemanticValue(string name, int ret) {
  if (!this -> checkStack.empty()) {

    semaCheck * check = &(this -> checkStack.top());

    switch (check -> checking -> sema) {
    case SEMA_STRC:
      {
        Params::iterator foundStructAttr = check -> checking -> list -> find(name);

        if (foundStructAttr == check -> checking -> list -> end())
          throw SemanticError("struct does not have attribute called " + name + ".");
        
        if (foundStructAttr -> second != ret)
          throw SemanticError("Struct attribute " + name + " value does not match.");
        
        this -> checkStack.pop();

      } break;

    case SEMA_FNCT:
      {
        IdTableMap::iterator found = this -> idTable.find(name);
        if (found == this -> idTable.end())
          throw SemanticError("Token " + name + " is not declared.");

        if (found -> second.ret != ret)
          throw SemanticError("Vriable " + name + " value does not match.");

      } break;

    }

  } else {
    IdTableMap::iterator found = this -> idTable.find(name);
    if (found == this -> idTable.end())
      throw SemanticError("Token " + name + " is not declared.");

    switch (found -> second.sema) {
    case SEMA_VAR:
      if (found -> second.ret != ret || found -> second.list != NULL)
        throw SemanticError("Vriable " + name + " value does not match.");
      break;

    }
      
  }

}

/*
 * Registration
 */
void IdTable::registrateContinousStart(string name) {
  IdTableMap::iterator found = this -> idTable.find(name);

  if (found != this -> idTable.end())
    throw "TODO: some rocks, already declared.";
  
  this -> seqRegStack.push(found -> second.sema);
}

void IdTable::registrate(string name, int sema, int ret) {
  IdTableValue newId;
  newId.sema = sema;
  newId.ret  = ret;

  if (sema == SEMA_FNCT || sema == SEMA_STRC)
    newId.list = new Params;

  if (this -> idTable.insert(pair<string, IdTableValue>(name, newId)).second == false)
    throw "TODO: some rocks";
}

void IdTable::registrateContinousEnd() {
  this -> seqRegStack.pop();
}
