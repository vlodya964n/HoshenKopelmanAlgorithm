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
