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

// Returns gcd, x, y, in a * x + b * y = gcd(a,b)
vi extendEuclid(int a, int b) {
	if (b % a == 0) return { a, 1, 0};
	vi params = extendEuclid(b % a, a);
	return { params[0], -b / a * params[1] + params[2], params[1] };
}

int main()
{
	vi para = extendEuclid(7, 12);
	for (auto i : para) {
		cout << i << "\n";
	}
	return 0;
}

