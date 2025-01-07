#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  cin >> input; // 读取输入字符串
  string result = input; // 初始化结果为原字符串
  // 遍历字符串的每一个字符
  for (int i = 0; i < input.length(); ++i) {
    // 在当前字符后寻找可以交换的最小字符
    for (int j = i + 1; j < input.length(); ++j) {
      // 检查是否需要进行交换
      if (input[j] < input[i]) {
        // 交换后构造新的序列
        string new_string = input;
        swap(new_string[i], new_string[j]);
        // 如果新的字符串字典序更小，则更新结果
        if (new_string < result) {
          result = new_string;
        }
      }
    }
  }

  // 输出变换后的最小字符串
  cout << result << endl;
  return 0;
}