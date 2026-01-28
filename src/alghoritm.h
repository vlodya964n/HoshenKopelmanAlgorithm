#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <map>

namespace pybind11 {
    class HoshenKopelmanLattice {
    private:
        int* _data;
        int L;
        std::map<int, int> parent;
        std::map<int, int> volume_counts;
    public:
        void setData(array_t<int> arr) {
            auto buf = arr.request();
            _data = static_cast<int*>(buf.ptr);

            L = buf.shape[0];
            parent.clear();
            volume_counts.clear();
        }

        void process() {
            auto idx = [&](int i, int j) -> int& {
                return _data[i * L + j];
            };

            auto min = [&](int i, int j) {
                return i < j ? i : j;
            };


            int index = 1;

            if (idx(0, 0) != 0) {
                parent.insert({index, index});
                idx(0, 0) = index++;
            }
            for (int i = 1; i < L; ++i) {
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

                for (int j = 1; j < L; ++j) {
                    if (idx(i, j) != 0) {
                        if (idx(i-1, j) == 0 && idx(i, j-1) == 0) {
                            parent.insert({index, index});
                            idx(i, j) = index++;
                        }
                        else if (idx(i-1, j) != 0 && idx(i, j-1) != 0) {
                            int up = parent[idx(i-1, j)],
                            left = parent[idx(i, j-1)];
                            int min_index = min(up, left);
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
            for (int i = 0; i < L; ++i) {
                for (int j = 0; j < L; ++j) {
                    if (idx(i, j) != 0) {
                        idx(i, j) = parent[idx(i, j)];
                    }
                }
            }
        }

        void calculateClusterVolumes() {
            auto idx = [&](int i, int j) -> int& {
                return _data[i * L + j];
            };

            int max_index = 0;
            for (auto [key, value] : parent) {
                max_index = max_index > value ? max_index : value;
            }
            ++max_index;
            int* index_volumes = new int[max_index];
            for (int i = 0; i < max_index; ++i) {
                index_volumes[i] = 0;
            }

            for (int i = 0; i < L; ++i) {
                for (int j = 0; j < L; ++j) {
                    index_volumes[idx(i, j)]++;
                }
            }

            for (int i = 1; i < max_index; ++i) {
                if (index_volumes[i] > 0) {
                    volume_counts.insert({index_volumes[i], 0});
                }
            }
            for (int i = 1; i < max_index; ++i) {
                if (index_volumes[i] > 0) {
                    volume_counts[index_volumes[i]]++;
                }
            }
            delete index_volumes;
        }

        std::map<int, int> getVolumes() {
            return volume_counts;
        }
    };
}
