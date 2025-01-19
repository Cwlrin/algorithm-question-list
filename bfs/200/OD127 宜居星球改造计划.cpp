#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

int main() {
  string line;
  vector<vector<string> > grid;
  int rows = 0, cols = 0;

  // 读取输入
  while (getline(cin, line)) {
    stringstream ss(line);
    vector<string> row;
    string cell;
    while (ss >> cell) {
      row.push_back(cell);
    }
    grid.push_back(row);
    cols = row.size(); // 每行的列数
    rows++;
  }

  // BFS 初始化
  queue<pair<int, int> > q; // BFS 队列
  int total_no_count = 0;     // 统计可改造区域数量
  int days = 0;             // 记录所需天数

  // 填充初始队列和统计可改造区域
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (grid[i][j] == "YES") {
        q.push(make_pair(i, j)); // 初始化 BFS
      } else if (grid[i][j] == "NO") {
        total_no_count++; // 统计可改造区域
      }
    }
  }

  // 如果没有可改造区域，检查是否有已改造的区域
  if (total_no_count == 0) {
    cout << (q.empty() ? -1 : 0) << endl;
    return 0;
  }

  // BFS 扩散
  int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 上下左右方向

  while (!q.empty()) {
    int size = q.size();
    bool modified = false; // 标记这一轮是否有区域被改造

    for (int i = 0; i < size; ++i) {
      // 使用传统方式访问队列元素
      int x = q.front().first;
      int y = q.front().second;
      q.pop();

      // 尝试向上下左右扩散
      for (int j = 0; j < 4; ++j) {
        int new_x = x + directions[j][0];
        int new_y = y + directions[j][1];

        // 检查边界条件
        if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && grid[new_x][
              new_y] == "NO") {
          grid[new_x][new_y] = "YES";      // 更新为已改造区域
          q.push(make_pair(new_x, new_y)); // 加入队列
          total_no_count--;                // 可改造区域减少
          modified = true;               // 标记发生改造
        }
      }
    }

    // 如果这一轮有更新，表示天数加一
    if (modified) {
      days++;
    }
  }

  // 如果所有可改造区域都已改造
  cout << (total_no_count == 0 ? days : -1) << endl;

  return 0;
}