#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  unordered_map<string, int> url_count;
  while (getline(cin, input)) {
    // 判断是否输入是数字
    if (isdigit(input[0])) {
      const int n = stoi(input);
      vector<pair<string, int> > url_list(url_count.begin(), url_count.end());

      // 对 url 进行排序
      sort(url_list.begin(), url_list.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) {
          return a.second > b.second; // 按照访问次数排序
        }
        return a.first < b.first; // 访问次数相同时按照字母序排序
      });

      // 输出前 n 个 URL
      for (int i = 0; i < n; ++i) {
        if (i > 0) {
          cout << ",";
        }
        cout << url_list[i].first;
      }
      cout << endl;
    } else {
      // 输入 url，更新统计数据
      url_count[input]++;
    }
  }
  return 0;
}