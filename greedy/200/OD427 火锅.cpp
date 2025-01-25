#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  vector<pair<int, int> > dishes(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    dishes[i] = {x + y, x}; // 计算最佳食用时间和下锅时间
  }

  // 按照最佳食用时间排序
  sort(dishes.begin(), dishes.end());

  int count = 0;
  int last_time = -1000; // 上一次捞菜的时间置为负，不影响比较

  for (const auto& dish : dishes) {
    int best_time = dish.first;

    // 如果当前菜的最优吃菜时间大于等于上一次捞菜时间 + m
    if (best_time >= last_time + m) {
      count++;
      last_time = best_time; // 更新捞菜的时间
    }
  }

  cout << count << endl;

  return 0;
}