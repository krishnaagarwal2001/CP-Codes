int prim()
{
	int ans = 0;

	vi minEdge(n + 1, inf), inc(n + 1);

	set<pii> s; //{min_w,u}
	s.insert({0, 1});
	minEdge[1] = 0;

	for (int i = 1; i <= n; ++i)
	{
		if (s.empty())
			return -1;

		auto it = s.begin();
		int u = it->second;

		s.erase(it);

		inc[u] = 1;
		ans += minEdge[u];

		for (auto &e : adj[u])
		{
			int v = e.first, w = e.second;

			if (inc[v])
				continue;

			if (w < minEdge[v])
			{
				s.erase({minEdge[v], v});
				minEdge[v] = w;
				s.insert({minEdge[v], v});
			}
		}
	}

	return ans;
}
