#include<iostream>
#include<cstdlib>
#include"MazeSolutions.h"
#define N 92

using namespace std;

int L[N], R[N];

void Eller(int m, int n) {
    char pat[3] = {};

    int M = m, N1 = n;

    for (int i = 0; i < n; i++) {
        //printf("__");
        std::cout << "__";
        Maze[0][i] = 1;
        Maze[0][i + n] = 1;
        L[i] = R[i] = i;
    }
    L[n] = n - 1;


    //Maze[0][2 * N1 - 1] = 1;
    Maze[0][2 * N1] = 1;
    //printf("_\n|");
    std::cout << "_" << std::endl << "|";
    Maze[1][0] = Maze[2][0] = 1;


    int level = 2;

    while (m >= 1) {
        for (int i = 0; i < n; i++) {
            int j = L[i + 1];
            if (i != j && rand() % 3) {
                L[R[j] = R[i]] = j;
                L[R[i] = i + 1] = i;
                pat[1] = '_';
                if ((i + 1) * 2 <= N1 * 2 + 1) {
                    Maze[level][(i + 1) * 2] = 1;
                    Maze[level - 1][(i + 1) * 2] = 0;
                }
            }
            else {
                pat[1] = '|';
                Maze[level][(i + 1) * 2] = 1;
                Maze[level - 1][(i + 1) * 2] = 1;
            }
            if (i != L[i] && rand() % 3) {
                L[R[i]] = L[i];
                R[L[i]] = R[i];
                L[i] = R[i] = i;
                pat[0] = '_';
                Maze[level][(i + 1) * 2 - 1] = 1;
                Maze[level - 1][(i + 1) * 2 - 1] = 0;
            }
            else {
                pat[0] = ' ';
                Maze[level][(i + 1) * 2 - 1] = 0;
                Maze[level - 1][(i + 1) * 2 - 1] = 0;
            }
            //printf(pat);
            cout << pat[0] << pat[1];
        }
        //printf("\n|");
        std::cout << endl << "|";
        level += 2;
        if (level < (M + 1) * 2 + 1) {
            Maze[level][0] = 1;
            Maze[level - 1][0] = 1;
        }
        m--;
    }

    pat[0] = '_';

    for (int i = 1; i < N1 * 2 + 1; i += 2) {
        Maze[(M + 1) * 2 - 1][i] = 0;
        Maze[(M + 1) * 2][i] = 1;
    }

    for (int i = 0; i < n; i++) {
        int j = L[i + 1];
        if (i != j && (i == L[i] || rand() % 3)) {
            L[R[j] = R[i]] = j;
            L[R[i] = i + 1] = i;
            pat[1] = '_';
            Maze[(M + 1) * 2][(i + 1) * 2] = 1;
            Maze[(M + 1) * 2 - 1][(i + 1) * 2] = 0;
        }
        else {
            pat[1] = '|';
            if ((i + 1) * 2 <= N1 * 2 + 1) {
                Maze[(M + 1) * 2 - 1][(i + 1) * 2] = 1;
                Maze[(M + 1) * 2][(i + 1) * 2] = 1;
            }
        }
        L[R[i]] = L[i];
        R[L[i]] = R[i];
        L[i] = R[i] = i;
        //printf(pat);
        std::cout << pat[0] << pat[1];
    }
}