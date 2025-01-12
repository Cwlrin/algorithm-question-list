#include <bits/stdc++.h>
using namespace std;

int main() {
  // ---------- 1. 读取输入 ----------
  string text, dict_str;
  getline(cin, text);
  getline(cin, dict_str);

  // ---------- 2. 构建可用词典 ----------
  // 这里用 multiset 或者 map 记录词频更灵活，方便控制每个词可使用几次
  // 如果只想用一次，用 set 也行，一旦匹配后就直接 erase
  multiset<string> dictionary;
  {
    stringstream ss(dict_str);
    string w;
    while (getline(ss, w, ',')) {
      // 去除可能的空格
      w.erase(remove_if(w.begin(), w.end(), ::isspace), w.end());
      if (!w.empty()) {
        dictionary.insert(w);
      }
    }
  }

  // ---------- 3. 分词处理 ----------
  vector<string> result;
  int n = text.size();
  int start = 0;
  while (start < n) {
    // 如果当前字符是标点，就跳过
    if (text[start] == ',' || text[start] == '.' || text[start] == ';') {
      start++;
      continue;
    }

    // 从大到小尝试，找最长匹配
    bool matched = false;
    for (int len = n - start; len > 0; len--) {
      string candidate = text.substr(start, len);
      // 如果字典中有这个候选词，则使用它
      auto it = dictionary.find(candidate);
      if (it != dictionary.end()) {
        result.push_back(candidate);
        // 用完就移除，使得后续不能再匹配到同一个词
        dictionary.erase(it);
        start += len;
        matched = true;
        break;
      }
    }

    // 如果没有匹配到，就把当前字符当作单字输出
    if (!matched) {
      result.push_back(string(1, text[start]));
      start++;
    }
  }

  // ---------- 4. 输出结果 ----------
  for (int i = 0; i < (int)result.size(); i++) {
    cout << result[i];
    if (i < (int)result.size() - 1) {
      cout << ",";
    }
  }
  cout << endl;

  return 0;
}