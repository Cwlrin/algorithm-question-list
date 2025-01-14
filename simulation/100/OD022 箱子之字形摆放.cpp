#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  // 输入字符串和宽度
  string s;
  int n;
  cin >> s >> n;

  // 创建n行的字符串向量
  vector<string> matrix(n);

  // 控制方向的标志
  bool reverse = true;

  // 遍历输入字符串
  for (int i = 0; i < s.length(); i++) {
    // 计算基础行号
    int k = i % n;

    // 每当 i % n == 0 时，切换方向
    if (k == 0) {
      reverse = !reverse;
    }

    // 如果是反向，则行号需要反转
    if (reverse) {
      k = n - 1 - k;
    }

    // 将字符添加到对应行
    matrix[k] += s[i];
  }

  // 输出结果
  for (const auto& line : matrix) {
    cout << line << endl;
  }

  return 0;
}