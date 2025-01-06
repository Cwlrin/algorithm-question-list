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
    sort(sorted_word.begin(), sorted_word.end());
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

  sort(count_vec.begin(), count_vec.end(), [](const auto& a, const auto& b) {
    if (a.second != b.second) {
      return a.second > b.second; // 按出现次数降序
    }
    if (a.first.length() != b.first.length()) {
      return a.first.length() < b.first.length(); // 按照长度升序
    }
    return a.first < b.first; // 按照字典序升序
  });

  vector<string> result;
  for (const auto& p : count_vec) {
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