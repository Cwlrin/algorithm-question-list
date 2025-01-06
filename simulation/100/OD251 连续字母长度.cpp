#include <bits/stdc++.h>

using namespace std;

int main() {
  // 读取输入字符串和 k 值
  string s;
  int k;
  cin >> s >> k;
  // 特殊情况处理：字符串长度小于等于1
  if (s.length() <= 1) {
    cout << 1 << endl;
    return 0;
  }
  if (k >= 26 || k <= 0) {
    cout << "-1" << endl;
    return 0;
  }
  // 存储每个字母最大出现次数
  unordered_map<char, int> max_lengths;
  // 遍历字符串，统计每个字母的最大连续长度
  for (int i = 0; i < s.length();) {
    char current_char = s[i];
    int count = 0;
    // 统计当前字母的连续出现次数
    while (i < s.length() && s[i] == current_char) {
      count++;
      i++;
    }
    // 更新对应字母的最大长度
    if (max_lengths.find(current_char) == max_lengths.end()) {
      max_lengths[current_char] = count;
    } else {
      max_lengths[current_char] = max(max_lengths[current_char], count);
    }
  }
  // 存储所有不同的最长长度
  vector<int> lengths;
  for (auto& entry : max_lengths) {
    lengths.push_back(entry.second);
  }
  // 对长度进行排序，降序
  sort(lengths.begin(), lengths.end(), greater<int>());
  // 处理 k 大于有效长度数量的情况
  if (k > lengths.size()) {
    cout << -1 << endl;
    return 0;
  }
  // 选择第 k 大的长度并输出
  cout << lengths[k - 1] << endl;
  return 0;
}

