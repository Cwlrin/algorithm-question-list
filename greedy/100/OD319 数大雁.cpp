#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;

  // 记录各字符出现次数的计数器
  int q_cnt = 0, u_cnt = 0, a_cnt = 0, c_cnt = 0;

  // 存储每个 quack 的区间
  vector<pair<int, int> > intervals;

  // 存储每个 q 的位置
  queue<int> q_pos;

  for (int i = 0; i < s.length(); i++) {
    char c = s[i];

    if (c == 'q') {
      q_pos.push(i);
      q_cnt++;
    } else if (c == 'u') {
      // u 出现次数不能超过 q 的次数
      if (u_cnt >= q_cnt)
        continue;
      u_cnt++;
    } else if (c == 'a') {
      // a 出现次数不能超过 u 的次数
      if (a_cnt >= u_cnt)
        continue;
      a_cnt++;
    } else if (c == 'c') {
      // c 出现次数不能超过 a 的次数
      if (c_cnt >= a_cnt)
        continue;
      c_cnt++;
    } else if (c == 'k') {
      // k 之前必须有 c
      if (c_cnt < 1)
        continue;

      // 取出第一个 q 的位置作为区间起点
      int start = q_pos.front();
      q_pos.pop();

      // 记录区间
      intervals.emplace_back(start, i);

      // 计数器归零
      q_cnt--;
      u_cnt--;
      a_cnt--;
      c_cnt--;
    }
  }

  // 如果没有合法的叫声，返回 -1
  if (intervals.empty()) {
    cout << -1 << endl;
    return 0;
  }

  // 计算最大重叠数
  int max_geese = 0;
  for (int i = 0; i < intervals.size(); i++) {
    int current_overlap = 1;
    for (int j = i + 1; j < intervals.size(); j++) {
      // 如果后一个区间的起点在前一个区间内，说明有重叠
      if (intervals[j].first <= intervals[i].second) {
        current_overlap++;
      } else {
        // 由于区间是按顺序的，一旦不重叠就可以退出
        break;
      }
    }
    max_geese = max(max_geese, current_overlap);
  }

  cout << max_geese << endl;
  return 0;
}