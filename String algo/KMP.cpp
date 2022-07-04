vll pref_fun(string &s)
{
	ll n=sz(s);
	vll pi(n,0);
	rep(i,1,n)
	{
		ll j=pi[i-1];
		while(j>0 and s[i]!=s[j])
			j=pi[j-1];

		if(s[i]==s[j])
			j++;

		pi[i]=j;
	}
	return pi;
}

bool kmp(string text,string pattern)
{
	vll pre=pref_fun(pattern);
	ll i=0,j=0;
	while(i<sz(text) and j<sz(pattern))
	{
		if(text[i]==pattern[j])
		{
			i++;
			j++;
		}
		else
		{
			if(j!=0)
			{
				j=pre[j-1];
			}
			else
				i++;
		}
	}

	return (j==sz(pattern));
}