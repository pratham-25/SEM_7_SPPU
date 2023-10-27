
/* PS: Write a program non-recursive and recursive program to calculate Fibonacci
numbers and analyze their time and space complexity.
*/

#include<bits/stdc++.h>
using namespace std;

// recursive
int fib(int n) {
    if(n <= 1) return n;

    return fib(n-1) + fib(n-2); 
}

int main(){
    // iterative

    int n;
    cout << "Enter limit: ";
    cin >> n;

    cout << "Using Iterative:- ";
    int f0 = 0, f1 = 1;
    cout << f0 << " ";
    for(int i = 0;i < n;i++) {
        cout << f1 << " ";
        int tmp = f0 + f1;
        f0 = f1;
        f1 = tmp;
    }
    cout << "\n";

    cout << "Using recursive:- ";
    cout << fib(n);
    cout << "\n";

}