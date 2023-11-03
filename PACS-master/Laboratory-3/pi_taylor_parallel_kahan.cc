#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <thread>
#include <utility>
#include <vector>

using my_float = float;

// Kahan summation algorithm
my_float kahan_sum(std::vector<my_float> &input) {
    my_float sum = 0.0;
    my_float c = 0.0;

    for (my_float &x : input) {
        my_float y = x - c;
        my_float t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }

    return sum;
}

void
pi_taylor_chunk(std::vector<my_float> &output,
        size_t thread_id, size_t start_step, size_t stop_step) {

    my_float pi_chunk = 0.0;
    int sign;

    if (start_step % 2 == 0) sign = 1;
    else sign = -1;

    my_float sum = 0.0;
    my_float c = 0.0;

    for(size_t i=start_step; i<stop_step; i++){
        my_float y = sign/(2.0*i+1.0) - c;
        my_float t = sum + y;
        c = (t - sum) - y;
        sum = t;
        sign = -sign;
    }
    

    pi_chunk = sum * 4;
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

    auto chunk_size = steps / threads;
    size_t start_step = 0;
    size_t stop_step = std::min(chunk_size, steps);

    for (size_t i = 0; i < threads; i++) {
        if(i==threads-1 && stop_step < steps) stop_step=steps;

        pi_threads[i] = std::thread(pi_taylor_chunk, std::ref(pi_chunks), i, start_step, stop_step);
        start_step = stop_step;
        stop_step = std::min(stop_step+chunk_size,steps);
        
    }

    for (auto &t : pi_threads) {
        t.join();
    }

    // Final summation
    pi = kahan_sum(pi_chunks);


    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "For " << steps << ", pi value: "
        << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
        << pi << std::endl;

    std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
}

