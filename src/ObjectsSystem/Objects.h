
#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "../utils.h"

class RandomFillingLattice {
private:
    perc::L_size_t L;
    perc::probability_t target_prob;
    perc::probability_t real_prob;
    perc::lattice_storage_t lattice;

    void create_lattice();

public:
    RandomFillingLattice(perc::L_size_t L_, perc::probability_t prob_)
        : L{L_}, target_prob{prob_}, real_prob{target_prob}, lattice(L_*L_, 0) { create_lattice(); };
    ~RandomFillingLattice() = default;

    perc::lattice_storage_t& get_lattice() {
        return lattice;
    };
    perc::L_size_t get_linear_size() {
        return L;
    }
    perc::probability_t get_real_prob() {
        return real_prob;
    };
    perc::probability_t get_target_prob() {
        return target_prob;
    }
    pybind11::array_t<perc::cell_t> to_numpy();
};
