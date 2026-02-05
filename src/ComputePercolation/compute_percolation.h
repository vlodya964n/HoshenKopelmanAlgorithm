#pragma once

#include "../utils.h"
#include "../PercolationSystem/percolation_system.h"

class NonPeriodicBoundsLattice {
private:
    perc::lattice_storage_t& labels;
    perc::L_size_t L, cluster_volume{0};
    bool is_percolation_{false};

    void process();

public:
    NonPeriodicBoundsLattice(
        LatticeSitesPercolation& lattice_)
        : labels{lattice_.get_lattice()},
        L{lattice_.get_linear_size()}
        { process(); };
    ~NonPeriodicBoundsLattice() = default;

    bool is_percolation() {
        return is_percolation_;
    };
    perc::L_size_t get_cluser_volume() {
        return cluster_volume;
    };
};
