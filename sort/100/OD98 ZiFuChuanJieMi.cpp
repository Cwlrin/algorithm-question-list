// OD098 字符串解密
// 题目描述：
// 给定两个字符串 string1 和 string2。 string1 是一个被加扰的字符串。
// string1 由小写英文字母（'a'~ 'z'）和数字字符（'0'~ '9'）组成，而加扰字符串由 '0'~ '9'、'a'~'f'组成。
// string1 里面可能包含 0 个或多个加扰子串，剩下可能有 0 个或多个有效子串，这些有效子串被加扰子串隔开。
// string2 是一个参考字符串，仅由小写英文字母（'a'~'z'）组成。
// 你需要在 string1 字符串里找到一个有效子串，这个有效子串要同时满足下面两个条件：
// 1. 这个有效子串里不同字母的数量不超过且最接近于 string2 里不同字母的数量，即小于或等于 string2 里不同字母的数量的同时且最大。
// 2. 这个有效子串是满足条件（1）里的所有子串（如果有多个的话）里字典序最大的一个。
// 如果没有找到合适条件的子串的话，请输出 "Not Found"
// 输入描述：
// input_string1
// input_string2
// 输出描述：
// output_string
// 用例 1：
// 输入：
// ```
// 123admyffc79pt
// ssyy
// ```
// 输出：
// ```
// pt
// ```
// 说明：
// 将输入字符串 1 里的加扰子串"123ad"、"ffc79"去除后得到有效子串序列："my"、"pt"，其中 "my" 里不同字母的数量为 2（有'm'和'y'两个不同字母），"pt" 里不同字母的数量为 2（有'p'和't'两个不同字母）；输入字符串 2 里不同字母的数量为 2（有's'和'y'两个不同字母）。
// 可得到最终输出结果为 "pt"，其不同字母的数量最接近与 "ssyy" 里不同字母的数量的同时字典序最大。
// 用例 2：
// 输入：
// ```
// 123admyffc79ptaagghi2222smeersst88mnrt
// ssyyfgh
// ```
// 输出：
// ```
// mnrt
// ```
// 说明：将输入字符串 1 里的加扰子串"123ad"、"ffc79"、"aa"、"2222"、"ee"、"88" 去除后得到有效子串序列："my"、"pt"、"gghi"、"sm"、"rsst"、"mnrt"；输入字符串 2 里不同字母的数量为 5（有's'、'y'、'f'、'g'、'h'5 个不同字母）。可得到最终输出结果为"mnrt"，其不同字母的数量（为 4）最接近于"ssyyfgh"里不同字母的数量，其他有效子串不同字母的数量都小于"mnrt"。
// 用例 3：
// 输入：
// ```
// abcmnq
// rt
// ```
// 输出：
// ```
// Not Found
// ```
// 说明：将输入字符串 1 里的加扰子串"abc"去除后得到有效子串序列："mnq"；输入字符串 2 里不同字母的数量为 2（有'r'、't'两个不同的字母）。可得到最终的输出结果为"Not Found"，没有符合要求的有效子串，因有效子串里的不同字母的数量（为 3），大于输入字符串 2 里的不同字母的数量。
// 难度：困难
// 标签：字符串、排序

#include <bits/stdc++.h>

using namespace std;

int main() {
  string input1, input2;
  cin >> input1 >> input2;

  // 计算 input2 中的不同字母的数量
  set unique_chars2(input2.begin(), input2.end());
  int target_count = unique_chars2.size();

  // 使用正则表达式分割字符串，提取仅含有字母的有效子串
  const regex non_letter_pattern("[0-9a-f]+");
  sregex_token_iterator it(input1.begin(), input1.end(), non_letter_pattern,
                           -1);
  sregex_token_iterator end;

  vector<string> vaild_substrings;
  for (; it != end; ++it) {
    // 移除空串
    if (string substring = it->str(); !substring.empty()) {
      vaild_substrings.push_back(substring);
    }
  }

  string best_substring = "Not Found";
  int best_count = -1;

  // 遍历有效子串
  for (const string& substring : vaild_substrings) {
    // 计算当前子串中不同字母的数量
    set unique_chars(substring.begin(), substring.end());
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