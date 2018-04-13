#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <limits>
using namespace std;
typedef long long ll;

const int inf = 2e9 + 100;
const int CMAX = 1e5 + 1e2;
struct rope {
	// We'll be keeping only one revision to copy/paste segments
private:
	typedef struct tNode {
		tNode *l = NULL, *r = NULL;
		// X now is just a value of the node
		// key is now implicit
		// Y is implicit now too!
		int X, subSize = 0;

		//int height = 0;
		tNode() {}
		tNode(int x) {
			//height = 0;
			subSize = 0;
			X = x;
			l = r = NULL;
		}
		tNode(int x, tNode *left, tNode*right) {
			X = x; l = left; r = right; //height = 0;
		}
		void updateSize() {
			if (!this)return;
			//height = 1 + max(l ? l->height : 0, r ? r->height : 0);
			subSize = 1 + (l ? l->subSize : 0) + (r ? r->subSize : 0);
		}
	} *node;
	int getSize(node lead) { return lead ? lead->subSize : 0; }
	tNode * root = NULL;

	void split(node lead, node & left, node & right, int insertPos, int currPos = 0) {
		if (!lead) {
			left = right = NULL; return;
		}
		left = right = NULL;
		int localPos = currPos + getSize(lead->l);
		if (localPos > insertPos) {
			split(lead->l, left, right, insertPos, currPos);
			right = new tNode(lead->X, right, lead->r);
			right->updateSize();
		}
		else {
			split(lead->r, left, right, insertPos, localPos + 1);
			left = new tNode(lead->X, lead->l, left);
			left->updateSize();
		}
		lead->updateSize();
	}

	void split_light(node lead, node & left, node & right, int insertPos, int currPos = 0) {
		if (!lead) {
			left = right = NULL; return;
		}
		int localPos = currPos + getSize(lead->l);
		if (localPos > insertPos) {
			split_light(lead->l, left, lead->l, insertPos, currPos); right = lead;
		}
		else {
			split_light(lead->r, lead->r, right, insertPos, localPos + 1); left = lead;
		}
		lead->updateSize();
	}
	node merge_light(node left, node right) {
		if (!left || !right) left ? left->updateSize() : right->updateSize();
		if (!left || !right) return left ? left : right;
		if (goLeft(left, right)) {
			left->r = merge_light(left->r, right);
			left->updateSize();
			return left;
		}
		else {
			right->l = merge_light(left, right->l);
			right->updateSize();
			return right;
		}
	}
	bool goLeft(node left, node right) {
		if (!left) return false;
		if (!right) return true;
		//return rand() % 2
		// This works for some reason
		return rand() % (left->subSize + right->subSize) < left->subSize;
		//return  (abs(rand()*rand())) % (left->subSize + right->subSize) < left->subSize;
		return  ((1 << rand()) ^ rand()) % (left->subSize + right->subSize) < left->subSize;
		return ((ll)rand() * (left->subSize) * right->subSize) < (ll)left->subSize * RAND_MAX;
	}
	node merge(node left, node right) {
		if (!left || !right) left ? left->updateSize() : right->updateSize();
		if (!left || !right) return left ? left : right;
		if (goLeft(left, right)) {
			node revNode = new tNode(left->X, left->l, merge(left->r, right));
			revNode->updateSize();
			return revNode;
		}
		else {
			node revNode = new tNode(right->X, merge(left, right->l), right->r);
			revNode->updateSize();
			return revNode;
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
		split_light(root, lDum, rDum, pos - 1);
		root = merge_light(merge_light(lDum, new tNode(key)), rDum);
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
		cout << "( " << lead->X << ");\n";
		if (lead->r) printTree(lead->r);
	}
	void print() {
		printTree(root);
	}

	void copypasteSegment(int copyFrom, int copyTo, int pasteFrom) {
		copyFrom--; pasteFrom--;
		int size = copyTo - copyFrom + 1;
		node split1left, split1right;
		split(root, split1left, split1right, copyTo - 1);
		split(split1left, split1left, split1right, copyFrom - 1);
		// should be ok

		node s4, s5, s6;
		split(root, s4, s6, pasteFrom + size - 2);
		split(s4, s4, s5, pasteFrom - 1);
		// should be ok
		root = merge(s4, merge(split1right, s6));
		delete(s5); delete(split1left); 
	}
};

rope rop = rope();


int main()
{
	srand(9085456);
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif // __DEBUG
	int n, m; cin >> n >> m;
	// build array
	for (int i = n; i >= 1; i--) {
		rop.insert(0, i);
	}
	vector<vector<int> > quer;
	while (m--) {
		int cnt, from, to; cin >> cnt >> from >> to;
		quer.push_back({ from,from+cnt-1,to });
	}
	for (int i = quer.size() - 1; i >= 0; i--) {
		int f, t, cf;  f = quer[i][0]; t = quer[i][1]; cf = quer[i][2];
		int msize = t - f;
		for(int j = 0; j < 1; j++)
			rop.copypasteSegment(cf, cf + msize, f); 
	}
	for (int i = 1; i <= n; i++) {
		cout << rop.get(i) << " ";
	}


	return 0;
}