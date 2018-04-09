#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;
typedef long long ll;

const int inf = 2e9 + 100;

struct rope {
private:
	typedef struct tNode {
		tNode *l = NULL, *r = NULL;
		// X now is just a value of the node
		// key is now implicit
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

	void split(node lead, node & left, node & right, int insertPos, int currPos = 0) {
		if (!lead) {
			left = right = NULL; return;
		}
		int localPos = currPos + getSize(lead->l);
		if (localPos > insertPos) {
			split(lead->l, left, lead->l, insertPos, currPos); right = lead;
		}
		else {
			split(lead->r, lead->r, right, insertPos, localPos + 1); left = lead;
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
public:
	rope() { root = NULL; }
	void insert(int pos, int key) {
		node lDum = NULL, rDum = NULL;
		split(root, lDum, rDum, pos - 1);
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
	int get(int K) {
		node dum = kTh(root, K);
		if (dum == NULL) return -inf;
		else return dum->X;
	}
	void change(int pos, int newVal) {
		if (pos > size()) return;
		node dum = kTh(root, pos);
		if (dum == NULL) return;
		dum->X = newVal;
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
	rope r = rope();
	for (int i = 0; i < 10; i++) {
		r.insert(2, i);
	}
	for (int i = 0; i < 20; i++) {
		cout << i << " " << r.get(i) << "\n";
	}
	return 0;
}
