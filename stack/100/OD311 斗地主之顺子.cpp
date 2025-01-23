#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
  // 定义牌的映射
  unordered_map<string, int> card_value = {
      {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7},
      {"8", 8}, {"9", 9}, {"10", 10}, {"J", 11},
      {"Q", 12}, {"K", 13}, {"A", 14}
  };

  // 反向映射
  unordered_map<int, string> value_card = {
      {3, "3"}, {4, "4"}, {5, "5"}, {6, "6"}, {7, "7"},
      {8, "8"}, {9, "9"}, {10, "10"}, {11, "J"},
      {12, "Q"}, {13, "K"}, {14, "A"}
  };

  // 读取输入
  string line;
  getline(cin, line);

  // 解析输入
  vector<string> cards;
  stringstream ss(line);
  string card;
  while (ss >> card) {
    cards.push_back(card);
  }

  // 统计每张牌的数量
  unordered_map<int, int> count;
  for (const string& c : cards) {
    if (c != "2") {
      // 排除2
      count[card_value[c]]++;
    }
  }

  // 存储所有顺子
  vector<vector<int> > straights;

  // 尝试生成顺子
  for (int len = 12; len >= 5; len--) {
    // 从最长的顺子开始
    for (int start = 3; start <= 14 - len + 1; start++) {
      unordered_map<int, int> tempCount = count;
      vector<int> straight;
      bool valid = true;

      // 检查连续len张牌是否存在
      for (int i = start; i < start + len; i++) {
        // 如果某张牌不存在，顺子无效
        if (tempCount.find(i) == tempCount.end() || tempCount[i] == 0) {
          valid = false;
          break;
        }
        straight.push_back(i);
        tempCount[i]--;
      }

      // 如果顺子有效，加入结果并更新原始计数
      if (valid) {
        // 更新原始计数
        for (int card : straight) {
          count[card]--;
        }
        straights.push_back(straight);
      }
    }
  }

  // 按顺子起始牌大小排序
  sort(straights.begin(), straights.end(),
       [](const vector<int>& a, const vector<int>& b) {
         return a[0] < b[0];
       });

  // 输出结果
  if (straights.empty()) {
    cout << "No" << endl;
  } else {
    for (const auto& straight : straights) {
      for (int i = 0; i < straight.size(); i++) {
        cout << value_card[straight[i]];
        if (i < straight.size() - 1)
          cout << " ";
      }
      cout << endl;
    }
  }

  return 0;
}