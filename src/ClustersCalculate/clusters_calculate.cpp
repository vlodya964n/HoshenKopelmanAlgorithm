#include "clusters_calculate.h"

using namespace perc;

void HoshenKopelmanLattice::process() {
    auto idx = [&](L_size_t i, L_size_t j) -> cell_t& {
        return labels[i * L + j];
    };

     cell_t index = 1;

    if (idx(0, 0) != 0) {
        parent.insert({index, index});
        idx(0, 0) = index++;
    }
    for (L_size_t i = 1; i < L; ++i) {
        if (idx(0, i) != 0) {
            if (idx(0, i-1) == 0) {
                parent.insert({index, index});
                idx(0, i) = index++;
            }
            else {
                idx(0, i) = idx(0, i-1);
            }
        }
    }

    for (int i = 1; i < L; ++i) {
        if (idx(i, 0) != 0) {
            if (idx(i-1, 0) == 0) {
                parent.insert({index, index});
                idx(i, 0) = index++;
            }
            else {
                idx(i, 0) = idx(i-1, 0);
            }
        }

        for (L_size_t j = 1; j < L; ++j) {
            if (idx(i, j) != 0) {
                if (idx(i-1, j) == 0 && idx(i, j-1) == 0) {
                    parent.insert({index, index});
                    idx(i, j) = index++;
                }
                else if (idx(i-1, j) != 0 && idx(i, j-1) != 0) {
                    cell_t up = parent[idx(i-1, j)],
                    left = parent[idx(i, j-1)];
                    cell_t min_index = left < up ? left : up;
                    parent[up] = min_index;
                    parent[left] = min_index;
                    idx(i, j) = min_index;
                }
                else if (idx(i-1, j) != 0) {
                    idx(i, j) = idx(i-1, j);
                }
                else {
                    idx(i, j) = idx(i, j-1);
                }
            }
        }
    }

    for (auto it = parent.begin(); it != parent.end(); ++it) {
        it->second = parent[it->second];
    }
    for (L_size_t i = 0; i < L; ++i) {
        for (L_size_t j = 0; j < L; ++j) {
            if (idx(i, j) != 0) {
                idx(i, j) = parent[idx(i, j)];
            }
        }
    }
};

void HoshenKopelmanLattice::calculate_volumes() {
    auto idx = [&](int i, int j) -> int& {
        return labels[i * L + j];
    };

    cell_t max_index = 0;
    for (auto [key, value] : parent) {
        max_index = max_index > value ? max_index : value;
    }
    ++max_index;
    L_size_t* index_volumes = new L_size_t[max_index];
    for (cell_t i = 0; i < max_index; ++i) {
        index_volumes[i] = 0;
    }

    for (L_size_t i = 0; i < L; ++i) {
        for (L_size_t j = 0; j < L; ++j) {
            index_volumes[idx(i, j)]++;
        }
    }

    for (cell_t i = 1; i < max_index; ++i) {
        if (index_volumes[i] > 0) {
            volume_counts.insert({index_volumes[i], 0});
        }
    }
    for (cell_t i = 1; i < max_index; ++i) {
        if (index_volumes[i] > 0) {
            volume_counts[index_volumes[i]]++;
        }
    }
    delete index_volumes;
};
