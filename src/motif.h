#ifndef MOTIF_H_INCLUDED
#define MOTIF_H_INCLUDED

int* kmp_tableau(int P[], int taille_P, int * T);
int kmp_recherche(int *T, int *P, int taille_P, int *S, int taille_S);

#endif // MOTIF_H_INCLUDED
