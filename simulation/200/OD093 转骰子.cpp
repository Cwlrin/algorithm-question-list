#include <bits/stdc++.h>
using namespace std;

int main() {
  // 定义骰子面的初始状态
  int left = 1, right = 2, front = 3, back = 4, top = 5, bottom = 6;

  // 读取输入的操作序列
  string moves;
  cin >> moves;

  // 处理每个操作
  for (char move : moves) {
    // 使用临时变量保存旋转前的状态
    int tmp;
    switch (move) {
      case 'L': // 左翻转
        tmp = right;
        right = bottom;
        bottom = left;
        left = top;
        top = tmp;
        break;
      case 'R': // 右翻转
        tmp = left;
        left = bottom;
        bottom = right;
        right = top;
        top = tmp;
        break;
      case 'F': // 前翻转
        tmp = front;
        front = top;
        top = back;
        back = bottom;
        bottom = tmp;
        break;
      case 'B': // 后翻转
        tmp = top;
        top = front;
        front = bottom;
        bottom = back;
        back = tmp;
        break;
      case 'A': // 逆时针旋转
        tmp = right;
        right = front;
        front = left;
        left = back;
        back = tmp;
        break;
      case 'C': // 顺时针旋转
        tmp = front;
        front = right;
        right = back;
        back = left;
        left = tmp;
        break;
    }
  }

  // 输出最终状态
  cout << left << right << front << back << top << bottom << endl;

  return 0;
}