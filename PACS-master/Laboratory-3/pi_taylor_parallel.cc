#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <thread>
#include <utility>
#include <vector>

using my_float = long double;

void
pi_taylor_chunk(std::vector<my_float> &output,
        size_t thread_id, size_t start_step, size_t stop_step) {

    my_float pi_chunk = 0.0;
    int sign;

    if (start_step % 2 == 0) sign = 1;
    else sign = -1;

    for(size_t i=start_step; i<stop_step; i++){
        pi_chunk += sign/(2.0*i+1.0);
        sign = -sign;
    }

    pi_chunk *= 4;
    output[thread_id] = pi_chunk;

}

std::pair<size_t, size_t>
usage(int argc, const char *argv[]) {
    // read the number of steps from the command line
    if (argc != 3) {
        std::cerr << "Invalid syntax: pi_taylor <steps> <threads>" << std::endl;
        exit(1);
    }

    size_t steps = std::stoll(argv[1]);
    size_t threads = std::stoll(argv[2]);

    if (steps < threads ){
        std::cerr << "The number of steps should be larger than the number of threads" << std::endl;
        exit(1);
    }

    return std::make_pair(steps, threads);
}

int main(int argc, const char *argv[]) {

    auto start = std::chrono::high_resolution_clock::now();

    auto ret_pair = usage(argc, argv);
    auto steps = ret_pair.first;
    auto threads = ret_pair.second;

    my_float pi;

    std::vector<std::thread> pi_threads(threads);
    std::vector<my_float> pi_chunks(threads);

    for (size_t i = 0; i < threads; i++) {
        size_t start_step = i * (steps / threads);
        size_t stop_step = (i + 1) * (steps / threads);
        pi_threads[i] = std::thread(pi_taylor_chunk, std::ref(pi_chunks), i, start_step, stop_step);
    }

    for (auto &t : pi_threads) {
        t.join();
    }

    // Final summation
    pi = std::accumulate(pi_chunks.begin(), pi_chunks.end(), 0.0);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "For " << steps << ", pi value: "
        << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
        << pi << std::endl;

    std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
}

