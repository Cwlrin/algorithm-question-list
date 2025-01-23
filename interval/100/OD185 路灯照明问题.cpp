#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n;
  cin >> n; // 输入路灯数量

  vector<int> radius(n);
  for (int i = 0; i < n; ++i) {
    cin >> radius[i]; // 输入每个路灯的照明半径
  }

  // 计算每个路灯的照明范围
  vector<pair<int, int> > ranges;
  for (int i = 0; i < n; ++i) {
    int position = i * 100;
    int start = max(0, position - radius[i]);
    int end = position + radius[i];
    ranges.emplace_back(start, end);
  }

  // 按起点升序排序
  sort(ranges.begin(), ranges.end());

  // 合并重叠的照明范围
  vector<pair<int, int> > merged;
  merged.push_back(ranges[0]);

  for (int i = 1; i < ranges.size(); ++i) {
    pair<int, int> current = ranges[i];
    pair<int, int>& last = merged.back();

    if (current.first <= last.second) {
      // 当前区间与最后一个区间有重叠，合并区间
      last.second = max(last.second, current.second);
    } else {
      // 当前区间与最后一个区间无重叠，直接加入结果
      merged.push_back(current);
    }
  }

  // 计算未覆盖的区间长度和
  int uncovered = 0;
  for (int i = 1; i < merged.size(); ++i) {
    int gap = merged[i].first - merged[i - 1].second;
    if (gap > 0) {
      uncovered += gap;
    }
  }

  cout << uncovered << endl; // 输出未覆盖的区间长度和
  return 0;
}