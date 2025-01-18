#include <bits/stdc++.h>
using namespace std;

int max_score = 0;

void dfs(vector<int>& card_count, int start_idx, int current_score,
         int remaining_cards) {
  // 如果没有剩余牌，更新最大分数
  if (remaining_cards == 0) {
    max_score = max(max_score, current_score);
    return;
  }

  // 跳过没有牌的位置
  while (start_idx <= 13 && card_count[start_idx] == 0) {
    start_idx++;
  }

  // 已经遍历完所有位置
  if (start_idx > 13) {
    max_score = max(max_score, current_score);
    return;
  }

  // 尝试出单张
  if (card_count[start_idx] >= 1) {
    card_count[start_idx]--;
    dfs(card_count, start_idx, current_score + start_idx, remaining_cards - 1);
    card_count[start_idx]++;
  }

  // 尝试出对子
  if (card_count[start_idx] >= 2) {
    card_count[start_idx] -= 2;
    dfs(card_count, start_idx, current_score + start_idx * 2 * 2,
        remaining_cards - 2);
    card_count[start_idx] += 2;
  }

  // 尝试出三张
  if (card_count[start_idx] >= 3) {
    card_count[start_idx] -= 3;
    dfs(card_count, start_idx, current_score + start_idx * 3 * 2,
        remaining_cards - 3);
    card_count[start_idx] += 3;
  }

  // 尝试出炸弹
  if (card_count[start_idx] >= 4) {
    card_count[start_idx] -= 4;
    dfs(card_count, start_idx, current_score + start_idx * 4 * 3,
        remaining_cards - 4);
    card_count[start_idx] += 4;
  }

  // 尝试出顺子
  if (start_idx + 4 <= 13) {
    bool can_sequence = true;
    for (int j = 0; j < 5; j++) {
      if (card_count[start_idx + j] < 1) {
        can_sequence = false;
        break;
      }
    }

    if (can_sequence) {
      int seq_sum = start_idx + (start_idx + 1) + (start_idx + 2) + (
                            start_idx + 3) + (start_idx + 4);
      for (int j = 0; j < 5; j++) {
        card_count[start_idx + j]--;
      }
      dfs(card_count, start_idx, current_score + seq_sum * 2,
          remaining_cards - 5);
      for (int j = 0; j < 5; j++) {
        card_count[start_idx + j]++;
      }
    }
  }

  // 跳过当前位置
  dfs(card_count, start_idx + 1, current_score, remaining_cards);
}

int main() {
  string cards;
  cin >> cards;

  // 初始化card_count
  vector<int> card_count(14, 0);
  for (char c : cards) {
    int num = 0;
    if (c >= '1' && c <= '9')
      num = c - '0';
    else if (c == '0')
      num = 10;
    else if (c == 'J')
      num = 11;
    else if (c == 'Q')
      num = 12;
    else
      if (c == 'K')
        num = 13;
    card_count[num]++;
  }

  // 计算总的剩余牌数
  int total_cards = cards.length();

  // 重置最大分数
  max_score = 0;

  // 开始深度优先搜索，从第1个位置开始
  dfs(card_count, 1, 0, total_cards);

  // 输出最大分数
  cout << max_score << endl;

  return 0;
}