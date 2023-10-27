#include<bits/stdc++.h>
using namespace std;

void nQueens(int c, int n, vector<string> &mat) {
    if(c < 0) return;

    for(int r = 0;r < n;r++) {
        if(isPossible(i, c, mat)) {
            
        }
    }
}

int main() {
    int n;
    cout << "Enter size: ";
    cin >> n;
    
    vector<string> mat(n);
    string tmp('.',n);
    for(int i = 0;i < n;i++) mat[i] = tmp;

    return 0;
}