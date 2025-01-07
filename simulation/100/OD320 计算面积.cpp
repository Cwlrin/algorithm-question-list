#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, e;
  cin >> n >> e;
  // 存储指令
  vector<pair<int, int> > instructions(n + 1);
  // 添加起点 (0, 0)
  instructions[0] = {0, 0};
  for (int i = 1; i <= n; ++i) {
    cin >> instructions[i].first >> instructions[i].second;
  }
  // 计算面积
  int area = 0, current_y = 0;
  // 遍历指令计算面积
  for (int i = 1; i <= n; ++i) {
    // 计算当前区域的宽度
    int width = instructions[i].first - instructions[i - 1].first;
    // 使用上一个点的纵坐标
    area += width * abs(current_y);
    // 更新当前纵坐标
    current_y += instructions[i].second;
  }
  // 处理最后一个点到终点 e 的区间
  area += (e - instructions[n].first) * abs(current_y);
  cout << area << endl;
  return 0;
}