#include <bits/stdc++.h>
using namespace std;

int main() {
  unsigned long long x, y; // 使用 unsigned long long 以处理最大值
  cin >> x >> y;

  // 计算可以生成的字母组合数
  unsigned long long letter_combinations = pow(26, y);

  int z = 1; // 从1开始，确保数字部分长度不为0
  while (letter_combinations * pow(10, z) < x) {
    z++; // 增加 Z 直到条件满足
  }

  cout << z << endl; // 输出最小 Z
  return 0;
}