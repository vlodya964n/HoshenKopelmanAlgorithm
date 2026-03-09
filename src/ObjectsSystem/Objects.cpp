#include "Objects.h"

#include <cmath>

#include "../utils.h"

using namespace perc;

void RandomFillingLattice::create_lattice() {
    L_size_t objects_number = round(L * L * target_prob);
    for (L_size_t i = 0; i < objects_number; ++i) {
        L_size_t row_num, col_num;
        do {
            row_num = random_linear_value(0, L-1);
            col_num = random_linear_value(0, L-1);
        } while (lattice[row_num * L + col_num] != 0);
        lattice[row_num * L + col_num] = 1;
    }
};

pybind11::array_t<cell_t> RandomFillingLattice::to_numpy() {
    return pybind11::array_t<cell_t>(
        {static_cast<pybind11::ssize_t>(L),
         static_cast<pybind11::ssize_t>(L)},
        {static_cast<pybind11::ssize_t>(sizeof(cell_t) * L),
         static_cast<pybind11::ssize_t>(sizeof(cell_t))},
        lattice.data(),
        pybind11::cast(this)
    );
}



bool CircleSystem::intersects_existing(double x, double y) {
    for (auto& c : centers) {
        double dx = x - c.x;
        double dy = y - c.y;

        double d2 = dx*dx + dy*dy;

        if (d2 < (2*radius)*(2*radius)) {
            return true;
        }
    }

    return false;
}

void CircleSystem::generate() {
    compute_particle_number();
    centers.clear();

    while (centers.size() < N) {
        double x = perc::random_real(L);
        double y = perc::random_real(L);

        if (!intersects_existing(x,y)) {
            centers.push_back({x,y});
        }
    }
}

void CircleSystem::compute_particle_number() {
    double area = L * L;
    double circle_area = M_PI * radius * radius;

    N = (int)(prob * area / circle_area);
}
