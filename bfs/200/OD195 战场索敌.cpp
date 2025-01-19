#include <bits/stdc++.h>

using namespace std;

void bfs(int start_x, int start_y, const vector<vector<char> >& grid,
         vector<vector<bool> >& visited, int& enemy_count) {
  int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 四个方向
  queue<pair<int, int> > q;
  q.push(make_pair(start_x, start_y)); // 使用 make_pair 创建 pair
  visited[start_x][start_y] = true;

  while (!q.empty()) {
    pair<int, int> current = q.front();
    q.pop();
    int cur_x = current.first;  // 获取 X 坐标
    int cur_y = current.second; // 获取 Y 坐标

    // 如果当前格子是敌人，增加敌人计数
    if (grid[cur_x][cur_y] == 'E') {
      enemy_count++;
    }

    for (auto& dir : directions) {
      int new_x = cur_x + dir[0];
      int new_y = cur_y + dir[1];

      // 检查边界和访问状态
      if (new_x >= 0 && new_x < grid.size() && new_y >= 0 && new_y < grid[0].
          size() &&
          grid[new_x][new_y] != '#' && !visited[new_x][new_y]) {
        visited[new_x][new_y] = true;
        q.push(make_pair(new_x, new_y)); // 加入队列
      }
    }
  }
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<vector<char> > grid(n, vector<char>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> grid[i][j];
    }
  }

  vector<vector<bool> > visited(n, vector<bool>(m, false));
  int valid_region_count = 0;

  // 遍历每个单元格，开始 BFS
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == '.' && !visited[i][j]) {
        int enemy_count = 0;
        bfs(i, j, grid, visited, enemy_count);
        // 检查敌人数是否小于 K
        if (enemy_count < k) {
          valid_region_count++;
        }
      }
      // 加入单独处理 enemy
      if (grid[i][j] == 'E' && !visited[i][j]) {
        int enemy_count = 0;
        bfs(i, j, grid, visited, enemy_count);
        // 检查敌人数是否小于 K
        if (enemy_count < k) {
          valid_region_count++;
        }
      }

    }
  }

  cout << valid_region_count << endl;

  return 0;
}