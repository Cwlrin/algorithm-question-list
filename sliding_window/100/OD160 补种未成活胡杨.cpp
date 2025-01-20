#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n, m; // n: 总棵树, m: 死树棵数  
  cin >> n >> m;

  vector<int> dead(m); // 保存未成活的树编号  
  for (int i = 0; i < m; i++) {
    cin >> dead[i];
  }

  int k; // 可补种的树棵数  
  cin >> k;

  // 如果未成活树的数量等于可补种的树数量，返回总树的数量  
  if (m == k) {
    cout << n << endl;
    return 0;
  }

  int max_length = 0; // 存储最大连续树的长度  

  // 遍历所有可能的补种起始位置  
  for (int i = 0; i <= m - k; i++) {
    // 计算左边界  
    int left_boundary = (i == 0) ? 1 : dead[i - 1] + 1; // 第一个补种时左边界是1  
    // 计算右边界  
    int right_boundary = (i + k < m) ? dead[i + k] - 1 : n; // 右边界考虑补种是否超出范围  

    // 计算当前段落的长度  
    int current_length = right_boundary - left_boundary + 1;
    max_length = max(max_length, current_length); // 更新最大长度  
  }

  // 输出结果  
  cout << max_length << endl;

  return 0;
}