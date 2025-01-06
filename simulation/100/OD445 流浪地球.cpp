#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, e;
  cin >> n >> e;

  // 发动机状态数组：是否启动、启动时间
  vector<bool> started(n, false);
  vector<int> start_time(n, -1);

  // 记录手动启动事件
  map<int, set<int> > manual_start_events;

  // 读取手动启动事件
  for (int i = 0; i < e; ++i) {
    int t, p;
    cin >> t >> p;
    manual_start_events[t].insert(p);
  }

  // 记录每个时刻的启动事件
  int max_start_time = 0;

  // 处理所有时刻的启动事件
  for (int t = 0; t <= n * 2; ++t) {
    // 手动启动事件
    // if (manual_start_events.contains(t)) {
    if (manual_start_events.find(t) != manual_start_events.end()) {
      for (int p : manual_start_events[t]) {
        if (!started[p]) {
          started[p] = true;
          start_time[p] = t;
          max_start_time = max(max_start_time, t);
        }
      }
    }

    // 关联启动
    vector<int> to_start;
    for (int i = 0; i < n; ++i) {
      if (!started[i]) {
        // 检查左右相邻发动机
        int left = (i - 1 + n) % n;
        int right = (i + 1) % n;

        // 左右任一已启动，则准备启动
        if (started[left] || started[right]) {
          to_start.push_back(i);
        }
      }
    }

    // 执行关联启动
    for (int p : to_start) {
      started[p] = true;
      start_time[p] = t + 1;
      max_start_time = max(max_start_time, t + 1);
    }
  }

  // 找出最后被启动的发动机
  vector<int> last_started;
  for (int i = 0; i < n; ++i) {
    if (start_time[i] == max_start_time) {
      last_started.push_back(i);
    }
  }

  cout << last_started.size() << endl;
  sort(last_started.begin(), last_started.end());
  for (int engine : last_started) {
    cout << engine << " ";
  }
  cout << endl;

  return 0;
}