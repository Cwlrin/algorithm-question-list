#include <bits/stdc++.h>
using namespace std;

int main() {
  int m, n;
  char comma; // 用于读取逗号分隔的输入
  cin >> m >> comma >> n;

  // 读取地图数据
  vector<vector<int> > grid(m, vector<int>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> grid[i][j];
      if (j < n - 1) {
        cin >> comma; // 读取逗号
      }
    }
  }

  // 特殊情况检查：起始点或终点不可达
  if (grid[0][0] == 0 || grid[m - 1][n - 1] == 0) {
    cout << -1 << endl;
    return 0;
  }

  // 上下左右方向偏移量
  int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  // 状态存储：到达每个点所需的最小初始油量和最多剩余油量
  vector<vector<int> > min_initial_oil(m, vector<int>(n, INT_MAX));
  vector<vector<int> > max_remaining_oil(m, vector<int>(n, 0));

  // BFS 队列：用于存储每个状态
  deque<tuple<int, int, int, int, bool> > bfs_queue;
  // x, y, initial_oil, remaining_oil, refueled
  if (grid[0][0] == -1) {
    // 起点是加油站
    bfs_queue.emplace_back(0, 0, 0, 100, true);
    min_initial_oil[0][0] = 0;
    max_remaining_oil[0][0] = 100;
  } else {
    // 起点不是加油站
    bfs_queue.emplace_back(0, 0, grid[0][0], 0, false);
    min_initial_oil[0][0] = grid[0][0];
    max_remaining_oil[0][0] = 0;
  }

  while (!bfs_queue.empty()) {
    auto [x, y, initial_oil, remaining_oil, refueled] = bfs_queue.front();
    bfs_queue.pop_front();

    // 遍历所有四个方向
    for (const auto& dir : directions) {
      int nx = x + dir[0];
      int ny = y + dir[1];

      // 新位置越界或为障碍
      if (nx < 0 || ny < 0 || nx >= m || ny >= n || grid[nx][ny] == 0)
        continue;

      int new_initial_oil = initial_oil;
      int new_remaining_oil = remaining_oil;

      // 新位置是加油站
      if (grid[nx][ny] == -1) {
        new_remaining_oil = 100; // 加满油
        refueled = true;         // 标记已加油
      } else {
        // 消耗油量
        new_remaining_oil -= grid[nx][ny];
      }

      // 剩余油量不足处理
      if (new_remaining_oil < 0) {
        if (refueled)
          continue;                           // 已经加过油，不能再借油，直接跳过
        new_initial_oil -= new_remaining_oil; // 借油
        new_remaining_oil = 0;                // 剩余油量归零
      }

      // 如果初始油量过高（超出最大承载能力）
      if (new_initial_oil > 100)
        continue;

      // 更新状态
      if (new_initial_oil < min_initial_oil[nx][ny] ||
          (new_initial_oil == min_initial_oil[nx][ny] && new_remaining_oil >
           max_remaining_oil[nx][ny])) {
        // 记录更优的路径
        min_initial_oil[nx][ny] = new_initial_oil;
        max_remaining_oil[nx][ny] = new_remaining_oil;
        // 将新状态加入队列
        bfs_queue.emplace_back(nx, ny, new_initial_oil, new_remaining_oil,
                               refueled);
      }
    }
  }

  // 输出结果
  cout << (min_initial_oil[m - 1][n - 1] == INT_MAX
             ? -1
             : min_initial_oil[m - 1][n - 1]) << endl;
  return 0;
}