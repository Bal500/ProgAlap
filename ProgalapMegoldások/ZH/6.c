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

Szamold ki egy s1, s2, s3, ... mertani sorozat elemeinek osszeget. A
fuggveny megkapja a sorozat elso elemet (elso) es a kvocienset (q),
valamint egy egesz intervallum also (a) es felso (b) vegpontjat.
A fuggveny visszateresi erteke az sa+...+sb osszeg.
A mertani sorozat n-edik eleme: sn=s1*q^(n-1)
*/

double sorozat(double elso, double q, int a, int b) {
    double osszeg = 0;
    for (int i = a; i <= b; i++) {
        double qPow = 1;
        for (int j = 1; j < i; j++) {
            qPow *= q;
        }
        
        double akt = elso * qPow;
        osszeg += akt;
    }
    
    return osszeg;
}

/*
2. feladat (5 pont)

A feladat egy fuggveny megirasa, amely parameterul
var egy allatkertbeli ketrecekbol allo nem ures tombot,
illetve annak hosszat. A fuggveny adja vissza a
legzsufoltabb ketrec azonositojat. Az a ketrec a
legzsufoltabb, amelyben atlagosan egy allatra a
legkisebb terulet jut.

Kodold le C nyelven a fuggvenyt! A fuggveny fejlecen es a strukturan ne valtoztass!
A fuggveny inputjai a parameterek, outputja a visszateresi ertek.
A fuggveny nem vegez IO muveleteket!
*/

typedef struct {
	long azonosito;
	char allat;
	int allatokSzama;
	int ketrecMeret;
} Ketrec;

long legzsufoltabb(Ketrec ketrecek[], int db) {
    double legkisebb = 999;
    int index = 0;
    for (int i = 0; i < db; i++) {
        double akt = ketrecek->ketrecMeret / ketrecek->allatokSzama;
        if (legkisebb > akt) {
            legkisebb = akt;
            index = ketrecek->azonosito;
        }
    }
    return index;
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
	double e, m, eredmeny;
	int a, b;
	if(fscanf(stdin, "%lf %lf %d %d", &e, &m, &a, &b)!=4) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	eredmeny=sorozat(e, m, a, b);
	fprintf(stdout, "%.5lf\n", eredmeny);
}
void test_1()
{
  int i, err;
  double eredmeny;
  struct {double e; double q; int a; int b; double eredmeny;} testlist[2] = {{1.0, 2.0, 3, 5, 28.0}, {1.0, 0.5, 2, 4, 0.875}};
  fprintf(stderr, "=== 1. feladat tesztelése ===\n");
  for (i = 0; i < 2; ++i) {
    err = 0;
    fprintf(stderr, "%d. teszteset ... ", i + 1);
    eredmeny = sorozat(testlist[i].e, testlist[i].q, testlist[i].a, testlist[i].b);
    if (eredmeny != testlist[i].eredmeny) {
      err = 1;
      fprintf(stderr, "HIBA: sorozat(%lf, %lf, %d, %d)\n"
                      "\telvárt eredmény: %lf\n"
                      "\tkapott eredmény: %lf\n",
              testlist[i].e, testlist[i].q, testlist[i].a, testlist[i].b, testlist[i].eredmeny, eredmeny);
    }
    err ?: fprintf(stderr, "OK\n");
  }
}

void call_2(){
    int db;
    Ketrec * ketrecek;
    if (fscanf(stdin, "%d\n", &db) != 1) {
        fprintf(stderr, "HIBA: Nem olvasható adat (db)!\n");
        return;
    }
    ketrecek = (Ketrec*)malloc(db * sizeof(Ketrec));
    for (int i = 0; i < db; ++i) {
        if(fscanf(stdin, "%ld %c %d %d\n", &(ketrecek[i].azonosito), &(ketrecek[i].allat), &(ketrecek[i].allatokSzama), &(ketrecek[i].ketrecMeret)) != 4) {
            fprintf(stderr, "HIBA: Nem olvasható adat (azonosito, allat, allatokSzama, ketrecMeret)!\n");
            free(ketrecek);
            return;
        }
    }
    fprintf(stdout, "%ld\n", legzsufoltabb(ketrecek, db));
    free(ketrecek);
}
void test_2(){
    int i, err;
    long eredmeny;
    struct { Ketrec ketrecek[3]; int db; long eredmeny; }
        testlist[2] = {
            {
                { {1, 'a', 6, 7}, {2, 'b', 2, 1}, {3, 'c', 4, 3} }, 3, 2
            },
            {
                { {1, 'a', 6, 6}, {2, 'b', 2, 4}, {3, 'c', 4, 12} }, 3, 1
            }
        };
    fprintf(stderr, "=== 2. feladat tesztelése ===\n");
    for (i = 0; i < 2; ++i) {
        err = 0;
        fprintf(stderr, "%d. teszteset ... ", i + 1);
        eredmeny = legzsufoltabb(testlist[i].ketrecek, testlist[i].db);
        if (eredmeny != testlist[i].eredmeny) {
            fprintf(stderr, "HIBA: legzsufoltabb([{%ld, '%c',%d,%d},{%ld, '%c',%d,%d},{%ld, '%c',%d,%d}],%d)\n"
                    "\telvárt eredmény: %ld\n"
                    "\tkapott eredmény: %ld\n",
                    testlist[i].ketrecek[0].azonosito, testlist[i].ketrecek[0].allat, testlist[i].ketrecek[0].allatokSzama, testlist[i].ketrecek[0].ketrecMeret,
                    testlist[i].ketrecek[1].azonosito, testlist[i].ketrecek[1].allat, testlist[i].ketrecek[1].allatokSzama, testlist[i].ketrecek[1].ketrecMeret,
                    testlist[i].ketrecek[2].azonosito, testlist[i].ketrecek[2].allat, testlist[i].ketrecek[2].allatokSzama, testlist[i].ketrecek[2].ketrecMeret,
                    testlist[i].db,
                    testlist[i].eredmeny,
                    eredmeny
            );
            err = 1;
        }
        err ?: fprintf(stderr, "OK\n");
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
