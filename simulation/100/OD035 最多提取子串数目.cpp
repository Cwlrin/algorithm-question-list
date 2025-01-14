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
  unordered_map<char, vector<int>> charPositions;
  for (int i = 0; i < target.length(); ++i) {
    charPositions[target[i]].push_back(i);
  }

  // 记录每个字符匹配的计数
  vector<int> matchCount(target.length(), 0);

  // 遍历源字符串
  for (char currentChar : source) {
    // 检查当前字符是否在目标字符串中
    if (charPositions.count(currentChar)) {
      // 遍历该字符在目标字符串中的位置
      for (int pos : charPositions[currentChar]) {
        // 匹配条件：
        // 1. 首个字符直接匹配
        // 2. 非首个字符需要前一个位置已经匹配
        if (pos == 0 || matchCount[pos - 1] > matchCount[pos]) {
          matchCount[pos]++;
          break;  // 匹配成功后跳出
        }
      }
    }
  }

  // 输出最终匹配数量
  cout << matchCount.back() << endl;

  return 0;
}