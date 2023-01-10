#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* inFile, *outFile;
    int height, width, **rocketData, *rocketLine, robotPlace = 0, rockets = 0, catchedRockets = 0;

    inFile = fopen("be.txt", "r");
    outFile = fopen("ki.txt", "w");

    fscanf(inFile, "%d %d*\n", &height, &width);
    robotPlace = width;
    rocketData = (int**)malloc(height * sizeof(int*));
    rocketLine = (int*)malloc(height * sizeof(int));
    for(int i = 0; i < height; i++) {
        rocketLine[i] = 0;
        rocketData[i] = (int*)malloc(width * sizeof(int));
    }

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            fscanf(inFile, "%d", &rocketData[i][j]);
            if (rocketData[i][j] == 1) {
                rockets++;
                rocketLine[i]++;
            }
        }
        //getc(inFile);
    }

    for(int i = 0; i < height; i++) {
        if (robotPlace == width) {
            for(int j = 0; j < width; j++) {
                if (rocketData[i][j] == 1) {
                    robotPlace = j;
                    break;
                }
            }
        }
        if (rocketData[i][robotPlace] == 1) {
            catchedRockets++;
            continue;
        }
        if (rocketLine[i] == 0) {
            continue;
        }
        if (rocketLine[i] == 1) {
            int j;
            for (j = 0; j < width && rocketData[i][j] == 0; j++);
            if (j < robotPlace) {
                robotPlace--;
            } else {
                robotPlace++;
            }
            if (rocketData[i][robotPlace] == 1) {
                catchedRockets++;
            } 
            continue;
        } else { 
            if (robotPlace > 0 && robotPlace < width - 1 && rocketData[i][robotPlace - 1] == 1 && rocketData[i][robotPlace + 1] == 1) {
                continue;
            } else if (robotPlace > 0 && rocketData[i][robotPlace - 1] == 1) {
                robotPlace--;
            } else if(robotPlace < width - 1 && rocketData[i][robotPlace + 1] == 1) {
                robotPlace++;
            } else if (robotPlace == 0) {
                robotPlace++;
            } else if (robotPlace == width - 1) {
                robotPlace--;
            } else {
                int left = 0, right = 0;
                for (int j = 0; j < width; j++) {
                    if(j < robotPlace) {
                        left++;
                    } else if (j > robotPlace) {
                        right++;
                    } if (left > right) {
                        robotPlace--;
                    } else if (right > left) {
                        robotPlace++;
                    }
                }
                if (rocketData[i][robotPlace] == 1) {
                    catchedRockets++;
                }
            }
        }
    }
    printf("%d\n", (rockets - catchedRockets));
    fprintf(outFile, "%d\n", (rockets - catchedRockets));

    for(int i = 0; i < height; i++) {
        free(rocketData[i]);
    }
    free(rocketData);
    
    fclose(inFile);
    fclose(outFile);

    return 0;
}