/* CLASS POSITION
 *
 * This class is used to save information on there
 * STRING is found in file excluding STRING IT SELF
 */

#ifndef SMALL_C_LIKE_POSITION
#define SMALL_C_LIKE_POSITION

#include <string>

using namespace std;

class Position {
 private:
  string fileName;
  int line;
  int col;

 public:
  Position(string, int, int);

  string getFilename();

  int getLine();
  int getCol();
};

#endif
