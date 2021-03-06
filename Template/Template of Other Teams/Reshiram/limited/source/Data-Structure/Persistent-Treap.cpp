int ran() {
	static int ret = 182381727;
	return (ret += (ret << 1) + 717271723) & (~0u >> 1);
}
int alloc(int node = 0) {
	size++;
	if (node) {
		c[size][0] = c[node][0];
		c[size][1] = c[node][1];
		s[size] = s[node];
		d[size] = d[node];
	}
	else{
		c[size][0] = c[size][1] = 0;
		s[size] = 1;
		d[size] = ' ';
	}
	return size;
}
void update(int x) {
	s[x] = 1;
	if (c[x][0]) s[x] += s[c[x][0]];
	if (c[x][1]) s[x] += s[c[x][1]];
}
int merge(const std::pair<int, int> &a) {
	if (!a.first) return a.second;
	if (!a.second) return a.first;
	if (ran() % (s[a.first] + s[a.second]) < s[a.first]) {
		int newnode = alloc(a.first);
		c[newnode][1] = merge(std::make_pair(c[newnode][1], a.second));
		update(newnode);
		return newnode;
	} else {
		int newnode = alloc(a.second);
		c[newnode][0] = merge(std::make_pair(a.first, c[newnode][0]));
		update(newnode);
		return newnode;
	}
}
std::pair<int, int> split(int x, int k) {
	if (!x || !k) return std::make_pair(0, x);
	int newnode = alloc(x);
	if (k <= s[c[x][0]]) {
		std::pair<int, int> ret = split(c[newnode][0], k);
		c[newnode][0] = ret.second;
		update(newnode);
		return std::make_pair(ret.first, newnode);
	} else {
		std::pair<int, int> ret = split(c[newnode][1], k - s[c[x][0]] - 1);
		c[newnode][1] = ret.first;
		update(newnode);
		return std::make_pair(newnode, ret.second);
	}
}
int build(int l, int r) {
	int newnode = alloc();
	d[newnode] = tmp[l + r >> 1];
	if (l <= (l + r >> 1) - 1) c[newnode][0] = build(l, (l + r >> 1) - 1);
	if ((l + r >> 1) + 1 <= r) c[newnode][1] = build((l + r >> 1) + 1, r);
	update(newnode);
	return newnode;
}
