#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "main.h"
#include "motif.h"
#include "discretisation.h"
#include "tool.h"
#include <time.h>

#define DEBUG 0
#define DEBUG_CLUSTERING 0

int testDiscret(){
    printf("***Cas Discret*** \n\n");
    int X1[18] = {12, 13, 14, 12, 13, 16, 12, 13, 15, 12, 13, 16, 11, 13, 15, 12, 13, 16};
    int X2[18] = {12, 13, 14, 19, 13, 16, 12, 13, 15, 12, 13, 16, 11, 13, 15, 12, 13, 16};
    long double distance = 0;
 
    distance = magicDistDiscrete(X1,LEN(X1), X2, LEN(X2));
	
    printf("X1 : "); affTab(X1, LEN(X1), 1);
    printf("X2 : "); affTab(X2, LEN(X2), 1);
    printf("Distance : %Lf \n\n", distance);
	
    return 1;
}

int testContinu() {
	printf("***Cas Continu*** \n\n");
	long double distance = 0;
	long double X[6] = { -1,2.6,-4,5.5,7,1.8 };
	long double Y[6] = { -0.5,2.6,-4,5.5,9,1.81 };
	//Discretisation *d = initDiscretisation ( X, LEN(X) );
	
	long double mM[2] = {0,0};
	minMax(X,LEN(X),mM,1);
	minMax(Y,LEN(Y),mM,0);
	
	distance = magicDistContinuous(X, LEN(X), Y, LEN(Y), mM );
	
	printf("X1 : "); affTabd(X, LEN(Y), 1);
	printf("X2 : "); affTabd(Y, LEN(Y), 1);
	printf("min %Lf ,  max %Lf\n", mM[0], mM[1]);
	printf("Distance : %Lf \n\n", distance);
	return 1;
}


long double patternCoefficient( const int i ) {
	return  pow( 2, -i );
}


long double  discretisationCoefficient( const int i ) {
	return  pow( 2, -i );
}

long double remainingSumOfDiscretisationCoefficient( const int i ) {
	assert(i>0);
	return pow( 2, -i + 1) ; //Geometrical sequence with q = 1/2
}


void initializeXpXg( int *Kp, int *Kg, int** Xp, int** Xg,const  int* X1,const  int* X2,const int taille_X1,const int taille_X2)
{
    if (taille_X1 > taille_X2)
    {
        *Kp = taille_X2;
        *Kg = taille_X1;
        *Xp = malloc((*Kp) * sizeof(int));
        memcpy(*Xp,X2,(*Kp) * sizeof(int));
        *Xg = malloc((*Kg) * sizeof(int));
        memcpy(*Xg,X1,(*Kg) * sizeof(int));
    }
    else
    {
        *Kp = taille_X1;
        *Kg = taille_X2;
        *Xp = malloc((*Kp) * sizeof(int));
        memcpy(*Xp,X1,(*Kp) * sizeof(int));
        *Xg = malloc((*Kg) * sizeof(int));
        memcpy(*Xg,X2,(*Kg) * sizeof(int));
    }
}



int occurences(int *X1, int taille_X1, int *X2, int taille_X2)
{   //on recherche X1 dans X2:
    int occ = 0;
    int *T = malloc((taille_X1+1)*sizeof(int));
    T = kmp_tableau(X1, taille_X1,T);
    int deja_lu = 0;
    int i_occurence = 0;

    while (i_occurence != -1)
    {
        i_occurence = kmp_recherche(T, X1, taille_X1, (X2 + deja_lu),(taille_X2- deja_lu));
        //printf("\ni_occurence: %d \n", i_occurence);
        deja_lu += i_occurence +1;
        occ +=1;
    }
    free(T);
    return(occ-1);
}


long double magicDistContinuous(const long double *X, const int lenX,const long double *Y,const int lenY, const long double * mM)
{
	assert(X != NULL);
	assert(Y != NULL);
	assert( (lenX>0) && (lenY>0) );
	long double distance = 0;
	
	int maxSplit = maxInterestingSplit(X,lenX, Y,lenY, mM );
	
	if (DEBUG_DISCRETISATION)  { 
		printf("X : "); affTabd(X, lenX, 1);
		printf("Y : "); affTabd(Y, lenY, 1);
		printf("MaxSplit : %i\n",maxSplit); 
	}
	
	// For the firsts discretisations, compute the distances 
	int * dx = malloc(sizeof(int) * lenX );
	int * dy = malloc(sizeof(int) * lenY );
	int i;
	long double contrib = 0;
	for (i=1; i<=maxSplit;i++) {
		discretise(X,lenX,mM,i,dx);
		discretise(Y,lenY,mM,i,dy);
		contrib = magicDistDiscrete(dx,lenX,dy,lenY);
		distance += discretisationCoefficient(i)*contrib;
		if (DEBUG_DISCRETISATION)  {
			printf("boxes : %i (%i)\n", i,(int) (pow(2,i)) );
			printf("dx : "); affTab(dx, lenX, 1);
			printf("dy : "); affTab(dy, lenY, 1);
			printf("contribution : %Lf, pondération : %Lf\n",contrib, discretisationCoefficient(i));
			printf("\n");
		}
	}
	free(dx); free(dy);

	// Add the constant term of distance for all the possible discretisations
	distance += remainingSumOfDiscretisationCoefficient(maxSplit+1)*contrib;
	if (DEBUG_DISCRETISATION || DEBUG) {
	    printf("distance : %Lf\n",distance);
	}
	return distance;
}

long double magicDistDiscrete(const int *X1, const int taille_X1, const int *X2, const int taille_X2) 
{  int j, i, Kp, Kg;
    int *Xp, *Xg;
    initializeXpXg( &Kp, &Kg , &Xp, &Xg, X1, X2, taille_X1, taille_X2);
    if (DEBUG) printf("Initialisation: Kp, Kg, Xp, Xg: %d %d \n\n", Kp, Kg);
    //int nb_similaire = 0;
    int *deja_parcouru_Xp = malloc((Kp) * sizeof(int));
    assert(deja_parcouru_Xp != NULL);
    //int *a_parcourir_Xg; // = malloc(Kg * sizeof(char));
    //int *a_parcourir_Xp;
    long double distance = 0;
    long double maillon_different;
    int *maillon_considere = NULL;
    int *T = NULL;

    for (j = 0; j<Kp; j++) // on s'interesse au sous-ensemble a J+1 element: si J = 0, on regarde un par un.
    {
        int taille_mc = j+1;
        maillon_considere = malloc(taille_mc * sizeof(int));
        assert(maillon_considere != NULL);

        T = malloc((taille_mc+1)*sizeof(int));
        assert(T!=NULL);

        memcpy(deja_parcouru_Xp, Xp, j*sizeof(int));
        if (DEBUG) {
		printf( "Deja parcouru:");
			affTab(deja_parcouru_Xp, j, 1);
        }
		maillon_different = 0;

        for(i = 0; i < (Kp-j) ; i++) // on aura k-j itération possible si on regarde les éléments j+1 par j+1.
        {
            memcpy(maillon_considere, &Xp[i], taille_mc*sizeof(int));

             if (DEBUG) { 
				printf("Maillon recherche: ");
				affTab(maillon_considere, taille_mc, 1);
			}
            // on regarde si ce genre de maillon n'a pas deja été cherché:
            //if (T!=NULL) free(T);
            T = kmp_tableau(maillon_considere, taille_mc,T);
            if (kmp_recherche(T, maillon_considere, taille_mc, deja_parcouru_Xp, j+i) == -1)
            {
                long double f_occ_p = occurences(maillon_considere, taille_mc, Xp, Kp);
                long double f_occ_g = occurences(maillon_considere, taille_mc, Xg, Kg);
                long double f_Kp = Kp, f_Kg = Kg, f_j = j;
                maillon_different += f_occ_g;
                distance += patternCoefficient( taille_mc ) * fabs( f_occ_p /(f_Kp-f_j) - f_occ_g /(f_Kg-f_j) );
                if (DEBUG) {
					printf("Occurence de ");
					affTab(maillon_considere, taille_mc, 0);
					printf ("dans Xp: %.0Lf, dans Xg: %.0Lf \n", f_occ_p, f_occ_g);
					printf("Calcul: pow(2,%.0Lf)*fabs(%.0Lf/(%.0Lf) - %.0Lf/(%.0Lf)); \n", -f_j-1,f_occ_p, f_Kp-f_j,f_occ_g,f_Kg-f_j);
					printf("Distance = %Lf \n", distance);
				}
            }
            deja_parcouru_Xp[i+j] = maillon_considere[j];

            if (DEBUG) { 
				printf("Parcouru:" );
				affTab(deja_parcouru_Xp, j+i+1, 1);
			}
        }
        free(maillon_considere);
        free(T);

        maillon_different = 1- (maillon_different/(Kg-j));
        if (DEBUG) printf("Frequence des maillons non lu dans l'autre chaine: %Lf \n\n", maillon_different);
        distance +=  patternCoefficient(j+1) * maillon_different;

    }
    free(deja_parcouru_Xp);
    free(Xp); free(Xg);
    return (distance);
}

