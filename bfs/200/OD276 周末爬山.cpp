#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cstdlib>  // for abs
using namespace std;

int main() {
  int m, n, k;
  cin >> m >> n >> k;

  // 读取地图
  vector<vector<int> > grid(m, vector<int>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> grid[i][j];
    }
  }

  // 定义方向数组：上下左右
  int dx[4] = {-1, 1, 0, 0};
  int dy[4] = {0, 0, -1, 1};

  // 记录访问状态
  vector<vector<bool> > visited(m, vector<bool>(n, false));

  // BFS 队列，存储坐标 (x, y) 和步数 step
  queue<tuple<int, int, int> > q;

  // 初始化
  q.push({0, 0, 0});
  visited[0][0] = true;

  // 记录最高山峰和最小步数
  int max_height = grid[0][0];
  int min_steps = 0;

  while (!q.empty()) {
    // 使用 std::get 获取队列元素
    int x = get<0>(q.front());
    int y = get<1>(q.front());
    int step = get<2>(q.front());
    q.pop();

    // 检查当前位置的高度
    int cur_height = grid[x][y];

    // 更新最高山峰和最小步数
    if (cur_height > max_height) {
      max_height = cur_height;
      min_steps = step; // 更新到更高峰的步数
    } else if (cur_height == max_height) {
      min_steps = min(min_steps, step); // 更新较小步数
    }

    // 四个方向搜索
    for (int i = 0; i < 4; ++i) {
      int new_x = x + dx[i];
      int new_y = y + dy[i];

      // 越界检查
      if (new_x < 0 || new_x >= m || new_y < 0 || new_y >= n)
        continue;
      // 已访问检查
      if (visited[new_x][new_y])
        continue;

      // 高度差检查
      if (abs(grid[new_x][new_y] - cur_height) > k)
        continue;

      // 标记访问并加入队列
      visited[new_x][new_y] = true;
      q.push({new_x, new_y, step + 1});
    }
  }

  // 检查结果输出
  if (max_height == grid[0][0]) {
    // 根据你的描述，如果没有可爬的更高山峰
    cout << "0 0" << endl;
  } else {
    cout << max_height << " " << min_steps << endl;
  }

  return 0;
}