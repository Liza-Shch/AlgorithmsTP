//
// Created by liza_shch on 14.12.18.
//

#include "Hasher.h"

template<>
int hash1_<int>(const int &item, const int m) {
    const long s = 2654435769;
    auto hash = (int) ((long) fmod(item * s, 1 << 25) >> (long) (25 - log2(m))) % m;
    return hash;
}

template <>
int hash2_<int>(const int& item, const int m) {
    const long s = 2654435769;
    auto hash = (int) ((long) fmod(item * s, 1 << 25) >> (long) (25 - log2(m)));
    hash = ( 2 * hash + 1) % m;
    return hash;
}
