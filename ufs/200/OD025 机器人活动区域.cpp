#include <bits/stdc++.h>
using namespace std;
// 四个方向：上、下、左、右
vector<pair<int, int> > directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// DFS遍历可达区域
int dfs(int x, int y, vector<vector<int> >& grid,
        vector<vector<bool> >& visited) {
  visited[x][y] = true; // 标记当前网格为已访问
  int area = 1;         // 统计当前网格
  // 遍历四个方向
  for (auto dir : directions) {
    int new_x = x + dir.first;
    int new_y = y + dir.second;
    // 检查边界条件和可移动条件
    if (new_x >= 0 && new_x < grid.size() &&
        new_y >= 0 && new_y < grid[0].size() &&
        !visited[new_x][new_y] &&
        abs(grid[new_x][new_y] - grid[x][y]) <= 1) {
      area += dfs(new_x, new_y, grid, visited); // 递归查找
    }
  }
  return area; // 返回当前可活动区域大小
}

int main() {
  int m, n;
  cin >> m >> n;
  vector<vector<int> > grid(m, vector<int>(n));
  // 输入网格
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> grid[i][j];
    }
  }
  vector<vector<bool> > visited(m, vector<bool>(n, false)); // 记录访问状态
  int max_area = 0;                                         // 记录最大活动区域
  // 遍历每个网格
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (!visited[i][j]) {
        // 只处理未访问的网格
        int area = dfs(i, j, grid, visited); // 计算当前网格的区域大小
        max_area = max(max_area, area);      // 更新最大区域
      }
    }
  }
  // 输出最大活动区域的网格点数目
  cout << max_area << endl;
  return 0;
}