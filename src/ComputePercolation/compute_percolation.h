#pragma once

#include <vector>

#include "../utils.h"
#include "../PercolationSystem/percolation_system.h"
#include "../ObjectsSystem/Objects.h"

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


class PercolationAnalyzer {
private:
    const CircleSystem& sys;
    const std::vector<int>& labels;

    int find_percolating_cluster();
public:
    PercolationAnalyzer(const CircleSystem& sys_,
                        const std::vector<int>& labels_)
                        : sys{sys_}, labels {labels_} {};
    bool has_percolation();
    int percolation_cluster_size();
};
