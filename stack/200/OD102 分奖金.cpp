#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n; // 读取员工数量
  vector<int> numbers(n);
  vector<int> bonuses(n); // 保存每位员工的奖金

  // 读取随机数字
  for (int i = 0; i < n; i++) {
    cin >> numbers[i];
  }

  stack<int> s; // 用于保存员工索引

  for (int i = 0; i < n; ++i) {
    while (!s.empty() && numbers[s.top()] < numbers[i]) {
      // 计算奖金
      int index = s.top();                                          // 获取栈顶员工的索引
      bonuses[index] = (i - index) * (numbers[i] - numbers[index]); // 奖金计算
      s.pop();                                                      // 弹出栈顶员工
    }
    s.push(i); // 将当前员工的索引压入栈
  }

  // 所有仍在栈中的员工，奖金为他们自己的随机数
  while (!s.empty()) {
    bonuses[s.top()] = numbers[s.top()];
    s.pop();
  }

  // 输出每位员工的奖金
  for (int i = 0; i < n; i++) {
    cout << bonuses[i] << " ";
  }
  cout << endl;

  return 0;
}