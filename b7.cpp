#include <iostream>
#include <vector>
using namespace std;

int num, b;
vector<int> a, x;

void Try(int index, int sum) {
    if (index == num) {
        if (sum == b) {
            for (int i = 0; i < num; i++)
                cout << "x[" << i << "] = " << x[i] << ' ';
            cout << "\n";
        }
        return;
    }
    
    int max_k = (b - sum) / a[index];
    for (int i = 0; i <= max_k; i++) {
        x[index] = i;
        Try(index + 1, sum + i * a[index]);
    }
}

int main() {    
    cout << "Nhap so phan tu: ";
    cin >> num;

    cout << "Nhap ket qua can dat duoc: ";
    cin >> b;

    a.resize(num);
    cout << "Nhap cac phan tu a_1 den a_n: ";
    for (int i = 0; i < num; i++) 
        cin >> a[i];
    x.assign(num, 0);

    cout << "Cac tap hop phan tu thoa man la: \n";
    Try(0, 0);
    return 0;
}
