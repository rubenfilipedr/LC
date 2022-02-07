#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>
#define MAXSIZE 200

int* printstd() {
  char ch;
  char ant = ' ';
  int lineCount = 0;
  int wordCount = 0;
  int letterCount = 0;
  int* total = (int*)malloc(MAXSIZE);
  while ( (ch=fgetc(stdin)) != EOF ) {
    letterCount++;
    if ( isspace(ant) && (isalnum(ch) || ch == '-') ) {
      wordCount++;
    }
    if ( ch == '\n' ) {
      lineCount++;
    }
    ant = ch;

  }
  printf("%d %d %d\n", lineCount, wordCount, letterCount);
  *total = lineCount;
  *(total + 1) = wordCount;
  *(total + 2) = letterCount;
  return total;
}


int* printfile(char* *const argv, int i, int cFlag, int lFlag, int wFlag, int LFlag) {
  char ch;
  char ant = ' ';
  int lineCount = 0;
  int wordCount = 0;
  int letterCount = 0;
  int longLine = 0;
  int tempLine = 0;
  int* total = (int*)malloc(MAXSIZE);
  FILE* fp = fopen(argv[i], "r");
  while ( (ch=fgetc(fp)) != EOF ) {
    letterCount++;
    tempLine++;
    if ( isspace(ant) && (isalnum(ch) || ch == '-') ) {
      wordCount++;
    }
    if ( ch == '\n' ) {
      if ( tempLine > longLine ) {
        longLine = tempLine;
      }
      tempLine = 0;
      lineCount++;
    }
    ant = ch;

  }
  longLine--;
  if ( lFlag == 1 && cFlag == 0 && wFlag == 0 && LFlag == 0 ) { printf("%d\n", lineCount); }
  if ( wFlag == 1 && cFlag == 0 && lFlag == 0 && LFlag == 0 ) { printf("%d\n", wordCount); }
  if ( cFlag == 1 && wFlag == 0 && LFlag == 0 && lFlag == 0 ) { printf("%d\n", letterCount); }
  if ( LFlag == 1 && wFlag == 0 && cFlag == 0 && lFlag == 0 ) { printf("%d\n", longLine); }
  if ( lFlag == 1 && cFlag == 1 && wFlag == 0 && LFlag == 0 ) { printf("%d %d\n", lineCount, letterCount ); }
  if ( lFlag == 1 && cFlag == 0 && wFlag == 1 && LFlag == 0 ) { printf("%d %d\n", lineCount, wordCount ); }
  if ( lFlag == 0 && cFlag == 1 && wFlag == 1 && LFlag == 0 ) { printf("%d %d\n", wordCount ,letterCount); }
  if ( lFlag == 1 && cFlag == 1 && wFlag == 1 && LFlag == 0 ) { printf("%d %d %d\n", lineCount, wordCount, letterCount); }
  if ( cFlag == 1 && lFlag == 1 && wFlag == 1 && LFlag == 1 ) { printf("%d %d %d %d\n", lineCount, wordCount, letterCount, longLine); }
  if ( cFlag == 0 && lFlag == 0 && wFlag == 0 && LFlag == 0 ) { printf("%d %d %d\n", lineCount, wordCount, letterCount);
  }
  *total = lineCount;
  *(total + 1) = wordCount;
  *(total + 2) = letterCount;
  *(total + 3) = longLine;
  return total;
}




int main (int argc, char *argv[]) {

  int* temp = (int*)malloc(MAXSIZE);
  int* total = (int*)malloc(MAXSIZE);

  if (argc == 1) {
    temp = printstd();
    for (int i=0 ; i<3 ; i++) { *(total + i) += *(temp + i); }
  }

  int opt;
  int cFlag = 0;
  int lFlag = 0;
  int wFlag = 0;
  int LFlag = 0;
  while ( (opt=getopt(argc, argv, ":clwL")) != -1 ) {
    switch (opt) {
      case 'c':
      cFlag = 1;
      break;
      case 'l':
      lFlag = 1;
      break;
      case 'w':
      wFlag = 1;
      break;
      case 'L':
      LFlag = 1;
      break;
    }
  }

  for (; optind<argc ; optind++) {
    if (argv[optind][0] == '-') { temp = printstd(); }
    else { temp = printfile(argv, optind, cFlag, lFlag, wFlag, LFlag); }
    for (int i=0 ; i<3 ; i++) { *(total + i) += *(temp + i); }
    if ( *(temp+3) > *(total+3) ) { *(total+3) = *(temp+3); }
  }


  if ( argc > 2 ) {
    // *total = line
    // *(total+1) = word
    // *(total+2) = letter
    // *(total+3) = longline
    if ( lFlag == 1 && cFlag == 0 && wFlag == 0 && LFlag == 0 ) { printf("%d total\n", *total); }
    if ( wFlag == 1 && cFlag == 0 && lFlag == 0 && LFlag == 0 ) { printf("%d total\n", *(total+1)); }
    if ( cFlag == 1 && wFlag == 0 && LFlag == 0 && lFlag == 0 ) { printf("%d total\n", *(total+2)); }
    if ( LFlag == 1 && wFlag == 0 && cFlag == 0 && lFlag == 0 ) { printf("%d total\n", *(total+3)); }
    if ( lFlag == 1 && cFlag == 1 && wFlag == 0 && LFlag == 0 ) { printf("%d %d total\n", *total, *(total+2)); }
    if ( lFlag == 1 && cFlag == 0 && wFlag == 1 && LFlag == 0 ) { printf("%d %d total\n", *total, *(total+1)); }
    if ( lFlag == 0 && cFlag == 1 && wFlag == 1 && LFlag == 0 ) { printf("%d %d total\n", *(total+1) ,*(total+2)); }
    if ( lFlag == 1 && cFlag == 1 && wFlag == 1 && LFlag == 0 ) { printf("%d %d %d total\n", *total, *(total+1) ,*(total+2)); }
    if ( cFlag == 1 && lFlag == 1 && wFlag == 1 && LFlag == 1 ) { printf("%d %d %d %d total\n", *total, *(total+1) ,*(total+2), *(total+3)); }
    if ( cFlag == 0 && lFlag == 0 && wFlag == 0 && LFlag == 0 ) {
      for (int i=0 ; i<3 ; i++) { printf("%d ", *(total + i)); }
      printf("total\n");
    }


  }

  exit(0);

}
