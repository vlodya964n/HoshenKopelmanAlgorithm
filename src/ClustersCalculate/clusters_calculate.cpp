#include "clusters_calculate.h"

#include <algorithm>

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


UnionFind::UnionFind(int n) {
    parent.resize(n);
    size.resize(n);

    for(int i=0;i<n;i++) {
        parent[i] = i;
        size[i] = 1;
    }
}

int UnionFind::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void UnionFind::unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) { return; }

    if (size[a] < size[b]) {
        std::swap(a,b);
    }

    parent[b] = a;
    size[a] += size[b];
}

int UnionFind::get_size(int x) {
    x = find(x);
    return size[x];
}

std::vector<int> ClusterFinder::find_clusters() {
    int N = sys.get_centers().size();

    UnionFind uf(N);

    double R = 2*(sys.get_r() + sys.get_shell());
    double R2 = R*R;

    const auto& c = sys.get_centers();

    for(int i=0;i<N;i++) {
        for(int j=i+1;j<N;j++) {
            double dx = c[i].x - c[j].x;
            double dy = c[i].y - c[j].y;

            if(dx*dx + dy*dy <= R2)
                uf.unite(i,j);
        }
    }

    std::vector<int> labels(N);

    for(int i=0;i<N;i++) {
        labels[i] = uf.find(i);
    }

    return labels;
}
