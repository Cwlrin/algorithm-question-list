#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// 将牌面值映射为对应索引
int ConvertCardToIndex(const string& card) {
  if (card == "J")
    return 11;
  if (card == "Q")
    return 12;
  if (card == "K")
    return 13;
  if (card == "A")
    return 14;
  if (card == "2")
    return 16;
  if (card == "B")
    return 17;
  if (card == "C")
    return 18;
  return stoi(card); // 对于 3 到 10，直接转换为整数
}

// 将索引映射为牌面值字符串
string ConvertIndexToCard(int index) {
  switch (index) {
    case 11:
      return "J";
    case 12:
      return "Q";
    case 13:
      return "K";
    case 14:
      return "A";
    case 16:
      return "2";
    case 17:
      return "B";
    case 18:
      return "C";
    default:
      return to_string(index); // 3 到 10
  }
}

int main() {
  // 初始化牌面数量的数组，大小为 19
  vector<int> card_count(19, 0);

  // 设定初始的牌面分布（示例：4张3,4张4,4张5...）
  card_count = {0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4, 1, 1};

  string hand_input, played_input;
  cin >> hand_input;   // 输入玩家手中的牌
  cin >> played_input; // 输入已出过的牌

  // 处理手中的牌
  stringstream hand_stream(hand_input);
  string current_card;
  while (getline(hand_stream, current_card, '-')) {
    card_count[ConvertCardToIndex(current_card)]--;
  }

  // 处理已出过的牌
  stringstream played_stream(played_input);
  while (getline(played_stream, current_card, '-')) {
    card_count[ConvertCardToIndex(current_card)]--;
  }

  int max_length = 0; // 记录当前找到的最长顺子的长度
  int max_start = -1; // 记录当前找到的最长顺子的起始索引

  // 左右指针的初始位置
  int left = 3;
  int right = 3;

  // 声明查找顺子的边界
  while (right <= 15) {
    if (card_count[right] > 0) {
      // 如果有该牌
      right++; // 继续扩展右边界
    } else {
      // 否则，连续性被打断
      if (right - left >= max_length) {
        // 更新最长顺子的长度和起始索引
        max_length = right - left;
        max_start = left;
      }
      left = right + 1; // 移动左指针到右指针的下一个位置
      right = left;     // 同步右指针
    }
  }

  // 输出结果
  if (max_length < 5) {
    cout << "NO-CHAIN"; // 如果没有找到有效的顺子
  } else {
    cout << ConvertIndexToCard(max_start); // 输出最长顺子的开始牌面
    for (int i = 1; i < max_length; ++i) {
      cout << "-" << ConvertIndexToCard(max_start + i); // 输出后续牌面
    }
  }

  return 0;
}