#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string line;
  string text;
  bool is_single_open = false;
  bool is_double_open = false;

  // 读取所有行
  while (getline(cin, line)) {
    for (size_t i = 0; i < line.size(); ++i) {
      // 处理单引号
      if (line[i] == '\'' && (i == 0 || line[i-1] != '\\')) {
        is_single_open = !is_single_open;
      }

      // 处理双引号
      if (line[i] == '"' && (i == 0 || line[i-1] != '\\')) {
        is_double_open = !is_double_open;
      }

      // 处于字符串内部，忽略字符串内容
      if (is_single_open || is_double_open) continue;

      // 处理注释
      if (line[i] == '-' && i + 1 < line.size() && line[i+1] == '-') {
        break; // 遇到注释，停止处理当前行后续字符
      }

      // 跳过空白字符
      if (line[i] == ' ' || line[i] == '\t') continue;

      // 记录有效文本
      text += line[i];
    }
  }

  // 如果最后一条没有分号，追加分号
  if (!text.empty() && text.back() != ';') {
    text += ';';
  }

  // 统计有效文本数量
  int count = 0;
  bool in_text = false;
  for (char c : text) {
    if (c == ';') {
      if (in_text) {
        count++;
      }
      in_text = false;
    } else if (c != ' ' && c != '\t') {
      in_text = true;
    }
  }

  // 输出结果
  cout << count << endl;

  return 0;
}