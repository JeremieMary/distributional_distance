#include "discretisation.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


int minMax( const long double *X , const int lenX, long double * _mM, const int initmM ) {
	assert(lenX>0);
	if (initmM) {
		if (lenX == 1) {
			_mM[0] = X[0];
			_mM[1] = X[0];
			return 1;
		}
		if (X[0]>X[1]) {
			_mM[0] = X[1];
			_mM[1] = X[0];
		} else {
			_mM[0] = X[0];
			_mM[1] = X[1];
		}
	}
	int i;
	for (i=0; i<lenX; i++){
		if ( X[i] > _mM[1] ) {
			_mM[1] = X[i];
		}  else {
			if (X[i] < _mM[0] ) {
				_mM[0] = X[i];
			}
		}
	}
	return 1;
}

int discretise(const long double *X,const int lenX,const long double * mM,const int nbSplit,int * _d) {
	int i;
	for (i=0; i<lenX; i++) {
		_d[i] =  floor ( pow(2,nbSplit) * ( (X[i] - mM[0])/ (mM[1] - mM[0] ) ) );
	}
	
	return 1;
}


/*
long double random_range (long double min, long double max)
{
   return min + ((max - min) * (rand () / (long double) RAND_MAX));
}
*/

static int cmp (void const *a, void const *b)
{
   int ret = 0;
   long double const *pa = a;
   long double const *pb = b;
   long double diff = *pa - *pb;
   if (diff > 0)
   {
      ret = 1;
   }
   else if (diff < 0)
   {
      ret = -1;
   }
   else
   {
      ret = 0;
   }
   return ret;
}


	
	
int maxInterestingSplit(const long double *X,const int lenX, const long double* Y,const int lenY, const long double * mM ){
	assert( (lenX > 0) && (lenY > 0) );
	int s = sizeof(long double);
	int i = 0;
	long double * allvalues = malloc( s*(lenX+lenY) );
	memcpy(allvalues, X, lenX*s);
	memcpy(allvalues + lenX, Y, lenY*s);
	qsort(allvalues, lenX+lenY, sizeof *allvalues, cmp);
	
	if (allvalues[0] == allvalues[lenX+lenY-1]) { //Toutes les valeurs sont identiques !
	    return 1;
	};

	long double minStep = allvalues[lenX+lenY-1]-allvalues[0];
	long double c = 0;
	for (i = 0; i < lenX+lenY-1; i++) {
		//printf("%f , %f\n",allvalues[i+1],allvalues[i] );
		 c = allvalues[i+1]-allvalues[i];
		 if ( (c < minStep) && (c != 0) ) { 
			minStep = c;
			}
	}
	free(allvalues);
	//printf("%Lf\n",minStep);
	int reply = ceil(-log2((minStep / (mM[1]-mM[0]))));
	if (reply == 0) reply++;
	return reply;
	
}




/*
int insert(long double x, Discretisation * _d) {
	return 1;
}

Discretisation *  initDiscretisation ( long double * X, int lenX ){
	int i;
	Discretisation *d = malloc (sizeof ( Discretisation ));
	
	long double mM[2];
	
	if  (DEBUG_DISCRETISATION) printf("min %f ,  max %f", mM[0], mM[1]);
	
	d->minValue = mM[0];
	d->maxValue = mM[1];
	d->nbStored = 0;
	
	for (i = 0; i < lenX; i++) {
		insert(X[i] , d );
	}
	return d;
}
	
	*/
	
	
	
	
