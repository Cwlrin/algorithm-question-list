// OD285. 数组去重和排序
// 题目描述：
// 给定一个乱序的数组，删除所有的重复元素，使得每个元素只出现一次，并且按照出现的次数从高到低进行排序，相同出现次数按照第一次出现顺序进行先后排序
// 输入描述：
// 一个数组
// 输出描述：
// 去重排序后的数组
// 用例 1：
// 输入：
// 1,3,3,3,2,4,4,4,5
// 输出：
// 3,4,1,2,5
// 难度：中等
// 标签：数组、哈希、排序

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
    // if (countMap.find(arr[i]) == countMap.end())
    if (!count_map.contains(arr[i])) {
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
  ranges::sort(sorted_arr, [](const auto& a, const auto& b) {
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