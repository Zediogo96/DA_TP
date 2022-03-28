#include "exercises.h"


#include <queue>

Labyrinth::Labyrinth(int values[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            labyrinth[i][j] = values[i][j];
}

#include <iostream>

void  Labyrinth::print() const {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::cout << labyrinth[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Labyrinth::findGoal_Non_Recursive(int x, int y) {
    using namespace std;
    //TODO

    queue<pair<int,int>> q;

    q.push(make_pair(1,1));

    pair<int,int> p = q.front();

    if (labyrinth[p.first][p.second] != 0) labyrinth[p.first][p.second] = -1;

    while (!q.empty()) {

        print();
        cout << "----------------------" << endl;

        /** dequeue topmost element of the queue; **/
        pair<int,int> p = q.front();
        q.pop();

        /** -1 equals marked as visited **/
        if (labyrinth[p.first][p.second] != 0) labyrinth[p.first][p.second] = -1;

        if (labyrinth[p.first][p.second + 1] == 2) return true;

        else {
            // UP
            if (labyrinth[p.first][p.second - 1] == 1) q.emplace(make_pair(p.first, p.second-1));
            // DOWN
            if (labyrinth[p.first][p.second + 1] == 1) q.emplace(make_pair(p.first, p.second+1));
            // LEFT
            if (labyrinth[p.first - 1][p.second] == 1) q.emplace(make_pair(p.first - 1, p.second));
            // RIGHT
            if (labyrinth[p.first + 1][p.second] == 1) q.emplace(make_pair(p.first + 1, p.second));
        }
    }
    return false;
}

bool Labyrinth::findGoal(int x, int y) {

    visited[x][y] = true;

    if (labyrinth[x][y] == 2) return true;

    if (!visited[x - 1][y] && labyrinth[x - 1][y] != 0) findGoal(x - 1, y);
    if (!visited[x + 1][y] && labyrinth[x + 1][y] != 0) findGoal(x + 1, y);
    if (!visited[x][y - 1] && labyrinth[x][y - 1] != 0) findGoal(x, y - 1);
    if (!visited[x][y + 1] && labyrinth[x][y + 1] != 0) findGoal(x, y + 1);

    return false;

}

void Labyrinth::initializeVisited() {
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            visited[i][j] = false;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex1, testLabyrinthPossible) {
    // This test assumes that the mazes only have a possible path to the exit
    int lab1[10][10] ={
        {0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,0,1,0,0},
        {0,1,0,0,0,1,0,1,0,0},
        {0,1,1,0,1,1,1,1,1,0},
        {0,1,0,0,0,1,0,0,0,0},
        {0,1,0,1,0,1,1,1,1,0},
        {0,1,1,1,0,0,1,0,1,0},
        {0,1,0,0,0,0,1,0,1,0},
        {0,1,1,1,0,0,1,2,0,0},
        {0,0,0,0,0,0,0,0,0,0}};

    Labyrinth l1(lab1);
    bool flag;
    EXPECT_EQ(l1.findGoal(1,1),true);
}

TEST(TP2_Ex1, testLabyrinthImpossible) {
    int lab1[10][10] ={
            {0,0,0,0,0,0,0,0,0,0},
            {0,1,1,1,1,1,0,1,0,0},
            {0,1,0,0,0,1,0,1,0,0},
            {0,1,1,0,1,1,1,1,1,0},
            {0,1,0,0,0,1,0,0,0,0},
            {0,1,0,1,0,1,1,1,1,0},
            {0,1,1,1,0,0,1,0,1,0},
            {0,1,0,0,0,0,1,0,1,0},
            {0,1,1,1,0,0,0,2,0,0},
            {0,0,0,0,0,0,0,0,0,0}};

    Labyrinth l1(lab1);
    bool flag = false;
    EXPECT_EQ(l1.findGoal(1,1),false);
}