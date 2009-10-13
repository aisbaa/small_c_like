/*
  Nuskaityti viena faila. Sukurti dvipusi sarasa, kurio elementai eilutes. i ji patalpinti 
  zodzius kurie prasideda ir baigiasi raide. Ji surusiuoti pagal antraji zodzio simboli pagal 
  abecele. Rezultata isvesti i atskira faila. 

  Reikalavimai 3 uzduociai:

  1. Pradinius duomenis nuskaityti is vieno ar keliu tekstiniu failu (kaip nurodyta salygoje).
  2. Idanalizuoti faila kaip nurodyta uzduotyje, informacija patalpinti i dinamines duomenu strukturas. Jei nurodyta uzduotyje sukurti kelis strukturu egzempliorius. Pastaba: kad atskirti zodzius tekste (jei taikytina), galima apsibrezti skirtuku aibe, pvz. atskirame faile.
  3. Rezultatines strukturos(-u) turini isvesti i faila(-us).
  4. Ivedant is failo eiluciu poru sarasa, nelygines failo eilutes atitinka pirmuosius poru narius, o lygines - antruosius.
  5. Isvedant i faila sarasu sarasa, sarasus atskirti tuscia eilute.

  Papildomi reikalavimai 4 uzduociai:

  6. Sukurti multifailini projekta. Dinamines duomenu strukturos(-u) apibrezima ir jos operacijas realizuoti atskirame faile (modulyje(-iuose)).
  7. Jei reikia, atlikti papildomas (pvz. rusiavimo, statistikos paskaiciavimo ir pan.) operacijas.
  8. Ivedimo ir isvedimo failu vardai perduodami programai kaip komandines eilutes parametrai (tiek kiek ju reikia programai).
  9. Programa turi buti apsaugota nuo nekorektisku parametru ar nuskaitomu duomenu - turi isvesti informatyvius klaidu pranesimus.

*/

# include <stdio.h>
# include <stdlib.h>
# include "File2StrLine.h"

// pirmo kurso antras semestras, uztrukau visa savaitgali XD

int main(int argc, char *argv[])
{
  FILE    *fp_in = NULL, *fp_out = NULL;
  StrLine *str   = NULL, *scstr  = NULL;

  if ( argc < 3 )
    printf ("nepakanka argumantu, pvc.: <programos pavadinimas> <ivedimo byla> <isvedimo byla>\n");
  else 
  /*  for (arg =1 ; arg < argc; arg++)
    { */
    if ( (fp_in = fopen (argv[1], "r")) == NULL )
      printf ("Bylos %s atidryti nepavyko.\n", argv[1]);
    else
      {
	str = (StrLine *) malloc (sizeof(StrLine));
	str->p = NULL;
	scstr = str; /*laikinai rodys i pirmaji*/
	
	while ( word4mfile(str, fp_in) ) //nuskaitau visus zodzius is failo
	  {
	    str->n    = (StrLine *) malloc (sizeof(StrLine));
	    str->n->p = str;
	    str       = str->n;
	  } /* while */
	
	/*nuskaitymas ir dvipusiu saraso sudarymas baigtas*/
	str->n = NULL;
	
	/*jei paskutine struktura tuscia*/
	if (str->str == NULL)
	  {
	    str = str->p;
	    cleanstrline (str->n);
	    str->n = NULL;
	  }
	
	if ( (fclose (fp_in)) != NULL ) 
	  printf ("Bylos %s uzdaryti nepavyko.\n", argv[1]);
	
	/*atidaromas iseities failas*/
	if ( ( fp_out = fopen (argv[2], "w") ) == NULL)
	  printf ("Bylos %s nepavyko atidaryti perasymui.\n", argv[2]);
	else
	  {
	    /*abipusis burbulas*/
	    bubblestrline (scstr);
	    
	    /*isvedimas*/
	    str = scstr;
	    
	    while ( str != NULL ) /*irasom i faila && isvalo atmini*/
	      {
		fprintf (fp_out, "%s\n", str->str);
		printf ( "%s\n", str->str);
		scstr = str;
		str = str->n;
		cleanstrline (scstr);
	      }
	    
	    if ( (fclose (fp_out)) != 0 )
	      printf ("Bylos %s nepavyko irasyti.\n", argv[2]);

	  } /* failas irasytas */

      } /* duomenys apdoroti*/

  return 0;
}
