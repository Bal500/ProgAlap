#include <stdlib.h>
#include <stdio.h>

FILE* inFile, *outFile;

char input[100];
int n = 0, x = 0, y = 0, fok = 0;


void readFiles() {
  inFile = fopen("be.txt", "r");
  outFile = fopen("ki.txt", "w");
}

void storeData() {
  fgets(input, 100, inFile);
  while (input[n] != '\0') {
    n++;
  }
  n -= 1;
}

void solution() {
  for (int i = 0; i < n; i++) {
    if (fok == 360) {
      fok = 0;
    }
    
    if (input[i] == 'b') {
      fok -= 90;
    }
    if (input[i] == 'j') {
      fok += 90;
    }
    if (input[i] == 'e') {
      fok = 0;
    }
    if (input[i] == 'k') {
      fok = 90;
    }
    if (input[i] == 'd') {
      fok = -180;
    }
    if (input[i] == 'n') {
      fok = -90;
    }

    if (input[i] != 'b' && input[i] != 'j' && input[i] != 'e' && input[i] != 'k' && input[i] != 'd' && input[i] != 'n' && (int)input[i] - 48 > 0 && (int)input[i] - 48 < 10) {
      if (fok == -90) {
        x -= (int)input[i] - 48;
      }
      if (fok == 90) {
        x += (int)input[i] - 48;
      }
      if (fok == 0 || fok == 180 || fok == 240) {
        y += (int)input[i] - 48;
      }
      if (fok == -180) {
        y -= (int)input[i] - 48;
      }
    }
  }

  fprintf(outFile, "%d\n", x + y);
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