#include <bits/stdc++.h>
using namespace std;

int main() {
  // 矩形坐标输入：左上角 x, 左上角 y, 宽度, 高度
  int x1, y1, w1, h1;
  int x2, y2, w2, h2;
  int x3, y3, w3, h3;

  // 输入 3 个矩形的坐标信息
  cin >> x1 >> y1 >> w1 >> h1;
  cin >> x2 >> y2 >> w2 >> h2;
  cin >> x3 >> y3 >> w3 >> h3;

  // 计算每个矩形的坐标范围
  // 注意：y 轴向下为正，所以右下角 y 坐标为 y + h
  int left = max({x1, x2, x3});            // x 轴最大左边界
  int right = min({x1 + w1, x2 + w2, x3 + w3});  // x 轴最小右边界

  int bottom = max({y1 - h1, y2 - h2, y3 - h3});  // y 轴最大下边界
  int top = min({y1, y2, y3});             // y 轴最小上边界

  // 计算重叠区域
  int width = max(0, right - left);
  int height = max(0, top - bottom);

  // 输出重叠面积
  cout << width * height << endl;

  return 0;
}