# Simple header-only Hashtable on C++
Course project for "Algorithms and Data Structures". SurSU 2022.\
Check dictionary.h to see available public methods.

## 📈 Comparison with std::map and std::unordered_map
To investigate the performance of the algorithm, as well as its comparison with ready-made STL implementations, 
operations of adding elements with different keys were performed. 
A total of 100 measurements were made in increments of 10000 elements, from 100,000 to 1,000,000.

<img src="https://github.com/GalaxyShad/cpp-hashtable/assets/52833080/71137514-2e71-49e1-935b-7688373a0551" alt="drawing" width="400"/>
<img src="https://github.com/GalaxyShad/cpp-hashtable/assets/52833080/da970825-b426-4498-8078-7c87f3a4b419" alt="drawing" width="400"/>

The realization of this course work corresponds to the graph "My Dictionary"

As can be seen, the asymptotic complexity of inserting an element in this realization and STL Unordered map corresponds to the theoretical asymptotic complexity and is O(1).

In the graph, My Dictionary also shows sharp jumps in some values. This means that at these moments there is an increase in the size of the array of values.

For stl::map, the values obtained in practice do not correspond to the theoretical asymptotic complexity O(log N).

## 🧪 Examples
### Code
```cpp
#include <iostream>
#include <string>

#include "dictionary.h"

int main() {
    std::string strs[] = {
        "sonic", 
        "tails",
        "knux",
        "shadow",
        "silver",
    };

    Dictionary<std::string, int> dict;

    for (int i = 0; i < 5; i++) {
        dict.add(strs[i], i);
    }

    dict.remove("knux");
    dict.add("shadow", 123);
    dict.printDebug();

    std::cout << "shadow=" << dict["shadow"]
              << "count=" << dict.count()
              << std::endl;

    return 0;
}
```
### Output
```
Elements count: 5
Real size: 11
Fill factor: 0.454545
0;
1;
2; (tails, 1) (shadow, 123)
3;
4;
5; (sonic, 0)
6; (silver, 4)
7;
8;
9;
10;
shadow=123count=5
```
