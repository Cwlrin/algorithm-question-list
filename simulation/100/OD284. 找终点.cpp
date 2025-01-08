#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);
  vector<int> nums;
  int num;
  stringstream ss(input);
  while (ss >> num) {
    nums.push_back(num);
  }
  int n = nums.size();
  // 如果数组为空或者仅有一个元素，无法移动
  if (n <= 1) {
    cout << -1 << endl;
    return 0;
  }
  int min_steps = INT_MAX;
  // 尝试所有可能的第一步步长
  for (int first_step = 0; first_step < n / 2; ++first_step) {
    // 第一步的目标位置
    int current_pos = first_step;
    // 如果第一步已经越界，则跳过
    if (current_pos >= n) {
      break;
    }
    // 步数计数器
    int steps = 1;
    // 继续移动直到达成越界
    while (current_pos < n - 1) {
      // 获取当前位置的步长
      int next_step = nums[current_pos];
      // 计算下一个位置
      current_pos += next_step;
      // 步数增加
      steps++;
      // 如果越界，则当前尝试失败
      if (current_pos >= n) {
        break;
      }
    }
    // 如果成功到达最后一个元素
    if (current_pos == n - 1) {
      min_steps = min(min_steps, steps);
    }
  }
  cout << (min_steps == INT_MAX ? -1 : min_steps) << endl;
  return 0;
}