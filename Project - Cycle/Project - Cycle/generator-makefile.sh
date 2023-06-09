#!/bin/bash

# Jezeli istnieje juz plik makefile, to go skopiuj do makefile-old
if [ -e makefile ] ; then mv makefile makefile-old ; fi 

ls -1 *.cpp | awk '
  BEGIN  {
             printf("kompilator=g++\n");
             printf("standard=-std=c++20\n");
             printf("optymalizacja=-O3\n");
             printf("errors=-pedantic-errors\n\n");
             printf("# debug=-g\n");
             printf("debug=\n");
             printf("\n");
  
  
             kompilacja = "$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^";
             linkowanie = "$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -o $@ $^";
             i = 0;
             
             printf("__ : main\n");
             printf("\t./main\n");
             printf("\n");
             printf("#\tvalgrind --leak-check=yes ./main\n");
             printf("\n");
         }

 
     {  split($1, nazwa, ".");
        printf("%s.o : %s.cpp\n", nazwa[1], nazwa[1]); 
        printf("\t%s\n", kompilacja);
        pliki[i++] = nazwa[1];
     } 
     
 END  {
          printf("\n");
          printf ("main : ");
          for (i in pliki)
             printf ("%s.o ", pliki[i]);
          printf("\n");
          printf("\t%s\n", linkowanie);
          printf("\n");
     }     
     
'  > makefile


