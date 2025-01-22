#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

// 深度优先搜索函数，用于寻找匹配
bool dfs(int row, int mid, const vector<vector<int> >& matrix,
         vector<int>& match, vector<bool>& visited) {
  for (int col = 0; col < matrix[0].size(); ++col) {
    // 如果该列没有被访问过，并且矩阵中对应元素的值小于等于 mid
    if (!visited[col] && matrix[row][col] <= mid) {
      visited[col] = true; // 标记该列已被访问
      // 如果该列没有匹配，或者可以重新匹配
      if (match[col] == -1 || dfs(match[col], mid, matrix, match, visited)) {
        match[col] = row; // 执行匹配
        return true;      // 匹配成功
      }
    }
  }
  return false; // 匹配失败
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<vector<int> > matrix(n, vector<int>(m));
  int max_val = INT_MIN;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> matrix[i][j];
      max_val = max(max_val, matrix[i][j]);
    }
  }

  int low = 1, high = max_val, result = -1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    vector<int> match(m, -1);       // 初始化匹配数组
    vector<bool> visited(m, false); // 初始化访问数组
    int count = 0;                  // 匹配成功的行数

    for (int i = 0; i < n; ++i) {
      fill(visited.begin(), visited.end(), false); // 清空访问标记
      if (dfs(i, mid, matrix, match, visited))
        count++; // 调用 dfs 进行匹配
    }

    // 根据匹配结果调整搜索范围
    if (count >= n - k + 1) {
      result = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  cout << result << endl;
  return 0;
}