#include <bits/stdc++.h>
using namespace std;

int main() {
  // 读取点的数量
  int N;
  cin >> N;

  // 输入坐标
  set<pair<int, int> > points; // 使用集合存储所有点
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    points.insert({x, y});
  }

  int count = 0;

  // 遍历所有点对以求正方形
  vector<pair<int, int> > point_list(points.begin(), points.end());
  for (int i = 0; i < point_list.size(); i++) {
    for (int j = i + 1; j < point_list.size(); j++) {
      // 找到 A 和 B 之间的坐标
      int x1 = point_list[i].first, y1 = point_list[i].second;
      int x2 = point_list[j].first, y2 = point_list[j].second;

      // 计算正方形的其他两个点 C 和 D
      // 旋转 90 度的公式
      int dx = x2 - x1;
      int dy = y2 - y1;

      pair<int, int> pointC = {x1 - dy, y1 + dx}; // A 旋转 90 度得到 C
      pair<int, int> pointD = {x2 - dy, y2 + dx}; // B 旋转 90 度得到 D

      // 检查 C 和 D 是否在 points 中
      if (points.count(pointC) && points.count(pointD)) {
        count++;
      }
    }
  }

  // 每个正方形被计数了 4 次（对于每一对对角线点）所以除以 4
  cout << count / 4 << endl;

  return 0;
}