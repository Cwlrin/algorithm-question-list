#include <bits/stdc++.h>

using namespace std;

int main() {
  string input1, input2;
  cin >> input1 >> input2;

  // 计算 input2 中的不同字母的数量
  set<char> unique_chars2(input2.begin(), input2.end());
  int target_count = unique_chars2.size();

  // 使用正则表达式分割字符串，提取仅含有字母的有效子串
  const regex non_letter_pattern("[0-9a-f]+");
  sregex_token_iterator it(input1.begin(), input1.end(), non_letter_pattern,
                           -1);
  sregex_token_iterator end;

  vector<string> vaild_substrings;
  for (; it != end; ++it) {
    // 移除空串
    string substring = it->str();
    if (!substring.empty()) {
      vaild_substrings.push_back(substring);
    }
  }

  string best_substring = "Not Found";
  int best_count = -1;

  // 遍历有效子串
  for (const string& substring : vaild_substrings) {
    // 计算当前子串中不同字母的数量
    set<char> unique_chars(substring.begin(), substring.end());
    int current_count = unique_chars.size();

    // 判断是否满足条件
    if (current_count <= target_count) {
      // 更新最佳子串的条件
      if (best_count == -1 || current_count > best_count || (
            current_count == best_count && substring > best_substring)) {
        best_substring = substring;
        best_count = current_count;
      }
    }
  }

  cout << best_substring << endl;
  return 0;
}