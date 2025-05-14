#include <iostream>
#include <set>
#include <vector>

using namespace std;

int N;
vector<int> X, Y;
vector<vector<int>> grid;
set<int> used;

vector<vector<pair<int, int>>> rowPairs, colPairs;

void precomputePairs() {
    rowPairs.resize(N);
    for (int i = 0; i < N; ++i) {
        int product = Y[i];
        for (int a = 1; a * a <= product; ++a) {
            if (product % a == 0) {
                int b = product / a;
                if (a != b) {
                    rowPairs[i].push_back({a, b});
                    rowPairs[i].push_back({b, a});
                }
            }
        }
    }

    colPairs.resize(N);
    for (int i = 0; i < N; ++i) {
        int product = X[i];
        for (int a = 1; a * a <= product; ++a) {
            if (product % a == 0) {
                int b = product / a;
                if (a != b) {
                    colPairs[i].push_back({a, b});
                    colPairs[i].push_back({b, a});
                }
            }
        }
    }
}

bool isValid(int row, int col, int num) {
    int count = 0;
    for (int r = 0; r < N; ++r)
        if (grid[r][col] != 0) count++;
    if (count >= 2) return false;

    return true;
}

bool backtrack(int row) {
    if (row == N) {
        for (int col = 0; col < N; ++col) {
            vector<int> nums;
            for (int r = 0; r < N; ++r)
                if (grid[r][col] != 0) nums.push_back(grid[r][col]);
            if (nums.size() != 2 || nums[0] * nums[1] != X[col]) return false;
        }
        return true;
    }

    for (auto& pair : rowPairs[row]) {
        int a = pair.first, b = pair.second;
        if (used.count(a) || used.count(b)) continue;

        for (int c1 = 0; c1 < N; ++c1) {
            for (int c2 = c1 + 1; c2 < N; ++c2) {
                if (grid[row][c1] == 0 && grid[row][c2] == 0) {
                    if (isValid(row, c1, a) && isValid(row, c2, b)) {
                        grid[row][c1] = a;
                        grid[row][c2] = b;
                        used.insert(a);
                        used.insert(b);

                        if (backtrack(row + 1)) return true;

                        grid[row][c1] = 0;
                        grid[row][c2] = 0;
                        used.erase(a);
                        used.erase(b);
                    }
                }
            }
        }
    }

    return false;
}

int main() {
    N = 3;
    X = {6, 6, 6};
    Y = {6, 6, 6};
    grid.resize(N, vector<int>(N, 0));

    precomputePairs();

    if (backtrack(0)) {
        cout << "Loi giai:" << endl;
        for (auto& row : grid) {
            for (int num : row) cout << (num ? to_string(num) : "0") << " ";
            cout << endl;
        }
    } else {
        cout << "Khong co loi giai." << endl;
    }

    return 0;
}