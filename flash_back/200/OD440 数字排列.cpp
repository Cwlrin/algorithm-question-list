#include <bits/stdc++.h>
using namespace std;

int main() {
  string input;
  getline(cin, input);

  // 解析输入
  vector<int> nums;
  stringstream ss(input);
  string item;
  while (getline(ss, item, ',')) {
    nums.push_back(stoi(item));
  }

  // 检查输入数量
  if (nums.size() != 4) {
    cout << "-1" << endl;
    return 0;
  }

  // 记录出现过的数字
  bool set[10] = {false};
  int n = INT_MIN;

  // 输入验证
  for (const auto& num : nums) {
    // 检查数字范围
    if (num < 1 || num > 9) {
      cout << "-1" << endl;
      return 0;
    }

    // 检查重复数字
    if (set[num]) {
      cout << "-1" << endl;
      return 0;
    }

    set[num] = true;
    // 找出最大数字
    n = max(n, num);
  }

  // 特殊数字冲突检查
  if (set[2] && set[5]) {
    cout << "-1" << endl;
    return 0;
  }
  if (set[6] && set[9]) {
    cout << "-1" << endl;
    return 0;
  }

  // 特殊数字替换映射
  map<int, int> dic = {
      {2, 5}, {5, 2},
      {6, 9}, {9, 6}
  };

  // 初始化
  vector<bool> vis(nums.size(), false);
  string path;
  vector<int> res;

  // DFS生成组合
  function<void(string)> dfs = [&](const string& path) {
    // 非空路径加入结果
    if (!path.empty()) {
      res.emplace_back(stoi(path));
    }

    // 深度限制
    if (path.size() == nums.size()) {
      return;
    }

    // 回溯生成组合
    for (int i = 0; i < nums.size(); i++) {
      if (vis[i])
        continue;

      vis[i] = true;

      // 尝试原数字
      dfs(path + to_string(nums[i]));

      // 尝试特殊替换数字
      if (dic.count(nums[i])) {
        dfs(path + to_string(dic[nums[i]]));
      }

      vis[i] = false;
    }
  };

  // 执行DFS
  dfs("");

  // 排序
  sort(res.begin(), res.end());

  // 返回结果
  if (n <= res.size()) {
    cout << res[n - 1] << endl;
  } else {
    cout << res.back() << endl;
  }

  return 0;
}