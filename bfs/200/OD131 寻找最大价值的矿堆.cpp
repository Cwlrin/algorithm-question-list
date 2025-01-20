#include <bits/stdc++.h>
using namespace std;

int main() {
  int n = 0, m = 0;
  string line;
  vector<vector<int> > grid;

  // 读取输入行并构建地图
  while (getline(cin, line)) {
    vector<int> row;
    for (char ch : line) {
      row.push_back(ch - '0'); // 将字符转换为整数
    }
    grid.push_back(row);
  }

  n = grid.size();
  m = grid[0].size();
  vector<vector<bool> > visited(n, vector<bool>(m, false));
  int max_value = 0;

  // 定义四个方向
  int directions[4][2] = {
      {-1, 0}, // 上
      {1, 0},  // 下
      {0, -1}, // 左
      {0, 1}   // 右
  };

  // 遍历每个单元格
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!visited[i][j] && grid[i][j] > 0) {
        // 启动 BFS
        queue<pair<int, int> > q;
        q.emplace(i, j);
        visited[i][j] = true;

        int total_value = 0; // 当前矿堆的总价值

        while (!q.empty()) {
          pair<int, int> current = q.front();
          q.pop();
          int x = current.first;  // 获取 x 坐标
          int y = current.second; // 获取 y 坐标

          // 加上当前矿的价值
          total_value += grid[x][y];

          for (auto& dir : directions) {
            int new_x = x + dir[0], new_y = y + dir[1];

            // 检查边界和访问状态
            if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m &&
                !visited[new_x][new_y] && grid[new_x][new_y] > 0) {
              visited[new_x][new_y] = true;
              q.emplace(new_x, new_y); // 加入队列
            }
          }
        }

        // 更新最大矿堆的价值
        max_value = max(max_value, total_value);
      }
    }
  }

  cout << max_value << endl; // 输出最大矿堆的价值
  return 0;
}