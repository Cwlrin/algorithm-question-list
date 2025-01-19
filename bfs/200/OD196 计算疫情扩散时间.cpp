#include <bits/stdc++.h>

using namespace std;

int main() {
  string line;
  getline(cin, line);

  // 将输入的数字字符串转换为二维数组  
  vector<int> nums;
  stringstream ss(line);
  string token;

  while (getline(ss, token, ',')) {
    nums.push_back(stoi(token));
  }

  int n = sqrt(nums.size());
  vector<vector<int> > grid(n, vector<int>(n));
  queue<pair<int, int> > q; // BFS 队列  
  int fresh_count = 0;       // 计算未感染区域  
  int days = 0;

  // 将输入填充到网格中，并初始化队列和未感染区域计数  
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      grid[i][j] = nums[i * n + j];
      if (grid[i][j] == 1) {
        q.push({i, j}); // 记录感染区域的坐标  
      } else {
        fresh_count++; // 统计未感染区域  
      }
    }
  }

  // 如果没有未感染区域或全部区域感染  
  if (fresh_count == 0) {
    cout << -1 << endl;
    return 0;
  }

  // BFS 扩散  
  while (!q.empty()) {
    int size = q.size();
    for (int i = 0; i < size; ++i) {
      // 使用 std::get 获取队列元素  
      int x = q.front().first;
      int y = q.front().second;
      q.pop();

      // 尝试向上下左右传播感染  
      for (const auto& direction : {make_pair(-1, 0), make_pair(1, 0),
                                    make_pair(0, -1), make_pair(0, 1)}) {
        int dx = direction.first;
        int dy = direction.second;
        int new_x = x + dx;
        int new_y = y + dy;

        // 检查边界和感染条件  
        if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < n && grid[new_x][new_y]
            == 0) {
          grid[new_x][new_y] = 1; // 更新为感染区域  
          q.push({new_x, new_y}); // 加入队列  
          fresh_count--;         // 未感染区域计数减少  
        }
      }
    }
    // 仅在 BFS 完成后才增加天数  
    if (!q.empty()) {
      days++;
    }
  }

  // 如果存在未感染区域，则返回 -1  
  if (fresh_count > 0) {
    cout << -1 << endl;
  } else {
    cout << days << endl;
  }

  return 0;
}