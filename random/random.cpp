#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <algorithm>

const size_t MB = 1024 * 1024;
using namespace std::chrono;

void die(const char *msg, bool printErrno) {
    std::cerr << msg << "\n";
    exit(1);
}

void print_time_diff(time_point<high_resolution_clock> start,
                     time_point<high_resolution_clock> end) {
    auto diff = end - start;
    std::cout << "time " << duration<double, std::nano> (diff).count() << "\n";
}

void print_time_diff_ms(time_point<high_resolution_clock> start,
                        time_point<high_resolution_clock> end) {
    auto diff = end - start;
    std::cout << "time " << duration<double, std::milli> (diff).count() << " ms\n";
}

int main(int argc, char *argv[]) {
    if (argc != 2)
        die("Need MB of integers for linear access", false);

    long size = std::stoi(argv[1]) * MB;
    long numInts = size / sizeof(int);

    std::cout << "Will access " << numInts << " integers (" << size / MB << " MB) linearly\n";
    std::vector<int> v(numInts);

    // Fill the vector with random integers
    std::srand(std::time(0));
    std::generate(v.begin(), v.end(), std::rand);

    // Create a random access pattern
    std::vector<int> accessPattern(numInts);
    for (int i = 0; i < numInts; ++i) {
        accessPattern[i] = std::rand() % numInts;
    }

    time_point<high_resolution_clock> start, end;
    start = high_resolution_clock::now();

    for (long i = 0; i < numInts; ++i) {
        sum += v[accessPattern[i]];
    }

    end = high_resolution_clock::now();
    print_time_diff_ms(start, end);

    return 0;
}
