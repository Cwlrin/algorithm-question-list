#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 判断在给定的最小间距下，是否能够放置指定数量的树苗
bool CanPlace(const vector<int>& positions, int minDistance, int m) {
  int count = 1;                   // 放置的树苗数量
  int last_position = positions[0]; // 上一个放置树苗的位置

  for (int i = 1; i < positions.size(); i++) {
    // 如果当前坐标与最后放置的树苗的距离大于等于最小间距
    if (positions[i] - last_position >= minDistance) {
      count++;                     // 放置树苗
      last_position = positions[i]; // 更新最后放置的树苗位置
      if (count >= m)
        return true; // 如果满足树苗数量，返回 true
    }
  }
  return count >= m; // 计算最终放置的树苗数量是否满足
}

int main() {
  int n; // 坐标数量
  cin >> n;

  vector<int> positions(n);
  for (int i = 0; i < n; i++) {
    cin >> positions[i];
  }

  int m; // 树苗数量
  cin >> m;

  // 排序坐标位置
  sort(positions.begin(), positions.end());

  // 二分查找的范围
  int left = 0;                                     // 最小间距
  int right = positions.back() - positions.front(); // 最大间距

  // 使用二分查找找出最佳最小种植间距
  int best_min_distance = 0;
  while (left <= right) {
    int mid = (left + right) / 2; // 当前尝试的最小距离
    if (CanPlace(positions, mid, m)) {
      best_min_distance = mid; // 记录当前最小距离
      left = mid + 1;        // 尝试更大的间距
    } else {
      right = mid - 1; // 尝试更小的间距
    }
  }

  cout << best_min_distance << endl; // 输出最佳最小种植间距
  return 0;
}