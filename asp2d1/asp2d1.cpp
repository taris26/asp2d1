#include <iostream>
#include <vector>

using namespace std;

int marySearch(int m, vector<int>& K, int key) {
    int k = K.size();
    int l = 0, r = k - 1;
    while (l <= r) {
        int ls = l;
        //int o = r - l;
        for (int i = 0; i <= m; i++) {
            int c = ls + (r - ls) * i / m;
            if (K[c] > key) {
                //l = lt;
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

int main()
{
    int k, m, key;
    vector<int> K = { 3,4,5,6,7,8,9,10,11,12,13,15,16 };
    /*cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> K[i];
    }
    cin >> m >> key;*/
    for (int i = 3; i <= 17; i++) {
        cout << i << ": " << marySearch(5, K, i) << endl;
    }
    //cout << 17 << ": " << marySearch(3, K, 17) << endl;
}
