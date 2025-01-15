#include <bits/stdc++.h>
using namespace std;

int main() {
  int c, b;
  cin >> c >> b;

  vector<int> data(10);
  unordered_map<int, int> type_count; // 记录每种有效类型的数据计数

  // 输入其余10个数据
  for (int i = 0; i < 10; i++) {
    cin >> data[i];
    // 拆分数据为4个字节
    int byte1 = (data[i] >> 24) & 0xFF;
    int byte2 = (data[i] >> 16) & 0xFF;
    int byte3 = (data[i] >> 8) & 0xFF;
    int byte4 = data[i] & 0xFF;

    // 字节求和并取模
    int sum = byte1 + byte2 + byte3 + byte4;
    int result = sum % b;

    // 判断有效性
    if (result < c) {
      type_count[result]++; // 增加该类型计数
    }
  }

  // 找到计数最多的有效类型
  int max_count = 0;
  for (const auto& entry : type_count) {
    max_count = max(max_count, entry.second);
  }

  cout << max_count << endl; // 输出最多数据的有效类型数量
  return 0;
}