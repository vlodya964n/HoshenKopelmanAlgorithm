#pragma once

#include <map>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "../utils.h"
#include "../ObjectsSystem/Objects.h"

class LatticeSitesPercolation {
private:
    RandomFillingLattice& lattice_obj;
    bool need_clusters_volumes;
    std::map<perc::L_size_t, perc::L_size_t> volume_counts;

    void calculate_clusters();

public:
    LatticeSitesPercolation(RandomFillingLattice& lattice_, bool need_clusters_volumes_=false)
        : lattice_obj{lattice_},
        need_clusters_volumes{need_clusters_volumes_} { calculate_clusters(); };
    ~LatticeSitesPercolation() = default;

    std::map<perc::L_size_t, perc::L_size_t> get_volumes() {
        return volume_counts;
    }
    perc::lattice_storage_t& get_lattice() {
        return lattice_obj.get_lattice();
    };
    perc::L_size_t get_linear_size() {
        return lattice_obj.get_linear_size();
    };
    perc::probability_t get_target_prob() {
        return lattice_obj.get_target_prob();
    };
    perc::probability_t get_real_prob() {
        return lattice_obj.get_real_prob();
    };
    pybind11::array_t<perc::cell_t> to_numpy() {
        return lattice_obj.to_numpy();
    }
};
