
#pragma once

#include <vector>

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

class CircleSystem {

private:
    std::vector<perc::Point> centers;
    double L;
    double prob;
    double radius;
    double shell;
    int N;
    void generate();
    bool intersects_existing(double x, double y);
    void compute_particle_number();

public:
    CircleSystem(double L_, double prob_)
        : L{L_}, prob{prob_}, radius{0.5}, shell{0.2} {
            generate();
        };

    const std::vector<perc::Point>& get_centers() const
        { return centers; };
    int size() const { return centers.size(); }

    double get_L() const { return L; }
    double get_r() const { return radius; }
    double get_shell() const { return shell; }
};
