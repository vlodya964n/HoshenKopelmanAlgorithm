#include "compute_percolation.h"

using namespace perc;

void NonPeriodicBoundsLattice::process() {
    cell_t percolation_cluster;


    for (L_size_t top=0; top < L; ++top ) {
        for (L_size_t bottom= L*L-1; bottom >= L * (L-1); --bottom) {
            if (labels[top] != 0 && labels[top] == labels[bottom]) {
                is_percolation_ = true;

                percolation_cluster = labels[top];
                for (L_size_t i = 0; i < L * L; ++i) {
                    if (labels[i] == percolation_cluster) {
                        cluster_volume++;
                    }
                }
                return;
            }
        }
    }
};
