#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <iostream>
#include <utility>
#include <tuple>
#include <set>
#include <stdio.h>

using namespace std;
typedef long long ll;
typedef tuple<int, int, int> t3;
typedef vector<ll> vi;
typedef pair<int, int> pii;
const ll MOD = 1e9 + 9;
const int CMAX = 2e5 + 100;


ll bit[CMAX];
void update(int x, ll dx) {
	for (int i = x; i < CMAX; i += i &(-i)) {
		bit[i] += dx;
	}
}
ll get(int x) {
	ll r = 0;
	for (int i = x; i >= 1; i -= i&(-i)) {
		r += bit[i];
	}
	return r;
}
void updateinterval(int l, int r, ll dx) {
	update(l, dx);
	update(r + 1, -dx);
}
ll sum(int l, int r) {
	return get(r) - get(l - 1);
}
int n;
ll arr[CMAX];
vi endi[CMAX];
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
	}
	for (int i = 1; i <= n; i++) {

		cin >> arr[i];
		update(i, 1);
		arr[i] = min(arr[i], (ll)n);
		endi[arr[i]].push_back(i);
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += arr[i] >= i ? (get(arr[i]) - get(i)) : 0;
		for (int j = 0; j < endi[i].size(); j++) {
			update(endi[i][j], -1);
		}
	}
	cout <<ans << "\n";
	return 0;
}