#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
  // 读取密码
  string key;
  cin >> key;

  // 读取箱子数组并处理
  string line;
  cin.ignore();  // 忽略换行符
  getline(cin, line);

  // 箱子遍历和处理
  int boxNum = 1;
  int start = 0, end = 0;
  while (start < line.length()) {
    // 找到下一个箱子字符串
    end = line.find(' ', start);
    if (end == string::npos)
      end = line.length();

    // 提取当前箱子字符串
    string box = line.substr(start, end - start);

    // 统计密码中字母数量
    unordered_map<char, int> keyCount;
    for (char c : key) {
      keyCount[c]++;
    }

    // 提取并处理字母
    bool match = true;
    for (char c : box) {
      if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        char lowerC = tolower(c);
        // 如果字母不在密码中，或已经超过密码中的数量
        if (keyCount.count(lowerC) == 0 || keyCount[lowerC] == 0) {
          match = false;
          break;
        }
        keyCount[lowerC]--;
      }
    }

    // 检查是否所有密码字母都被使用
    if (match) {
      for (const auto& pair : keyCount) {
        if (pair.second > 0) {
          match = false;
          break;
        }
      }
    }

    // 如果匹配，返回箱子编号
    if (match) {
      cout << boxNum << endl;
      return 0;
    }

    // 移动到下一个箱子
    start = end + 1;
    boxNum++;
  }

  // 未找到匹配的箱子
  cout << -1 << endl;
  return 0;
}