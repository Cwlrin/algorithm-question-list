#include <bits/stdc++.h>
using namespace std;

int main() {
  int m, n;
  cin >> m >> n;

  vector<double> arrive_times(m);

  // 读取每辆车的速度
  for (int i = 0; i < m; i++) {
    double speed;
    cin >> speed;

    // 正常情况下的到达时间
    double normal_arrive_time = (double)n / speed + i;

    // 如果不是第一辆车，需要比较是否被前车阻碍
    if (i > 0) {
      // 前一辆车的到达时间
      double prev_arrive_time = arrive_times[i - 1];

      // 如果正常行驶到达时间早于前车到达时间，则被阻碍
      arrive_times[i] = max(normal_arrive_time, prev_arrive_time);
    } else {
      // 第一辆车正常行驶
      arrive_times[i] = normal_arrive_time;
    }
  }
  // 输出最后一辆车的行驶时间（到达时刻 - 出发时刻）
  cout << fixed << setprecision(1) << arrive_times[m - 1] - (m - 1) << endl;

  return 0;
}