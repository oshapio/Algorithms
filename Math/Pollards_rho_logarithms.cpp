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
// Finds x in  g ^ x = alpha MOD(N) 
// Only works when order of group doesn't have small factors
int modExp(int x, int pow, int mod) {
	int res = 1;
	while (pow) {
		if (pow & 1) res = res * x % mod;
		pow >>= 1;
		x = x * x % mod;
	}
	return res;
}

vi extendEuclid(int a, int b) {
	if (b % a == 0) return { a, 1, 0};
	vi params = extendEuclid(b % a, a);
	return { params[0], (-b / a) * params[1] + params[2], params[1] };
}

int findInverse(int x, int mod) {
	vi interRes = extendEuclid(x, mod);
	if (interRes[0] != 1)
		// Inverse doesn't exist!
		return -1;
	
	return (interRes[1] + mod) % mod;
}

vi getNext(vi args,int g, int alpha, int order, int N) {
	int x, a, b; x = args[0], a = args[1], b = args[2];
	int xMod = x % 3;
	if (xMod == 1) {
		x = (alpha * x) % N;
		b = (b + 1) % order;
	}
	else if (xMod == 0) {
		x = (x * x) % N;
		a = (2 * a) % order;
		b = (2 * b) % order;
	}
	else {
		// x % 3 == 2
		x = (x * g) % N;
		a = (a + 1) % order;
	}
	return { x,a,b };
}
int getRand(int from, int to) {
	int range = to - from + 1;
	int numb = rand() % (range);
	return from + numb;
}
int pollardsRhoDL(int g, int alpha, int order, int N, int a = 0, int b = 0, int tries = 0) {
	if (tries >= 10) return -1;
	// init vals
	int x = (modExp(g, a, N) * modExp(alpha, b, N)) % N;
	vi slow = { x, a, b}, fast = { x, a, b};
	for (int i = 0; i < N + 1; i++) {
		slow = getNext(slow, g, alpha, order, N);

		fast = getNext(getNext(fast, g, alpha, order, N), g, alpha, order, N);

		if (slow[0] == fast[0]) {
			int rem = (slow[2] - fast[2]);
			if (rem == 0) {
				//cout << "Can't find solution\n";
				break;
			}
			else {
				// Answer found
				int inv = findInverse(rem, order);
				if (inv == -1) {
					// No inverse exists, reinitialize values
					break;
				}
				return ((findInverse(rem, order) * (fast[1] - slow[1]))) % (order);
			}
		}
	}
	// Try again with different values
	return pollardsRhoDL(g, alpha, order, N, getRand(1, order - 1), getRand(1, order - 1), tries + 1);
}

int main()
{
	vector<int> tests[]= {
	// g, N, order, alpha, answer
	{7, 499, 498, 12, 321},
	{3, 7, 6, 2, 2},
	{2, 383, 191, 228, 110},
	{2, 1019, 1018, 5, 10}
    };
	for (auto test : tests) {
		int g = test[0], N = test[1], order = test[2], alpha = test[3], answer = test[4];
		int temp = pollardsRhoDL(g, alpha, order, N);
		cout << temp << " " << ((temp) % order + order) % order << " " << answer << "\n";
	}
	return 0;
}

