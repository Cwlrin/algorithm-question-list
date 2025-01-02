// OD003 字符串重新排序
// 题目描述：
// 给定一个字符串 s，s 包括以空格分隔的若干个单词，请对 s 进行如下处理后输出：
// 1. 单词内部调整：对每个单词字母重新按字典序排序
// 2. 单词间顺序调整：
//   1. 统计每个单词出现的次数，并按次数降序排列
//   2. 次数相同，按单词长度升序排列
//   3. 次数和单词长度均相同，按字典升序排列
// 请输出处理后的字符串，每个单词以一个空格分隔。
// 输入描述：
// 一行字符串，每个字符取值范围：[a-zA-z0-9] 以及空格，字符串长度范围：[1，1000]
// 输出描述：
// 输出处理后的字符串，每个单词以一个空格分隔。
// 用例 1：
// 输入：
// ```
// This is an apple
// ```
// 输出：
// ```
// an is This aelpp
// ```
// 用例 2：
// 输入：
// ```
// My sister is in the house not in the yard
// ```
// 输出：
// ```
// in in eht eht My is not adry ehosu eirsst
// ```
// 难度：中等
// 标签：字符串、排序

#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);

  // 分割字符串为单词，并对单词内部字母进行排序
  istringstream ss(input);
  vector<string> words;
  string word;

  auto sort_word = [](const string& word) {
    string sorted_word = word;
    ranges::sort(sorted_word);
    return sorted_word;
  };

  while (ss >> word) {
    words.push_back(sort_word(word));
  }

  // 统计每个单词出现的次数
  map<string, int> word_count;
  for (const auto& w : words) {
    word_count[w]++;
  }

  // 转换为向量，方便排序
  vector<pair<string, int> > count_vec(word_count.begin(), word_count.end());

  ranges::sort(count_vec, [](const auto& a, const auto& b) {
    if (a.second != b.second) {
      return a.second > b.second; // 按出现次数降序
    }
    if (a.first.length() != b.first.length()) {
      return a.first.length() < b.first.length(); // 按照长度升序
    }
    return a.first < b.first; // 按照字典序升序
  });

  vector<string> result;
  for (const auto &p : count_vec) {
    // 按次数输出单词
    for (int i = 0; i < p.second; i++) {
      result.push_back(p.first);
    }
  }

  cout << result[0];
  for (size_t i = 1; i < result.size(); i++) {
    cout << " " << result[i];
  }
  cout << endl;

  return 0;
}