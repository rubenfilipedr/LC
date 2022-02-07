#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
void printIntSeq(int first, int inc, int last) {
  if (first <= last && inc > 0 )
    while (first <= last) {
      printf("%d\n", first);
      first += inc;
    }
  else {
    while (first >= last) {
      printf("%.d\n", first);
      first += inc;
    }
  }
}
void printDoubleSeq(double first, double inc, double last) {
  int p=0;
  double finc = fabs(inc);
  if (finc >= 0.1 && finc <= 0.9) {
            p = 1;
        } else if (finc >= 0.01 && finc <= 0.09) {
            p = 2;
        } else if (finc >= 0.001 && finc <= 0.009) {
            p = 3;
        } else if (finc >= 0.0001 && finc <= 0.0009) {
            p = 4;
        } else if (finc >= 0.00001 && finc <= 0.00009) {
            p = 5;
        } else if (finc >= 0.000001 && finc <= 0.000009) {
            p = 6;
        } else {
            p = 0;
        }
  if (first < last )
  {
    while (fabs(last-first)> 0.0000000000000001 && first < last + inc) {
      printf("%.*lf\n",p, first);
      first += inc;
    }
  }
  else {
    while (fabs(last-first)> 0.0000000000000001 && first > last + inc) {
      printf("%.*lf\n",p, first);
      first += inc;
    }
  }
}
int main(int argc, char* argv[]) {
  double first, inc, last;
  if (argc == 2) {
    first = 1;
    inc = 1;
    last = atoi(argv[1]);
    printIntSeq(first, inc, last);
  }
  else if (argc == 3) {
    first = atoi(argv[1]);
    inc = 1;
    last = atoi(argv[2]);
    printIntSeq(first, inc, last);
  }
  else {
    int flag = 0;
    for (int i=0 ; argv[2][i] != '\0' ; i++) {
      if (!isdigit(argv[2][i]) && argv[2][i]!='-') { flag = 1; }
    }
    if (flag == 1) {
      first = atof(argv[1]);
      inc = atof(argv[2]);
      last = atof(argv[3]);
      printDoubleSeq(first, inc, last);
    } else {
      first = atoi(argv[1]);
      inc = atoi(argv[2]);
      last = atoi(argv[3]);
      printIntSeq(first, inc, last);
    }
  }
  exit(0);
}
