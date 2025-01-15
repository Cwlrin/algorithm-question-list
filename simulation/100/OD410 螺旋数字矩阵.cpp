#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  // 计算最小列数（向上取整）
  int cols = (n + m - 1) / m;

  // 创建矩阵并初始化为*
  vector<vector<string> > matrix(m, vector<string>(cols, "*"));

  // 定义四个方向：右、下、左、上
  const int dx[] = {0, 1, 0, -1};
  const int dy[] = {1, 0, -1, 0};

  int x = 0, y = 0; // 当前位置
  int dir = 0;      // 当前方向
  int num = 1;      // 当前要填入的数字

  // 填充数字
  while (num <= n) {
    // 填入当前数字
    matrix[x][y] = to_string(num++);

    // 计算下一个位置
    int nextX = x + dx[dir];
    int nextY = y + dy[dir];

    // 检查是否需要改变方向
    if (nextX < 0 || nextX >= m || nextY < 0 || nextY >= cols ||
        matrix[nextX][nextY] != "*") {
      dir = (dir + 1) % 4;
      nextX = x + dx[dir];
      nextY = y + dy[dir];
    }

    x = nextX;
    y = nextY;
  }

  // 输出矩阵
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < cols; j++) {
      if (j > 0)
        cout << " ";
      cout << matrix[i][j];
    }
    cout << endl;
  }

  return 0;
}