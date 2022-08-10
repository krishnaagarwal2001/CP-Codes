struct DSU{
	ll n;
	vll root;
	vll val;
	vll s;
	DSU(ll n_val)
	{
		n=n_val;
		root.resize(n+1);
		val.resize(n+1);
		s.resize(n+1);

		rep(i,1,n+1)
		{
			root[i]=i;
			val[i]=0;
			s[i]=1;
		}
	}

	ll find(ll x) {
	    if (x == root[x]) return x;
	    ll par = root[x];
	    root[x] = find(root[x]);
	    d[x] += d[par];
	    return root[par];
  	}
}