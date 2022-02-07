#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

int cflag = 0, dflag = 0, iflag = 0;

char* lower(char* s) {
  int n = strlen(s);
  char* out = malloc(n * sizeof(char));

  for(int i = 0; i < n; i++)
    *(out + i) = tolower(*(s + i));

  return out;
}

void uniq(FILE *f) {
  char* line = malloc(200 * sizeof(char));
  char* next = malloc(200 * sizeof(char));
  int end = 0;

  line = fgets(line, 200, f);

  while(!end) {
    int repeated = 0;

    do {
      repeated++;
      if(fgets(next, 200, f) == NULL) end = 1;
    } while(!end && ((!iflag && strcmp(next, line) == 0) || (iflag && strcmp(lower(next), lower(line)) == 0)));

    if((dflag && repeated > 1) || !dflag) {
      if(cflag) printf("%d ", repeated);
      printf("%s", line);
      if(line[strlen(line) - 1] != '\n') printf("\n");
    }

    strcpy(line, next);
  }
}

int main(int argc, char* argv[]) {
  FILE *f;
  char op;

  while((op = getopt(argc, argv, "cdi")) != -1)
    switch (op) {
    case 'c': cflag = 1; break;
    case 'd': dflag = 1; break;
    case 'i': iflag = 1; break;
    }

  if(optind == argc || argv[optind][0] == '-') uniq(stdin);
  else if((f = fopen(argv[optind], "r")) == NULL) printf("No such file\n");
  else uniq(f);

  return 0;
}
