#include <bits/stdc++.h>

using namespace std;

int main() {
  // 读取输入  
  int n, m;
  cin >> n >> m;

  vector<vector<int> > matrix(n, vector<int>(m));

  // 读取矩阵  
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> matrix[i][j];
    }
  }

  int max_sum = INT_MIN; // 初始化最大和为最小整数值  

  // 固定上下边界  
  for (int top = 0; top < n; ++top) {
    vector<int> temp(m, 0);

    for (int bottom = top; bottom < n; ++bottom) {
      // 更新当前列的和  
      for (int j = 0; j < m; ++j) {
        temp[j] += matrix[bottom][j];
      }

      // 在temp数组上找到最大子数组和  
      int current_sum = 0;
      int max_current_sum = INT_MIN;

      for (int value : temp) {
        current_sum += value;
        if (current_sum > max_current_sum) {
          max_current_sum = current_sum;
        }
        if (current_sum < 0) {
          current_sum = 0;
        }
      }

      // 更新全局最大和
      max_sum = max(max_sum, max_current_sum);
    }
  }

  // 输出结果  
  cout << max_sum << endl;

  return 0;
}