#include <bits/stdc++.h>

using namespace std;

struct Task {
  int priority;  // 任务优先级
  int index;     // 原始索引
};

int main() {
  // 读取输入
  string input;
  cin >> input;

  // 解析输入
  vector<Task> tasks;
  stringstream ss(input);
  string priority;
  int idx = 0;

  // 解析优先级
  while (getline(ss, priority, ',')) {
    tasks.push_back({stoi(priority), idx++});
  }

  // 打印顺序
  vector<int> print_order(tasks.size());

  // 打印计数器
  int print_count = 0;

  // 任务队列
  queue<Task> task_queue;
  for (const auto& task : tasks) {
    task_queue.push(task);
  }

  // 模拟打印过程
  while (!task_queue.empty()) {
    // 当前任务
    Task current = task_queue.front();
    task_queue.pop();

    // 检查是否有更高优先级的任务
    bool has_higher_priority = false;
    queue<Task> temp_queue = task_queue;
    while (!temp_queue.empty()) {
      if (temp_queue.front().priority > current.priority) {
        has_higher_priority = true;
        break;
      }
      temp_queue.pop();
    }

    // 如果有更高优先级，放到队尾
    if (has_higher_priority) {
      task_queue.push(current);
    }
    // 否则打印任务
    else {
      print_order[current.index] = print_count++;
    }
  }

  // 输出打印顺序
  for (int i = 0; i < print_order.size(); ++i) {
    cout << print_order[i];
    if (i < print_order.size() - 1) {
      cout << ",";
    }
  }
  cout << endl;

  return 0;
}