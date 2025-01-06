#include <bits/stdc++.h>

using namespace std;

int main() {
  string sentence, prefix;
  getline(cin, sentence);
  cin >> prefix;
  // 使用 set 自动去重  
  set<string> unique_words;
  string current_word;
  // 分割句子为单词，特别处理带撇号的单词  
  for (char c : sentence) {
    if (isalpha(c) || c == '\'') {
      current_word += c;
    } else {
      if (!current_word.empty()) {
        // 特殊处理带撇号的单词  
        if (current_word.find('\'') != string::npos) {
          size_t pos = current_word.find('\'');
          string first = current_word.substr(0, pos);
          string second = current_word.substr(pos + 1);
          // 确保非空的单词被添加  
          if (!first.empty()) unique_words.insert(first);
          if (!second.empty()) unique_words.insert(second);
        } else {
          unique_words.insert(current_word);
        }
        current_word.clear();
      }
    }
  }
  // 添加最后一个单词  
  if (!current_word.empty()) {
    if (current_word.find('\'') != string::npos) {
      size_t pos = current_word.find('\'');
      string first = current_word.substr(0, pos);
      string second = current_word.substr(pos + 1);
      if (!first.empty()) unique_words.insert(first);
      if (!second.empty()) unique_words.insert(second);
    } else {
      unique_words.insert(current_word);
    }
  }
  // 查找匹配前缀的单词  
  vector<string> matched_words;
  // 查找以前缀开头的单词  
  for (const auto& w : unique_words) {
    // 单词开头匹配  
    // 添加长度检查，避免substr越界  
    if (w.length() >= prefix.length() && w.substr(0, prefix.length()) ==
        prefix) {
      matched_words.push_back(w);
    }
  }
  // 去重  
  sort(matched_words.begin(), matched_words.end());
  matched_words.erase(unique(matched_words.begin(), matched_words.end()),
                     matched_words.end());
  // 只在没有找到任何匹配时，输出前缀  
  if (matched_words.empty()) {
    cout << prefix << endl;
  } else {
    // 输出结果  
    for (size_t i = 0; i < matched_words.size(); ++i) {
      cout << matched_words[i];
      if (i < matched_words.size() - 1) cout << " ";
    }
    cout << endl;
  }
  return 0;
}  