#include<bits/stdc++.h>
using namespace std;

struct Manacher{
    vector<int>p;

    void runManacher(string s){
        int n = s.length();
        p.assign(n,1);

        int l = 1, r = 1;

        for(int i=1;i<n;i++){
            p[i] = max(1,min(r-i,p[l+r-1]));

            while(i+p[i]<n and i-p[i]>=0 and s[i+p[i]] == s[i-p[i]]){
                p[i]++;
            }

            if(i+p[i]>r){
                l = i-p[i];
                r = i+p[i];
            }
        }
    }

    void build(string s){
        string t = "";

        for(auto v: s){
            t += string("#") + v;
        }

        t+=string("#");
        runManacher(t);
    }

    int getLongestPalindromeLength(int center, bool odd){
        int pos = 2*center + 1 + (!odd);
        return p[pos] - 1;
    }

    bool checkPalindrome(int l, int r){
        return ((r-l+1)<=getLongestPalindromeLength( (l+r)/2, l%2 == r%2 ));
    }
} m;
