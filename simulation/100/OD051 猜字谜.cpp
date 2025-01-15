#include <bits/stdc++.h>

using namespace std;

int main() {
  // 输入谜面和谜底
  string puzzles_input, words_input;
  getline(cin, puzzles_input);
  getline(cin, words_input);

  // 结果集
  vector<string> results;

  // 分割输入字符串的 lambda 函数
  auto split = [](const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream token_stream(s);
    while (getline(token_stream, token, delimiter)) {
      tokens.push_back(token);
    }
    return tokens;
  };

  // 标准化单词的 lambda 函数
  auto normalize_word = [](string word) {
    sort(word.begin(), word.end());
    return word;
  };

  // 去重标准化单词的 lambda 函数
  auto deduplicate_word = [](string word) {
    set<char> unique_chars(word.begin(), word.end());
    string result(unique_chars.begin(), unique_chars.end());
    sort(result.begin(), result.end());
    return result;
  };

  // 分割谜面和谜底
  vector<string> puzzles = split(puzzles_input, ',');
  vector<string> words = split(words_input, ',');

  // 遍历每个谜面
  for (const string& puzzle : puzzles) {
    // 用于存储当前谜面的所有匹配单词
    vector<string> current_matched_words;

    // 标准化谜面
    string normalized_puzzle = normalize_word(puzzle);
    string deduplicated_puzzle = deduplicate_word(puzzle);

    // 遍历谜底库
    for (const string& word : words) {
      // 标准化谜底
      string normalized_word = normalize_word(word);
      string deduplicated_word = deduplicate_word(word);

      // 匹配规则：顺序可调换或去重后相同
      if (normalized_puzzle == normalized_word ||
          deduplicated_puzzle == deduplicated_word) {
        current_matched_words.push_back(word);
      }
    }

    // 如果没找到匹配，加入 "not found"
    if (current_matched_words.empty()) {
      results.push_back("not found");
    } else {
      // 将所有匹配的单词以逗号分隔加入结果
      string match_result;
      for (size_t i = 0; i < current_matched_words.size(); ++i) {
        match_result += current_matched_words[i];
        if (i < current_matched_words.size() - 1) {
          match_result += ",";
        }
      }
      results.push_back(match_result);
    }
  }

  // 输出结果
  for (size_t i = 0; i < results.size(); ++i) {
    cout << results[i];
    if (i < results.size() - 1)
      cout << ",";
  }
  cout << endl;

  return 0;
}