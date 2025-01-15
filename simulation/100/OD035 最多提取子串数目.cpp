#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  // 读取输入字符串
  string source, target;
  cin >> source >> target;

  // 记录目标字符串中每个字符的所有位置
  unordered_map<char, vector<int> > char_positions;
  for (int i = 0; i < target.length(); ++i) {
    char_positions[target[i]].push_back(i);
  }

  // 记录每个字符匹配的计数
  vector<int> match_count(target.length(), 0);

  // 遍历源字符串
  for (char current_char : source) {
    // 检查当前字符是否在目标字符串中
    if (char_positions.count(current_char)) {
      // 遍历该字符在目标字符串中的位置
      for (int pos : char_positions[current_char]) {
        // 匹配条件：
        // 1. 首个字符直接匹配
        // 2. 非首个字符需要前一个位置已经匹配
        if (pos == 0 || match_count[pos - 1] > match_count[pos]) {
          match_count[pos]++;
          break; // 匹配成功后跳出
        }
      }
    }
  }

  // 输出最终匹配数量
  cout << match_count.back() << endl;

  return 0;
}