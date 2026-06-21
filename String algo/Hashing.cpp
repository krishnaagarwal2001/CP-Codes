using ll = long long;

struct DoubleHash {
    static const ll MOD1 = 1000000007;
    static const ll MOD2 = 1000000009;

    static const ll BASE1 = 29;
    static const ll BASE2 = 31;

    vector<ll> h1, h2;
    vector<ll> p1, p2;

    DoubleHash(string &s) {
        init(s);
    }

    void init(const string &s) {
        int n = s.size();
        
        h1.clear();
        h2.clear();
        p1.clear();
        p2.clear();
            
        if(n == 0){
            return;
        }
        
        h1.resize(n);
        h2.resize(n);
        p1.resize(n);
        p2.resize(n);

        h1[0] = h2[0] = s[0] - 'a' + 1;     //important 1 based indexing else wrong ans
        p1[0] = p2[0] = 1;

        for (int i = 1; i < n; i++) {
            int val = s[i] - 'a' + 1;

            h1[i] = (h1[i - 1] * BASE1 + val) % MOD1;
            h2[i] = (h2[i - 1] * BASE2 + val) % MOD2;

            p1[i] = (p1[i - 1] * BASE1) % MOD1;
            p2[i] = (p2[i - 1] * BASE2) % MOD2;
        }
    }

    // Returns hash of s[l...r] (0-indexed, inclusive)
    pair<ll, ll> getHash(int l, int r){
        ll x1 = h1[r];
        ll x2 = h2[r];

        if (l > 0) {
            x1 = (x1 - (h1[l - 1] * p1[r - l + 1]) % MOD1 + MOD1) % MOD1;
            x2 = (x2 - (h2[l - 1] * p2[r - l + 1]) % MOD2 + MOD2) % MOD2;
        }

        return {x1, x2};
    }
};