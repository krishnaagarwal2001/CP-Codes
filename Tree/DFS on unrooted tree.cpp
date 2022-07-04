
/* SEE AFTER THE MAIN ALSO*/


ll U[M], V[M], W[M], pos[M];
vector<ll> g[N];
void add_edge(ll e, ll x, ll y, ll w) {
  U[e] = x;
  V[e] = y;
  W[e] = w;
  pos[e] = g[x].size();
  g[x].push_back(e);
}

// Properties to calculate for every edge.
ll far[M];
// Additional information.
ll vis[M];
vector<ll> prefix_ans[N], suffix_ans[N];

ll val_or_zero(vector<ll>& v, ll idx) {
  if (idx >= 0 && idx < (ll)v.size()) return v[idx];
  return 0;
}

void recompute_prefix_suffix_ans(ll x) {
  ll n = g[x].size();
  prefix_ans[x].resize(n);
  suffix_ans[x].resize(n);
  for (ll i = 0, j = n - 1; i < n; i++, j--) {
    prefix_ans[x][i] = max(val_or_zero(prefix_ans[x], i - 1), far[g[x][i]]);
    suffix_ans[x][j] = max(val_or_zero(suffix_ans[x], j + 1), far[g[x][j]]);
  }
}

// DFS on UnRooted Tree.
void dfs(ll x, ll pe) {
  if (!vis[x]) {
    // Visiting x for the first time.
    // Explore all edges except parent edge.
    vis[x] = (pe ^ 1);
    for (auto e : g[x])
      if (e != vis[x]) dfs(V[e], e);
    recompute_prefix_suffix_ans(x);
  } else if (vis[x] > 1) {
    // Visiting x for the second time.
    // Only 1 outgoing edge would be unexplored.
    dfs(V[vis[x]], vis[x]);
    vis[x] = 1;
    recompute_prefix_suffix_ans(x);
  }
  if (pe) {
    ll idx = pos[pe ^ 1];
    far[pe] = max(val_or_zero(prefix_ans[x], idx - 1),
                  val_or_zero(suffix_ans[x], idx + 1)) +
              W[pe];
  }
}

ll main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ll n;
  cin >> n;
  for (ll i = 1; i < n; i++) {
    ll x, y, w = 1;
    // cin >> x >> y >> w;
    cin >> x >> y;
    add_edge(2 * i, x, y, w);
    add_edge(2 * i + 1, y, x, w);
  }


  for (ll i = 1; i <= n; i++) {
    if (vis[i] != 1) {
      dfs(i, 0);
    }
  }

  for (ll i = 1; i <= n; i++) {
    cout << suffix_max[i][0] << " ";
  }
}



// https://codeforces.com/contest/1092/problem/F

// ll U[M], V[M], W[M], pos[M];
//     vector<ll> g[N];
//     void add_edge(ll e, ll x, ll y, ll w) {
//       U[e] = x;
//       V[e] = y;
//       W[e] = w;
//       pos[e] = g[x].size();
//       g[x].push_back(e);
//     }

//     // Properties to calculate for every edge.
//     pii far[M];
//     // Additional information.
//     ll vis[M];
//     ll sum[N];
//     ll val[N];
//     vector<ll> prefix_max[N], suffix_max[N],prefix_sum[N],suffix_sum[N];

//     ll val_or_zero(vector<ll>& v, ll idx) {
//       if (idx >= 0 && idx < (ll)v.size()) return v[idx];
//       return 0;
//     }

//     void recompute_prefix_suffix_max(ll x) {
//       ll n = g[x].size();
//       prefix_max[x].resize(n);
//       suffix_max[x].resize(n);
//       prefix_sum[x].resize(n);
//       suffix_sum[x].resize(n);

//       for (ll i = 0, j = n - 1; i < n; i++, j--) {
//         prefix_sum[x][i] = val_or_zero(prefix_sum[x], i - 1)+ far[g[x][i]].fi;
//         suffix_sum[x][j] = val_or_zero(suffix_sum[x], j + 1)+ far[g[x][j]].fi;
//       }

//       for (ll i = 0, j = n - 1; i < n; i++, j--) {
//         prefix_max[x][i] = val_or_zero(prefix_max[x], i - 1)+far[g[x][i]].se;
//         suffix_max[x][j] = val_or_zero(suffix_max[x], j + 1)+ far[g[x][j]].se;
//       }

//     }


//     // DFS on UnRooted Tree.
//     void dfs(ll x, ll pe) {
//       if (!vis[x]) {
//         // Visiting x for the first time.
//         // Explore all edges except parent edge.
//         vis[x] = (pe ^ 1);
//         for (auto e : g[x])
//           if (e != vis[x]) dfs(V[e], e);

//         recompute_prefix_suffix_max(x);
//       } else if (vis[x] > 1) {
//         // Visiting x for the second time.
//         // Only 1 outgoing edge would be unexplored.
//         dfs(V[vis[x]], vis[x]);
//         vis[x] = 1;
//         recompute_prefix_suffix_max(x);
//       }
//       if (pe) {
//         ll idx = pos[pe ^ 1];
//         far[pe].fi = val_or_zero(prefix_sum[x], idx - 1)+val_or_zero(suffix_sum[x], idx + 1)+val[x];
//         far[pe].se = val_or_zero(prefix_max[x], idx - 1)+val_or_zero(suffix_max[x], idx + 1)+far[pe].fi;
                  
//       }
//     }