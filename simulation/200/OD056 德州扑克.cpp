#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  // 牌值转换映射
  unordered_map<string, int> cardValues = {
      {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8},
      {"9", 9}, {"10", 10}, {"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}};

  // 读取牌面和花色
  vector<int> values;
  vector<char> suits;
  unordered_map<int, int> value_count;
  unordered_map<char, int> suit_count;

  // 读入5张牌
  for (int i = 0; i < 5; i++) {
    string card;
    cin >> card;
    char suit;
    cin >> suit;

    // 转换牌面值
    int value = cardValues[card];
    values.push_back(value);
    suits.push_back(suit);

    // 统计牌面和花色数量
    value_count[value]++;
    suit_count[suit]++;
  }

  // 排序牌面值
  sort(values.begin(), values.end());

  // 判断特殊顺子
  const bool is_special_straight =
      (values == vector<int>{14, 2, 3, 4, 5}) ||   // A2345
      (values == vector<int>{10, 11, 12, 13, 14}); // 10JQKA

  // 判断普通顺子
  const bool is_straight = (values.back() - values.front() == 4 &&
                     set<int>(values.begin(), values.end()).size() == 5) ||
                    is_special_straight;

  // 判断同花
  const bool is_flush = suit_count.size() == 1;

  // 找出最大重复数和次大重复数
  int max_same_count = 0, second_max_same_count = 0;
  for (const auto& [value, count] : value_count) {
    if (count > max_same_count) {
      second_max_same_count = max_same_count;
      max_same_count = count;
    } else if (count > second_max_same_count) {
      second_max_same_count = count;
    }
  }

  // 牌型判断（按优先级）
  int result = 7; // 默认为最低级牌型
  if (is_flush && is_straight)
    result = 1; // 同花顺
  else if (max_same_count == 4)
    result = 2; // 四条
  else if (max_same_count == 3 && second_max_same_count == 2)
    result = 3; // 葫芦
  else if (is_flush)
    result = 4; // 同花
  else if (is_straight)
    result = 5; // 顺子
  else if (max_same_count == 3)
    result = 6; // 三条

  // 输出结果
  cout << result << endl;

  return 0;
}