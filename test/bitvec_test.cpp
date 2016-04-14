#include <bitvec/bitvec.hpp>
#include <iostream>
#include <vector>

int main()
{
    bitvec::bitvec<std::vector> bv;
    // for (auto i = 0; i < 64; ++i) {
    //     bv.push_back(1);
    // }
    bv.push_back(0);
    bv.push_back_bits(0xFFFFFFFFFFFFFFFFULL, 64);
    bv.PP();
}
