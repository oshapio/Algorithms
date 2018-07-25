#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <bitset>
#include <iomanip>
#include <cmath>
#include <queue>
#include <iterator>
#include <unordered_set>
#include <cstring>
#include <functional>
#include <stack>
#include <limits.h>
#include <memory>

using namespace std;

typedef long long ll;
typedef pair<string, int> si;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef pair<ll, ll> pll;
const int CMAX = 26 + 26 + 10;
ll MOD = 1000000007;
const double eps = 1e-6;
const ll linf = LLONG_MAX;
const int inf = INT_MAX;
const double PI = 3.14159265359;


using namespace std;
const int MAXN = 1e5 + 100;
vector< int > tree[MAXN];
vector< int > weight[MAXN];
int n, m;
int ancestor[MAXN][30], parent[MAXN], height[MAXN], weightsAcc[MAXN], ansItself[MAXN];

multiset<int> mins[MAXN];

void dfsStart(int u, int par) {
	if (par == -1) {
		parent[u] = -1;
		height[u] = 0;
	}
	else {
		parent[u] = par;
		weightsAcc[u] += weightsAcc[parent[u]];
		height[u] = height[par] + 1;
	}
	for (int i = 0; i < tree[u].size(); i++) {
		if (tree[u][i] == par) continue;
		weightsAcc[tree[u][i]] += weight[u][i];
		dfsStart(tree[u][i], u);
	}
}

void lcaPreprocess(int u, int par) {
	for (int i = 1; i <= n; i++) {
		ancestor[i][0] = parent[i];
	}
	for (int e = 1; (1 << e) < n; e++) {
		for (int i = 1; i <= n; i++) {
			if (ancestor[i][e - 1] != -1)
				ancestor[i][e] = ancestor[ancestor[i][e - 1]][e - 1];
		}
	}
}

int findLca(int a, int b) {
	if (height[a] < height[b])
		swap(a, b);

	int logVal = log2(height[a]);

	for (int i = logVal; i >= 0; i--) {
		if (height[a] - (1 << i) >= height[b]) {
			a = ancestor[a][i];
		}
	}
	if (a == b) return a;
	int backLog = log2(height[a]);
	for (; backLog >= 0; backLog--) {
		if (ancestor[a][backLog] != -1 && ancestor[a][backLog] != ancestor[b][backLog]) {
			a = ancestor[a][backLog];
			b = ancestor[b][backLog];
		}
	}
	return parent[a];
}

// Decomposition or smth
int nodesInComp = 0;
int subSize[MAXN];
int rootComponent[MAXN]; // centroido parentai
bool hasDecomp[MAXN];
void findSubSize(int u, int par) {
	subSize[u] = 1;
	nodesInComp++;
	for (int v : tree[u]) {
		if (v == par || hasDecomp[v]) continue;
		findSubSize(v, u);
		subSize[u] += subSize[v];
	}
}
int findCentroidLocation(int u, int par) {
	for (int v : tree[u]) {
		if (!hasDecomp[v] && v != par && subSize[v] > nodesInComp / 2) {
			return findCentroidLocation(v, u);
		}
	}
	return u;
}


//
// Sitas todo XD
int deccnt = 0;
void decompose(int root, int parent)
{
	deccnt++;
	nodesInComp = 0;
	//memset(subSize, 0, sizeof(subSize));
	findSubSize(root, -1);
	int centroid = findCentroidLocation(root, -1);

	//cout << "root: " << root << " centroid: " << centroid << "\n";
	if (parent == -1)parent = centroid;
	rootComponent[centroid] = parent;
	hasDecomp[centroid] = true;

	for (int u : tree[centroid]) {
		if (!hasDecomp[u] && u != parent) {
			decompose(u, centroid);
		}
	}
}
//
//
ll getDist(int nodeA, int nodeB) {
	return weightsAcc[nodeA] + weightsAcc[nodeB] - 2  * weightsAcc[findLca(nodeA, nodeB)];
}
int update(int node, char add) {
	int theMinLol = 1e9;
	if (add == '+') {
		int oldAnswer = ansItself[node];
		ansItself[node] = 0;

		//propogate upwards
		int parent_local = -1;
		parent_local = rootComponent[node];
		while (parent_local != rootComponent[parent_local]) {
			//
			
			// find the old answer, and the update it
			parent_local = rootComponent[node];
			int distOld = min((ll)1e9, oldAnswer + getDist(node, parent_local));
			auto iters = mins[parent_local].find(distOld);
			int distNew = getDist(node, parent_local);
			if (iters == mins[parent_local].end()) {
				// doesn't exist, let's just add new
				// erase it, and then update it
				mins[parent_local].insert(distNew);
			}
			else {
				mins[parent_local].erase(distOld);
				mins[parent_local].insert(distNew);
				theMinLol = min(theMinLol, distNew);
			}
			
		}
	}
	else {
		// hospital is closed now
		int oldAnswer = 1e9;
		ansItself[node] = 1e9;

		//propogate upwards
		int parent_local = -1;
		parent_local = rootComponent[node];
		while (parent_local != rootComponent[parent_local]) {
			//

			// find the old answer, and the update it
			parent_local = rootComponent[node];
			int distOld = min((ll)1e9,oldAnswer + getDist(node, parent_local));
			auto iters = mins[parent_local].find(distOld);
			if (iters == mins[parent_local].end()) {
				// doesn't exist, we don't care
			}else {
				mins[parent_local].erase(distOld);
			}
		}
	}
	return theMinLol;
}
int get(int node) {
	ll theMinLol = ansItself[node];

	//propogate upwards
	int parent_local = -1;
	parent_local = rootComponent[node];

	do{
		//
		int a1 = getDist(node, parent_local),
			 a2 = ansItself[parent_local];
		theMinLol = min(theMinLol, a1 + a2);
		if (!mins[parent_local].size()) continue;
		int distNew = *mins[parent_local].begin() + getDist(node, parent_local);
	} while (parent_local != rootComponent[parent_local]);
	return theMinLol;
}
//


int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif // DEBUG
	memset(hasDecomp, false, sizeof(hasDecomp));
	memset(ancestor, -1, sizeof(ancestor));
	memset(weightsAcc, 0, sizeof(weightsAcc));
	memset(ansItself, 0, sizeof(ansItself));
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int f, t, w; cin >> f >> t >> w;
		tree[f].push_back(t);
		tree[t].push_back(f);
		weight[t].push_back(w);
		weight[f].push_back(w);

	}
	dfsStart(1, -1);
	// padarom LCA thingie, kad zinoti, kokie yra atstumai nuo vertex u iki vertex v
	lcaPreprocess(1, -1);
	decompose(1, -1);


	for (int i = 1; i <= n; i++) {
		//cout << i << " :  " << rootComponent[i] << "\n";
	
	}
	//cout << "\n";
	for (int i = 1; i <= n; i++) {
		//cout << i << " : " << weightsAcc[i] << "\n";
		
	}
	for (int i = 1; i <= n; i++) {
		ansItself[i] = 1e9;
	}
	ansItself[1] = 0;

	int m; cin >> m;
	for (int i = 0; i < m; i++) {
		char c; int node; cin >> c >> node;
		if (c == '?') {
			int getha = get(node);
			cout << getha << "\n";
		}
		else {
			int xd = update(node, c);
		}
	}

	

	return 0;
}
