#include <bits/stdc++.h>
using namespace std;

int main() {
  string ip;
  getline(cin, ip);

  // 检查空输入
  if (ip.empty()) {
    cout << "invalid IP" << endl;
    return 0;
  }

  // 用于存储四个数字
  vector<int> nums;
  size_t start = 0;

  // 分割并验证每个部分
  for (int i = 0; i < 4; i++) {
    // 找到下一个#号位置
    size_t end = (i < 3) ? ip.find('#', start) : ip.length();

    // 检查格式
    if (i < 3 && end == string::npos) {
      cout << "invalid IP" << endl;
      return 0;
    }

    // 获取当前部分
    string section = ip.substr(start, end - start);

    // 检查部分是否为空或过长
    if (section.empty() || section.length() > 3) {
      cout << "invalid IP" << endl;
      return 0;
    }

    // 检查前导零
    if (section.length() > 1 && section[0] == '0') {
      cout << "invalid IP" << endl;
      return 0;
    }

    // 验证是否都是数字
    for (char c : section) {
      if (!isdigit(c)) {
        cout << "invalid IP" << endl;
        return 0;
      }
    }

    // 转换为数字
    int num = stoi(section);

    // 检查范围
    if (i == 0 && (num < 1 || num > 128)) {
      cout << "invalid IP" << endl;
      return 0;
    }
    if (i != 0 && (num < 0 || num > 255)) {
      cout << "invalid IP" << endl;
      return 0;
    }

    nums.push_back(num);
    start = end + 1;
  }

  // 检查是否有多余的字符
  if (start < ip.length() + 1) {
    cout << "invalid IP" << endl;
    return 0;
  }

  // 计算结果
  unsigned int result = 0;
  for (int num : nums) {
    result = (result << 8) | num;
  }

  cout << result << endl;

  return 0;
}