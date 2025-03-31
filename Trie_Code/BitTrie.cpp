#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    TrieNode* children[2];
    bool isEnd;
    int cnt = 0; //How many strings have this node in it's prefix
    TrieNode() {
        children[0] = children[1] = nullptr;
        isEnd = false;
        
    }
};

class BitTrie {
private:
    TrieNode* root;
public:
    BitTrie() { root = new TrieNode(); }

    void insert(int num) {
        TrieNode* node = root;
        for (int i = 30; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (node->children[bit] == nullptr)
                node->children[bit] = new TrieNode();
            node = node->children[bit];
            node->cnt++;
        }
        node->isEnd = true;
    }

    bool search(int num) {
        TrieNode* node = root;
        for (int i = 30; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (!node->children[bit])
                return false;
            node = node->children[bit];
        }
        return node->isEnd;
    }
    
    void remove(int n) { //will only work if the number is present
        TrieNode* node = root;
        for(int i = 30; i >= 0; i--) {
            int x = (n & (1LL<<i)) ? 1 : 0;
            node = node->children[x];
            node->cnt--;
        }
    }
};

