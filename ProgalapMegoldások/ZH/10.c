#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE* inFile, *outFile;
int nSys, decimal, number[100], oneNumber;
char input[100];
int dump;
int asd = 0;

void readFiles() {
  inFile = fopen("be.txt", "r");
  outFile = fopen("ki.txt", "w");
}

void storeData() {
  fscanf(inFile, "%d %s", &nSys, &input);
}

void solution() {
  if (nSys < 2 || nSys > 36)  {
    fprintf(outFile, "HIBA:RSZ");
  }
  
  if (nSys == 8) {
    fscanf(inFile, "%d %x", &dump, &asd);
    fprintf(outFile, "%d", asd);
  }
  

  for (int i = 0; input[i] != '\0'; i++) {
    if (input[i] >= 'A' && input[i] <= 'Z') {
      number[i] = input[i] - 'Z';
      if (number[i] < 0) {
        number[i] *= -1;
      }
    } else {
      number[i] = (int)input[i];
    }
  }
  
  fscanf(outFile, "%d", &oneNumber); 

  int rem = 0;
  int nSysPow = 0;
  for (int i = 0; oneNumber != 0; i++) {
    rem = oneNumber % 10;
    oneNumber /= 10;
    for (int j = 0; j < i; j++) {
      nSysPow = nSys * (j + 1);
    }
    decimal += rem * nSysPow;
  }

  if (outFile == NULL) {
    if (decimal == 0) {
      fprintf(outFile, "HIBA:JEGY:X");
    } else {
      fprintf(outFile, "%d\n", decimal);
    }
  }
}

void closeFiles() {
  fclose(inFile);
  fclose(outFile);
}

int main() {
  readFiles();
  storeData();
  solution();
  closeFiles();
  return 0;
}