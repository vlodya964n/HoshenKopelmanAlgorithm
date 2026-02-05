#pragma once

#include <vector>
#include <random>
#include <cstdint>

#include <pybind11/pybind11.h>

namespace perc {
    using cell_t = int;
    using L_size_t = int;
    using probability_t = double;
    using lattice_storage_t = std::vector<cell_t>;

    class Lattice {
    private:
        lattice_storage_t data;
        L_size_t L;

    public:
        Lattice(L_size_t L_) : L{L_}, data(L_*L_, 0) { };
        ~Lattice() = default;
        inline cell_t& at(size_t i, size_t j) {
            return data[i * L + j];
        }
    };

    // ---------------- Случайное целое ----------------
inline int random_linear_value(L_size_t min, L_size_t max) {
    static thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// ---------------- Случайное вещественное ----------------
inline double random_real(double min=0.0, double max=1.0) {
    static thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}

// ---------------- Случайный bool с вероятностью ----------------
inline bool random_bool(double p=0.5) {
    static thread_local std::mt19937 gen(std::random_device{}());
    std::bernoulli_distribution dist(p);
    return dist(gen);
}
}
