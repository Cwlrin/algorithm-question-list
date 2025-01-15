#include <bits/stdc++.h>
using namespace std;

int main() {
  // 读取矩阵大小
  string size_str;
  getline(cin, size_str);
  int pos = size_str.find(',');
  int rows = stoi(size_str.substr(0, pos));
  int cols = stoi(size_str.substr(pos + 1));

  // 定义方向数组
  constexpr int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  constexpr int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  // 读取矩阵
  vector<vector<char> > matrix(rows, vector<char>(cols));
  for (int i = 0; i < rows; i++) {
    string row_str;
    getline(cin, row_str);

    // 解析每一行
    int start = 0;
    int col = 0;
    while (start < row_str.length()) {
      int comma_pos = row_str.find(',', start);
      if (comma_pos == string::npos) {
        matrix[i][col++] = row_str[start];
        break;
      }
      matrix[i][col++] = row_str.substr(start, comma_pos - start)[0];
      start = comma_pos + 1;
    }
  }

  // 最大连续男生数量
  int max_connected = 0;

  // 遍历每个位置作为起点
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      // 只有男生才开始搜索
      if (matrix[i][j] == 'M') {
        // 尝试八个方向
        for (int dir = 0; dir < 8; dir++) {
          int length = 1;
          int nx = i + dx[dir];
          int ny = j + dy[dir];

          // 延伸这个方向直到不再是男生为止
          while (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
                 matrix[nx][ny] == 'M') {
            length++;
            nx += dx[dir];
            ny += dy[dir];
          }

          // 更新最大值
          max_connected = max(max_connected, length);
        }
      }
    }
  }

  // 输出结果
  cout << max_connected << endl;

  return 0;
}