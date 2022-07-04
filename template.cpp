    #include <bits/stdc++.h>
    // #include <ext/pb_ds/assoc_container.hpp>
    // #include <ext/rope>
    // #include <ext/pb_ds/tree_policy.hpp>
    // #include <ext/pb_ds/trie_policy.hpp>
    // using namespace __gnu_pbds;
    // using namespace __gnu_cxx;
    // typedef tree<long long, null_type, std::less<long long>, rb_tree_tag, tree_order_statistics_node_update> pbds;
    // typedef trie<std::string,null_type,trie_string_access_traits<>,pat_trie_tag,trie_prefix_search_node_update>Trie;
    
    using namespace std;
    #define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
    #define pb push_back
    #define eb emplace_back
    #define all(x) (x).begin(),(x).end()
    #define fi first
    #define se second
    #define sz(x) ((int)(x).size())
    #define rdv(x) long long x; cin>>x;
    #define deb(x) cout<<#x<<"="<<x<<endl;
    #define inf 1e18
    #define endl "\n"
    #define log(args...)    { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
    void err(istream_iterator<string> it) {}
    template<typename T, typename... Args>
    void err(istream_iterator<string> it, T a, Args... args) {cout << *it << " = " << a << endl;err(++it, args...);}

    typedef vector<long long> vll;
    typedef vector<vll> vvl;
    typedef long long ll;
    typedef pair<long long,long long> pii;
    typedef vector<pii> vpii;
    typedef long double ld;
    mt19937 mrand(random_device{}());
    const ll mod=1000000007;
    const ll N = 2e5 + 10;
    const ll M = 2 * N;
    int rnd(int x) { return mrand() % x;}
    ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
    ld powmod(ld a,ll b) {ld res=1; for(;b;b>>=1){if(b&1)res=res*a;a=a*a;}return res;}
    bool prime[200001];
    void SieveOfEratosthenes(){memset(prime, true, sizeof(prime));prime[1]=false;for (int p=2; p*p<=200000; p++){if (prime[p] == true){for (int i=p*p; i<=200000; i += p)prime[i] = false;}}return;}

    /*-------------------------------------------------------------------------------------------*/
   
    void solve()  
    {
        
        cout<<"\n";
    }
    int main()
    {
        ios_base::sync_with_stdio(false); 			//Used to reduce the time
        cin.tie(NULL);
        cout.tie(NULL);


        ll T=1;
        //cin>>T;
        //ll temp=T;
        while(T--)
        {   
            //cout<<"Case #"<<temp-T<<": ";
            solve();
        }
        cerr<<"Time : "<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<" ms\n";
    }
