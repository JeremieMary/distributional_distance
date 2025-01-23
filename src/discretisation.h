#ifndef DISCRETISATION_H_INCLUDED
#define DISCRETISATION_H_INCLUDED


#define DEBUG_DISCRETISATION 0

typedef struct Discretisation Discretisation;

struct Discretisation {
    long double minValue;
	long double maxValue;
	int nbStored;
    struct Discretisation* left;
    struct Discretisation* right;
};

/*
int insert(long double x, Discretisation * _d);
Discretisation * initDiscretisation ( long double * X, int lenX );
*/

int minMax( const long double *X , const int lenX, long double * _mM, const int initmM );
int discretise(const long double *X, const int lenX,const long double * mM,const int nbSplit,int * _d);
int maxInterestingSplit(const long double *X,const int lenX, const long double* Y,const int lenY, const long double* mM);

#endif
