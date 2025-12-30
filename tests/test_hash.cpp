
#include <cassert>
#include <iostream>

#include "Hash.hpp"


int main() {
    std::cout << "Running tests..." << std::endl;

    Hash hash;
    hash.Update("Hello, world!");
    auto digest = hash.Digest();
    assert(digest == "123");

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
