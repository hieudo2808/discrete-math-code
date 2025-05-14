#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int n, K;
vector<pair<int, int>> cells;  // danh sách (i,j) cần điền
vector<vector<int>> A;         // ma trận n×n (1-based)
vector<bool> used;             // đánh dấu số đã lấy
bool found = false;

void dfs(int idx, int sumNow) {
    if (idx == (int)cells.size()) {
        if (sumNow == K) {
            // in lời giải và dừng
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    cout << setw(2) << A[i][j] << ' ';
                }
                cout << "\n";
            }
            found = true;
        }
        return;
    }
    if (found) return;
    auto [i, j] = cells[idx];
    // thử tất cả giá trị chưa dùng
    for (int v = 1; v <= 3 * n - 3; v++) {
        if (!used[v] && sumNow + v <= K) {
            used[v] = true;
            A[i][j] = v;
            dfs(idx + 1, sumNow + v);
            if (found) return;
            used[v] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> K;
    A.assign(n + 1, vector<int>(n + 1, 0));
    // tạo danh sách cells (cột 1)
    for (int i = 1; i <= n; i++) cells.emplace_back(i, 1);
    // dòng n, từ cột 2..n
    for (int j = 2; j <= n; j++) cells.emplace_back(n, j);
    // đường chéo chính, từ i=1..n-1, j=i+1..n (tránh ô (n,1) & (n,n) đã thêm)
    for (int i = 1; i <= n - 1; i++) cells.emplace_back(i, i);

    used.assign(3 * n, false);
    dfs(0, 0);
    if (!found) cout << "Khong co loi giai\n";
    return 0;
}
