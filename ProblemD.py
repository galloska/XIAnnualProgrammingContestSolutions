from sys import stdin, stdout

last = 0
n = 1
lvl = [0, 0]
p = [[], []]
p[1] = [1] * 18

def LCA (u, v):
	global lvl
	global p
	if lvl[u] < lvl[v]:
		u, v = v, u

	for j in range(18):
		if (lvl[u] - lvl[v]) & (1 << j):
			u = p[u][j]

	if u == v:
		return u
	
	for j in range(17, -1, -1):
		if p[u][j] != p[v][j]:
			u = p[u][j]
			v = p[v][j]

	return p[u][0]

q = int(stdin.readline())

for i in range(q):
	s = stdin.readline();

	if s[0] == "1":
		t, u = (int(x) for x in s.split(' '))
		u = (u + last) % n + 1

		p.append([u] * 18)
		lvl.append(lvl[u] + 1)
		n += 1
		for j in range(1, 18):
			p[n][j] = p[p[n][j-1]][j-1]

		last = lvl[n] + 1
	else:
		t, u, v = (int(x) for x in s.split(' '))
		u = (u + last) % n + 1
		v = (v + last) % n + 1

		lca = LCA(u, v)
		last = lvl[u] + lvl[v] - 2 * lvl[lca] + 1

	stdout.write(str(last) + '\n')
