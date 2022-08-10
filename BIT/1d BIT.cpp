struct BIT{
	vll tree;
	ll n;

	BIT(ll n)
	{
		this->n=n;
		tree.assign(n+1,0);
	}

	ll sum(ll idx)
	{
		ll res=0;
		while(idx)
		{
			res+=tree[idx];
			idx-=(idx & (-idx));
		}
		return res;
	}

	ll sum(ll l,ll r)
	{
		return sum(r)-sum(l-1);
	}

	void update(ll idx,ll delta)
	{
		while(idx<=n)
		{
			tree[idx]+=delta;
			idx+= (idx & (-idx));
		}
	}	
};