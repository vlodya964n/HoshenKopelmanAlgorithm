#pragma once

#include <map>

#include "../ObjectsSystem/Objects.h"

class HoshenKopelmanLattice {
private:
    perc::lattice_storage_t& labels;
    perc::L_size_t L;
    std::map<perc::cell_t, perc::cell_t> parent;
    std::map<perc::L_size_t, perc::L_size_t> volume_counts;

    inline perc::L_size_t index(
        perc::L_size_t i,
        perc::L_size_t j)
        const { return i*L + j; };
    void process();
    void calculate_volumes();

public:
    HoshenKopelmanLattice(
        perc::lattice_storage_t& lattice_,
        perc::L_size_t L_)
        : labels{lattice_}, L{L_} { process(); };
    ~HoshenKopelmanLattice() = default;

    std::map<perc::L_size_t, perc::L_size_t> get_volumes() {
        calculate_volumes();
        return volume_counts;
    };
};
