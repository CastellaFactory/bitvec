#ifndef BITVEC_BITVEC_HPP_INCLUDED
#define BITVEC_BITVEC_HPP_INCLUDED

#include <bitset>
#include <bitvec/common_types.hpp>
#include <boost/optional.hpp>
#include <iostream>
#include <memory>

namespace bitvec {

constexpr u64 SMALL_BLOCK_SIZE = 64;   // 1 << 6
constexpr u64 LARGE_BLOCK_SIZE = 512;  // 1 << 9
constexpr u64 BLOCK_RATE = LARGE_BLOCK_SIZE / SMALL_BLOCK_SIZE;

template <template <class, class> class Container,
          class Alloc = std::allocator<u64>>
class bitvec {
private:
    Container<u64, Alloc> B_;  // Bit vector
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

    boost::optional<u8> operator[](u64 idx) const
    {
        if (idx >= size_) {
            return boost::none;
        }
        u64 block_idx = idx / SMALL_BLOCK_SIZE;
        u64 offset = idx % SMALL_BLOCK_SIZE;

        return (B_[block_idx] & (0x1ULL << (offset))) != 0;
    }

    boost::optional<u64> get_nth_block(u64 n)
    {
        if (n >= B_.size()) {
            return boost::none;
        }
        return B_[n];
    }

    bool empty() const { return size_ == 0; }
    u64 size() const { return size_; }
    void PP()
    {
        std::cout << "size: " << size_ << std::endl;
        std::cout << "blocks: " << B_.size() << std::endl;

        std::cout << "[\n";
        for (auto& v : B_) {
            std::cout << "  [ " << static_cast<std::bitset<SMALL_BLOCK_SIZE>>(v)
                      << " ]" << std::endl;
        }
        std::cout << "]" << std::endl;
    }
};
}  // namespace bitvec

#endif  // BITVEC_BITVEC_HPP_INCLUDED
