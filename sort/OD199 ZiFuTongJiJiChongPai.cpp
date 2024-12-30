// OD199. 字符统计及重排
// 题目描述：
// 给出一个仅包含字母的字符串，不包含空格，统计字符串中各个字母（区分大小写）出现的次数，并按照字母出现次数从大到小的顺序。
// 输出各个字母及其出现次数。 如果次数相同，按照自然顺序进行排序，且小写字母在大写字母之前。
// 输入描述：输入一行，为一个仅包含字母的字符串。
// 输出描述：按照字母出现次数从大到小的顺序输出各个字母和字母次数，用英文分号分隔，注意末尾的分号；字母和次数间用英文冒号分隔。
// 用例：
// 输入 1： xyxyXX
// 输出 1： x:2;y:2;X:2
// 说明：每个字符出现的个数都是 2，故 x 排在 y 之前，而小写字母 x 排在 X 之前
// 输入 2： abababb
// 输出 2： b:4;a:3
// 说明： b 出现的个数比 a 多，故 b 排在 a 之前
// 难度：中等
// 标签：字符串、 哈希、 排序

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
  ranges::sort(sorted_chars, [](const auto& a, const auto& b) {
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