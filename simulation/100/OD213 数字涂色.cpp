#include <bits/stdc++.h>
using namespace std;

int main() {
  // 读取输入
  int n;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  // 排序，方便处理
  sort(nums.begin(), nums.end());

  // 存储每个颜色组的最小值
  vector<int> color_groups;

  // 遍历每个数字
  for (int num : nums) {
    bool found_group = false;

    // 检查是否可以加入现有的组
    for (int min_num : color_groups) {
      if (num % min_num == 0) {
        found_group = true;
        break;
      }
    }

    // 如果不能加入任何现有组，创建新组
    if (!found_group) {
      color_groups.push_back(num);
    }
  }

  // 输出颜色组数量
  cout << color_groups.size() << endl;

  return 0;
}