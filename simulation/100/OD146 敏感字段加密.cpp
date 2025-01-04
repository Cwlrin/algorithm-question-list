#include <bits/stdc++.h>

using namespace std;

int main() {
  int k;
  string s;
  cin >> k >> s;
  vector<string> commands;
  string current;
  bool in_quotes = false;

  for (char c : s) {
    if (c == '"') {
      // 只有在非引号状态，开始新的引导命令字
      if (!in_quotes) {
        // 如果当前有命令字，先加入
        if (!current.empty()) {
          commands.push_back(current);
          current.clear();
        }
        current += c;
      }
      // 已经在引号内，关闭引号
      else {
        current += c;
        commands.push_back(current);
        current.clear();
      }
      // 切换引号状态
      in_quotes = !in_quotes;
    }
    // 不在引号内处理下划线
    else if (!in_quotes && c == '_') {
      // 只有当前命令字非空时才加入
      if (!current.empty()) {
        commands.push_back(current);
        current.clear();
      }
    } else {
      current += c;
    }
  }
  // 处理最后一个命令字
  if (!current.empty()) {
    commands.push_back(current);
  }
  // 检查索引是否有效
  if (k < 0 || k >= commands.size()) {
    cout << "ERROR" << endl;
    return 0;
  }

  // 替换指定索引的命令字
  commands[k] = "******";
  // 重新构建字符串
  string result;
  for (int i = 0; i < commands.size(); ++i) {
    if (i > 0) {
      result += '_';
    }
    result += commands[i];
  }
  cout << result << endl;
  return 0;
}