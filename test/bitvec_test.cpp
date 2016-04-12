#include "../bitvec/bitvec.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

int main()
{
    /* bitvec<std::uint8_t, std::vector> bv; */
    bv.push_back(1);
    bv.push_back(0);
    bv.print();
}
