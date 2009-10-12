#include "innerLang.h"

using namespace std;

class TESTinnerLang : public InnerLang::InnerLang {
public:
  TESTinnerLang(string fileName) : InnerLang::InnerLang(fileName) {
  };
  
  void runTest() {
    /*
    CPPUNIT_ASSERT( Complex (10, 1) == Complex (10, 1) );
    CPPUNIT_ASSERT( !(Complex (1, 1) == Complex (2, 2)) );
    */
  }
};
