#include <bits/stdc++.h>

using namespace std;

int main() {
  // 读取任务列表
  string input;
  getline(cin, input);
  vector<int> tasks;
  size_t pos = 0;
  while ((pos = input.find(',')) != string::npos) {
    tasks.push_back(stoi(input.substr(0, pos)));
    input.erase(0, pos + 1);
  }
  tasks.push_back(stoi(input));

  // 读取冷却时间
  int n;
  cin >> n;

  // 统计任务频率
  unordered_map<int, int> task_counts;
  for (int task : tasks) {
    task_counts[task]++;
  }

  // 找到出现次数最多的任务类型及其出现次数
  int max_count = 0;
  for (auto& pair : task_counts) {
    max_count = max(max_count, pair.second);
  }

  // 统计有多少个任务类型出现次数等于 maxCount
  int num_max_tasks = 0;
  for (auto& pair : task_counts) {
    if (pair.second == max_count) {
      num_max_tasks++;
    }
  }

  // 计算最短时间
  int result = (max_count - 1) * (n + 1) + num_max_tasks;
  result = max(result, (int)tasks.size());

  // 输出结果
  cout << result << endl;

  return 0;
}