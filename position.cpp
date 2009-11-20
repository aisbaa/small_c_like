/*
#include <string>
*/
#include "position.h"

Position::Position(string *filename, int line, int col) {
  this -> filename = filename;
  this -> line = line;
  this -> col = col;
}

const string * Position::getFilename() {
  return this -> filename;
}

int Position::getLine() {
  return this -> line;
}

int Position::getCol() {
  return this -> col;
}

ostream& operator<<(ostream& stream, Position &pos) {
  return stream << pos.getLine()
                << ":"
                << pos.getCol()
                << " "
    //                << *(pos.getFilename())
    ;
}
