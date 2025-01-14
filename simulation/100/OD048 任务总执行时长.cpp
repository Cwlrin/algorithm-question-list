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
  int taskA, taskB, num;
  sscanf(input.c_str(), "%d,%d,%d", &taskA, &taskB, &num);

  // 特殊处理：如果任务数为0，直接输出空数组
  if (num == 0) {
    cout << "[]" << endl;
    return 0;
  }

  // 存储所有可能的总执行时长
  set<int> results;

  // 遍历可能的执行组合
  for (int countA = 0; countA <= num; ++countA) {
    int countB = num - countA;
    int totalTime = countA * taskA + countB * taskB;
    results.insert(totalTime);
  }

  // 转换为有序vector并输出
  vector<int> finalResults(results.begin(), results.end());

  // 输出结果
  cout << "[";
  for (int i = 0; i < finalResults.size(); ++i) {
    cout << finalResults[i];
    if (i < finalResults.size() - 1)
      cout << ", ";
  }
  cout << "]" << endl;

  return 0;
}