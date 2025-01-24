#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
  // 输入任务依赖关系
  string dependencies;
  getline(cin, dependencies);

  // 构建图和入度字典
  unordered_map<string, vector<string> > graph; // 邻接表
  unordered_map<string, int> in_degree;         // 入度字典

  size_t pos = 0;
  string input = dependencies;
  while ((pos = input.find(" ")) != string::npos) {
    string dep = input.substr(0, pos);
    input.erase(0, pos + 1);

    size_t arrow_pos = dep.find("->");
    if (arrow_pos == string::npos)
      continue;

    string u = dep.substr(0, arrow_pos);
    string v = dep.substr(arrow_pos + 2);

    graph[v].push_back(u); // u 依赖 v
    in_degree[u]++;
    if (in_degree.find(v) == in_degree.end()) {
      in_degree[v] = 0;
    }
  }

  // 处理最后一个依赖关系
  size_t arrow_pos = input.find("->");
  if (arrow_pos != string::npos) {
    string u = input.substr(0, arrow_pos);
    string v = input.substr(arrow_pos + 2);

    graph[v].push_back(u); // u 依赖 v
    in_degree[u]++;
    if (in_degree.find(v) == in_degree.end()) {
      in_degree[v] = 0;
    }
  }

  // 优先队列（最小堆），按字母顺序排序
  priority_queue<string, vector<string>, greater<string> > min_heap;

  // 将所有入度为0的任务加入优先队列
  for (const auto& pair : in_degree) {
    if (pair.second == 0) {
      min_heap.push(pair.first);
    }
  }

  vector<string> result;
  while (!min_heap.empty()) {
    // 当前梯队的所有任务
    vector<string> current_tier;
    while (!min_heap.empty()) {
      current_tier.push_back(min_heap.top());
      min_heap.pop();
    }

    // 按字母顺序执行当前梯队的任务
    for (const string& task : current_tier) {
      result.push_back(task);

      // 减少依赖任务的入度
      for (const string& neighbor : graph[task]) {
        in_degree[neighbor]--;
        if (in_degree[neighbor] == 0) {
          min_heap.push(neighbor);
        }
      }
    }
  }

  // 输出结果
  for (size_t i = 0; i < result.size(); ++i) {
    cout << result[i];
    if (i != result.size() - 1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}