#include <bits/stdc++.h>

using namespace std;

// 计算非环形数组的最大得分
int RobHelper(const vector<int>& nums, int start, int end) {
  int prev2 = 0, prev1 = 0;
  for (int i = start; i <= end; ++i) {
    int curr = max(prev1, prev2 + nums[i]);
    prev2 = prev1;
    prev1 = curr;
  }
  return prev1;
}

int main() {
  // 读取输入
  vector<int> nums;
  int value;
  while (cin >> value) {
    nums.push_back(value);
  }

  // 处理环形数组
  if (nums.size() == 1) {
    cout << nums[0] << endl;
    return 0;
  }

  // 计算不包含第一个格子和不包含最后一个格子的最大得分
  int score1 = RobHelper(nums, 0, nums.size() - 2); // 不包含最后一个格子
  int score2 = RobHelper(nums, 1, nums.size() - 1); // 不包含第一个格子

  // 输出结果
  cout << max(score1, score2) << endl;

  return 0;
}