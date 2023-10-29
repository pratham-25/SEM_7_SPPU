#include<bits/stdc++.h>
using namespace std;

struct MinHeapNode {
    char data;
    int freq;
    MinHeapNode *left, *right;
    
    MinHeapNode(char data, int freq) {
        this->data = data;
        this->freq = freq;
        this->left = nullptr;
        this->right = nullptr;
    }
};

struct compare {
    bool operator()(MinHeapNode* ele1, MinHeapNode* ele2) {
        return ele1->freq > ele2->freq;
    }
};

class HuffmanCoding {

    string s;
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    map<char,int> str;
    map<char, string> codes;



    void huffmanCodeHelper(map<char,int> &str) {
        for(auto node : str) {
            minHeap.push(new MinHeapNode(node.first, node.second));
        }

        MinHeapNode *left, *right;
        while(minHeap.size() != 1) {
            left = minHeap.top();
            minHeap.pop();
            right = minHeap.top();
            minHeap.pop();
            MinHeapNode *tmp = new MinHeapNode('$', left->freq + right->freq);
            tmp->left = left;
            tmp->right = right;
            minHeap.push(tmp);
        }

        getCodes(minHeap.top(), "");
    }

    void getCodes(MinHeapNode *root, string code){
        if(root == nullptr) return;

        if(root->data != '$') codes[root->data] = code;

        getCodes(root->left, code + '0');
        getCodes(root->right, code + '1');
    }

    void printCodes(map<char, string> &codes) {
        for(auto x : codes) {
            cout << x.first << " -> " << x.second << "\n"; 
        }
    }

public: 
    HuffmanCoding(string s) {
        this->s = s;
        for(auto x : s) str[x]++;
    }

    HuffmanCoding(map<char, int> str){
        this->str = str;
    }

    void getHuffmanCodes(){ 
        if(codes.empty()) huffmanCodeHelper(str);
        printCodes(codes);
    }

    void encryptString() {
        if(codes.empty()) huffmanCodeHelper(str);

        string es = "";
        for(auto ch : s) {
            es += codes[ch];
        }

        cout << "Encrypted string: " << es << "\n";
    }
};

int main() {
    string s;
    // cout << "Enter raw string:- ";
    // cin >> s;

    int n;
    cout << "Enter number of characters:- ";
    cin >> n;
    map<char,int> str;
    for(int i = 0;i < n;i++) {
        char ch;
        int x;
        cout << "Enter character: ";
        cin >> ch;
        cout << "Enter frequency:- ";
        cin >> x;
        str[ch] = x;
    }

    // HuffmanCoding h(s);
    HuffmanCoding h(str);

    h.getHuffmanCodes();
    h.encryptString();

    return 0;
}