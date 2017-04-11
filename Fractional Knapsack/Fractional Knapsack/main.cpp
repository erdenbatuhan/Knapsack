//
//  main.cpp
//  Fractional Knapsack
//
//  Created by Batuhan Erden on 31/03/2017.
//  Copyright © 2017 Batuhan Erden. All rights reserved.
//

#include <iostream>
#include <algorithm>
#define MAX_N   101
#define INF     std::numeric_limits<int>::infinity()

struct Spice {
    double weight, value, density;
};

struct DensityComparator {
    bool operator() (const Spice &a, const Spice &b) {
        return a.density > b.density;
    }
};

double Knapsack(int n, int capacity, double weights[], double values[]) {
    Spice spices[MAX_N];
    double M[MAX_N], collected = 0;
    
    for (int i = 0; i <= n; i++) {
        spices[i].weight = weights[i];
        spices[i].value = values[i];
        spices[i].density = values[i] / weights[i];
    }
    
    std::sort(spices, spices + n + 1, DensityComparator());
    
    for (int i = 1; i <= n; i++) {
        if (collected + spices[i].weight > capacity) {
            double partial = (capacity - collected) * spices[i].density;
            M[i] = partial + M[i - 1];
            
            return M[i];
        }
        
        M[i] = spices[i].value + M[i - 1];
        collected += spices[i].weight;
    }
    
    return M[n];
}

void readInput(int &n, int &capacity, double weights[], double values[]) {
    freopen("/Users/batuhan/Documents/Xcode Workspace/Knapsack/Fractional Knapsack/items", "r", stdin);
    
    scanf("%d", &capacity);
    while (scanf("%lf%lf", &weights[n], &values[n]) == 2)
        n++;
    n--;
}

int main(int argc, const char * argv[]) {
    int n = 1, capacity = 0;
    double weights[MAX_N], values[MAX_N];
    weights[0] = INF, values[0] = INF;
    
    readInput(n, capacity, weights, values);
    
    printf("Optimal Weight: %f\n", Knapsack(n, capacity, weights, values));
    return 0;
}

/*
 Sample items file
 -----------------
 17
 3 4
 4 5
 7 10
 8 11
 9 13
 -----------------
 */
