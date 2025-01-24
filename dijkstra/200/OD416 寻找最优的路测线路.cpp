#include <bits/stdc++.h>
using namespace std;

int main() {
  int r, c;
  cin >> r >> c;

  // 读取栅格信号值  
  vector<vector<int> > cov(r, vector<int>(c));
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      cin >> cov[i][j];
    }
  }

  // 优先队列，存储 {当前路径的最小值, {行, 列}}  
  priority_queue<pair<int, pair<int, int> > > pq;
  pq.push({cov[0][0], {0, 0}});

  // 记录到达每个栅格时的路径最小值  
  vector<vector<int> > dist(r, vector<int>(c, -1));
  dist[0][0] = cov[0][0];

  // 四个方向：上下左右  
  int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  while (!pq.empty()) {
    auto top = pq.top();
    pq.pop();
    int current_min = top.first;
    int x = top.second.first;
    int y = top.second.second;

    // 如果到达终点，输出结果  
    if (x == r - 1 && y == c - 1) {
      cout << current_min << endl;
      return 0;
    }

    // 遍历四个方向  
    for (const auto& dir : dirs) {
      int nx = x + dir[0];
      int ny = y + dir[1];

      // 检查新位置是否在范围内  
      if (nx >= 0 && nx < r && ny >= 0 && ny < c) {
        // 计算新路径的最小值  
        int new_min = min(current_min, cov[nx][ny]);

        // 如果新路径的最小值更大，更新并加入优先队列  
        if (new_min > dist[nx][ny]) {
          dist[nx][ny] = new_min;
          pq.push({new_min, {nx, ny}});
        }
      }
    }
  }

  // 如果没有找到路径，输出 -1  
  cout << -1 << endl;
  return 0;
}