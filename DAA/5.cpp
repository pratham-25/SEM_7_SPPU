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

int randomized_partition(vector<int> &arr, int lo, int hi) {
    int pi = lo + rand() % (hi-lo);

    swap(arr[pi], arr[lo]);

    return partition(arr, lo, hi);
}

void quickSort(vector<int> &arr, int lo, int hi) {
    if(lo < hi) {
        int pi = randomized_partition(arr, lo, hi);

        quickSort(arr, lo, pi-1);
        quickSort(arr, pi+1, hi);  
    }
}

int main() {

    int n;
    try{
        if(!(cin >> n)) {
            throw invalid_argument("Not an Integer, give a number");
        }
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