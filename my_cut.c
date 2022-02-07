#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int bflag = 0, dflag = 0;

void cut(FILE *f, int* barray, char dchar, int* darray) {
  char ch;

  if(dflag) {
    int indice = 0, input = 0, i = 0;
    char* token = malloc(100 * sizeof(char));

    while(fscanf(f, "%c", &ch) != EOF) {
      if(ch == dchar || ch == '\n') {
	indice++;

	if(*(darray + indice - 1)) {
	  if(input) printf("%c", dchar);
	  printf("%s", token);
	  input = 1;
	}

	if(ch == '\n') {
	  printf("\n");
	  indice = 0;
	  input = 0;
	}

	i = 0; token = malloc(100 * sizeof(char));
      }

      else *(token + i++) = ch;
    }
  }

  else if(bflag){
    for(int bytes = 1; fscanf(f, "%c", &ch) != EOF; bytes++) {
      if(ch == '\n') {
	printf("\n");
	bytes = 0;
      }

      else if (*(barray + bytes - 1)) printf("%c", ch);
    }
  }
}

int* buildArray(char* s) {
  int* array = malloc(100 * sizeof(int));
  memset(array, 0, 100);

  for(char* token = strtok(s, ","); token != NULL; token = strtok(NULL, ","))
    *(array + atoi(token) - 1) = 1;

  return array;
}

int main(int argc, char* argv[]) {
  FILE *f;
  int* barray; int* darray;
  int optind; char dchar;

  for(int i = 0; i < argc; i++) {
    if(strstr(*(argv + i), "-b") != NULL) {
      bflag = 1;
      barray = buildArray(argv[++i]);
      optind = i + 1;
    }

    if(strstr(*(argv + i), "-d") != NULL) {
      dflag = 1;
      if(strlen(*(argv + i)) - 2 == 0) dchar = argv[++i][0];
      else dchar = argv[i][2];
    }

    if(strstr(*(argv + i), "-f") != NULL) {
      if(strlen(*(argv + i)) - 2 == 0) darray = buildArray(argv[++i]);
      else darray = buildArray(argv[i] + 2);
      optind = i + 1;
    }
  }

  if(argc == optind) cut(stdin, barray, dchar, darray);

  for(int i = optind; i < argc; i++) {
    if(argv[i][0] == '-') cut(stdin, barray, dchar, darray);
    else if((f = fopen(argv[i], "r")) == NULL) continue;
    else cut(f, barray, dchar, darray);
  }

  return 0;
}
