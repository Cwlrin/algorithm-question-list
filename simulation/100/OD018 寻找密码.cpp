#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
  // 读取密码本
  string line;
  getline(cin, line);

  // 存储密码本
  vector<string> passwords;
  unordered_set<string> passwordSet;

  // 解析密码本
  size_t pos = 0;
  while ((pos = line.find(' ')) != string::npos) {
    string password = line.substr(0, pos);
    passwords.push_back(password);
    passwordSet.insert(password);
    line.erase(0, pos + 1);
  }
  // 处理最后一个密码
  if (!line.empty()) {
    passwords.push_back(line);
    passwordSet.insert(line);
  }

  // 按长度降序排序，长度相同时按字典序降序
  sort(passwords.begin(), passwords.end(),
       [](const string& a, const string& b) {
         if (a.length() != b.length()) {
           return a.length() > b.length();
         }
         return a > b; // 长度相同时按字典序降序
       });

  // 寻找符合条件的最长密码
  for (const string& password : passwords) {
    bool valid = true;
    string current = password;

    // 逐步去掉末尾字符
    while (current.length() > 1) {
      current = current.substr(0, current.length() - 1);
      if (passwordSet.find(current) == passwordSet.end()) {
        valid = false;
        break;
      }
    }

    // 检查最后一个字符
    if (valid && passwordSet.find(current) != passwordSet.end()) {
      cout << password << endl;
      return 0;
    }
  }

  // 没有找到符合条件的密码
  cout << "" << endl;
  return 0;
}