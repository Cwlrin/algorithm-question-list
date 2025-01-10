#include <bits/stdc++.h>

using namespace std;

int main() {
  // 输入起始单词的索引和单词数量
  int start_index, word_count;
  cin >> start_index >> word_count;

  // 读取单词数组
  vector<string> word_list(word_count);
  for (int i = 0; i < word_count; i++) {
    cin >> word_list[i];
  }

  // 取出起始单词
  string chain = word_list[start_index];

  // 创建前缀字典，存储以首字母为键的单词集合
  unordered_map<char, vector<string>> prefix;

  // 填充前缀字典
  for (int i = 0; i < word_count; i++) {
    if (i != start_index) {  // 不加入起始单词
      prefix[word_list[i][0]].push_back(word_list[i]);
    }
  }

  // 按照长度和字典序排序每个字母对应的单词
  for (auto& pair : prefix) {
    sort(pair.second.begin(), pair.second.end(),
         [](const string& a, const string& b) {
           if (a.length() != b.length()) {
             return a.length() > b.length();  // 长度优先
           }
           return a < b;  // 字典序优先
         });
  }

  // 开始接龙
  while (true) {
    char last_char = chain.back();  // 得到当前链的尾字符

    // 找到以last_char为首字母的单词
    if (prefix.find(last_char) == prefix.end() || prefix[last_char].empty()) {
      break;  // 如果不存在可接的单词，退出循环
    }

    // 取出首字母相同的优先级最高的单词
    string next_word = prefix[last_char].front();
    chain += next_word;  // 拼接到chain字符串

    // 从字典中移除已使用的单词
    prefix[last_char].erase(prefix[last_char].begin());
  }

  // 输出结果
  cout << chain << endl;

  return 0;
}