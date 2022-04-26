//
// Created by b on 3/22/22.
//

#ifndef GRAPHICSASSIGN2_VEC_2_HPP
#define GRAPHICSASSIGN2_VEC_2_HPP
#include <string>
#include <cmath>
#include "mat_mul.hpp"

#define VEC2G template<typename T>

VEC2G
struct Vec2
{
    T x,
      y,
      h = 1; // Homogenous coordinates

    Vec2() = default;
    Vec2(T horizontal, T vertical);
    std::string to_string_rep();

    bool operator==(Vec2<T> &right);
};

// Unfortunately, template C++ requires all code visible to the calling unit
// I don't like putting code in headers but here we are

VEC2G
Vec2<T>::Vec2(T horizontal, T vertical): x{ horizontal }, y{ vertical } {}

VEC2G
std::string Vec2<T>::to_string_rep()
{
    std::string rep = std::string();
    rep = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    return rep;
}

VEC2G
bool Vec2<T>::operator==(Vec2<T> &right)
{
    if (x == right.x && y == right.y)
        return true;

    return false;
}

VEC2G
Vec2<T> vec2_homogenous_transform(T (&matrix)[3][3], const Vec2<T>& vec)
{
    T result[3][1];
    T temp_arr[3][1] = { { vec.x },
                         { vec.y },
                         { vec.h } };

    matrix_multiply<T, 3, 3, 3, 1>(matrix, temp_arr, result); // No need to check return values as arguments are static

    return Vec2<T>(result[0][0], result[1][0]);
}

#endif //GRAPHICSASSIGN2_VEC_2_HPP
