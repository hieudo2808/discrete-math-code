#include <iostream>
#include <vector>
using namespace std;

int dx_kn[8] = {2, 2, 1, 1, -1, -1, -2, -2},
    dy_kn[8] = {1, -1, 2, -2, 2, -2, 1, -1};
// (chân ngựa)
int dx_rook[4] = {1, -1, 0, 0}, dy_rook[4] = {0, 0, 1, -1};
// (Xe, Tượng tương tự canh chéo)

struct Piece {
    char type;
};

int board[9][9];      // 0=rỗng, >0: index quân
bool attacked[9][9];  // đánh dấu ô bị khống chế

vector<Piece> pieces = {{'V'}, {'H'}, {'N'}, {'N'}, {'T'}, {'T'}, {'X'}, {'X'}};
bool used[8];

bool inb(int x, int y) { return x >= 1 && x <= 8 && y >= 1 && y <= 8; }

// đánh dấu/vô hiệu hoá tấn công từ vị trí (x,y)
void markAttack(int x, int y, bool on) {
    char t = board[x][y] ? pieces[board[x][y] - 1].type : 0;
    if (t == 'N') {
        for (int d = 0; d < 8; d++) {
            int nx = x + dx_kn[d], ny = y + dy_kn[d];
            if (inb(nx, ny)) attacked[nx][ny] = on;
        }
    } else if (t == 'V' || t == 'H' || t == 'T') {
        // Xe (V/H), Tượng (T), Hậu (H) = V+T
        vector<pair<int, int>> dirs;
        if (t == 'V' || t == 'H') {  // V chỉ dọc, H chỉ ngang
            if (t == 'V')
                dirs = {{1, 0}, {-1, 0}};
            else
                dirs = {{0, 1}, {0, -1}};
        } else {  // Tượng
            dirs = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        }
        // Hậu:
        if (t == 'H')  // H loại H=rook+bishop
            dirs = {{1, 0}, {-1, 0}, {0, 1},  {0, -1},
                    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        for (auto [dx, dy] : dirs) {
            int nx = x, ny = y;
            while (true) {
                nx += dx;
                ny += dy;
                if (!inb(nx, ny)) break;
                attacked[nx][ny] = on;
                if (board[nx][ny]) break;
            }
        }
    } else if (t == 'X') {
        // Xe (rook)
        for (int d = 0; d < 4; d++) {
            int nx = x, ny = y;
            while (inb(nx += dx_rook[d], ny += dy_rook[d])) {
                attacked[nx][ny] = on;
                if (board[nx][ny]) break;
            }
        }
    }
}

void dfs(int idx) {
    if (idx == 8) {
        // đã đặt đủ 8 quân, in được
        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                if (board[i][j])
                    cout << pieces[board[i][j] - 1].type;
                else
                    cout << '.';
            }
            cout << "\n";
        }
        cout << "\n";
        return;
    }
    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++) {
            if (board[i][j] == 0 && !attacked[i][j]) {
                board[i][j] = idx + 1;
                // đánh dấu tấn công
                markAttack(i, j, true);
                used[idx] = true;
                dfs(idx + 1);
                used[idx] = false;
                // bỏ đánh dấu
                markAttack(i, j, false);
                board[i][j] = 0;
            }
        }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    dfs(0);
    return 0;
}
