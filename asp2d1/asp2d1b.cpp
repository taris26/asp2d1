#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

void generateArray(int k, vector<int>& K, int low, int high) {
	srand(time(NULL));
	set<int> skup;
	for (int i = 0; i < k; i++) {
		/*K.push_back(low + rand()%(high-low-k+i+1));
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

int marySearch(int m, vector<int>& K, int key, int& num, int l = 0, int r = -1) {
	if (r == -1) r = K.size() - 1;
	while (l <= r) {
		int ls = l;
		for (int i = 1; i < m; i++) {
			num++;
			int c = ls + (r - ls) * i / m;
			if (K[c] > key) {
				r = c - 1;
				break;
			}
			else if (K[c] == key) {
				return c;
			}
			l = c + 1;
		}
	}
	return -1;
}

void optimizedSearch(int m, vector<int>& K, vector<int>& P, vector<int>& R, int& num) {
	int l = 0;
	for (int key : P) {
		//num = 0;
		int pos = marySearch(m, K, key, num, l);
		R.push_back(pos);
		//cout << key << ": " << pos << ", " << num << endl;
		l = max(l, pos + 1);
	}
}

void evalMary(vector<int>& K, vector<int>& P) {
	for (int m = 2; m <= 6; m++) {
		int sum = 0;
		for (int key : P) {
			int num = 0;
			int pos = marySearch(m, K, key, num);
			//cout << key << ": " << pos << ", " << num << endl;
			sum += num;
		}
		cout << m << ": " << 1.0 * sum / P.size() << endl;
	}
	cout << endl;
}

void evalOptimized(vector<int>& K, vector<int>& P) {
	for (int m = 2; m <= 6; m++) {
		int sum = 0;
		vector<int> R;
		optimizedSearch(m, K, P, R, sum);
		cout << m << ": " << 1.0 * sum / P.size() << endl;
	}
	cout << endl;
}

int main()
{
	int k, m, key, num = 0, item;
	vector<int> K, P, R;
	/*K = { 1,2,3,4 };
	P = { 2,1,3,4 };*/
	/*generateArray(k, K, 1, 1000000);
	generateArray(k, P, 1, 1000000);*/
	ifstream fajl("array.txt");
	while (1) {
		cout << "1. Unos niza sa standardnog ulaza\n2. Unos niza iz datoteke\n3. Pseudoslucajno generisanje niza\n"
			"4. M-arna pretraga niza K\n5. Optimizovana pretraga niza K na niz P\n6. Evaluacija M-arne pretrage\n"
			"7. Evaluacija optimizovane pretrage\n8. Izlaz\n\n";
		cin >> item;
		switch (item)
		{
		case 1:
			cout << "1. Niz K\n 2. Niz P\n\n";
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
			if (!fajl.is_open()) return 0;
			fajl >> k;
			for (int i = 0; i < k; i++) {
				int temp;
				fajl >> temp;
				K.push_back(temp);
			}
			break;
		case 3:
			cout << "1. Niz K\n2. Niz P\n\n";
			int low, high;
			cin >> item;
			cout << "Uneti k i granice opsega:\n\n";
			cin >> k >> low >> high;
			if (k < 1 || k>high - low || low>high) {
				cout << "Neodgovarajuci parametri\n\n";
				break;
			}
			if (item == 1)
				generateArray(k, K, low, high);
			if (item == 2)
				generateArray(k, P, low, high);
			break;
		case 4:
			cout << "Uneti m i kljuc:\n\n";
			cin >> m >> key;
			if (m < 2) cout << "Neodgovarajuci parametar\n\n";
			cout << marySearch(m, K, key, num) << endl;
			break;
		case 5:
			cout << "Uneti m:\n\n";
			cin >> m;
			if (m < 2) cout << "Neodgovarajuci parametar\n\n";
			optimizedSearch(m, K, P, R, num);
			for (int pos : R) {
				cout << pos << " ";
			}
			cout << endl;
			break;
		case 6:
			evalMary(K, P);
			break;
		case 7:
			evalOptimized(K, P);
			break;
		default:
			/*for (int i : K) {
				cout << i << ", ";
			}
			cout << endl;
			for (int i : P) {
				cout << i << ", ";
			}*/
			return 0;
		}
	}
	return 0;
}