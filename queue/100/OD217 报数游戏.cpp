#include <bits/stdc++.h>
using namespace std;

int main() {
  int m;
  cin >> m;

  // 输入参数不合法处理
  if (m <= 1 || m >= 100) {
    cout << "ERROR!" << endl;
    return 0;
  }

  vector<int> people;
  // 初始化1到100的编号
  for (int i = 1; i <= 100; ++i) {
    people.push_back(i);
  }

  int index = 0; // 起始报数的索引

  // 模拟报数过程
  while (people.size() >= m) {
    index = (index + m - 1) % people.size(); // 计算被移除者的索引（-1因为下标从0开始）
    people.erase(people.begin() + index);    // 移除该人
  }

  // 输出剩余人的编号
  stringstream result;
  for (size_t i = 0; i < people.size(); ++i) {
    if (i > 0)
      result << ","; // 处理前面的逗号
    result << people[i];
  }

  cout << result.str() << endl; // 输出结果
  return 0;
}