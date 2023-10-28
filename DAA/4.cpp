/*
PS : Design n-Queens matrix having first Queen placed. Use backtracking to place
remainingQueens to generate the final n-queen
*/

#include<bits/stdc++.h>
using namespace std;

void nQueens(int c, int n, map<int,bool> &row, map<int,bool> &ld, map<int,bool> &ud, vector<string> &mat, vector<vector<string>> &res) {
    if(c == n) {
        res.push_back(mat);
        return;
    }

    for(int r = 0;r < n;r++) {
        if(!row[r] && !ld[r+c] && !ud[n-1 + c-r]) {
            mat[r][c] = 'Q';
            row[r] = true;
            ld[r+c] = true;
            ud[n-1 + c-r] = true;

            nQueens(c+1, n, row, ld, ud, mat, res);

            row[r] = false;
            ld[r+c] = false;
            ud[n-1 + c-r] = false;
            mat[r][c] = '.';
        }
    }
}

int main() {
    int n;
    cout << "Enter size: ";
    cin >> n;
    
    vector<string> mat(n);
    string tmp(n,'.');
    for(int i = 0;i < n;i++) mat[i] = tmp;
    map<int,bool> row, ld, ud;
    vector<vector<string>> res;

    nQueens(0, n, row, ld, ud, mat, res);

    for(auto x : res) {
        for(int i = 0;i < n;i++) cout << x[i] << "\n";
        cout << "\n";
    }

    return 0;
}