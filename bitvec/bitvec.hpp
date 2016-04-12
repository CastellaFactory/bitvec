#ifndef BITVEC_BITVEC_HPP_INCLUDED
#define BITVEC_BITVEC_HPP_INCLUDED

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>

namespace bitvec {

constexpr std::uint64_t S_BLOCK_SIZE = 64;   // 1 << 6
constexpr std::uint64_t L_BLOCK_SIZE = 512;  // 1 << 9
constexpr std::uint64_t BLOCK_RATE = 8;      // L_BLOCK_SIZE / S_BLOCK_SIZE

// template <class T,
//           template <class U, class A = std::allocator<U>> class Container>
class bitvec {
private:
    using block_type = std::uint64_t;
    std::vector<block_type> B_;  // Bit vector
    std::uint64_t size_;
    // Container<T> blocks;

public:
    // bitvec();
    //
    // bitvec(std::size_t size);

    // virtual ~bitvec();

    // void clear();
    // void set(std::size_t i, T v);
    void push_back(std::uint8_t v) { blocks.push_back(v); };
    void push_back_bits(std::uint64_t x, std::uint64_t len)
    {
        blocks.push_back(v);
    };
    // T operator[](std::size_t idx) const;
    void print()
    {
        for (auto& v : blocks)
            std::cout << static_cast<unsigned>(v) << ' ';
        std::cout << std::endl;
    }
};
}  // namespace bitvec

#endif  // BITVEC_BITVEC_HPP_INCLUDED
