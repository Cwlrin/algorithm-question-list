#include <bits/stdc++.h>
using namespace std;

int main() {
  long long n;
  cin >> n;

  int ops = 0;
  while (n != 1) {
    // 偶数直接除2
    if (n % 2 == 0) {
      n /= 2;
    }
    // 奇数需要特殊处理
    else {
      // 对于 10 这种特殊数字
      if (n == 3) {
        ops += 2; // 3 需要特殊处理：3-1=2，再除2
        break;
      }

      // 对于奇数，判断+1或-1能更快到1
      if ((n + 1) % 4 == 0) {
        n++;
      } else {
        n--;
      }
    }
    ops++;
  }

  cout << ops << endl;

  return 0;
}