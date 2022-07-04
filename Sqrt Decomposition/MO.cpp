void remove()
{

}
    
void remove()
{

}
ll get_answer()
    
ll block_size=300;

struct Query 
{
    ll l, r, idx;
};

bool cmp(Query p, Query q) 
{
    if (p.l / block_size != q.l / block_size)
        return p.l / block_size < q.l / block_size;
    return (p.l / block_size & 1) ? (p.r < q.r) : (p.r > q.r);
}

vll MO(vector<Query> queries,vll a) 
{
    vll answers(queries.size());
    sort(queries.begin(), queries.end(),cmp);

    multiset<ll>s;

    ll cur_l = 0;
    ll cur_r = -1;
    ll ans=0;
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(a,s,cur_l,ans);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(a,s,cur_r,ans);
        }
        while (cur_l < q.l) {
            remove(a,s,cur_l,ans);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(a,s,cur_r,ans);
            cur_r--;
        }
        answers[q.idx] = ans;
    }

    return answers;
}