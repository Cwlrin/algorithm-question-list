#include <bits/stdc++.h>

using namespace std;

int main() {
  vector<string> dic = {" ", ",.", "abc", "def", "ghi",
                        "jkl", "mno", "pqrs", "tuv", "wxyz"};

  string input_string;
  cin >> input_string;

  input_string += '/';

  string result;
  bool is_num_mode = true;
  int delay_num = -1;
  int delay_idx = -1;

  for (const auto& current_char : input_string) {
    // 处理模式切换
    if (current_char == '#') {
      is_num_mode = !is_num_mode;
    }

    // 处理中断情况
    if (current_char == '#' || current_char == '/') {
      // 如果之前有英文输入
      if (delay_num != -1) {
        result += dic[delay_num][delay_idx];
      }

      // 更新delay_num和delay_idx
      if (current_char == '#' || current_char == '/') {
        delay_num = -1;
        delay_idx = -1;
      } else {
        delay_num = current_char - '0';
        delay_idx = 0;
      }
    } else if (is_num_mode) {
      // 数字模式下, 数字直接录入结果
      result += current_char;
    } else if (current_char - '0' == delay_num) {
      // 英文模式下, 如果当前按键与上一次按键相同, 则进行英文字母切换
      delay_idx += 1;
      delay_idx %= dic[delay_num].length();
    } else {
      // 英文模式下, 如果当前按键与上一次按键不同, 则打断英文字母切换动作
      // 如果之前有英文输入
      if (delay_num != -1) {
        result += dic[delay_num][delay_idx];
      }

      // 更新delay_num和delay_idx
      delay_num = current_char - '0';
      delay_idx = 0;
    }
  }

  cout << result << endl;

  return 0;
}