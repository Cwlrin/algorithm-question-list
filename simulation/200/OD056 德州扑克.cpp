#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  // 牌值转换映射
  unordered_map<string, int> cardValues = {
      {"2", 2}, {"3", 3},   {"4", 4},  {"5", 5},  {"6", 6},  {"7", 7}, {"8", 8},
      {"9", 9}, {"10", 10}, {"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}};

  // 读取牌面和花色
  vector<int> values;
  vector<char> suits;
  unordered_map<int, int> valueCount;
  unordered_map<char, int> suitCount;

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
    valueCount[value]++;
    suitCount[suit]++;
  }

  // 排序牌面值
  sort(values.begin(), values.end());

  // 判断特殊顺子
  bool isSpecialStraight =
      (values == vector<int>{14, 2, 3, 4, 5}) ||    // A2345
      (values == vector<int>{10, 11, 12, 13, 14});  // 10JQKA

  // 判断普通顺子
  bool isStraight = (values.back() - values.front() == 4 &&
                     set<int>(values.begin(), values.end()).size() == 5) ||
                    isSpecialStraight;

  // 判断同花
  bool isFlush = suitCount.size() == 1;

  // 找出最大重复数和次大重复数
  int maxSameCount = 0, secondMaxSameCount = 0;
  for (const auto& [value, count] : valueCount) {
    if (count > maxSameCount) {
      secondMaxSameCount = maxSameCount;
      maxSameCount = count;
    } else if (count > secondMaxSameCount) {
      secondMaxSameCount = count;
    }
  }

  // 牌型判断（按优先级）
  int result = 7;  // 默认为最低级牌型
  if (isFlush && isStraight)
    result = 1;  // 同花顺
  else if (maxSameCount == 4)
    result = 2;  // 四条
  else if (maxSameCount == 3 && secondMaxSameCount == 2)
    result = 3;  // 葫芦
  else if (isFlush)
    result = 4;  // 同花
  else if (isStraight)
    result = 5;  // 顺子
  else if (maxSameCount == 3)
    result = 6;  // 三条

  // 输出结果
  cout << result << endl;

  return 0;
}