#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// 计算满足条件的字符串数量
void backtrack(string& current, const int n, unordered_map<char, int>& char_count, int& result) {
  // 当生成的字符串达到目标长度时，增加计数
  if (current.length() == n) {
    result++;
    return;
  }

  // 遍历所有字符
  for (auto& entry : char_count) {
    char c = entry.first;
    if (entry.second > 0) {
      // 边界条件：不允许相同字符相邻
      if (current.empty() || current.back() != c) {
        // 选择当前字符
        current.push_back(c);
        char_count[c]--; // 使用一个字符

        backtrack(current, n, char_count, result); // 递归调用

        // 回溯
        current.pop_back();
        char_count[c]++; // 恢复字符数量
      }
    }
  }
}

int main() {
  string input;
  getline(cin, input); // 读取输入

  // 从输入中提取字符和字符串长度
  string characters = input.substr(0, input.size() - 2);
  const int n = input.back() - '0'; // 读取末尾的数字

  // 统计字符频率
  unordered_map<char, int> char_count;
  for (char c : characters) {
    char_count[c]++;
  }

  // 输入非法、无法拼接字符串或者所需长度大于可用字符总数
  if (n > characters.size() || n <= 0 || characters.empty()) {
    cout << 0 << endl;
    return 0;
  }

  // 计算结果
  int result = 0;
  string current;
  backtrack(current, n, char_count, result);

  // 输出结果
  cout << result << endl;

  return 0;
}