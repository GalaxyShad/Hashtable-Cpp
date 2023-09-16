#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <ratio>

#include <map>
#include <unordered_map>

#include "dictionary.h"

typedef std::chrono::high_resolution_clock Clock;

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

#define N       100000
#define N_DIV     100

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


void testStrings() {
    Dictionary<std::string, int> dict;

    dict.add("sonic",  0)
        .add("tails",  1)
        .add("knux",   2)
        .add("shadow", 3)
        .add("silver", 4);

    dict.remove("knux");
    dict.add("shadow", 123);
    dict.printDebug();

    std::cout << "shadow=" << dict["shadow"]
              << "count=" << dict.count()
              << std::endl;
}


void testPerfomance() {
    std::cout << "My Dictionary;";

    for (size_t i = N / 10; i <= N; i += N / N_DIV) {
        auto before = Clock::now();

        Dictionary<std::string, int> dict;
        for (size_t j = 0; j < i; j++) {
            dict.add(std::to_string(j), j);
        }
        auto after = Clock::now();

        using namespace std::chrono;
        duration<double> time_span = duration_cast<duration<double>>(after - before);
        std::cout << time_span.count() << ";";
    } 
    std::cout << std::endl;
}


void testPerfomanceSTLMap() {
    std::cout << "STL map;";

    for (size_t i = N / 10; i <= N; i += N / N_DIV) {
        auto before = Clock::now();

        std::map<std::string, int> dict;
        for (size_t j = 0; j < i; j++) {
            dict[std::to_string(j)] = j;
        }
        auto after = Clock::now();

        using namespace std::chrono;
        duration<double> time_span = duration_cast<duration<double>>(after - before);
        std::cout << time_span.count() << ";";
    } 
    std::cout << std::endl;
}


void testPerfomanceSTLUnorderedMap() {
    std::cout << "Unordered STL map;";

    for (size_t i = N / 10; i <= N; i += N / N_DIV) {
        auto before = Clock::now();

        std::unordered_map<std::string, int> dict;
        for (size_t j = 0; j < i; j++) {
            dict[std::to_string(j)] = j;
        }
        auto after = Clock::now();

        using namespace std::chrono;
        duration<double> time_span = duration_cast<duration<double>>(after - before);
        std::cout << time_span.count() << ";";
    } 
    std::cout << std::endl;
}


int main() {
    testStrings();

    // testPerfomance();
    // testPerfomanceSTLMap();
    // testPerfomanceSTLUnorderedMap();

    return 0;
}