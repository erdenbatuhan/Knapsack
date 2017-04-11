//
//  main.cpp
//  0-1 Knapsack
//
//  Created by Batuhan Erden on 02/04/2017.
//  Copyright © 2017 Batuhan Erden. All rights reserved.
//

#include <iostream>
#include <algorithm>
#define MAX_N   101

using namespace std;

int PureRecursiveKnapsack(int n, int capacity, int weights[], int values[]) {
    if (n == 0 || capacity == 0)
        return 0;
    
    if (capacity < weights[n])
        return PureRecursiveKnapsack(n - 1, capacity, weights, values);
    else
        return max(PureRecursiveKnapsack(n - 1, capacity, weights, values), values[n] + PureRecursiveKnapsack(n - 1, capacity - weights[n], weights, values));
}

int MemoryFunctionKnapsack(int M[MAX_N][MAX_N], int n, int capacity, int weights[], int values[]) {
    if (M[n][capacity] < 0) {
        if (capacity < weights[n]) {
            M[n][capacity] = MemoryFunctionKnapsack(M, n - 1, capacity, weights, values);
        } else {
            M[n][capacity] = max(MemoryFunctionKnapsack(M, n - 1, capacity, weights, values), values[n] + MemoryFunctionKnapsack(M, n - 1, capacity - weights[n], weights, values));
        }
    }
    
    return M[n][capacity];
}

int MemoryFunctionKnapsack(int n, int capacity, int weights[], int values[]) {
    int M[MAX_N][MAX_N];
    
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= capacity; j++)
            M[i][j] = -1;
    
    M[0][0] = 0;
    
    return MemoryFunctionKnapsack(M, n, capacity, weights, values);
}

int Knapsack(int n, int capacity, int weights[], int values[]) {
    int M[n + 1][capacity + 1];
    
    for (int i = 0; i <= n; i++)
        M[i][0] = 0;
    
    for (int w = 0; w <= capacity; w++)
        M[0][w] = 0;
    
    for (int i = 1; i <= n; i++)
        for (int w = 0; w <= capacity; w++)
            if (weights[i] <= w)
                M[i][w] = max(M[i - 1][w], values[i] + M[i - 1][w - weights[i]]);
            else
                M[i][w] = M[i - 1][w];
    
    return M[n][capacity];
}

void readInput(int &n, int &capacity, int weights[], int values[]) {
    freopen("/Users/batuhan/Documents/Xcode Workspace/Knapsack/0-1 Knapsack/items", "r", stdin);
    
    scanf("%d", &capacity);
    while (scanf("%d%d", &weights[n], &values[n]) == 2)
        n++;
    n--;
}

int main(int argc, const char * argv[]) {
    int n = 1, capacity = 0;
    int weights[MAX_N], values[MAX_N];
    
    readInput(n, capacity, weights, values);
    
    printf("Optimal Weight (bottom-up): %d\n", Knapsack(n, capacity, weights, values));
    printf("Optimal Weight (top-down, Memoization): %d\n", MemoryFunctionKnapsack(n, capacity, weights, values));
    printf("Optimal Weight (top-down, Pure Recursion): %d\n", PureRecursiveKnapsack(n, capacity, weights, values));
    return 0;
}

/*
 Sample items file
 -----------------
 11
 1 1
 2 6
 5 18
 6 22
 7 28
 -----------------
 */
