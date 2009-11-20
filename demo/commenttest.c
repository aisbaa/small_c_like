/*-+*!@#$%^&**()_-\|*/
/* comment above would be returned
 * by text streamas sigle entity
 * 
 * and should be handled by scanner
 */
#include <iostream>

using namespace std;

int main() {
  int /* this */comment_style_one/* should be alowed */;
  /*
   */
  /**//* any char between //
       */
  /**///
  int
    comment_minus_five = 123,// this one to /* */ /* */ /* */  these should be passed until newline found
    comment_style_two =/*_*//*|.|*/-// <- these multi line comments
    12,// handeled by scanner
    /*
     odd multy line comment
    */comment_multi_line =+/*
                            */ 456 //
    ;

  cout
    << comment_style_two
    << endl
    << comment_minus_five++
    << endl
    << comment_multi_line
    << endl; 

  return 0/*-+*/; /* dont know why anyone should write something like this, but ...*/
}
