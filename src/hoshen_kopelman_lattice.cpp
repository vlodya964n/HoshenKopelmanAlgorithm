#include <pybind11/pybind11.h>

#include "ObjectsSystem/Objects.h"
#include "PercolationSystem/percolation_system.h"
#include "ComputePercolation/compute_percolation.h"

namespace py = pybind11;

PYBIND11_MODULE(hoshen_kopelman_lattice, m) {
    py::class_<RandomFillingLattice>(m, "RandomFillingLattice")
        .def(py::init<perc::L_size_t, perc::probability_t>())
        .def("to_numpy", &RandomFillingLattice::to_numpy)
        .def("get_L", &RandomFillingLattice::get_linear_size)
        .def("get_real_prob", &RandomFillingLattice::get_real_prob)
        .def("get_target_prob", &RandomFillingLattice::get_target_prob);
    py::class_<LatticeSitesPercolation>(m, "LatticeSitesPercolation")
        .def(py::init<RandomFillingLattice&, bool>(),
            py::arg("lattice"),
            py::arg("need_clusters_volumes") = false,
            py::keep_alive<1, 2>())
        .def("to_numpy", &LatticeSitesPercolation::to_numpy)
        .def("get_L", &LatticeSitesPercolation::get_linear_size)
        .def("get_real_prob", &LatticeSitesPercolation::get_real_prob)
        .def("get_target_prob", &LatticeSitesPercolation::get_target_prob);
    py::class_<NonPeriodicBoundsLattice>(m, "NonPeriodicBoundsLattice")
        .def(py::init<LatticeSitesPercolation&>())
        .def("is_percolation", &NonPeriodicBoundsLattice::is_percolation)
        .def("get_cluster_volume", &NonPeriodicBoundsLattice::get_cluser_volume);
}
