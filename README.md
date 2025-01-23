# distributionalDist

An R package that implements distributional distance calculations for discrete and continuous variables, based on the work presented in "Online Clustering of Processes" (Khaleghi et al., 2012).

## Overview

This package provides functions to compute distributional distances between two sequences of values, supporting both discrete and continuous data types. The implementation uses a weighted approach with 2^(-i) ponderation.

The distributional distance metric implemented in this package was introduced for online clustering of stationary ergodic processes, where it was proven to be asymptotically consistent under minimal assumptions.

## Installation

You can install the package from GitHub using:

    # install.packages("devtools")
    devtools::install_github("username/distributionalDist")

## Usage

### Discrete Data

For discrete sequences (integers):

    X1 <- as.integer(c(12, 13, 14, 12, 13, 16, 12, 13, 15, 12, 13, 16, 11, 13, 15, 12, 13, 16))
    X2 <- as.integer(c(12, 13, 14, 19, 13, 16, 12, 13, 15, 12, 13, 16, 11, 13, 15, 12, 13, 16))
    dist <- distributionalDistDiscrete(X1, X2)

### Continuous Data

For continuous sequences:

    X1 <- c(-1, 2.6, -4, 5.5, 7, 1.8)
    X2 <- c(-0.5, 2.6, -4, 5.5, 9, 1.81)
    dist <- distributionalDistContinuous(X1, X2)

    # With custom discretization bounds
    nM <- c(-5, 10)  # min and max bounds
    dist <- distributionalDistContinuous(X1, X2, nM)

## Implementation Details

- The package uses C++ (via Rcpp) for efficient computation
- For discrete data, it computes pattern frequencies using KMP algorithm
- For continuous data, it uses adaptive discretization
- Distances are weighted using a 2^(-i) scheme

## Dependencies

- Rcpp

## License

GPL (>= 2)

## Author

Jeremie Mary <jeremie.mary@gmail.com>

## References

If you use this package, please cite:

    @InProceedings{pmlr-v22-khaleghi12,
      title     = {Online Clustering of Processes},
      author    = {Khaleghi, Azadeh and Ryabko, Daniil and Mary, Jeremie and Preux, Philippe},
      booktitle = {Proceedings of the Fifteenth International Conference on Artificial Intelligence and Statistics},
      pages     = {601--609},
      year      = {2012},
      editor    = {Lawrence, Neil D. and Girolami, Mark},
      volume    = {22},
      series    = {Proceedings of Machine Learning Research},
      address   = {La Palma, Canary Islands},
      month     = {21--23 Apr},
      publisher = {PMLR},
      url       = {https://proceedings.mlr.press/v22/khaleghi12.html}
    }

The distributional distance metric implemented in this package was introduced in this paper, which presents a novel approach to online clustering of stationary ergodic processes. The paper proves the asymptotic consistency of this distance measure under minimal assumptions, making it particularly useful for time series analysis and process clustering applications.
