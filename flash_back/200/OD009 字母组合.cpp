#include <bits/stdc++.h>
using namespace std;

// 数字到字母的映射
unordered_map<char, vector<char>> num_to_letters = {
  {'0', {'a','b','c'}},
  {'1', {'d','e','f'}},
  {'2', {'g','h','i'}},
  {'3', {'j','k','l'}},
  {'4', {'m','n','o'}},
  {'5', {'p','q','r'}},
  {'6', {'s','t'}},
  {'7', {'u','v'}},
  {'8', {'w','x'}},
  {'9', {'y','z'}}
};

int main() {
  string digits, shield;
  cin >> digits >> shield;

  vector<string> result;

  // 回溯函数，使用 lambda 实现
  function<void(string, int)> backtrack =
  [&](const string& current, int index) {
    // 递归终止条件：达到数字串长度
    if (index == digits.length()) {
      // 检查是否包含所有屏蔽字符
      bool is_valid_combination = true;
      for (const char shield_char : shield) {
        if (current.find(shield_char) == string::npos) {
          is_valid_combination = false;
          break;
        }
      }

      // 如果不包含所有屏蔽字符，则加入结果
      if (!is_valid_combination) {
        result.push_back(current);
      }
      return;
    }

    // 获取当前数字对应的字母列表
    vector<char>& letters = num_to_letters[digits[index]];

    for (char letter : letters) {
      // 递归生成组合
      backtrack(current + letter, index + 1);
    }
  };

  // 启动回溯
  backtrack("", 0);

  // 输出结果
  for (const string& combo : result) {
    cout << combo << ",";
  }
  cout << endl;

  return 0;
}