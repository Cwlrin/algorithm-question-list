#include <iostream>
#include <string>

using namespace std;

int main() {
  string cabinets;
  cin >> cabinets;

  int n = cabinets.length();
  int electric_boxes = 0;

  // 特殊情况处理
  if (n == 1) {
    return cout << (cabinets[0] == 'I' ? 0 : -1), 0;
  }

  for (int i = 0; i < n;) {
    // 找到机柜
    while (i < n && cabinets[i] == 'I') {
      i++;
    }

    // 已经遍历完
    if (i >= n)
      break;

    // 优先在右侧放电箱
    if (i + 1 < n && cabinets[i + 1] == 'I') {
      electric_boxes++;
      i += 3;  // 跳过当前机柜和放电箱的间隔，以及下一个位置
    }
    // 在左侧放电箱
    else if (i > 0 && cabinets[i - 1] == 'I') {
      electric_boxes++;
      i++;
    }
    // 无法放置电箱
    else {
      return cout << -1, 0;
    }
  }

  cout << electric_boxes << endl;
  return 0;
}