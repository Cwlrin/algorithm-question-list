#include <iostream>
#include <map>
#include <climits>
#include <vector>

using namespace std;

int main() {
  // 矩阵行数和列数  
  int n, m;
  cin >> n >> m;

  // 创建矩阵  
  vector<vector<int> > matrix(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> matrix[i][j];
    }
  }

  // 目标数组长度  
  int k;
  cin >> k;

  // 记录目标元素的计数  
  map<int, int> needed;
  for (int i = 0; i < k; i++) {
    int num;
    cin >> num;
    needed[num]++;
  }

  // 初始化变量：未匹配元素总数  
  int remaining = k;
  int min_width = INT_MAX;

  // 滑动窗口的左右边界  
  int left = 0, right = 0;

  // 开始滑动窗口  
  while (right < m) {
    // 将当前右边界列的元素纳入窗口  
    for (int row = 0; row < n; row++) {
      int current = matrix[row][right];

      // 如果是目标元素，减少计数  
      if (needed[current]-- > 0) {
        remaining--;
      }
    }

    // 当所有目标元素都被覆盖  
    while (remaining == 0) {
      // 更新最小宽度  
      min_width = min(min_width, right - left + 1);

      // 尝试收缩左边界  
      for (int row = 0; row < n; row++) {
        int current = matrix[row][left];

        // 恢复元素计数，检查是否需要重新匹配  
        if (needed[current]++ >= 0) {
          remaining++;
        }
      }

      // 左边界右移  
      left++;
    }

    // 右边界右移  
    right++;
  }

  // 输出结果  
  cout << (min_width == INT_MAX ? -1 : min_width) << endl;

  return 0;
}