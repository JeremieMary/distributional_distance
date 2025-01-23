#ifndef TOOL_H_INCLUDED
#define TOOL_H_INCLUDED


#define LEN(g) (sizeof(g)/sizeof(g[0]))

   /*
char* creerString(int ligne);
long double* creerTab(int ligne);
*/

int sumInt(const int *X, const int lenX); 
void affTab(const int *tab, const int taille, const int retour_chariot);
void affTabd(const long double *tab,const int taille, const int retour_chariot);
int contains(int a, const int * Array, const int len);
double partitionError(const int * GoodClasses, const int * Classes, int N,int k);


#endif
