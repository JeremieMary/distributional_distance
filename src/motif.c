#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

int* kmp_tableau(int P[], int taille_P, int *T)
{
    int taille_tab = taille_P;
    //int *T = malloc((taille_tab+1)*sizeof(int));
    int i = 1;
    int j = 0;
    int c = P[j];
    T[0] = -1;
    if (taille_P == 0)
    {
        return (T);
    }
    T[1] = 0;
                   //c'est-à-dire -1
    while (i != taille_tab) {      //Tant que l'on a pas atteint la fin de la chaine
/* ATTENTION la condition suivante est fausse, contre exemple avec la chaine "ABABABAB", il faut plutot mettre if((P[i] == P[j]) && j < ((i+(i%2))/2)) */
        if (P[i] == c) {        /* Si P[i]==P[j] donc si le caractère qu'on regarde est le meme que le caractere suivant la fin
                                 * du dernier motif initial trouve */
            T[i + 1] = j + 1;   //alors le motif est continue, et on incremente i et j.
            ++j;
            ++i;
        } else if (j > 0) {     //Sinon si au caractere precedant il existe un motif
            j = T[j];           //on va regarder le motif initial precedant qui peut correspondre a la lettre oe l'on etait.
        }
        else {                  /* Sinon j=0 ou -1, i.e. si les lettres qui precedent la ieme suivie de la ieme ne peuvent
                                 * correspondre a aucun marquage initiale */
            T[i + 1] = 0;       //alors on indique qu'il n'y a aucun motif initiale pour cette lettre.
            ++i;
            j = 0;              //Cet affectation ne sert en fait que lorsque j=-1.
        }
        c = P[j];


    }

    return(T);
}


int kmp_recherche(int *T, int *P, int taille_P, int *S, int taille_S)
{
    if (taille_S == 0 || taille_P == 0)
    {
        return (-1);
    }
    // On recherche P dans S:
    int m = 0;
    int i = 0;

    // Tant que l'on a pas atteint la fin de la chaene S ou de la chaene P.
    while ((m + i) != taille_S && i != taille_P)
    {
        if (S[m + i] == P[i])
        {
                              // Si on a encore une correspondance
            i++;
                     // alors on regarde la lettre suivante
        }
        else
        {

            // sinon
            m += i - T[i];    /* la prochaine correspondance partielle possible est e T[i]
                                 lettre avant celle qu'on vient de regarder. */

            if (i > 0)
                i = T[i];     /* Puisque l'on sait que les T[i]-1 premieres lettres e partir
                                 de m sont bonne, il suffit de regarder P e partir de la T[i]eme
                                 position. Pour S on peut remarquer que on m+i est maintenant
                                 egale e (m+i-T[i])+(T[i]) avec les anciennes valeurs. Ce qui
                                 montre qu'on ne retourne pas en arriere. */
        }
    }

    //Quand on a fini de parcourir une des deux chaines

    if (i == taille_P)
    {
        //si la chaine finie est P alors on a trouve une correspondance e la place m
        return m;
    }
    else
    {                    /* Sinon c'est qu'il n'existe pas de correspondance de
                            P dans S donc on renvoie un nombre impossible */
        return (-1);    /* m est forcement le nombre de caractere de S, donc
                            m+1 est impossible. On pourrait aussi renvoyer -1 */
    }
}
