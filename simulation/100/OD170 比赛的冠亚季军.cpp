#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // 读取实力值
  vector<long> strengths;
  long strength;
  while (cin >> strength) {
    strengths.push_back(strength);
  }

  // 初始化运动员ID
  vector<int> sports;
  for (int i = 0; i < strengths.size(); ++i) {
    sports.push_back(i);
  }

  // 比赛分组队列
  deque<vector<int>> match_groups;
  match_groups.push_front(sports);

  // 进行淘汰赛
  while (match_groups.front().size() > 1) {
    // 取出当前分组
    vector<int> current_group = match_groups.front();
    match_groups.pop_front();

    // 胜者和败者分组
    vector<int> winners, losers;

    // 两两比赛
    for (int i = 1; i < current_group.size(); i += 2) {
      int id1 = current_group[i - 1];  // 序号小的选手
      int id2 = current_group[i];      // 序号大的选手

      // 比较规则：实力不同按实力，相同按id
      if (strengths[id1] > strengths[id2]) {
        winners.push_back(id1);
        losers.push_back(id2);
      } else if (strengths[id1] < strengths[id2]) {
        winners.push_back(id2);
        losers.push_back(id1);
      } else {
        // 实力相同，id小的获胜
        winners.push_back(id1);
        losers.push_back(id2);
      }
    }

    // 处理奇数情况
    if (current_group.size() % 2 != 0) {
      winners.push_back(current_group.back());
    }

    // 压入败者组和胜者组
    match_groups.push_front(losers);
    match_groups.push_front(winners);
  }

  // 确定冠军
  int first = match_groups[0][0];

  // 确定亚军
  int second = match_groups[1][0];

  // 确定季军（排序处理）
  sort(match_groups[2].begin(), match_groups[2].end(),
       [&strengths](int a, int b) {
         return strengths[a] != strengths[b] ? strengths[a] > strengths[b]
                                             : a < b;
       });
  int third = match_groups[2][0];

  // 输出结果
  cout << first << " " << second << " " << third << endl;

  return 0;
}