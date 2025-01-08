#include <bits/stdc++.h>

using namespace std;

int main() {
  int k;
  cin >> k;
  int n;
  cin >> n;
  cin.ignore();
  // 存储输入数组
  vector<vector<int> > arrays(n);
  // 读取数组
  for (int i = 0; i < n; ++i) {
    string line;
    getline(cin, line);
    stringstream ss(line);
    string num;
    while (getline(ss, num, ',')) {
      // 跳过空字符串
      if (!num.empty()) {
        arrays[i].push_back(stoi(num));
      }
    }
  }
  // 存储结果的数组
  vector<int> result;
  // 记录每个数组的当前索引
  vector<int> indices(n, 0);
  // 标记是否仍有未处理完的数组
  bool has_remaining = true;
  // 循环知道所有数组处理完毕
  while (has_remaining) {
    has_remaining = false;
    // 遍历每个数组
    for (int i = 0; i < n; ++i) {
      // 当前数组还有元素
      if (indices[i] < arrays[i].size()) {
        has_remaining = true;
        // 尝试读取 k 个元素
        int count = 0;
        while (count < k && indices[i] < arrays[i].size()) {
          result.push_back(arrays[i][indices[i]]);
          indices[i]++;
          count++;
        }
      }
    }
  }
  for (int i = 0; i < result.size(); ++i) {
    cout << result[i];
    if (i < result.size() - 1) {
      cout << ',';
    }
  }
  cout << endl;
  return 0;
}