#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
  // 读取桃树数量和每棵树上的桃子数
  vector<int> piles;

  // 处理输入
  string line;
  getline(cin, line);

  // 分割字符串并转换为整数
  size_t pos = 0;
  while ((pos = line.find(' ')) != string::npos) {
    string token = line.substr(0, pos);
    piles.push_back(stoi(token));
    line.erase(0, pos + 1);
  }
  piles.push_back(stoi(line)); // 添加最后一个数

  int h;
  cin >> h;

  // 特殊情况处理：桃树数量大于可用时间
  if (piles.size() > h) {
    cout << 0 << endl;
    return 0;
  }

  // 二分查找的左右边界
  int left = 1;
  int right = *max_element(piles.begin(), piles.end());

  // 特殊情况处理：来不及吃完
  int total_hours = 0;
  for (int pile : piles) {
    total_hours += ceil((double)pile / right);
  }
  if (total_hours > h) {
    cout << 0 << endl;
    return 0;
  }

  // 二分查找最小速度
  int result = 0;
  while (left <= right) {
    int mid = left + (right - left) / 2;

    // 直接在这里实现原来 canEatAll 的逻辑
    int hours = 0;
    for (int pile : piles) {
      // 向上取整，计算吃完这堆桃子需要的时间
      hours += ceil((double)pile / mid);
    }

    // 判断是否在规定时间内吃完
    if (hours <= h) {
      // 如果当前速度可以吃完，尝试更小的速度
      result = mid;
      right = mid - 1;
    } else {
      // 当前速度不够，需要增加速度
      left = mid + 1;
    }
  }

  cout << result << endl;

  return 0;
}