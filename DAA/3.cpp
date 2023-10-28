/*
PS : Write a program to solve a 0-1 Knapsack problem using dynamic programming
or branch and bound strategy.
*/

#include<bits/stdc++.h>
using namespace std;


int f(int ind, int W, vector<int> &wt, vector<int> &val, vector<vector<int>> &dp) {
    if(ind == 0) {
        if(wt[0] <= W) return val[0];
        return 0;
    }

    if(dp[ind][W] != -1) return dp[ind][W];

    int notTake = 0 + f(ind-1, W, wt, val, dp);
    int take = INT_MIN;
    if(W >= wt[ind]) take = val[ind] + f(ind-1, W-wt[ind], wt, val, dp);

    return dp[ind][W] = max(take, notTake);
}

int fractionalKnapsack(int n, int W, vector<int> wt, vector<int> val) {
    vector<vector<int>> dp(n, vector<int>(W+1, -1));
    return f(n-1, W, wt, val, dp);
}

int tabulatedKnapsack(int n, int W, vector<int> wt, vector<int> val) {
    vector<vector<int>> dp(n, vector<int>(W+1, 0));

    for(int i = wt[0];i <= W;i++) dp[0][i] = val[0];

    for(int ind = 1;ind < n;ind++) {
        for(int w = 0;w <= W;w++) {
            int notTake = 0 + dp[ind-1][w];
            int take = INT_MIN;
            if(w >= wt[ind]) take = val[ind] + dp[ind-1][w-wt[ind]];

            dp[ind][w] = max(take, notTake);
        }
    }

    return dp[n-1][W];
}

int main() {
    int n;
    cout << "Enter number of items: ";
    cin >> n;

    int W;
    cout << "Enter Knapsack capacity: ";
    cin >> W;

    vector<int> wt(n), val(n);
    for(int i = 0;i < n;i++) {
        cout << "Enter " << i+1 << " weight: ";
        cin >> wt[i];
    }
    for(int i = 0;i < n;i++) {
        cout << "Enter " << i+1 << " value: ";
        cin >> val[i];
    }

    cout << "Maximum Profit: " << fractionalKnapsack(n, W, wt, val) << "\n";
    cout << "Maximum Profit(T): " << tabulatedKnapsack(n, W, wt, val) << "\n";


    return 0;
}


/*
    Input ->
    N = 5 
    W = 100
    Weights = {20, 24, 36, 40, 42}
    Values = {12, 35, 41, 25, 32}

    Ouptut -> 101
*/

/*
    Complexity Analysis ->
    Memoization -> T.C -> O(N*W)
                   S.C -> O(N*W) + O(N)
    Tabulation  -> T.C -> O(N*W)
                   S.C -> O(N*W)

*/
