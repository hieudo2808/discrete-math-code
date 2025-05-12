#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> partitions;
int n, k;

void Try(int index, vector<int>& partition) {
    if (index > n) {
        if (partition.size() == k) {
            partitions.push_back(partition);
        }
        return;
    }

    // Xếp quả bóng thứ i vào các hộp hiện có
    for (int i = 0; i < partition.size(); i++) {
        int old_subset = partition[i];
        partition[i] |= (1 << (index - 1));
        Try(index + 1, partition);
        partition[i] = old_subset;
    }

    // Tạo một hộp mới cho quả bóng thứ i
    if (partition.size() < k) {
        partition.push_back(1 << (index - 1));
        Try(index + 1, partition);
        partition.pop_back();
    }
}

int main() {
    cout << "Nhap n: ";
    cin >> n;
        
    cout << "Nhap k: ";
    cin >> k;
        
    vector<int> initial_partition;
    Try(1, initial_partition);
            
    cout << "Cac phan hoach: " << endl;
    
    for (auto& partition : partitions) {
        for (auto& item : partition) {
            cout << "{";
            bool first = true;
            for (int i = 1; i <= n; i++) {
                if (item & (1 << (i - 1))) {
                    if (!first) cout << ", ";
                    cout << i;
                    first = false;
                }
            }
            cout << "} ";
        }
        cout << endl;
    }
            
    return 0;
}