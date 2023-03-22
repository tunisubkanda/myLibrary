/**
 * @file bit.hpp
 * @brief bit用関数
 * @version 0.1
 * @date 2023-03-22
 */
#ifndef MYLIBRARY_BIT_HPP
#define MYLIBRARY_BIT_HPP

#include <cstdint>

#define count_bits_on_one_byte(n) (0x0f & ((0x33 & ((0x55 & (n)) + ((0xaa & (n)) >> 1))) + ((0xcc & ((0x55 & (n)) + ((0xaa & (n)) >> 1))) >> 2))) + ((0xf0 & ((0x33 & ((0x55 & (n)) + ((0xaa & (n)) >> 1))) + ((0xcc & ((0x55 & (n)) + ((0xaa & (n)) >> 1))) >> 2))) >> 4)

struct Bit {
    std::uint64_t x;

    Bit(std::uint64_t v) noexcept;

    short count() noexcept;
    bool isOne() noexcept;
    short lsb() noexcept;
    short msb() noexcept;
};

inline Bit::Bit(std::uint64_t v) noexcept
    : x(v) {}

inline short Bit::count() noexcept {
    x = (x & 0x5555555555555555) + ((x >> 1) & 0x5555555555555555);
    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
    x = (x & 0x0f0f0f0f0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f0f0f0f0f);
    x = (x & 0x00ff00ff00ff00ff) + ((x >> 8) & 0x00ff00ff00ff00ff);
    x = (x & 0x0000ffff0000ffff) + ((x >> 16) & 0x0000ffff0000ffff);
    x = (x & 0x00000000ffffffff) + ((x >> 32) & 0x00000000ffffffff);
    return x;
}

inline bool Bit::isOne() noexcept {
    return ((count() == 1) ? true : false);
}

inline short Bit::lsb() noexcept {  //要素 32まで
    if(x == 0) return 0;  // 例外処理がいるかも...
    x |= (x << 1);
    x |= (x << 2);
    x |= (x << 4);
    x |= (x << 8);
    x |= (x << 16);
    x |= (x << 32);
    return 64 - count();
}

inline short Bit::msb() noexcept {
    if(x == 0) return 0;  // 例外処理がいるかも...
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    x |= (x >> 32);
    return count() - 1;
}

#endif /* MYLIBRARY_BIT_HPP */
