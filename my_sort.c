#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int nflag = 0, rflag = 0, size = 0;

void swap(char* a, char* b) {
  char* t = malloc(100 * sizeof(char));

  strcpy(t, a);
  strcpy(a, b);
  strcpy(b, t);
}

int condition(char* a, char* b) {
  int out;

  if(!nflag) out = strcmp(a,b) > 0 ? 0 : 1;
  else out = (atof(a) < atof(b) ? 1 : 0);

  return (rflag ? abs(1 - out) : out);
}

int partition(char* sort[], int low, int high) {
  char* pivot = sort[high];
  int i = low - 1;

  for(int j = low; j < high; j++)
    if(condition(sort[j], pivot)) swap(sort[++i], sort[j]);

  swap(sort[++i], sort[high]);

  return i;
}

void quicksort(char* sort[], int low, int high) {
  if(low < high) {
    int pivot = partition(sort, low, high);
    quicksort(sort, low, pivot - 1);
    quicksort(sort, pivot + 1, high);
  }
}

void setInMat(FILE *f, char* sort[]) {
  char* line = malloc(1000 * sizeof(char));
  char cur; int flag = 0;

  for(int i = 0; fscanf(f, "%c", &cur) != EOF; ) {
    *(line + i++) = cur;
    flag = 1;

    if(cur == '\n') {
      *(sort + size++) = line;
      line = malloc(1000 * sizeof(char));
      i = flag = 0;
    }
  }

  if(flag) *(sort + size++) = line;
}

int main(int argc, char* argv[]) {
  FILE *f;
  char** sort = malloc(1000 * 1000 * sizeof(char));

  for(char op; (op = getopt(argc, argv, "rn")) != -1; ) {
    if(op == 'r') rflag = 1;
    if(op == 'n') nflag = 1;
  }

  if(optind == argc) setInMat(stdin, sort);

  for(int i = optind; i < argc; i++) {
    if(argv[i][0] == '-') setInMat(stdin, sort);
    else if((f = fopen(argv[i], "r")) == NULL) continue;
    else setInMat(f, sort);
  }

  quicksort(sort, 0, size - 1);

  for(int i = 0; i < size; i++) {
    printf("%s", *(sort + i));
    if(sort[i][strlen(sort[i]) - 1] != '\n') printf("\n");
  }

  return 0;
}
