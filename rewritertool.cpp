#include <iostream>
#include <fstream>

#include <stdlib.h>

#include "ascii_info.h"

#include <string.h>
#include <map>

using namespace std;

const string dontTouch = "-/+*~|";

typedef map<string, int> reservedValueMap;

int numericValue(reservedValueMap * , string);

int main(int argc, char ** argv) {
  string word;
  reservedValueMap reservedValues;

  while (cin.good()) {
    int c = cin.get();

    if (!isWhiteSpace((char)c))
      word += (char)c;
    else {
      /* have word */

      /* checking if symbol is one of symbols in dontTouch const */
      if (word.length() == 1 && dontTouch.find(word) != string::npos)
          cout << word
               << ' ';
      else /* its not reserved symbol */
        cout << numericValue(&reservedValues, word)
             << ' ';

      word.erase();

      if (c == '\n')
        cout << endl;
    }

  }

  if (argc >= 2) {
    ofstream saveHeaderFile(argv[1], ios_base::out);

    saveHeaderFile << "#ifndef " << argv[1] << endl;
    saveHeaderFile << "#define " << argv[1] << endl;

    for (
         reservedValueMap::iterator it = reservedValues.begin();
         it != reservedValues.end();
         it++
         )
      saveHeaderFile << "#define "
                     << it -> first
                     << " "
                     << it -> second
                     << endl;

    saveHeaderFile << "#endif" << endl;
    saveHeaderFile.close();
  }

  return 0;
}

int numericValue(reservedValueMap * reservedValues, string word) {
  /*
   * firstly if we read decimal number,
   * it must be positive
   */
  if (isDecimalNumber(word.c_str()))
      return atoi(word.c_str());
  
  /* else its not a number */
  reservedValueMap::iterator pos = reservedValues -> find(word);
  if (pos != reservedValues -> end())
    return pos -> second;

  (*reservedValues)[word] = -1 -(reservedValues -> size());

  return (*reservedValues)[word];
}
