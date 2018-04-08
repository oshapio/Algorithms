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

using namespace std;
typedef long long ll;
typedef tuple<int, int, int> t3;
typedef vector<int> vi;

// Computes x ^ pow MOD (mod) in log(pow) time
int modExp(int x, int pow, int mod) {
	int res = 1;
	while (pow) {
		if (pow & 1) res = res * x % N;
		pow >>= 1;
		x = x * x % N;
	}
	return res;
}

int main()
{
	cout << modExp(2, 5, 123123);
	return 0;
}

