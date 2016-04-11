#ifndef BITVEC_BITVEC_HPP_INCLUDED
#define BITVEC_BITVEC_HPP_INCLUDED

#include <cstdint>
#include <iostream>
#include <memory>

template <class T,
          template <class U, class A = std::allocator<U>> class Container>
class bitvec {
private:
    Container<T> blocks;

public:
    // bitvec();
    //
    // bitvec(std::size_t size);

    // virtual ~bitvec();

    // void clear();
    // void set(std::size_t i, T v);
    void push_back(T v) { blocks.push_back(v); };
    // T operator[](std::size_t idx) const;
    void print()
    {
        for (auto& v : blocks)
            std::cout << static_cast<unsigned>(v) << ' ';
        std::cout << std::endl;
    }
};

#endif  // BITVEC_BITVEC_HPP_INCLUDED
