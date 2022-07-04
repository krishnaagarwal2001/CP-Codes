struct node {
	ll l, r;
	ll value; 
	ll carry=0;
	void merge(node & lft, node & rgt) {
		value = lft.value + rgt.value;
	}
	void split(node & lft, node & rgt) {
		lft.update(carry);
		rgt.update(carry);
		carry = 0;
	}
	void update(ll c) {
		value += c * (r - l + 1);
		carry += c;
	}
 
};
 
 
void build_segtree(vll &a,vector<node>segtree, ll l, ll r,ll x) {
	if (l == r) {
		segtree[x].l = l;
		segtree[x].r = r;
		segtree[x].value = inp[l];
		return ;
	}
	ll m = (l + r)/2, lft = 2 * x, rgt = 2*x + 1; 
	build_segtree(lft, l, m);
	build_segtree(rgt, m + 1, r);
	segtree[x].l = l;
	segtree[x].r = r;
	segtree[x].value = segtree[lft].value + segtree[rgt].value;
}
 
void update_segtree(vll &a,vector<node>segtree,ll x, ll l, ll r, ll v) {

	if (r < segtree[x].l || segtree[x].r < l) {
		return;
	}
	if (l <= segtree[x].l && segtree[x].r <= r) {
		segtree[x].update(v);
		return ;
	}

	segtree[x].split(segtree[2*x], segtree[2*x+1]);
 
	update_segtree(2*x, l, r, v);
	update_segtree(2*x + 1, l, r, v);
	segtree[x].merge(segtree[2*x], segtree[2*x+1]);
}
 
ll seg_query(vll &a,vector<node>segtree,ll x, ll l, ll r) {
	if (r < segtree[x].l || segtree[x].r < l) {
		return 0;
	}
	if (l <= segtree[x].l && segtree[x].r <= r) {
		return segtree[x].value;
	}
 
	segtree[x].split(segtree[2*x], segtree[2*x+1]);
 
	return seg_query(2*x, l, r) + seg_query(2*x+1, l, r);
}
 