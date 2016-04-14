#ifndef BITVEC_BITVEC_HPP_INCLUDED
#define BITVEC_BITVEC_HPP_INCLUDED

#include <algorithm>
#include <bitset>
#include <iostream>
#include "common_types.hpp"

namespace bitvec {

constexpr u64 SMALL_BLOCK_SIZE = 64;   // 1 << 6
constexpr u64 LARGE_BLOCK_SIZE = 512;  // 1 << 9
constexpr u64 BLOCK_RATE = 8;          // L_BLOCK_SIZE / S_BLOCK_SIZE

template <template <class...> class Container>
class bitvec {
private:
    using block_type = u64;
    Container<block_type> B_;  // Bit vector
    u64 size_;

public:
    bitvec() : size_{0} {}
    bitvec(u64 size) : size_{size}
    {
        // この書き方だとsize == 0のときダメ
        // u64 block_num = (size - 1) / SMALL_BLOCK_SIZE + 1;
        u64 block_num = (size + SMALL_BLOCK_SIZE - 1) / SMALL_BLOCK_SIZE;
        B_.resize(block_num);
    }

    virtual ~bitvec() {}
    // void clear();
    // void set(std::size_t i, T v);
    void push_back(u8 v)
    {
        // size_ : 0, B_.size() : 0 -> 1(1-63まで条件を満たさない)
        // size_ : 64, B_.size() : 1 -> 2(65-127まで条件を満たさない)
        // SMALL_BLOCK_SIZEの倍数のときに条件が満たされる
        if (size_ / SMALL_BLOCK_SIZE >= B_.size()) {
            B_.push_back(0);
        }

        // どのブロックか
        u64 block_idx = size_ / SMALL_BLOCK_SIZE;
        // ブロックの中でどのビットか
        u64 offset = size_ % SMALL_BLOCK_SIZE;
        // offset番目のビットだけたてる
        u64 m = 0x1ULL << offset;

        if (v == 0) {
            // offsetの位置のビットはたてない
            B_[block_idx] &= ~m;
        }
        else {
            // offsetの位置のビットを立てる
            B_[block_idx] |= m;
        }
        ++size_;
    }

    void push_back_bits(u64 x, u64 len)
    {
        u64 block_idx = size_ / SMALL_BLOCK_SIZE;
        u64 offset = size_ % SMALL_BLOCK_SIZE;

        // 入れられるだけ入れる
        B_[block_idx] |= x << offset;

        // 残りを次のブロックに
        if (offset + len - 1 >= SMALL_BLOCK_SIZE) {
            B_.push_back(0);
            B_[block_idx + 1] |= x >> (SMALL_BLOCK_SIZE - offset);
        }
        size_ += len;
    }

    u8 operator[](u64 idx) const
    {
        if (idx >= size_) {
            std::cerr << "Out of range\n";
        }
        return (B_[idx / SMALL_BLOCK_SIZE]
                & (0x1ULL << (idx % SMALL_BLOCK_SIZE)))
               != 0;
    }

    void PP(std::string blank = "  ")
    {
        std::cout << "size: " << size_ << std::endl;
        std::cout << "blocks: " << B_.size() << std::endl;

        std::cout << "[\n";
        for (auto& v : B_) {
            std::cout << blank << "[ "
                      << static_cast<std::bitset<SMALL_BLOCK_SIZE>>(v) << " ]"
                      << std::endl;
        }
        std::cout << "]" << std::endl;
    }
};
}  // namespace bitvec

#endif  // BITVEC_BITVEC_HPP_INCLUDED
