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
  IdTableMap::iterator found = this -> idTable.find(name);
  if (found == this -> idTable.end())
    throw SemanticError("Token " + name + " is not declared.");

  switch (found -> second.sema) {
  case semanticClass_Variable:
    cout << "found " << found -> first << " value " << found -> second.ret << " == " << ret << endl;
    if (found -> second.ret != ret)
      throw SemanticError("Vriable " + name + " value does not match.");
    cout << "look at me" << endl;
    break;

  case semanticClass_Structur:
    break;

  case semanticClass_Function:
    break;
  }

  return true;
}

/*
 * Registration
 */
void IdTable::registrateContinousStart(string name) {
  IdTableMap::iterator found = this -> idTable.find(name);

  if (found != this -> idTable.end())
    throw SemanticError("Already declared " + name + ".");
  
  this -> seqRegStack.push(found -> second.sema);
}

void IdTable::registrate(string name, int sema, int ret) {
  IdTableValue newId;
  newId.sema = sema;
  newId.ret  = ret;

  if (sema == SEMA_FNCT || sema == SEMA_STRC)
    newId.list = new Params;

  if (this -> idTable.insert(pair<string, IdTableValue>(name, newId)).second == false)
    throw SemanticError("TODO: throw some rocks");

}

void IdTable::registrateContinousEnd() {
  this -> seqRegStack.pop();
}

ostream& operator<<(ostream& output, IdTable &table) {
  for (
       IdTableMap::iterator it = table.idTable.begin();
       it != table.idTable.end();
       it++
       )
    {
      output.width(4);

      output << it -> first
             << " "
             << it -> second.sema
             << " "
             << it -> second.ret
             << endl;
    }

  return output;
}
