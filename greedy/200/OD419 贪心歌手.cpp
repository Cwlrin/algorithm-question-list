#include <bits/stdc++.h>

using namespace std;

int main() {
  int t, n;
  cin >> t >> n;

  vector<int> travel_days(n + 1);
  for (int i = 0; i <= n; i++) {
    cin >> travel_days[i];
  }

  vector<pair<int, int> > cities(n);
  for (int i = 0; i < n; i++) {
    cin >> cities[i].first >> cities[i].second;
  }

  // 计算剩余天数  
  int total_travel_days = 0;
  for (int day : travel_days) {
    total_travel_days += day;
  }
  int remaining_days = t - total_travel_days;

  // 优先队列（最大堆）存储所有可能的卖唱收入  
  priority_queue<int> max_heap;

  // 计算每座城市的卖唱收入  
  for (auto& city : cities) {
    int m = city.first;
    int d = city.second;
    int day = 1;
    while (m > 0 && remaining_days > 0) {
      max_heap.push(m);
      m -= d;
      day++;
    }
  }

  // 分配卖唱天数  
  int total_income = 0;
  while (remaining_days > 0 && !max_heap.empty()) {
    total_income += max_heap.top();
    max_heap.pop();
    remaining_days--;
  }

  cout << total_income << endl;

  return 0;
}