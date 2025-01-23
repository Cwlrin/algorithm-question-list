#include <bits/stdc++.h>

using namespace std;

int main() {
  // 读取输入
  string line;
  getline(cin, line);

  // 特殊输入处理
  if (line.empty()) {
    cout << -1 << endl;
    return 0;
  }

  // 解析输入
  vector<int> people;
  int num;
  stringstream ss(line);

  while (ss >> num) {
    people.push_back(num);
  }

  // 输入有效性检查
  if (people.empty() || people.size() > 30000) {
    cout << -1 << endl;
    return 0;
  }

  for (auto p : people) {
    if (p == 0) {
      cout << -1 << endl;
      return 0;
    }
  }

  // 使用栈来处理逃生逻辑
  stack<int> s;           // 用于存储向右逃生的人（正数）
  int negative_count = 0; // 成功向左逃生的人数

  for (int person : people) {
    if (person > 0) {
      // 正数，向右逃生，入栈
      s.push(person);
    } else {
      // 负数，向左逃生
      int current_fight_power = abs(person);
      while (current_fight_power > 0 && !s.empty()) {
        // 先检查栈是否为空
        // 栈顶元素
        int top_power = s.top();
        if (top_power > current_fight_power) {
          // 正数战斗力大于负数
          s.pop();
          s.push(top_power - current_fight_power); // 正数继续逃生
          current_fight_power = 0;                 // 负数已被打败
        } else if (top_power < current_fight_power) {
          // 负数战斗力大于正数
          s.pop();
          current_fight_power -= top_power; // 负数继续战斗
        } else {
          // 同归于尽
          s.pop();
          current_fight_power = 0; // 两者都死亡
        }
      }
      if (current_fight_power > 0) {
        // 如果栈已空，负数逃生成功
        negative_count++;
      }
    }
  }

  // 存活的人数为栈中的正数加上成功的负数人数
  int positive_count = s.size();
  int total_survivors = positive_count + negative_count;

  cout << total_survivors << endl;

  return 0;
}