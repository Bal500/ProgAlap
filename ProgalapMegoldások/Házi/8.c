#include <stdio.h>
#include <stdlib.h>

FILE* inFile, *outFile;

int fromMountain = 0, fromWater = 0, fromSand = 0, height = 0, width = 0;
char **terrain;

void readFiles() {
    inFile = fopen("be.txt", "r");
    outFile = fopen("ki.txt", "w");
}

void storeData() {
    fscanf(inFile, "%d %d %d\n", &fromMountain, &fromWater, &fromSand);
    fscanf(inFile, "%d %d\n", &height, &width);
    terrain = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        terrain[i] = (char*)malloc(width * sizeof(char));
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fscanf(inFile, "%c", &terrain[i][j]);
        }
        getc(inFile);
    }
}

void testPrint() {
    printf("%d %d %d\n", fromMountain, fromWater, fromSand);
    printf("%d %d\n", height, width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", terrain[i][j]);
        }
        printf("\n");
    }
}

void solution() {
    int places = 100;
    int asd = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            #pragma region X
            if (terrain[i][j] == 'X') {
                places--;
            }
            if (i == 0 && j == 0 && terrain[i][j] == 'X' || i == 0 && j == width - 1 && terrain[i][j] == 'X' ||
                i == height - 1 && j == 0 && terrain[i][j] == 'X'  || i == height - 1 && j == width - 1 && terrain[i][j] == 'X') {
                places -= 3;
            }
            if (terrain[i][j] == 'X' && i > 0 && i < height - 1 && j == 0 || j == width - 1) {
                places -= 5;
            }
            if (terrain[i][j] == 'X' && i > 0 && i < height - 1 && j > 0 && j < width - 1) {
                places -= 8;
            }
            #pragma endregion

            if (terrain[i][j] == 'A') {
                places--;
            }
            if (i > 1 && i < height - 2 && j > 1 && j < width - 2 && terrain[i][j] != 'A') {
                if (terrain[i][j - 1] != 'A' || terrain[i][j + 1] != 'A' || terrain[i - 1][j] != 'A' || terrain[i + 1][j] != 'A' ||
                    terrain[i - 1][j - 1] != 'A' || terrain[i - 1][j + 1] != 'A' || terrain[i + 1][j - 1] != 'A' || terrain[i + 1][j + 1] != 'A' &&
                    terrain[i][j - 1] == '~' || terrain[i][j + 1] == '~' || terrain[i - 1][j] == '~' || terrain[i + 1][j] == '~' ||
                    terrain[i - 1][j - 1] == '~' || terrain[i - 1][j + 1] == '~' || terrain[i + 1][j - 1] == '~' || terrain[i + 1][j + 1] == '~' ||
                    terrain[i][j - 2] == '~' || terrain[i][j + 2] == '~' || terrain[i - 2][j] == '~' || terrain[i + 2][j] == '~' ||
                    terrain[i - 2][j - 2] == '~' || terrain[i - 2][j + 2] == '~' || terrain[i + 2][j - 2] == '~' || terrain[i + 2][j + 2] == '~') {
                    places--;
                }
            }
        }
    }
    places++;
    if (places < 0) {
        places *= -1;
    }
    
    fprintf(outFile, "%d", places);
}

void closeFiles() {
    fclose(inFile);
    fclose(outFile);
    for(int i = 0; i < width; i++) {
        free(terrain[i]);
    }
    free(terrain);
}

int main() {
    readFiles();
    storeData();
    //testPrint();
    solution();
    closeFiles();
    return 0;
}