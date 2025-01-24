#include <bits/stdc++.h>
using namespace std;

int main() {
  int rows, cols, size, min_power;
  cin >> rows >> cols >> size >> min_power;

  // 读取发电量矩阵  
  vector<vector<int> > power(rows, vector<int>(cols));
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      cin >> power[i][j];
    }
  }

  // 计算二维前缀和  
  vector<vector<int> > prefix_sum(rows + 1, vector<int>(cols + 1, 0));
  for (int i = 1; i <= rows; ++i) {
    for (int j = 1; j <= cols; ++j) {
      prefix_sum[i][j] = prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[
                          i - 1][j - 1] + power[i - 1][j - 1];
    }
  }

  int count = 0;

  // 遍历所有可能的正方形区域  
  for (int i = size; i <= rows; ++i) {
    for (int j = size; j <= cols; ++j) {
      int sum = prefix_sum[i][j] - prefix_sum[i - size][j] - prefix_sum[i][
                  j - size] + prefix_sum[i - size][j - size];
      if (sum >= min_power) {
        ++count;
      }
    }
  }

  // 输出结果  
  cout << count << endl;

  return 0;
}