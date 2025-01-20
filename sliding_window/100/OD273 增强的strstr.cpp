#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string haystack, needle;

  // 读取输入的源字符串和目标字符串
  getline(cin, haystack);
  getline(cin, needle);

  vector<vector<char> > layers; // 用于存储目标字符串的层次
  vector<char> current_layer;   // 当前层次的字符集合

  // 解析目标字符串并构建层次
  for (size_t i = 0; i < needle.size(); i++) {
    if (needle[i] == '[') {
      current_layer.clear(); // 新层开始，清空当前层
      i++;                   // 跳过 '['
      while (i < needle.size() && needle[i] != ']') {
        current_layer.push_back(needle[i]); // 将可选字符添加到当前层
        i++;
      }
      layers.push_back(current_layer); // 将当前层添加到层次列表
    } else {
      // 如果是普通字符，单独作为一层
      layers.push_back(vector<char>{needle[i]});
    }
  }

  int layer_count = layers.size(); // 层的数量
  int layers_size = haystack.size();

  // Slidng窗口匹配
  for (int i = 0; i <= layers_size - layer_count; i++) {
    bool match = true; // 默认匹配标记为真

    for (int j = 0; j < layer_count; j++) {
      bool found = false; // 每层是否找到匹配字符
      for (char ch : layers[j]) {
        if (haystack[i + j] == ch) {
          found = true; // 找到匹配字符
          break;
        }
      }
      if (!found) {
        match = false; // 如果一层没有找到匹配，标记为不匹配
        break;
      }
    }

    if (match) {
      cout << i << endl; // 匹配成功，输出起始位置
      return 0;          // 结束程序
    }
  }

  cout << -1 << endl; // 如果没有找到匹配，输出 -1
  return 0;
}