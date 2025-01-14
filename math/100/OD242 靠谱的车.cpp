#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  int actual = 0;
  int base = 1;

  while (N > 0) {
    int current_digit = N % 10;
    N /= 10;

    // 处理当前位
    if (current_digit < 4) {
      actual += current_digit * base;
    } else if (current_digit > 4) {
      actual += (current_digit - 1) * base;
    }

    // 更新基数
    base *= 9;
  }

  cout << actual << endl;

  return 0;
}