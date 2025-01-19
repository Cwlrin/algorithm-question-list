#include <bits/stdc++.h>

using namespace std;

int main() {
  int m, n;
  cin >> m >> n;

  vector<vector<int> > array(m, vector<int>(n));

  // 输入网格数组
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> array[i][j];
    }
  }

  // 读取需要计算的 (i, j)
  int target_i, target_j;
  cin >> target_i >> target_j;

  // BFS 初始化
  queue<tuple<int, int, int> > q; // (x, y, 信号强度)
  int signal_strength = 0;        // 信号源的强度

  // 查找信号源并初始化 BFS
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (array[i][j] > 0) {
        // 检查信号源
        q.push({i, j, array[i][j]});   // (行, 列, 信号强度)
        signal_strength = array[i][j]; // 保存信号强度
      }
    }
  }

  // 方向数组：上下左右
  int dx[4] = {-1, 1, 0, 0};
  int dy[4] = {0, 0, -1, 1};

  // 记录信号强度到达的值
  vector<vector<int> > signal_value(m, vector<int>(n, 0));
  signal_value[get<0>(q.front())][get<1>(q.front())] = signal_strength;
  // 信号源的强度初始化

  // BFS 传播信号
  while (!q.empty()) {
    auto [x, y, strength] = q.front();
    q.pop();

    // 逐邻居传播信号
    for (int i = 0; i < 4; ++i) {
      int new_x = x + dx[i];
      int new_y = y + dy[i];

      // 边界检查
      if (new_x < 0 || new_x >= m || new_y < 0 || new_y >= n)
        continue;
      // 不能到达阻碍物
      if (array[new_x][new_y] == -1)
        continue;

      int new_signal_strength = strength - 1; // 信号衰减
      // 只在信号大于现有值时更新
      if (new_signal_strength > signal_value[new_x][new_y]) {
        signal_value[new_x][new_y] = new_signal_strength; // 更新信号值
        q.push({new_x, new_y, new_signal_strength});      // 继续传播
      }
    }
  }

  // 输出目标位置的信号值
  cout << signal_value[target_i][target_j] << endl;

  return 0;
}