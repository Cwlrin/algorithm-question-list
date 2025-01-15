#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
  // 读取输入
  string input;
  getline(cin, input);

  // 解析输入
  int task_a, task_b, num;
  sscanf(input.c_str(), "%d,%d,%d", &task_a, &task_b, &num);

  // 特殊处理：如果任务数为0，直接输出空数组
  if (num == 0) {
    cout << "[]" << endl;
    return 0;
  }

  // 存储所有可能的总执行时长
  set<int> results;

  // 遍历可能的执行组合
  for (int count_a = 0; count_a <= num; ++count_a) {
    int count_b = num - count_a;
    int total_time = count_a * task_a + count_b * task_b;
    results.insert(total_time);
  }

  // 转换为有序vector并输出
  const vector<int> final_results(results.begin(), results.end());

  // 输出结果
  cout << "[";
  for (int i = 0; i < final_results.size(); ++i) {
    cout << final_results[i];
    if (i < final_results.size() - 1)
      cout << ", ";
  }
  cout << "]" << endl;

  return 0;
}