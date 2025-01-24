#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  // 存储任务的区间
  vector<pair<int, int> > tasks(n);
  for (int i = 0; i < n; ++i) {
    cin >> tasks[i].first >> tasks[i].second; // 读取任务的开始和结束时间
  }

  // 按结束时间降序排序，结束时间相同则按开始时间降序
  sort(tasks.begin(), tasks.end(),
       [](const pair<int, int>& a, const pair<int, int>& b) {
         if (a.second == b.second) {
           return a.first > b.first; // 开始时间降序
         }
         return a.second > b.second; // 结束时间降序
       });

  priority_queue<int> pq; // 优先队列，存储任务开始时间
  int count = 0;          // 计数已执行的任务数量
  int pq_end = INT_MAX;   // 维护公共结束时间，从很大开始

  for (const auto& task : tasks) {
    int start = task.first;
    int end = task.second;

    // 处理时间段
    // 如果当前任务的结束时间小于已知的公共结束时间
    if (end < pq_end) {
      // 从结束时间到公共结束时间,环顾可用任务
      while (!pq.empty() && pq_end > end) {
        // 只有当开始时间 <= 公共结束时间时，才能执行任务
        if (pq.top() <= pq_end) {
          pq.pop();
          pq_end--; // 更新时间
          count++;  // 执行任务计数
        } else {
          pq.pop(); // 不满足条件的任务直接弹出
        }
      }
    }

    // 添加当前任务的开始时间到优先队列
    pq.push(start);
    // 更新公共结束时间
    pq_end = end;
  }

  // 处理优先队列中剩余的任务
  while (!pq.empty()) {
    if (pq.top() <= pq_end) {
      pq.pop();
      pq_end--; // 每处理一次任务，公共结束时间减少一次
      count++;
    } else {
      pq.pop(); // 过期任务移除
    }
  }

  cout << count << endl; // 输出可处理的最大任务数量

  return 0;
}