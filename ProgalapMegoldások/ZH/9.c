/***********************************************************************
* A PROGRAMBAN NEM SZEREPELHETNEK AZ ALÁBBI SOROK:
* #include <string.h>
* #include <math.h>
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************
************************************************************************
**  ETTŐL A PONTTÓL DOLGOZHATSZ A FELADATOKON
************************************************************************
***********************************************************************/

/*
1. feladat (5 pont)

Az alabbi fuggveny feladata helyet foglalni egy ketdimenzios int tombnek.
A tomb sor- es oszlopszama megegyezik.
A tomb N meretet a fuggveny parameterkent kapja.
A helyfoglalas ugy tortenjen, hogy eloszor helyet foglalunk az N sor
pointereinek, majd megfelelo modon minden sor N-N darab elemenek is.
A helyfoglalas utan toltsuk fel a tomb elemeit ertekekkel a kovetkezo modon:
Minden cellaba irjuk be a sor- es oszlopindexek osszeget.
A fuggveny terjen vissza a tombre mutato pointerrel. A memoria felszabaditasaval
nem kell foglalkoznod.
*/

int **foglal(int n) {
	int **matrix;
	matrix = (int**)malloc(n * sizeof(int*));

	for (int i = 0; i < n; i++) {
		matrix[i] = (int*)malloc(n * sizeof(int));
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = i + j;
		}
	}
	
	return matrix;
}

/*
2. feladat (5 pont)

Irj egy egyszeru szoveg-kitomorito fuggvenyt, amely egy sztring karakterein
vegiglepkedve ha szamjegy jon, akkor a kovetkezo karaktert annyiszor irja ki,
mint amennyi a szamjegy erteke, es az azt koveto karakterrel folytatja a
muveletet. A fuggveny az eredmenyt a masodik parameterben allitsa ossze.
Pelda: "be2la 16alma0x" sztringbol "bella 6alma" lesz.
*/

void kitomorit(char* tomoritett, char* eredeti) {
	int into = 0;
	for (int i = 0; tomoritett[i] != '\0'; i++) {
		int number = -1;
		if (tomoritett[i] >= '0' && tomoritett[i] <= '9') {
			number = (int)tomoritett[i] - 48;
			i++;
		}

		if (number != -1) {
			for (int j = 0; j < number; j++) {
				eredeti[into] = tomoritett[i];
				into++;
			}
		} else {
			eredeti[into] = tomoritett[i];
			into++;
		}
	}
}
/***********************************************************************
************************************************************************
**
**  EZEN A PONTON TÚL NE VÁLTOZTASS SEMMIT SEM A FÁJLON!
**
************************************************************************
***********************************************************************/

void call_1()
{
	int chck;
	int n, i, j;
	int **ptr = NULL;
	if(fscanf(stdin, "%d %d", &chck, &n)!=2) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	ptr = foglal(n);
	switch (chck) {
		case 1:
			if (ptr != NULL) {
				free(ptr);
				fprintf(stdout,"%d\n", n);
			} else {
				fprintf(stdout,"NULL\n");
			}
			break;
		case 2:
			for(i=0; i<n; i++) {
				free(ptr[i]);
				fprintf(stdout,"%d", n);
			}
			fputc('\n', stdout);
			break;
		case 3:
			for(i=0; i<n; i++) {
				for(j=0; j<n; j++) {
					fprintf(stdout, "%d%c", ptr[i][j], (j==n-1)?'\n':' ');
				}
			}
			break;
		default:
			if(fscanf(stdin, "%d %d", &i, &j)!=2) {
				fprintf(stderr, "HIBA: Nem olvasható adat!\n");
				return;
			}
			fprintf(stdout,"%d\n", ptr[i][j]);
			break;
	}
}
void test_1()
{
	const int n = 3;
	int i, j, k;
  int **ptr = NULL;
  struct {int ptr[3][3];} testlist[1] = {
  	{
  		{
  			{0,1,2},
  			{1,2,3},
  			{2,3,4}
  		}
  	}
  };
  for (i = 0; i < 1; ++i) {
    ptr = foglal(n);
    if (ptr == NULL) {
    	fprintf(stderr, "HIBA: NULL pointer\n");
    	return;
    } else {
    	for (j = 0; j < n; ++j) {
    		if (ptr[j] == NULL) {
		    	fprintf(stderr, "HIBA: NULL pointer\n");
		    	return;
    		} else {
	    		for (k = 0; k < n; ++k) {
	    			if (ptr[j][k] != testlist[i].ptr[j][k]) {
	    				fprintf(stderr, "HIBA a(z) (%d,%d) pozíción\n"
	    					              "\telvárt eredmény: %d\n"
	    					              "\tkapott eredmény: %d\n",
	    					              j, k, testlist[i].ptr[j][k], ptr[j][k]);
	    				return;
	    			}
	    		}
	    	}
    	}
    }
    for (j = 0; j < n; free(ptr[j++]));
    free(ptr);
  }
}

void call_2()
{
	char s1[100], s2[1000];
	if(fgets(s1, 100, stdin)==NULL) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	kitomorit(s1,s2);
	fputs(s2, stdout);
}
void test_2()
{
	int i, j;
	char tomoritett[1000];
	struct {char eredeti[100]; char tomoritett[1000];} testlist[1] = {
		{"be2la 16alma0x", "bella 6alma"}
	};
	for (i = 0; i < 1; ++i) {
		kitomorit(testlist[i].eredeti, tomoritett);
		for(j = 0; tomoritett[j] != 0 && testlist[i].tomoritett[j] != 0 && tomoritett[j] == testlist[i].tomoritett[j]; ++j);
        if (tomoritett[j] != testlist[i].tomoritett[j]) {
			fprintf(stderr, "HIBA: kitomorit(\"%s\", \"...\")\n"
							"\telvárt eredmény: \"%s\"\n"
							"\tkapott eredmény: \"%s\"\n",
					testlist[i].eredeti, testlist[i].tomoritett, tomoritett);
		}
	}
}

typedef void (*call_function)();

call_function call_table[] = {
	call_1,
	call_2,
	NULL
};


call_function test_table[] = {
	test_1,
	test_2,
	NULL
};

static int __arg_check_helper(const char * exp, const char * arg) {
    while (*exp && *arg && *exp == *arg) {
        ++exp;
        ++arg;
    }
    return *exp == *arg;
}

int main(int argc, char *argv[])
{
    int feladat, calltabsize;
    if ((argc > 1) && !(__arg_check_helper("-t", argv[1]) && __arg_check_helper("--test", argv[1]))) {
        if (argc > 2) {
            feladat = atoi(argv[2]);
            for (calltabsize=0; test_table[calltabsize]; calltabsize++);
            if (feladat <= 0 || calltabsize < feladat) {
                fprintf(stderr, "HIBA: rossz feladat sorszám: %d!\n", feladat);
                return 1;
            }
            (*test_table[feladat-1])();
        } else {
            for (feladat=0; test_table[feladat]; ++feladat) {
                (*test_table[feladat])();
            }
        }
        return 0;
    }
    if (!freopen("be.txt", "r", stdin)) {
        fprintf(stderr, "HIBA: Hiányzik a `be.txt'!\n");
        return 1;
    }
    if (!freopen("ki.txt", "w", stdout)) {
        fprintf(stderr, "HIBA: A `ki.txt' nem írható!\n");
        return 1;
    }
    for (calltabsize=0; call_table[calltabsize]; calltabsize++);
    if (fscanf(stdin, "%d%*[^\n]", &feladat)!=1) {
        fprintf(stderr, "HIBA: Nem olvasható a feladat sorszám!\n");
        return 1;
    }
    fgetc(stdin);
    if (0<feladat && feladat<=calltabsize) {
        (*call_table[feladat-1])();
    } else {
        fprintf(stderr, "HIBA: Rossz feladat sorszám: %d!\n", feladat);
        return 1;
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
