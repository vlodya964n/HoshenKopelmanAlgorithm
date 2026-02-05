#include "percolation_system.h"

#include <memory>

#include "../ClustersCalculate/clusters_calculate.h"

void LatticeSitesPercolation::calculate_clusters() {
    std::unique_ptr<HoshenKopelmanLattice> algorithm
        = std::make_unique<HoshenKopelmanLattice>(
            get_lattice(), get_linear_size()
        );

    if (need_clusters_volumes) {
        volume_counts = algorithm->get_volumes();
    }
};
