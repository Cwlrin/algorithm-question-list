#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  // 初始化绘图区域，大小为 201x201（坐标范围 -100 到 100）  
  vector<vector<int> > grid(201, vector<int>(201, 0));

  for (int i = 0; i < n; ++i) {
    char op;
    int x1, y1, x2, y2;
    cin >> op >> x1 >> y1 >> x2 >> y2;

    // 将坐标映射到 [0, 200] 范围  
    x1 += 100;
    y1 += 100;
    x2 += 100;
    y2 += 100;

    // 确保 x1 <= x2 和 y1 <= y2  
    if (x1 > x2)
      swap(x1, x2);
    if (y1 > y2)
      swap(y1, y2);

    // 处理绘制或擦除操作  
    for (int x = x1; x < x2; ++x) {
      for (int y = y1; y < y2; ++y) {
        if (op == 'd') {
          grid[x][y] = 1;
        } else if (op == 'e') {
          grid[x][y] = 0;
        }
      }
    }
  }

  // 计算最终图形的面积  
  int area = 0;
  for (int x = 0; x < 201; ++x) {
    for (int y = 0; y < 201; ++y) {
      if (grid[x][y] == 1) {
        area++;
      }
    }
  }

  cout << area << endl;
  return 0;
}