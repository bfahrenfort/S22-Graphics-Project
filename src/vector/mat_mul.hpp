//
// Created by b on 3/22/22.
//

#ifndef GRAPHICSASSIGN2_MAT_MUL_HPP
#define GRAPHICSASSIGN2_MAT_MUL_HPP

#include <cstddef>
#include <iostream>

template<typename T, std::size_t N, std::size_t M, std::size_t J, std::size_t K>
int matrix_multiply(const T (&left)[N][M], const T (&right)[J][K], T (&result)[N][K])
{
    int sum{ };

    if(M != J)
        return -1;
    else
    {
        for (int c = 0; c < N; c++)
        {
            for (int d = 0; d < K; d++)
            {
                for (int e = 0; e < J; e++)
                {
                    sum += left[c][e] * right[e][d];
                }

                result[c][d] = sum;
                sum = 0;
            }
        }

        return 0;
    }
}

#endif //GRAPHICSASSIGN2_MAT_MUL_HPP
