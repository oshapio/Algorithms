#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string> 

using namespace std;
typedef long long ll;

struct treap { 
	typedef struct tNode {
		tNode *l = NULL, *r = NULL;
		int X, Y, subSize = 0;
		tNode() {}
		tNode(int x) {
			subSize = 0;
			X = x; Y = rand() * rand();
			l = r = NULL;
		}
		void updateSize() {
			if (!this)return;
			subSize = 1 + (l ? l->subSize : 0) + (r ? r->subSize : 0);
		}
	} *node;
	int getSize(node lead) { return lead ? lead->subSize : 0; }
	tNode * root = NULL;
	treap() { root = NULL; }
	void split(node lead, node & left, node & right, int key) {
		left = NULL; right = NULL;
		if (!lead) return;
		if (key >= lead->X) {
			split(lead->r, lead->r, right, key); left = lead;
		}
		else {
			split(lead->l, left, lead->l, key); right = lead;
		}
		lead->updateSize();
	}

	node merge(node left, node right) {
		if (!left || !right) left ? left->updateSize() : right->updateSize();
		if (!left || !right) return left ? left : right;
		if (left->Y > right->Y) {
			left->r = merge(left->r, right);
			left->updateSize();
			return left;
		}
		else {
			right->l = merge(left, right->l);
			right->updateSize();
			return right;
		}
	}

	node kTh(node lead, int K) {
		if (!lead) return NULL;
		if (getSize(lead->l) + 1 == K) return lead;
		else if (K > getSize(lead->l) + 1) {
			return kTh(lead->r, K - getSize(lead->l) - 1);
		}
		else return kTh(lead->l, K);
	}
	void insert(int key) {
		node lDum = NULL, rDum = NULL;
		split(root, lDum, rDum, key);
		root = merge(merge(lDum, new tNode(key)), rDum);
	}

	void erase(int key) {
		node lDum = NULL, midDum = NULL, rDum = NULL;
		split(root, lDum, rDum, key);
		split(lDum, lDum, midDum, key - 1);
		root = merge(lDum, rDum);
	}
	int size() {
		return !root ? 0 : root->subSize;
	}

	int getKth(int K) {
		if (K > size()) return -1;
		node dum = kTh(root, K);
		if (dum == NULL) return -1;
		else return dum->X;
	}

	void printTree(node lead) {
		if (lead->l) printTree(lead->l);
		cout << "( " << lead->X << "; " << lead->Y << " ) \n";
		if (lead->r) printTree(lead->r);
	}
	void print() {
		printTree(root);
	}

};

int main()
{
	treap t = treap();
	int n; cin >> n;
	while (n--) {
		string com; cin >> com; int key; cin >> key;
		key *= -1;
		if (com == "+1") {
			t.insert(key);
		}
		else if (com == "0") {
			key *= -1;
			cout << -t.getKth(key) << "\n";
		}
		else {
			t.erase(key);
		}
	}
	return 0;
}
