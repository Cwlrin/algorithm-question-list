#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  cin.ignore();

  // 存储输入行的二维vector
  vector<vector<int> > lines;

  // 读取输入
  for (int i = 0; i < n; i++) {
    string line;
    getline(cin, line);

    // 解析每行
    stringstream ss(line);
    vector<int> row;
    int num;

    // 按空格读取数字
    while (ss >> num) {
      row.push_back(num);
    }

    lines.push_back(row);
  }

  // 定义64*64的矩阵，初始化为0
  vector<vector<int> > matrix(64, vector<int>(64, 0));

  // 向矩阵中填充数字
  for (const auto& line : lines) {
    // 第一个数是要填充的数字
    int num = line[0];

    // 后续每两个数一组，表示坐标
    for (int i = 1; i < line.size(); i += 2) {
      int x = line[i];
      int y = line[i + 1];
      matrix[x][y] = num;
    }
  }

  // 定义四个方向
  int offsets[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  // 遍历每个图形
  for (const auto& line : lines) {
    int num = line[0];
    int perimeter = 0;

    // 遍历当前图形的每个点
    for (int i = 1; i < line.size(); i += 2) {
      int x = line[i];
      int y = line[i + 1];

      // 检查四个方向
      for (const auto& offset : offsets) {
        const int new_x = x + offset[0];
        const int new_y = y + offset[1];

        // 如果越界或不是同一图形，周长+1
        if (new_x < 0 || new_x >= 64 || new_y < 0 || new_y >= 64 ||
            matrix[new_x][new_y] != num) {
          perimeter++;
        }
      }
    }

    // 输出周长
    cout << perimeter << (line == lines.back() ? "\n" : " ");
  }

  return 0;
}