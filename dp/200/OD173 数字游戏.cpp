#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
  int n, m;
  while (cin >> n >> m) {
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
      cin >> nums[i];
    }

    // 前缀和和哈希表
    unordered_set<int> mod_set;
    int prefix_sum = 0;
    bool found = false;

    for (int i = 0; i < n; ++i) {
      prefix_sum += nums[i];
      int mod = prefix_sum % m;

      // 如果模数为0，说明前i+1张牌的和可以整除m
      if (mod == 0) {
        found = true;
        break;
      }

      // 如果模数已经存在于哈希表中，说明存在满足条件的子数组
      if (mod_set.find(mod) != mod_set.end()) {
        found = true;
        break;
      }

      // 将当前模数加入哈希表
      mod_set.insert(mod);
    }

    // 输出结果
    cout << (found ? 1 : 0) << endl;
  }

  return 0;
}