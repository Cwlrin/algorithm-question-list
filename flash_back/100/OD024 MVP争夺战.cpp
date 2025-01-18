#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t; // 读入得分分钟数

  vector<int> scores(t);
  for (int i = 0; i < t; i++) {
    cin >> scores[i]; // 读入每分钟的得分
  }

  // 计算总得分
  const int total_score = accumulate(scores.begin(), scores.end(), 0);

  // 定义递归进行分配
  function<bool(deque<int>&, int, vector<int>&, int)> partition =
      [&](deque<int>& link, int index, vector<int>& buckets, int sub_sum) {
    // 如果所有得分都分配完，返回 true
    if (index == link.size())
      return true;

    int select = link[index];

    for (int i = 0; i < buckets.size(); i++) {
      if (i > 0 && buckets[i] == buckets[i - 1])
        continue; // 避免重复处理

      if (select + buckets[i] <= sub_sum) {
        buckets[i] += select; // 分配得分
        // 递归检查下一个得分
        if (partition(link, index + 1, buckets, sub_sum))
          return true;
        buckets[i] -= select; // 回退
      }
    }

    return false; // 无法分配
  };

  // 检查能否分配成 m 组
  const function<bool(deque<int>&, int, int)> can_partition_m_subsets =
      [&](deque<int>& link, int sum, int m) {
    if (sum % m != 0)
      return false; // 总分不能被 m 整除

    const int sub_sum = sum / m;

    // 若最大得分超过目标分数，无法分配
    if (sub_sum < link[0])
      return false;

    // 移除被完全占用的得分
    while (!link.empty() && link[0] == sub_sum) {
      link.pop_front();
      m--;
    }

    vector<int> buckets(m, 0);
    return partition(link, 0, buckets, sub_sum);
  };

  // 进行从总人数到最少人数的尝试
  int max_players = t;                                        // 初始设定最多人数
  sort(scores.begin(), scores.end(), greater<int>());         // 从大到小排序
  const deque<int> score_deque(scores.begin(), scores.end()); // 将分数转换为双端队列

  // 尝试从所有人数到 1 人，每次减少人数
  while (max_players >= 1) {
    // 复制分数队列以进行检查
    deque<int> link_cp = score_deque;
    if (can_partition_m_subsets(link_cp, total_score, max_players)) {
      cout << total_score / max_players << endl; // 输出最小 MVP 得分
      return 0;
    }
    max_players--;
  }

  // 理论上不会到达这里
  cout << total_score << endl;
  return 0;
}