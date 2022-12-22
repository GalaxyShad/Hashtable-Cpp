#include <iostream>
#include <string>

#include "dictionary.h"

int main() {
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
        // "kupava"
    };

    for (int i = 0; i < 5; i++) {
        dict.add(strs[i], i);
        dict.printDebug();

    }

    dict.add("shadow", 123);
    // dict.remove("shadow");

    dict.printDebug();

    std::cout << dict["shadow"] << std::endl;

    std::cout << "done" << std::endl;

    return 0;
}