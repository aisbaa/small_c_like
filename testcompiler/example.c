/* eilute zemiau demonstruoja laisvai aprasoma komentara */
2 laisvai aprasomas komentaras 0
/* */
struct coordinates {
  int x, y, z;
};
 
int add(int a, int b) {
  return (a +b);
};
 
int grt(int a, int b) {
  if (a > b)
    return true;
  else
    return false;
};

int main() {
  // sveikas neigiamas skaicius
  int sveikas = -5;
  char raide = 'a';
 
  int aibe [5] = {1, 2, 3, 4, 5};
  char raides[5] = "abcd";
  char zodis[6] = "Labas";
 
  zodis[4+0] = 'a';
 
  sveikas = sveikas +5 *10 /2 -6;
 
  while (sveikas > 5)
    sveikas -= 5;
 
  printf("\n"+ sveikas);
 
  /*
    if else demonstracija
   */

  if (sveikas == 5) {
    printf("puikumelis sveikas == 5\n");
  } else if (sveikas > 3) {
    printf("puikumelis sveikas > 3\n");
  } else if (sveikas < 4) {
    printf("puikumelis sveikas < 4\n");
  } else if (sveikas <= 3) {
    printf("puikumelis sveikas <= 3\n");
  } else if (sveikas >= 1) {
    printf("puikumelis sveikas >= 1\n");
  } else {
    printf("oj\n");
  }
 
  printf("zodis = " +zodis +"\ngalite pakeisti zodzio reiksme: ");
  zodis = scanf(5);
  printf(zodis +"\n" +raides);
 
  return 0;
}
