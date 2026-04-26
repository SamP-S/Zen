#include <chrono>
#include <thread>
#include <iostream>
#include <filesystem>

#include "zen/core/timer.hpp"
#include "zen/core/uuid.hpp"
#include "zen/core/handle_pool.hpp"
#include "spdlog/spdlog.h"

using namespace zen::core;

int main() {
    // test timing
    Timer timer;
    timer.Reset();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    double elapsed = timer.GetElapsed();
    std::cout << "Elapsed time: " << elapsed << " seconds\n";
    
    // test uuid
    UUID uuid1;
    UUID uuid2;
    std::cout << "UUID 1: " << static_cast<int64_t>(uuid1) << "\n";
    std::cout << "UUID 2: " << static_cast<int64_t>(uuid2) << "\n";

    // test spdlog
    spdlog::info("This is an info message");
    spdlog::warn("This is a warning message");
    spdlog::error("This is an error message");

	// test handle pool
	struct X {};
	X x;
	X y;
	HandlePool<X> pool;
	H a = pool.alloc(x);
	std::cout << "A: " << a << "\n";
	H b = pool.alloc(y);
	std::cout << "B: " << b << "\n";
	pool.free(a);
	H c = pool.alloc(y);
	H d = pool.alloc(X{});
	std::cout << "c: " << c << "\n";
	std::cout << "d: " << d << "\n";
	std::cout << "x: " << &x << "\tc: " << pool.get(c) << "\n";
	std::cout << "y: " << &y << "\tb: " << pool.get(b) << "\n";
	std::cout << "_: " << "\td: " << pool.get(d) << "\n";
    return 0;
}