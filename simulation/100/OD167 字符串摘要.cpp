#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  string input;
  getline(cin, input);

  // 1. 预处理：统计所有字母出现次数（不区分大小写）
  unordered_map<char, int> count;
  string cleaned;
  for (char c : input) {
    if (isalpha(c)) {
      cleaned += tolower(c);
      count[tolower(c)]++;
    }
  }

  // 2. 存储摘要信息的数组
  vector<pair<char, int> > summary;

  // 3. 遍历字符串，处理连续和非连续字符
  for (int i = 0; i < cleaned.length();) {
    char current = cleaned[i];
    int consecutive_count = 0;

    // 统计连续字符
    while (i < cleaned.length() && cleaned[i] == current) {
      consecutive_count++;
      count[current]--;
      i++;
    }

    // 处理连续字符和非连续字符
    if (consecutive_count > 1) {
      // 连续字符
      summary.emplace_back(current, consecutive_count);
    } else if (consecutive_count == 1) {
      // 非连续字符，统计后续出现次数
      summary.emplace_back(current, count[current]);
    }
  }

  // 4. 排序
  sort(summary.begin(), summary.end(), [](const auto& a, const auto& b) {
    // 按数字降序排序
    if (a.second != b.second) {
      return a.second > b.second;
    }
    // 数字相同时按字母升序排序
    return a.first < b.first;
  });

  // 5. 生成并输出最终字符串
  string result;
  for (const auto& item : summary) {
    result += item.first;
    result += to_string(item.second);
  }

  cout << result << endl;

  return 0;
}