// By: Gonçalo Leão

#include "exercises.h"
#include <iostream>

bool changeMakingGreedy(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    //TODO...
    unsigned int curr = 0;
    unsigned int total_possible = 0;

    for (int i = 0; i < n; i++) {
        usedCoins[i] = 0;
        total_possible += (C[i] * Stock[i]);
        std::cout << total_possible << std::endl;
    }

    if (total_possible < T) return false;

    for (unsigned int i = n - 1; i >= 0; i--) {
        while (Stock[i] > 0) {

            if (curr + C[i] > T) break;

            curr += C[i];
            Stock[i]--;
            usedCoins[i]++;
            /*std::cout << "i => " << i << std::endl;
            std::cout << "--------------------" << std::endl;
            std::cout << "Curr => " << curr << std::endl;*/

            if (curr == T) return true;
        }
    }
    return curr == T;
    return false;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex4, hasGreedyChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGreedy(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingGreedy(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP1_Ex4, hasNoGreedyChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGreedy(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingGreedy(C,Stock,n,1,usedCoins), false);
}