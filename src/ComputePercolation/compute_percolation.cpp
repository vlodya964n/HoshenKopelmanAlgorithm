#include "compute_percolation.h"

#include <unordered_map>
#include <iostream>

using namespace perc;

void NonPeriodicBoundsLattice::process() {
    cell_t percolation_cluster;


    for (L_size_t top=0; top < L; ++top ) {
        for (L_size_t bottom= L*L-1; bottom >= L * (L-1); --bottom) {
            if (labels[top] != 0 && labels[top] == labels[bottom]) {
                is_percolation_ = true;

                percolation_cluster = labels[top];
                for (L_size_t i = 0; i < L * L; ++i) {
                    if (labels[i] == percolation_cluster) {
                        cluster_volume++;
                    }
                }
                return;
            }
        }
    }
};

int PercolationAnalyzer::find_percolating_cluster() {
    const auto &c = sys.get_centers();

    std::cout << "centers: " << c.size() << std::endl;
    std::cout << "labels: " << labels.size() << std::endl;

    double L = sys.get_L();
    double reach = sys.get_r() + sys.get_shell();

    std::unordered_map<int,bool> left;
    std::unordered_map<int,bool> right;

    for(size_t i=0;i<c.size();i++)
    {
        int cl = labels[i];

        if(c[i].y < reach)
            left[cl] = true;

        if(c[i].y > L - reach)
            right[cl] = true;
    }

    for(auto &p : left)
    {
        if(right[p.first])
            return p.first;
    }

    return -1;
}

bool PercolationAnalyzer::has_percolation() {
    return find_percolating_cluster() != -1;
}

int PercolationAnalyzer::percolation_cluster_size() {
    int cluster = find_percolating_cluster();

    if(cluster == -1)
        return 0;

    int count = 0;

    for(int l : labels)
        if(l == cluster)
            count++;

    return count;
}
