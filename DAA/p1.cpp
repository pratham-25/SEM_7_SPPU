/*
// 1. Fibonacci Numbers

#include<bits/stdc++.h>
using namespace std;

int fibonacci(int n) {
    if(n == 0 || n == 1) return n;

    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    int n;
    try{
        if(!(cin >> n)) throw invalid_argument("Not an integer");
    }catch(const invalid_argument &e) {
        cout << e.what() << "\n";
    }

    for(int i = 0;i <= n;i++)
        cout << fibonacci(i) << " ";

    cout << "\n";

    int n1 = 0, n2 = 1;
    for(int i = 0;i <= n;i++) {
        cout << n1 << " ";
        int n3 = n1 + n2;
        n1 = n2;
        n2 = n3;
    }

    return 0;
}

*/

/*
// 2. Huffman Encoding

#include<bits/stdc++.h>
using namespace std;

struct MinHeapNode {
    char data;
    int freq;
    MinHeapNode *left,*right;

    MinHeapNode(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};

class compare {
    public: bool operator()(MinHeapNode *p, MinHeapNode *q) {
        return p->freq > q->freq;
    }
};

class HuffmanCoding{
    string s;
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> pq;
    map<char,string> codes;
    map<char,int> str;

public:
    HuffmanCoding(map<char,int> str) {
        this->str = str;
    }

    HuffmanCoding(string s) {
        this->s = s;
        for(int i = 0;i < s.size();i++) str[s[i]]++;
    }

    void printCodes() {
        for(auto x : codes) {
            cout << x.first << " : " << x.second << "\n";
        }
    }

    void getCodes(MinHeapNode *root, map<char, string> &codes, string tmp) {
        if(root == nullptr) return;

        if(root->data != '$') codes[root->data] = tmp;

        getCodes(root->left, codes, tmp + "0");
        getCodes(root->right, codes, tmp + "1");
    }

    void huffmanHelper() {
        for(auto x : str) pq.push(new MinHeapNode(x.first,x.second));

        while(pq.size() != 1) {
            MinHeapNode *left = pq.top();
            pq.pop();
            MinHeapNode *right = pq.top();
            pq.pop();

            MinHeapNode *tmp = new MinHeapNode('$', left->freq + right->freq);
            tmp->left = left;
            tmp->right = right;
            pq.push(tmp);
        }

        getCodes(pq.top(), codes, "");
    }

    void huffman() {
        if(!codes.size()) huffmanHelper();
        printCodes(); 
    }
};


int main() {

    int n;
    map<char,int> str;

    try {
        if(!(cin >> n)) throw invalid_argument("Not an integer");
    }catch(const invalid_argument &e) {
        cout << e.what() << "\n";
    }

    bool flag = true;
    for(int i = 0;i < n;i++) {
        char ch;
        int fq;
        cin >> ch >> fq;
        // try{ 
        //     if(!cin >> ch) throw invalid_argument("Not a character");
        // }catch(const invalid_argument &e) {
        //     cout << e.what() << "\n";
        //     flag = false;
        //     break;
        // }
        // try {
        //     if(!(cin >> fq)) throw invalid_argument("Not an integer");
        // }catch(const invalid_argument &e) {
        //     cout << e.what() << "\n";
        //     flag = false;
        //     break;
        // }

        str[ch] = fq;
    }

    if(flag) {
        HuffmanCoding hc(str);
        hc.huffman();
    }

    return 0;
}

*/


// 3. 0/1 Knapsack

#include<bits/stdc++.h>
using namespace std;

int f(int ind, int W, vector<int> &wt, vector<int> &val, vector<vector<int>> &dp) {
    if(ind == 0) {
        if(W >= wt[ind]) return val[ind];
        return 0;
    }

    if(dp[ind][W] != -1) return dp[ind][W];

    int notTake = 0 + f(ind-1, W, wt, val, dp);
    int take = INT_MIN;
    if(W >= wt[ind]) take = val[ind] + f(ind-1, W-wt[ind], wt, val, dp);

    return dp[ind][W] = max(take, notTake); 
}

int knapsack(int n, int W, vector<int> &wt, vector<int> &val) {
    vector<vector<int>> dp(n, vector<int>(W+1, -1));
    return f(n-1, W, wt, val, dp);
}

int tabulatedKnapsack(int n, int Wt, vector<int> &wt, vector<int> &val) {
    vector<vector<int>> dp(n, vector<int>(Wt+1, 0));

    for(int i = wt[0];i <= Wt;i++) dp[0][i] = val[0];

    for(int ind = 1;ind < n;ind++) {
        for(int W = 0;W <= Wt;W++) {
            int notTake = 0 + dp[ind-1][W];
            int take = INT_MIN;
            if(W >= wt[ind]) take = val[ind] + dp[ind-1][W-wt[ind]];

            dp[ind][W] = max(take, notTake); 
        }
    }

    return dp[n-1][Wt];
}

int spaceOptimizedKnapsack(int n, int Wt, vector<int> &wt, vector<int> &val) {
    vector<int> prev(Wt+1, 0), curr(Wt+1, 0);

    for(int i = wt[0];i <= Wt;i++) prev[i] = val[0];

    for(int ind = 1;ind < n;ind++) {
        for(int W = 0;W <= Wt;W++) {
            int notTake = 0 + prev[W];
            int take = INT_MIN;
            if(W >= wt[ind]) take = val[ind] + prev[W-wt[ind]];

            curr[W] = max(take, notTake); 
        }
        prev = curr;
    }

    return prev[Wt];
}

int superSpaceOptimizedKnapsack(int n, int Wt, vector<int> &wt, vector<int> &val) {
    vector<int> prev(Wt+1, 0);

    for(int i = wt[0];i <= Wt;i++) prev[i] = val[0];

    for(int ind = 1;ind < n;ind++) {
        for(int W = Wt;W >= 0;W--) {
            int notTake = 0 + prev[W];
            int take = INT_MIN;
            if(W >= wt[ind]) take = val[ind] + prev[W-wt[ind]];

            prev[W] = max(take, notTake); 
        }
    }

    return prev[Wt];
}

int main() {

    int n, W;
    try {
        if(!(cin >> n)) throw invalid_argument("Not an integer !");
    }catch(const invalid_argument &e) {
        cout << e.what() << "\n";
    }
    try {
        if(!(cin >> W)) throw invalid_argument("Not an integer !");
    }catch(const invalid_argument &e) {
        cout << e.what() << "\n";
    }

    vector<int> wt(n), val(n);
    bool flag = true;
    for(int i = 0;i < n;i++) {
        try {
            if(!(cin >> wt[i])) throw invalid_argument("Not an integer");
        }catch(const invalid_argument &e) {
            cout << e.what() << "\n";
            flag = false;
            break;
        }
    }

    for(int i = 0;i < n;i++) {
        try {
            if(!(cin >> val[i])) throw invalid_argument("Not an integer");
        }catch(const invalid_argument &e) {
            cout << e.what() << "\n";
            flag = false;
            break;
        }
    }


    cout << knapsack(n, W, wt, val) << "\n";
    cout << tabulatedKnapsack(n, W, wt, val) << "\n";
    cout << spaceOptimizedKnapsack(n, W, wt, val) << "\n";
    cout << superSpaceOptimizedKnapsack(n, W, wt, val) << "\n";

    return 0;
}


/*
// 4. N-Queens

#include<bits/stdc++.h>
using namespace std;

void nQueens(int col, int fcol, int frow, int n, map<int, bool> &l, map<int, bool> &ld, map<int, bool> &ud, vector<string> &mat, vector<vector<string>> &res) {
    if(col == n) {
        res.push_back(mat);
        return;
    }
    if(col == fcol) {
        nQueens(col+1, fcol, frow, n, l, ld, ud, mat, res);
        return;
    }

    for(int row = 0;row < n;row++) {
        if(!l[row] && !ld[row+col] && !ud[n-1 + col-row]) {
            mat[row][col] = 'Q';
            l[row] = true;
            ld[row + col] = true;
            ud[n - 1 + col - row] = true;

            nQueens(col+1, fcol, frow, n, l, ld, ud, mat, res);

            mat[row][col] = '.';
            l[row] = false;
            ld[row + col] = false;
            ud[n - 1 + col - row] = false;
        }
    }
}

int main() {

    int n;
    try {
        if(!(cin >> n)) throw invalid_argument("Not an integer !");
    }catch(const invalid_argument &e) {
        cout << e.what() << "\n";
    }

    vector<string> mat(n);
    string tmp(n, '.');
    for(int i = 0;i < n;i++) mat[i] = tmp;
    vector<vector<string>> res;

    map<int,bool> l, ld, ud;

    int frow, fcol;
    cin >> frow >> fcol;
    mat[frow][fcol] = 'Q';
    l[frow] = true;
    ld[frow + fcol] = true;
    ud[n - 1 + fcol - frow] = true;

    nQueens(0, fcol, frow, n, l, ld, ud, mat, res);

    for(auto matt : res) {
        cout << "Arrangement: " << "\n"; 
        for(int i = 0;i < n;i++) cout << matt[i] << "\n";
        cout << "\n";
    }

    return 0;
}
*/

/*
// 5. Quick Sort

#include<bits/stdc++.h>
using namespace std;

int partition(vector<int> &arr, int lo, int hi) {
    int pivot = arr[lo];
    int i = lo, j = hi;

    while(i < j) {
        while(i < hi && arr[i] <= pivot) i++;
        while(j > lo && arr[j] > pivot) j--;

        if(i < j) swap(arr[i], arr[j]);
    }
    swap(arr[lo], arr[j]);

    return j;
}

int randomized_pivot(vector<int> &arr, int lo, int hi) {
    int pi = lo + rand() % (hi - lo);
    swap(arr[lo], arr[pi]);

    return partition(arr, lo, hi);
}

void quickSort(vector<int> &arr, int lo, int hi) {
    if(lo < hi) {
        int pi = randomized_pivot(arr, lo, hi);

        quickSort(arr, lo, pi-1);
        quickSort(arr, pi+1, hi);
    }
}

int main() {

    int n;
    try {
        if(!(cin >> n)) throw invalid_argument("Not an integer !");
    }catch(const invalid_argument &e) {
        cout << e.what() << "\n";
    }

    bool flag = true;
    vector<int> arr(n);
    for(int i = 0;i < n;i++) {
       try{
            if(!(cin >> arr[i])) {
                throw invalid_argument("Not an Integer, give a number");
            }
       }catch(const invalid_argument &e) {
            cout << e.what() << "\n";
            flag = false;
            break;
       }
    }

    if(flag) {
        quickSort(arr,0,n-1);

        for(auto x : arr) cout << x << " ";
    } 

    return 0;
}

*/