#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <map>
#include <pybind11/eigen.h>
#include <Eigen/Dense>
#include "alghoritm.h"
#include <memory>

#include "ObjectsSystem/Objects.h"
#include "PercolationSystem/percolation_system.h"

namespace py = pybind11;

static std::unique_ptr<py::HoshenKopelmanLattice> alghoritm = std::make_unique<py::HoshenKopelmanLattice>();

void process(py::array_t<int> arr) {
    alghoritm->setData(arr);
    alghoritm->process();
}

std::map<int, int> get_volumes() {
    alghoritm->calculateClusterVolumes();
    return alghoritm->getVolumes();
}

PYBIND11_MODULE(hoshen_kopelman_lattice, m) {
    m.doc() = "Hoshen Kopelman Lattice Alghoritm C++ python module";
    m.def("process", &process, "Calculate Clusters on System");
    m.def("get_volumes", &get_volumes, "Calulate Cluster Volumes Counts");
    py::class_<RandomFillingLattice>(m, "RandomFillingLattice")
        .def(pybind11::init<perc::L_size_t, perc::probability_t>())
        .def("to_numpy", &RandomFillingLattice::to_numpy)
        .def("get_L", &RandomFillingLattice::get_linear_size)
        .def("get_real_prob", &RandomFillingLattice::get_real_prob)
        .def("get_target_prob", &RandomFillingLattice::get_target_prob);
    py::class_<LatticeSitesPercolation>(m, "LatticeSitesPercolation")
        .def(pybind11::init<RandomFillingLattice&, bool>(),
            py::arg("lattice"),
            py::arg("need_clusters_volumes") = false,
            py::keep_alive<1, 2>())
        .def("to_numpy", &LatticeSitesPercolation::to_numpy)
        .def("get_L", &LatticeSitesPercolation::get_linear_size)
        .def("get_real_prob", &LatticeSitesPercolation::get_real_prob)
        .def("get_target_prob", &LatticeSitesPercolation::get_target_prob);
}
