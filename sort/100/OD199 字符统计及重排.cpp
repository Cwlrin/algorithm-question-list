#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  cin >> input;

  // 创建一个哈希表来存储每个字符的出现次数
  unordered_map<char, int> count_map;
  for (char c : input) {
    count_map[c]++;
  }

  // 将哈希表转换为向量
  vector<pair<char, int> > sorted_chars(count_map.begin(), count_map.end());

  // 排序
  sort(sorted_chars.begin(), sorted_chars.end(),
       [](const auto& a, const auto& b) {
         if (a.second == b.second) {
           if (islower(a.first) && !islower(b.first)) {
             return true; // 小写字母优先
           }
           if (!islower(a.first) && islower(b.first)) {
             return false; // 大写字母不优先
           }
           return a.first < b.first; // 自然顺序排序，小写字母在大写字母之前
         }
         return a.second > b.second; // 按出现次数降序排列
       });

  // 输出结果
  for (int i = 0; i < sorted_chars.size(); ++i) {
    if (i > 0) {
      cout << ";";
    }
    cout << sorted_chars[i].first << ":" << sorted_chars[i].second;
  }
  cout << ";" << endl;
}