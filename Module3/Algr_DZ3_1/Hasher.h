//
// Created by liza_shch on 14.12.18.
//

#ifndef ALGR_DZ3_1_HASHER_H
#define ALGR_DZ3_1_HASHER_H

#include <cmath>

template <class T>
int hash1_(const T& item, const int m);


template<class T>
int hash2_(const T&item, const int m);

template <>
int hash1_<int>(const int& item, const int m);
template <>
int hash2_<int>(const int& item, const int m);

template <class T>
int hash(const T& item, const int m, int i) {
    return (hash1_(item, m) + hash2_(item, m) * i) % m;
}


template <class T>
class Hasher {
public:
    int operator()(const T& item, int m, int i) const { return hash(item, m, i); }
};


#endif //ALGR_DZ3_1_HASHER_H
