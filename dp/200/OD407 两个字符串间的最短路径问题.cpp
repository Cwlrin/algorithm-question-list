#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  string A, B;
  cin >> A >> B;

  int m = A.length();
  int n = B.length();

  // 使用两个一维数组代替二维数组  
  vector<int> pre_row(n + 1, 0);
  vector<int> cur_row(n + 1, 0);

  // 初始化 preRow（第一行）  
  for (int j = 0; j <= n; ++j) {
    pre_row[j] = j;
  }

  // 填充动态规划表  
  for (int i = 1; i <= m; ++i) {
    cur_row[0] = i; // 初始化当前行的第一列
    for (int j = 1; j <= n; ++j) {
      if (A[i - 1] == B[j - 1]) {
        cur_row[j] = pre_row[j - 1] + 1; // 斜边  
      } else {
        cur_row[j] = min(pre_row[j], cur_row[j - 1]) + 1; // 水平或垂直边  
      }
    }
    pre_row = cur_row; // 更新 preRow  
  }

  // 输出结果  
  cout << pre_row[n] << endl;

  return 0;
}