#pragma once

namespace Utility {
    using ll = long long;
    static_assert(sizeof(ll) == 8, "long must be 8 bytes");
    static_assert(sizeof(int) == 4, "int must be 4 bytes");

    ll cnt = 0;
    ll usedMem = 0;
}


#include <cstdlib>
void* operator new(size_t size) {
    Utility::usedMem += size;
    Utility::cnt++;
    return malloc(size);
}


#include <iostream>
#include <chrono>
#include <fstream>
#include <cassert>

namespace Utility {
    class Timer
    {
    public:
        Timer() : beg(clock_t::now()) {};
        ~Timer() {
            std::cout << std::chrono::duration_cast<second_t>(clock_t::now() - beg).count();
        };
    private:
        using clock_t = std::chrono::high_resolution_clock;
        using second_t = std::chrono::duration<double, std::ratio<1>>;
        std::chrono::time_point<clock_t> beg;
    };

    class Logger
    {
    public:
        Logger() : cerrFile("CERR_LOG.txt") {
            assert(cerrFile.is_open() && " X_ERROR ");
            std::cerr.rdbuf(cerrFile.rdbuf());
            std::cerr << "Start\n";
        }
        ~Logger() { std::cerr << "Close\n";  cerrFile.close(); };
    private:
        std::ofstream cerrFile;
    };
}

