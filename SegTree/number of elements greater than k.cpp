using namespace std;
 
//place these includes *before* the `#define int long long` else compile error
//not using <bits/extc++.h> as it compile errors on codeforces c++20 compiler
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
//BST with extra functions https://c...content-available-to-author-only...s.com/blog/entry/11080
//order_of_key - # of elements *strictly* less than given element
//find_by_order - find kth largest element, k is 0 based so find_by_order(0) returns min element
template<class T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
//example initialization:
indexed_set<pair<long long, int>> is;
//hash table (apparently faster than unordered_map): https://c...content-available-to-author-only...s.com/blog/entry/60737
//example initialization:
gp_hash_table<string, long long> ht;
 
 
//For point updates: either switch to policy based BST, or use sqrt decomposition
struct merge_sort_tree {
	const int N;
	vector<int> arr;
	vector<indexed_set<pair<int,int>>> tree;
	merge_sort_tree(const vector<int>& a_arr) : N(a_arr.size()), arr(a_arr), tree(2 * N) {
		for (int i = 0, j = 1 << __lg(2 * N - 1); i < N; i++, j = (j + 1) % N + N)
			tree[j].insert({arr[i], i});
		for (int i = N - 1; i >= 1; i--) {
			for(pair<int,int> e : tree[2 * i]) tree[i].insert(e);
			for(pair<int,int> e : tree[2 * i + 1]) tree[i].insert(e);
		}
	}
	int value(int v, int x) const {
		return tree[v].order_of_key({x, -1});
	}
	int to_leaf(int i) const {
		i += 1 << __lg(2 * N - 1);
		return i < 2 * N ? i : 2 * (i - N);
	}
	//update index i to new_val
	void update(int i, int new_val) {
		assert(0 <= i && i < N);
		for(int v = (i + (1 << __lg(2 * N - 1))) % N + N; v >= 1; v >>= 1) {
			tree[v].erase({arr[i], i});
			tree[v].insert({new_val, i});
		}
		arr[i] = new_val;
	}
	//How many values in range [l, r) are < x?
	//O(log^2(n))
	int query(int l, int r, int x) const {
		assert(0 <= l && l <= r && r <= N);
		int res = 0;
		for (l = to_leaf(l), r = to_leaf(r); l < r; l >>= 1, r >>= 1) {
			if (l & 1) res += value(l++, x);
			if (r & 1) res += value(--r, x);
		}
		return res;
	}
};
 
 
//MUCH RANDOM!!!
seed_seq seed{
	(uint32_t)chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
	(uint32_t)random_device()(),
	(uint32_t)(uintptr_t)make_unique<char>().get(),
	(uint32_t)__builtin_ia32_rdtsc()
};
mt19937 rng(seed);
 
//intended types: int, unsigned, long long
//returns a random number in range [l, r)
template<class T> inline T get_rand(T l, T r) {
	assert(l < r);
	return uniform_int_distribution<T>(l, r - 1)(rng);
}
 
int main() {
 
	for(int test = 1; ; test++) {
		cout << "test: " << test << endl;
		int n = get_rand(1, 1000);
		vector<int> arr(n);
		for(int i = 0; i < n; i++) {
			arr[i] = get_rand<int>(-10, 10);
		}
		merge_sort_tree mst(arr);
		for(int t = 1000; t--;) {
			if(get_rand(1, 3) == 1) {
				int i = get_rand(0, n);
				int new_val = get_rand<int>(-10, 10);
				arr[i] = new_val;
				mst.update(i, new_val);
			} else {//query
				int l = get_rand(0, n + 1), r = get_rand(0, n + 1);
				if(l > r) swap(l, r);
				int x = get_rand<int>(-10, 10);
				int cnt_naive = 0;
				for(int i = l; i < r; i++) {
					cnt_naive += arr[i] < x;
				}
				assert(cnt_naive == mst.query(l, r, x));
			}
		}
	}
 
	return 0;
}