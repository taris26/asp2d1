#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

class node {
private:
	node* parent = NULL, * left = NULL, * right = NULL;

public:
	int key;

	node* search(int key, int& num) {
		node* last = NULL, * curr = this;
		while (curr) {
			last = curr;
			num++;
			if (key == curr->key) {
				break;
			}
			if (key > curr->key) {
				curr = curr->right;
			}
			else if (key < curr->key) {
				curr = curr->left;
			}
		}
		return last;
	}

	node(node** proot, int num) {
		key = num;
		if (*proot == NULL) {
			*proot = this;
			return;
		}
		int temp;
		node* curr = (**proot).search(key, temp), * last = NULL;
		if (key == curr->key) {
			if (curr->left) {
				curr = curr->left;
				while (curr) {
					last = curr;
					curr = curr->right;
				}
				last->right = this;
				this->parent = last;
			}
			else {
				curr->left = this;
				this->parent = curr;
			}
			return;
		}

		if (key < curr->key) {
			curr->left = this;
		}
		else {
			curr->right = this;
		}
		this->parent = curr;
	}

	void erase() {
		if (!this) return;
		if (this->parent) {
			if (this->parent->left == this) this->parent->left = NULL;
			else if (this->parent->right == this) this->parent->left = NULL;
		}
		queue<node*> q;
		q.push(this);
		while (!q.empty()) {
			node* curr = q.front();
			q.pop();
			if (curr->left) q.push(curr->left);
			if (curr->right) q.push(curr->right);
			delete curr;
		}
	}

	int getHeight() {
		if (!this) return 0;
		int ans = 0;
		stack<pair<node*, int>> s;
		s.push({ this, 1 });
		while (!s.empty()) {
			pair<node*, int> temp = s.top();
			s.pop();
			ans = max(ans, temp.second);
			if (temp.first->right) {
				s.push({ temp.first->right, temp.second + 1 });
			}
			if (temp.first->left) {
				s.push({ temp.first->left, temp.second + 1 });
			}
		}
		return ans;
	}

	void print() {
		queue<node*> q;
		q.push(this);
		int h = getHeight(), rowlen = 1 << h + 1;
		for (int i = 0; i < h; i++) {
			int br = 1 << i;
			int space = (rowlen - 2 * br) / br / 2;
			for (int j = 0; j < space; j++) cout << " ";
			for (int j = 0; j < br; j++) {
				node* temp = q.front();
				q.pop();
				if (temp) {
					q.push(temp->left);
					q.push(temp->right);
					printf("%2d", temp->key);
				}
				else {
					q.push(NULL);
					q.push(NULL);
					printf("  ");
				}
				for (int k = 0; k < space; k++) cout << "  ";
			}
			cout << endl;
		}
	}
};

void generateArray(int k, vector<int>& K, int low, int high) {
	srand(time(NULL));
	set<int> skup;
	for (int i = 0; i < k; i++) {
		/*K.push_back(low + rand() % (high - low - k + i + 1));
		low = K.back() + 1;*/
		int temp = low + rand() % (high - low);
		while (skup.count(temp)) {
			temp = low + rand() % (high - low);
		}
		skup.insert(temp);
		K.push_back(temp);
	}
	sort(K.begin(), K.end());
	for (int elem : K) cout << elem << " ";
	cout << endl;
}

node* transform(vector<int>& K) {
	node* root = NULL;
	int k = K.size();
	queue<pair<int, int>> q;
	q.push({ 0, k - 1 });
	while (!q.empty()) {
		int l = q.front().first, r = q.front().second;
		q.pop();
		if (l <= r) {
			int m = (l + r) / 2;
			new node(&root, K[m]);
			q.push({ l, m - 1 });
			q.push({ m + 1, r });
		}
	}
	return root;
}

void evaluate(node* root, vector<int>& P) {
	int sum = 0;
	for (int el : P) {
		cout << el << ": ";
		int num = 0;
		node* temp = root->search(el, num);
		if (!temp || temp->key != el) cout << "Nije pronadjen";
		else cout << "Pronadjen";
		cout << " (" << num << " koraka)\n";
		sum += num;
	}
	cout << "Prosek: " << 1.0 * sum / P.size() << endl;
}

int main() {
	vector<int> K, P;
	int k, item, key, num = 0;
	node* root = NULL, * temp;
	//K = { 1, 7, 10, 14, 18, 22, 23, 27, 29, 31, 37, 39, 41, 47, 48, 58, 62, 64, 72, 73, 76, 78, 82, 83, 84, 88, 90, 91, 95, 98 };
	//P = { 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	while (1) {
		cout << "1. Unos niza sa standardnog ulaza\n2. Pseudoslucajno generisanje niza\n"
			"3. Formiranje stabla\n4. Umetanje novog kljuca\n5. Pretraga kljuca\n"
			"6. Ispis stabla\n7. Evaluacija performansi\n8. Brisanje stabla\n9. Izlaz\n\n";
		cin >> item;
		switch (item)
		{
		case 1:
			cout << "1. Niz K\n2. Niz P\n\n";
			cin >> item;
			cout << "Uneti k:\n\n";
			cin >> k;
			if (k < 1) {
				cout << "Neodgovarajuza dimenzija\n\n";
				break;
			}
			for (int i = 0; i < k; i++) {
				int temp;
				cin >> temp;
				if (item == 1)
					K.push_back(temp);
				else if (item == 2)
					P.push_back(temp);
			}
			break;
		case 2:
			cout << "1. Niz K\n2. Niz P\n\n";
			int low, high;
			cin >> item;
			cout << "Uneti k i granice opsega:\n\n";
			cin >> k >> low >> high;
			if (k < 1 || k>high - low || low > high) {
				cout << "Neodgovarajuci parametri\n\n";
				break;
			}
			if (item == 1)
				generateArray(k, K, low, high);
			if (item == 2)
				generateArray(k, P, low, high);
			break;
		case 3:
			root = transform(K);
			break;
		case 4:
			cout << "Uneti kljuc:\n\n";
			cin >> key;
			new node(&root, key);
			break;
		case 5:
			cout << "Uneti kljuc:\n\n";
			/*if (!root) {
				cout<<"Ne postoji stablo"
			}*/
			cin >> key;
			num = 0;
			temp = root->search(key, num);
			if (!temp || temp->key != key) cout << "Nije pronadjen";
			else cout << "Pronadjen";
			cout << " (" << num << " koraka)\n";
			break;
		case 6:
			root->print();
			break;
		case 7:
			evaluate(root, P);
			break;
		case 8:
			root->erase();
			K = {};
			P = {};
			cout << "Stablo obrisano\n\n";
			break;
		default:
			return 0;
		}
	}
	return 0;
}