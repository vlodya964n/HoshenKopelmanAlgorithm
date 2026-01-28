#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <map>
#include <pybind11/eigen.h>
#include <Eigen/Dense>
#include "alghoritm.h"
#include <memory>

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
}
