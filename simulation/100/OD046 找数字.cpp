#include <bits/stdc++.h>

using namespace std;

int main() {
  // 读取矩阵行数和列数
  int rows, cols;
  cin >> rows >> cols;

  // 创建二维数组存储输入
  vector<vector<int> > nums(rows, vector<int>(cols));

  // 读取矩阵元素
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cin >> nums[i][j];
    }
  }

  // 创建结果矩阵
  vector<vector<int> > result(rows, vector<int>(cols));

  // 遍历每个元素
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int min_dist = INT_MAX;

      // 在整个矩阵中查找值相同的元素
      for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
          // 跳过自身
          if (i == x && j == y)
            continue;

          // 找到值相同的元素
          if (nums[i][j] == nums[x][y]) {
            // 计算曼哈顿距离
            int dist = abs(i - x) + abs(j - y);
            // 更新最小距离
            min_dist = min(min_dist, dist);
          }
        }
      }

      // 更新结果矩阵
      result[i][j] = (min_dist == INT_MAX) ? -1 : min_dist;
    }
  }

  cout << "[";
  for (int i = 0; i < rows; i++) {
    cout << "[";
    for (int j = 0; j < cols; j++) {
      cout << result[i][j];
      if (j < cols - 1)
        cout << ", ";
    }
    cout << "]";
    if (i < rows - 1)
      cout << ", ";
  }
  cout << "]" << endl;

  return 0;
}