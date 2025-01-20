#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
  int m, n;
  cin >> m >> n;

  vector<vector<int> > matrix(m, vector<int>(n));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> matrix[i][j];
    }
  }

  // 将 (0, 0) 的值设为 1  
  if (matrix[0][0] == 0) {
    matrix[0][0] = 1;
  }

  // 定义方向数组  
  vector<pair<int, int> > directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  queue<pair<int, int> > bfs_queue; // BFS队列  
  bfs_queue.emplace(0, 0);           // 初始位置  

  int count = 0; // 记录值为1的元素个数  

  // BFS遍历  
  while (!bfs_queue.empty()) {
    pair<int, int> current = bfs_queue.front();
    bfs_queue.pop();

    int x = current.first;
    int y = current.second;

    // 当前元素被值为1记录  
    count++;

    // 遍历四个方向  
    for (const auto& dir : directions) {
      int new_x = x + dir.first;
      int new_y = y + dir.second;

      // 检查边界和同化条件  
      if (new_x >= 0 && new_x < m && new_y >= 0 && new_y < n && matrix[new_x][new_y]
          == 0) {
        matrix[new_x][new_y] = 1;      // 同化  
        bfs_queue.emplace(new_x, new_y); // 将新的位置加入队列  
      }
    }
  }

  // 最终输出矩阵中值为0或2的元素个数  
  int total_elements = m * n;               // 总元素个数  
  int non_one_count = total_elements - count; // 非1元素的个数  

  cout << non_one_count << endl; // 输出结果  
  return 0;
}