vll z_fun(string &s)
{
	ll n=sz(s);
	vll z(n,0);

	for(int i=1,l=0,r=0;i<n;++i)
	{
		if(i<=r)
			z[i]=min(r-i+1,z[i-l]);
		while(i+z[i]<n and s[z[i]]==s[i+z[i]])
			++z[i];
		if(i+z[i]-1>r)
			l=i,r=i+z[i]-1;
	}

	return z;
}