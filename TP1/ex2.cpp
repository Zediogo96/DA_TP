// By: Gonçalo Leão

#include "exercises.h"
#include <iostream>

int maxSubsequence(const int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    //TODO...
    int curr_sum = 0;
    int max_sum = INT16_MIN;

    for (int x = 0; x < n; x++) {
        curr_sum = 0;
        for (int y = x; y < n; y++) {
            curr_sum += A[y];
            if (curr_sum > max_sum) {
                std::cout << "i: " << i << " j: " << j << " max: " << max_sum << std::endl;
                i = x;
                j = y;
                max_sum = curr_sum;
            }
        }
    }
    return max_sum;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex2, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequence(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}