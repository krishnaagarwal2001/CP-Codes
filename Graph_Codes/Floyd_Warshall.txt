vector<vll> floyd_warshall(ll n)
{
	vector<vll> d(n + 1, vll(n + 1, inf));

	for (ll i = 1; i <= n; ++i)
	{
		d[i][i] = 0;

		for (auto e : adj[i])
		{
			ll j = e.fi, w = e.se;

			d[i][j] = min(d[i][j], w);
		}
	}

	for (ll k = 1; k <= n; ++k)
		for (ll i = 1; i <= n; ++i)
			for (ll j = 1; j <= n; ++j)
				if (d[i][k] < inf && d[k][j] < inf)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

	return d;
}