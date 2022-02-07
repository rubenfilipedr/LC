#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXSIZE 200


int printFile(char* *const argv, int i, int nFlag, int bFlag, int sFlag, int line) {
  FILE* fp = fopen(argv[i], "r");
  if (nFlag == 1 && bFlag == 0 && sFlag == 0) {
    char* str = (char*)malloc(MAXSIZE);
    while ( fgets(str, MAXSIZE, fp) != NULL ) {
      printf ("%6d\t""%s", line, str);
      line++;
    }
    free(str);
  }
  if (bFlag == 1 && nFlag == 0 && sFlag == 0) {
    char* str = (char*)malloc(MAXSIZE);
    while ( fgets(str, MAXSIZE, fp) != NULL ) {
      if (*str != '\n') {
        printf("%6d\t%s", line, str);
        line++;
      }
      else {
        printf("%s", str);
      }
    }
    free(str);
  }
  if (sFlag == 1 && nFlag == 0 && bFlag == 0) {
    char* str = (char*)malloc(MAXSIZE);
    char* lineant = (char*)malloc(MAXSIZE);
    while ( fgets(str, MAXSIZE, fp) != NULL ) {
      if (*str == '\n' && *lineant == '\n') { ; }
      else {
        printf("%s", str);
        *lineant = *str;
      }
    }
    free(str);
  }
  if (nFlag == 1 && sFlag == 1 && bFlag == 0) {
    char* str = (char*)malloc(MAXSIZE);
    char* lineant = (char*)malloc(MAXSIZE);
    while ( fgets(str, MAXSIZE, fp) != NULL ) {
      if (*str == '\n' && *lineant == '\n') { ; }
      else {
        printf("%6d\t%s", line, str);
        *lineant = *str;
        line++;
      }
    }
    free(str);
  }
  if (bFlag == 1 && sFlag == 1 && nFlag == 0) {
    char* str = (char*)malloc(MAXSIZE);
    char* lineant = (char*)malloc(MAXSIZE);
    while ( fgets(str, MAXSIZE, fp) != NULL ) {
      if (*str == '\n' && *lineant == '\n') { ; }
      else {
        if (*str == '\n') {
          printf("%s", str);
          *lineant = *str;
        } else {
          printf("%6d\t%s", line, str);
          *lineant = *str;
          line++;
        }
      }
    }
    free(str);
  }
  if ( nFlag == 0 && bFlag == 0 && sFlag == 0 ) {
    char c;
    while ( (c=fgetc(fp)) != EOF ) {
      printf("%c", c);
    }
  }
  fclose(fp);

  return line;
}



void printstd () {
  char ch;
  while ( (ch=fgetc(stdin)) != EOF ) {
    printf("%c", ch);
  }

}



int main (int argc, char *argv[]) {

  if ( argc == 1 ) {
    printstd();
  }
  int line = 1;
  int opt;
  int nFlag = 0;
  int bFlag = 0;
  int sFlag = 0;
  while ( (opt=getopt(argc, argv, ":nbs")) != -1 ) {
    switch (opt) {
      case 'n':
      nFlag = 1;
      break;
      case 'b':
      bFlag = 1;
      break;
      case 's':
      sFlag = 1;
      break;
    }
  }

  for (; optind<argc ; optind++) {
    if (argv[optind][0] == '-') { printstd(); }
    else {
      line = printFile(argv, optind, nFlag, bFlag, sFlag, line); }
    }

    exit(0);
  }
