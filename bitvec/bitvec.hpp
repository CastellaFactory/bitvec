#ifndef BITVEC_BITVEC_HPP_INCLUDED
#define BITVEC_BITVEC_HPP_INCLUDED

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

namespace bitvec {

constexpr std::uint64_t SMALL_BLOCK_SIZE = 64;   // 1 << 6
constexpr std::uint64_t LARGE_BLOCK_SIZE = 512;  // 1 << 9
constexpr std::uint64_t BLOCK_RATE = 8;          // L_BLOCK_SIZE / S_BLOCK_SIZE

// template <class T,
//           template <class U, class A = std::allocator<U>> class Container>
class bitvec {
private:
    using block_type = std::uint64_t;
    std::vector<block_type> B_;  // Bit vector
    std::uint64_t size_;

public:
    bitvec() : size_{0} {}
    //
    bitvec(std::uint64_t size) : size_{size}
    {
        // この書き方だとsize == 0のときダメ
        // std::uint64_t block_num = (size - 1) / SMALL_BLOCK_SIZE + 1;
        std::uint64_t block_num =
            (size + SMALL_BLOCK_SIZE - 1) / SMALL_BLOCK_SIZE;
        B_.resize(block_num);
    }

    virtual ~bitvec() {}
    // void clear();
    // void set(std::size_t i, T v);
    void push_back(std::uint8_t v)
    {
        // size_ : 0, B_.size() : 0 -> 1(1-63まで条件を満たさない)
        // size_ : 64, B_.size() : 1 -> 2(65-127まで条件を満たさない)
        // SMALL_BLOCK_SIZEの倍数のときに条件が満たされる
        if (size_ / SMALL_BLOCK_SIZE >= B_.size()) {
            B_.push_back(0);
        }

        // どのブロックか
        std::uint64_t block_idx = size_ / SMALL_BLOCK_SIZE;
        // ブロックの中でどのビットか
        std::uint64_t rel_pos = size_ % SMALL_BLOCK_SIZE;
        // rel番目のビットだけたてる
        std::uint64_t m = 0x1ULL << rel_pos;

        if (v == 0) {
            // rel_posのビットはたてない
            B_[block_idx] &= ~m;
        }
        else {
            // rel_posのビットを立てる
            B_[block_idx] |= m;
        }
        ++size_;
    }

    void push_back_bits(std::uint64_t x, std::uint64_t len)
    {
        // blocks.push_back(v);
    }
    std::uint8_t operator[](std::uint64_t idx) const
    {
        if (idx >= size_) {
            std::cerr << "Out of range\n";
        }
        return (B_[idx / SMALL_BLOCK_SIZE]
                & (0x1ULL << (idx % SMALL_BLOCK_SIZE)))
               != 0;
    }
    void print()
    {
        std::cout << "size: " << size_ << std::endl;
        for (auto& v : B_)
            std::cout << static_cast<std::bitset<SMALL_BLOCK_SIZE>>(v)
                      << std::endl;
    }
};
}  // namespace bitvec

#endif  // BITVEC_BITVEC_HPP_INCLUDED
