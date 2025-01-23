#include <Rcpp.h>

extern "C" {
    #include "main.h"
}

using namespace Rcpp;

// [[Rcpp::export(distributionalDistDiscrete)]]
Rcpp::NumericVector distributionalDistDiscrete(Rcpp::IntegerVector X1, Rcpp::IntegerVector X2) {
    int taille_X1 = X1.size();
    int taille_X2 = X2.size();
    
    const int* ptr_X1 = X1.begin();
    const int* ptr_X2 = X2.begin();
    
    long double result = magicDistDiscrete(ptr_X1, taille_X1, ptr_X2, taille_X2);
    return Rcpp::NumericVector::create(result);

}

// [[Rcpp::export(distributionalDistContinuous)]]
Rcpp::NumericVector distributionalDistContinuous(Rcpp::NumericVector X1, Rcpp::NumericVector X2, Rcpp::NumericVector nM) {
    
    int taille_X1 = X1.size();
    int taille_X2 = X2.size();
    
    const long double* ptr_X1 = reinterpret_cast<const long double*>(X1.begin());
    const long double* ptr_X2 = reinterpret_cast<const long double*>(X2.begin());
    const long double* ptr_nM = reinterpret_cast<const long double*>(nM.begin());
    
    long double result = magicDistContinuous(ptr_X1, taille_X1, ptr_X2, taille_X2, ptr_nM);
    return Rcpp::NumericVector::create(result);
}