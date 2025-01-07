#include <bits/stdc++.h>

using namespace std;

int main() {
  string line;
  getline(cin, line);
  line = line.substr(1, line.length() - 2);
  // 解析步数
  vector<int> steps;
  stringstream ss(line);
  string num;
  while (getline(ss, num, ',')) {
    steps.push_back(stoi(num));
  }
  int count;
  cin >> count;
  // 记录最终结果的索引
  int result_index1 = 0, result_index2 = 0;
  // 记录最小索引和
  int min_index_sum = INT_MAX;
  // 遍历所有可能的两个步数之和
  for (int i = 0; i < steps.size(); ++i) {
    for (int j = 0; j < steps.size(); ++j) {
      // 忽略相同索引的组合
      if (i == j) continue;
      // 判断两个步数是否可以跳到目标格数
      if (steps[i] + steps[j] == count) {
        // 当前索引和
        int current_index_sum = i + j;
        // 更新最小索引和
        if (current_index_sum < min_index_sum) {
          min_index_sum = current_index_sum;
          result_index1 = steps[i];
          result_index2 = steps[j];
        }
      }
    }
  }
  cout << "[" << result_index1 << ", " << result_index2 << "]" <<
      endl;
  return 0;
}