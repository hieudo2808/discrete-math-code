#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> part;

void Try(int current_sum, int last) {
    if (current_sum == n) {
        for (int x : part) cout << x << ' ';
        cout << "\n";
        return;
    }

    for (int k = min(last, n - current_sum); k >= 1; k--) {
        part.push_back(k);
        Try(current_sum + k, k);
        part.pop_back();
    }
}

int main() {
    cout << "Nhap N: ";
    cin >> n;
    Try(0, n);
    return 0;
}
