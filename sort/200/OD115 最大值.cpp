// OD115 最大值
// 题目描述：
// 给定一组整数（非负），重排顺序后输出一个最大的整数。
// 示例 1
// 输入：[10,9]
// 输出：910
// 说明: 输出结果可能非常大，所以你需要返回一个字符串而不是整数。
// 输入描述：
// 数字组合
// 输出描述：
// 最大的整数
// 用例 1：
// 输入：
// ```
// 10 9
// ```
// 输出：
// ```
// 910
// ```
// 难度：中等
// 标签：贪心、排序、字符串、数组

#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);
  stringstream ss(input);

  vector<string> nums;
  string num;

  while (ss >> num) {
    nums.push_back(num);
  }

  ranges::sort(nums, [](const string& a, const string& b) {
    return a + b > b + a;
  });

  string result;
  for (const string& n : nums) {
    result += n;
  }

  // 处理边界情况
  if (result[0] == '0') {
    cout << "0" << endl; // 如果最高位是 0，则结果是 0
  } else {
    cout << result << endl;
  }

  return 0;
}