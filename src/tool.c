#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

int sumInt(const int *X, const int lenX){
	int r = 0;
	int i;
	for (i = 0; i<lenX; i++) {
		r+=X[i];
	}
	return(r);
}



void affTab(const int *tab, const int taille,const int retour_chariot )
{
    int i;
	for (i=0; i < taille; i++)
    {
        printf("%d ", tab[i]);
    }
    for (i =0; i < retour_chariot; i++)
    {
        printf("\n");
    }

}


void affTabd(const long double *tab, const int taille, const int retour_chariot )
{
    int i;
	for (i=0; i < taille; i++)
    {
        printf("%Lf ", tab[i]);
    }
    for (i =0; i < retour_chariot; i++)
    {
        printf("\n");
    }

}

int contains(int a, const int * Array, const int len){
    int i;
    for (i=0; i<len; i++) {
        if (a==Array[i]) return 1;
    }
    return 0;
}


double partitionError(const int * GoodClasses, const int * Classes, int N,int k){
    int i,j;
    int error = 0, good = 0;
    int ** confusion = malloc(k*sizeof(int *));
    int * used = malloc(k * sizeof(int));
    for (i=0;i<k;i++) {
        confusion[i] = malloc(k*sizeof(int));
        used[i] = 0;
    }
    for (i=0;i<k;i++){
        for (j=0;j<k;j++){
            confusion[i][j] = 0;
        }
    }
    for (i=0;i<N;i++){
        confusion[Classes[i]][GoodClasses[i]]++;
    }

    for (i=0;i<k;i++){
        int pmax = 0;
        int init = 0;
        for (j=0;j<k;j++){
            if (used[j] == 1) continue;
            if (init == 0) {
                init = 1;
                pmax = j;
            }
            if (confusion[i][j]>confusion[i][pmax]) {
                pmax = j;
            }
        }
        used[pmax] = 1;
        good += confusion[i][pmax];
    }
    error = N - good;

    for (i=0;i<k;i++) free(confusion[i]);
    free(confusion);
    free(used);
    return (double) error / (double) N;
}




/*
char* creerString(int ligne)
{
    char *tab = malloc(ligne * sizeof(char));
    assert(tab != NULL);
    return (tab);
}

long double* creerTab(int ligne)
{
    long double *tab = malloc(ligne * sizeof(long double));
    assert( tab != NULL );
    return (tab);
}

*/
