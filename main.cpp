#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <ratio>

#include <map>
#include <unordered_map>

#include "dictionary.h"

typedef std::chrono::high_resolution_clock Clock_t;

#define N           1000000
#define N_DIV       100
#define K           N / 100

void testStrings() {
    Dictionary<std::string, int> dict;

    std::string strs[] = {
        "sonic", 
        "tails",
        "knux",
        "shadow",
        "silver",
        // "momo",
        // "asd",
        // "arstan",
        // "aisd",
    };

    for (int i = 0; i < 5; i++) {
        dict.add(strs[i], i);
        dict.printDebug(std::cout);

    }

    dict.add("shadow", 123);
    // dict.remove("shadow");

    dict.printDebug(std::cout);

    std::cout << dict["shadow"] << std::endl;
}

void testPerfomance() {
    std::cout << "My Dictionary;";

    for (size_t i = N / 10; i <= N; i += N / N_DIV) {

        Dictionary<std::string, int> dict;
        for (size_t j = 0; j < i; j++) {
            dict.add(std::to_string(j), j);
        }

        auto before = Clock_t::now();
        for (size_t k = 0; k < K; k++) {
            dict.add(std::to_string(N + k), k);
        }
        auto after = Clock_t::now();

        using namespace std::chrono;
        duration<double> time_span = duration_cast<duration<double>>(after - before);
        std::cout << time_span.count() / K << ";";
    } 
    std::cout << std::endl;

}

void testPerfomanceSTLMap() {
    std::cout << "STL map;";

    for (size_t i = N / 10; i <= N; i += N / N_DIV) {

        std::map<std::string, int> dict;
        for (size_t j = 0; j < i; j++) {
            dict[std::to_string(j)] = j;
        }

        auto before = Clock_t::now();
        for (size_t k = 0; k < K; k++) {
            dict[std::to_string(N + k)] = k;
        }
        auto after = Clock_t::now();

        using namespace std::chrono;
        duration<double> time_span = duration_cast<duration<double>>(after - before);
        std::cout << time_span.count() / K << ";";
    } 
    std::cout << std::endl;
}


void testPerfomanceSTLUnorderedMap() {
    std::cout << "Unordered STL map;";

    for (size_t i = N / 10; i <= N; i += N / N_DIV) {

        std::unordered_map<std::string, int> dict;
        for (size_t j = 0; j < i; j++) {
            dict[std::to_string(j)] = j;
        }

        auto before = Clock_t::now();
        for (size_t k = 0; k < K; k++) {
            dict[std::to_string(N + k)] = k;
        }
        auto after = Clock_t::now();

        using namespace std::chrono;
        duration<double> time_span = duration_cast<duration<double>>(after - before);
        std::cout << time_span.count() / K << ";";
    } 
    std::cout << std::endl;
}



int main() {
    
    for (size_t i = N / 10; i <= N; i += N / N_DIV)
        std::cout << i << ";";
    std::cout << std::endl;
    
    testPerfomance();
    testPerfomanceSTLMap();
    testPerfomanceSTLUnorderedMap();

    // testStrings();

    std::cout << std::endl << "done" << std::endl;

    return 0;
}