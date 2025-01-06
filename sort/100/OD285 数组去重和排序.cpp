#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);

  // 去除输入字符串中的空格，并按逗号分割成数组
  stringstream ss(input);
  string token;
  vector<int> arr;
  while (getline(ss, token, ',')) {
    arr.push_back(stoi(token));
  }

  // 创建一个哈希表来存储每个元素的出现次数和第一次出现的位置
  unordered_map<int, pair<int, int> > count_map;
  for (int i = 0; i < arr.size(); ++i) {
    if (count_map.find(arr[i]) == count_map.end()) {
      count_map[arr[i]] = {0, i};
    }
    count_map[arr[i]].first++;
  }

  // 将哈希表转换为向量
  vector<pair<int, pair<int, int> > > sorted_arr;
  // for (const auto& entry : count_map) {
  //   sorted_arr.push_back({entry.first, entry.second});
  // }
  for (const auto& [fst, snd] : count_map) {
    sorted_arr.emplace_back(fst, snd);
  }

  // 排序
  // sort(sort_arr.begin(), sort_arr.end());
  sort(sorted_arr.begin(), sorted_arr.end(), [](const auto& a, const auto& b) {
    if (a.second.first == b.second.first) {
      return a.second.second < b.second.second;
    }
    return a.second.first > b.second.first;
  });

  for (int i = 0; i < sorted_arr.size(); ++i) {
    if (i > 0) {
      cout << ",";
    }
    cout << sorted_arr[i].first;
  }
  cout << endl;
}