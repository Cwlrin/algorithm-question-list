#include <bits/stdc++.h>

using namespace std;

int main() {
  // 输入谜面和谜底
  string puzzlesInput, wordsInput;
  getline(cin, puzzlesInput);
  getline(cin, wordsInput);

  // 结果集
  vector<string> results;

  // 分割输入字符串的 lambda 函数
  auto split = [](const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
      tokens.push_back(token);
    }
    return tokens;
  };

  // 标准化单词的 lambda 函数
  auto normalizeWord = [](string word) {
    sort(word.begin(), word.end());
    return word;
  };

  // 去重标准化单词的 lambda 函数
  auto deduplicateWord = [](string word) {
    set<char> uniqueChars(word.begin(), word.end());
    string result(uniqueChars.begin(), uniqueChars.end());
    sort(result.begin(), result.end());
    return result;
  };

  // 分割谜面和谜底
  vector<string> puzzles = split(puzzlesInput, ',');
  vector<string> words = split(wordsInput, ',');

  // 遍历每个谜面
  for (const string& puzzle : puzzles) {
    // 用于存储当前谜面的所有匹配单词
    vector<string> currentMatchedWords;

    // 标准化谜面
    string normalizedPuzzle = normalizeWord(puzzle);
    string deduplicatedPuzzle = deduplicateWord(puzzle);

    // 遍历谜底库
    for (const string& word : words) {
      // 标准化谜底
      string normalizedWord = normalizeWord(word);
      string deduplicatedWord = deduplicateWord(word);

      // 匹配规则：顺序可调换或去重后相同
      if (normalizedPuzzle == normalizedWord ||
          deduplicatedPuzzle == deduplicatedWord) {
        currentMatchedWords.push_back(word);
      }
    }

    // 如果没找到匹配，加入 "not found"
    if (currentMatchedWords.empty()) {
      results.push_back("not found");
    } else {
      // 将所有匹配的单词以逗号分隔加入结果
      string matchResult;
      for (size_t i = 0; i < currentMatchedWords.size(); ++i) {
        matchResult += currentMatchedWords[i];
        if (i < currentMatchedWords.size() - 1) {
          matchResult += ",";
        }
      }
      results.push_back(matchResult);
    }
  }

  // 输出结果
  for (size_t i = 0; i < results.size(); ++i) {
    cout << results[i];
    if (i < results.size() - 1) cout << ",";
  }
  cout << endl;

  return 0;
}