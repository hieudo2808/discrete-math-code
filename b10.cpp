#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int n, M;
vector<int> a;     // chứa 1..n^2
set<string> seen;  // lưu signature đã in (dạng chuẩn)

int magicSum;
bool isMagic(const vector<int> &A) {
    // kiểm tra hàng, cột, 2 chéo
    // hàng
    for (int i = 0; i < n; i++) {
        int s = 0;
        for (int j = 0; j < n; j++) s += A[i * n + j];
        if (s != magicSum) return false;
    }
    // cột
    for (int j = 0; j < n; j++) {
        int s = 0;
        for (int i = 0; i < n; i++) s += A[i * n + j];
        if (s != magicSum) return false;
    }
    // chéo chính
    int s1 = 0, s2 = 0;
    for (int i = 0; i < n; i++) {
        s1 += A[i * n + i];
        s2 += A[i * n + (n - 1 - i)];
    }
    return s1 == magicSum && s2 == magicSum;
}

// tạo tất cả 8 biến thể quay/đối xứng, chọn đại diện lexicographically nhỏ nhất
string canonical(const vector<int> &A) {
    vector<string> forms;
    auto idx = [&](int i, int j) { return i * n + j; };
    for (int t = 0; t < 8; t++) {
        vector<int> B(n * n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                int ii = i, jj = j;
                // 0..3: quay 0°,90°,180°,270°
                // 4..7: cùng 4 hình trên nhưng phản chiếu ngang thêm
                int ti = i, tj = j;
                // quay k*90
                int k = t % 4;
                if (k == 1) {
                    ti = j;
                    tj = n - 1 - i;
                }
                if (k == 2) {
                    ti = n - 1 - i;
                    tj = n - 1 - j;
                }
                if (k == 3) {
                    ti = n - 1 - j;
                    tj = i;
                }
                // nếu phản chiếu (t>=4), hoán đổi cột
                if (t >= 4) tj = n - 1 - tj;
                B[ti * n + tj] = A[idx(i, j)];
            }
        // chuyển thành chuỗi so sánh
        string s;
        for (int x : B) {
            s += to_string(x) + ",";
        }
        forms.push_back(s);
    }
    return *min_element(forms.begin(), forms.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    M = n * n;
    for (int i = 1; i <= M; i++) a.push_back(i);
    magicSum = n * (M + 1) / 2;
    // tính tổng theo công thức ma phương: S = n*(n^2+1)/2

    do {
        if (isMagic(a)) {
            string key = canonical(a);
            if (!seen.count(key)) {
                seen.insert(key);
                // in
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) cout << setw(3) << a[i * n + j];
                    cout << "\n";
                }
                cout << "\n";
            }
        }
    } while (next_permutation(a.begin(), a.end()));

    return 0;
}
