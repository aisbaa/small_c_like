/**
 * CLASS POSITION
 *
 * This class used for saveing information on there
 * STRING is found in file excluding STRING IT SELF
 */

#ifndef SMALL_C_LIKE_POSITION
#define SMALL_C_LIKE_POSITION

#include <string>
#include <iostream>

using namespace std;

class Position {
 private:
  string * filename;
  int line;
  int col;

 public:
  Position(string *, int, int);

  const string * getFilename();

  int getLine();
  int getCol();

  friend ostream& operator<<(ostream& stream, Position &pos);

};

#endif
