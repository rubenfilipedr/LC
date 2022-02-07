#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MAXSIZE 2000


char* toLower(char *str) {
  char* new = (char*)malloc(MAXSIZE);
  for (int i=0 ; str[i]!='\0' ; i++) {
    new[i] = tolower(str[i]);
  }
  return new;
}


void findWord(int argc, char* *const argv, char* s, int i, int iFlag, int vFlag, int lFlag, int cFlag) {
  int lFlagTMP = 0;
  int cFlagTMP = 0;
  if ( i==-1 ) {
    char* str = (char*)malloc(MAXSIZE);
    while ( fgets(str, MAXSIZE, stdin) != NULL ) {
      char* original = str;
      if (iFlag) {
        str = toLower(str);
        s = toLower(s);
      }
      if (lFlag) {
        if (vFlag) {
          if(!strstr(str, s)) {
            lFlagTMP = 1;
          }
        } else {
          if (strstr(str, s)) {
            lFlagTMP = 1;
          }
        }
      } else if (cFlag) {
        if (vFlag) {
          if(!strstr(str, s)) {
            cFlagTMP++;
          }
        } else {
          if (strstr(str, s)) {
            cFlagTMP++;
          }
        }
      } else {
        if (vFlag) {
          if(!strstr(str, s)) {
            printf("%s", original);
          }
        } else {
          if (strstr(str, s)) {
            printf("%s", original);
          }
        }
      }
    }
    if (lFlagTMP) { printf("(standard input)\n"); }
    if (cFlag) { printf("%d\n", cFlagTMP); }
  } else {
    char* str = (char*)malloc(MAXSIZE);
    FILE* fp = fopen(argv[i], "r");
    while ( fgets(str, MAXSIZE, fp) != NULL ) {
      char* original = str;
      if (iFlag) {
        str = toLower(str);
        s = toLower(s);
      }
      if (lFlag) {
        if (vFlag) {
          if(!strstr(str, s)) {
            lFlagTMP = 1;
          }
        } else {
          if (strstr(str, s)) {
            lFlagTMP = 1;
          }
        }
      } else if (cFlag) {
        if (vFlag) {
          if(!strstr(str, s)) {
            cFlagTMP++;
          }
        } else {
          if (strstr(str, s)) {
            cFlagTMP++;
          }
        }
      } else {
        if (vFlag) {
          if(!strstr(str, s)) {
            printf("%s", original);
          }
        } else {
          if (strstr(str, s)) {
            printf("%s", original);
          }
        }
      }
    }
    if (lFlagTMP) { printf("%s\n", argv[i]); }
    if (cFlag) { printf("%d\n", cFlagTMP); }
    fclose(fp);
  }
}


int main(int argc, char *argv[]) {

  char* str;
  int opt;
  int iFlag = 0;
  int vFlag = 0;
  int lFlag = 0;
  int cFlag = 0;
  int thisArg;

  while ( (opt=getopt(argc, argv, ":ivlc")) != -1 ) {
    switch (opt) {
      case 'i':
      iFlag = 1;
      break;
      case 'v':
      vFlag = 1;
      break;
      case 'l':
      lFlag = 1;
      break;
      case 'c':
      cFlag = 1;
      break;
    }
  }

  if (iFlag || vFlag || lFlag || cFlag) {   // Se houver opcoes
    for (int i=2 ; i<argc ; i++) {
      if (argv[i][0] != '-') {
        str = argv[i];
        thisArg = i+1;
        break;
      }
    }
    if (argc == 3) { findWord(argc, NULL, str, -1, iFlag, vFlag, lFlag, cFlag); }
    else {
      for (int j = thisArg ; j<argc ; j++) {
        if (argv[j][0] == '-') { findWord(argc, NULL, str, -1, iFlag, vFlag, lFlag, cFlag); }
        else { findWord(argc, argv, str, j, iFlag, vFlag, lFlag, cFlag); }
      }
    }
  }

  else {                                    // Se nao houver opcoes
    for (int i=1 ; i<argc ; i++) {
      if (argv[i][0] != '-') {
        str = argv[i];
        thisArg = i+1;
        break;
      }
    }
    if (argc == 2) { findWord(argc, NULL, str, -1, iFlag, vFlag, lFlag, cFlag); }
    else {
      for (int j = thisArg ; j<argc ; j++) {
        if (argv[j][0] == '-') { findWord(argc, NULL, str, -1, iFlag, vFlag, lFlag, cFlag); }
        else { findWord(argc, argv, str, j, iFlag, vFlag, lFlag, cFlag); }
      }
    }
  }



}
