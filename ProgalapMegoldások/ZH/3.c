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

Az alabbi fuggveny elso parametere egy egeszek sorozatat tarolo tomb,
amiben a sorozat veget a -1 ertek jelzi. A feladat a tomb megforditasa.
A feladat megoldhato egy ciklus es ket szamlalo hasznalataval. Az elso
szamlalo a tomb elejerol, a masodik az eredmeny-tomb vegerol indul.
Minden lepesben az elso szamlalo altal mutatott elemet kell beszurni az
eredmeny-tombbe a masodik szamlalo altal mutatott helyre. Figyelj arra,
hogy az eredmeny-tomb veget lezard a -1 ertekkel!
Az eredmenyt a masodik parameterben kapott eredmeny nevu tombben kell
elkesziteni.
Kodold le a fuggvenyt C nyelven. A fuggveny fejlecen ne valtoztass!
*/
void tombmegforditas(int tomb[], int eredmeny[]) {
    int j = 0;
    while (tomb[j] != -1) {
        j++;
    }
    
    int i;
    for (i = 0; tomb[i] != -1; i++) {
        eredmeny[j - 1] = tomb[i];
        j--;
    }
    eredmeny[i] = -1;
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
	char x=0;
	int i, n=0, a[32]={-2}, r[32];
	for(i=0;i<32;++i) r[i]=-2;
	if(fscanf(stdin, "%c", &x)!=1) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	if(fscanf(stdin, "%d", &n)!=1) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	for(i=0; i<n; i++) {
		if(fscanf(stdin, "%d", a+i)!=1) {
			fprintf(stderr, "HIBA: Nem olvasható adat!\n");
			return;
		}
	}
	a[n]=-1;
	tombmegforditas(a, r);
	if(x=='R') {
		fprintf(stdout, "%d\n", r[n]);
	} else if(x=='E') {
		for(i=0; i<n; i++) {
			fprintf(stdout, "%d\n", r[i]);
		}
	} else {
		for(i=0; r[i]!=-1; i++) {
			fprintf(stdout, "%d\n", r[i]);
		}
	}
}
void test_1()
{
    int i, j, tomb[20] = {0}, eredmeny[20] = {0};
    struct {int tomb[20]; int eredmeny[20];} testlist[2] = {
        {{3,2,1,2,3,-1},   {3,2,1,2,3,-1}  },
        {{1,2,3,4,5,6,-1}, {6,5,4,3,2,1,-1}},
    };
    for (i = 0; i < 2; ++i) {
        for(j = 0; testlist[i].tomb[j] != -1; tomb[j] = testlist[i].tomb[j], ++j);
        tomb[j] = -1;
        tombmegforditas(tomb, eredmeny);
        for(j = 0; eredmeny[j] != -1 && testlist[i].eredmeny[j] != -1 && eredmeny[j] == testlist[i].eredmeny[j]; ++j);
        if (eredmeny[j] != testlist[i].eredmeny[j]) {
            fprintf(stderr, "HIBA: tombmegforditas({");
            for(j = 0; testlist[i].tomb[j] != -1; fprintf(stderr, "%d,", testlist[i].tomb[j++]));
            fprintf(stderr, "-1}, {...})\n");
            fprintf(stderr, "\telvárt eredmény: {");
            for(j = 0; testlist[i].eredmeny[j] != -1; fprintf(stderr, "%d,", testlist[i].eredmeny[j++]));
            fprintf(stderr, "-1}\n");
            fprintf(stderr, "\tkapott eredmény: {");
            for(j = 0; eredmeny[j] != -1 && j < 10; fprintf(stderr, "%d,", eredmeny[j++]));
            fprintf(stderr, "%s}\n", (j < 10) ? "-1" : "...");
        }
    }
}

typedef void (*call_function)();

call_function call_table[] = {
	call_1,
	NULL
};


call_function test_table[] = {
	test_1,
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
