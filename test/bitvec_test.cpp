#include "../bitvec/bitvec.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

int main()
{
    /* bitvec<std::uint8_t, std::vector> bv; */
    bitvec::bitvec bv;
    for(auto i = 0; i < 64; ++i) {
        bv.push_back(1);
    }
    bv.print();
}
