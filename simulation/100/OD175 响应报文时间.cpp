#include <bits/stdc++.h>

using namespace std;

int main() {
  int c;
  cin >> c;
  // 记录最小响应时间
  int min_resp_time = INT_MAX;
  // 处理每个报文
  for (int i = 0; i < c; ++i) {
    int t, m;
    cin >> t >> m;
    // 计算最大响应时间
    int resp_time;
    if (m < 128) {
      // 直接使用 m 为响应时间
      resp_time = t + m;
    } else {
      int exp = m >> 4 & 0x07; // 高 5~7 位
      int mant = m & 0x0f;     // 低 4 位
      // 按照公式计算
      resp_time = t + ((mant | 0x10) << exp + 3);
    }
    // 更新最小响应时间
    min_resp_time = min(min_resp_time, resp_time);
  }
  cout << min_resp_time << endl;
  return 0;
}