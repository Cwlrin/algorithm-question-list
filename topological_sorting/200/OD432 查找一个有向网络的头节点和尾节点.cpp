#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  if (n == 0) {
    cout << "-1" << endl; // 若没有边，则返回 -1
    return 0;
  }

  vector<int> edges(2 * n);
  for (int i = 0; i < 2 * n; ++i) {
    cin >> edges[i];
  }

  unordered_map<int, vector<int> > graph; // 邻接表
  unordered_map<int, int> in_degree;      // 入度
  unordered_map<int, int> out_degree;     // 出度

  // 填充图的邻接表和入度/出度字典
  for (int i = 0; i < edges.size(); i += 2) {
    int start = edges[i];
    int end = edges[i + 1];
    graph[start].push_back(end);
    out_degree[start]++;
    in_degree[end]++;
  }

  // 找到所有节点
  unordered_set<int> nodes;
  for (const auto& pair : in_degree) {
    nodes.insert(pair.first);
  }
  for (const auto& pair : out_degree) {
    nodes.insert(pair.first);
  }

  // 检查图中是否存在环
  auto has_cycle = [&]() {
    queue<int> q;
    for (const auto& node : nodes) {
      if (in_degree[node] == 0) {
        q.push(node);
      }
    }

    int visited_count = 0;

    while (!q.empty()) {
      int current = q.front();
      q.pop();
      visited_count++;
      for (const auto& neighbor : graph[current]) {
        in_degree[neighbor]--;
        if (in_degree[neighbor] == 0) {
          q.push(neighbor);
        }
      }
    }

    // 如果访问的节点数量小于节点总数，则存在环
    return visited_count < nodes.size();
  };

  if (has_cycle()) {
    cout << "-1" << endl; // 有环的情况下返回 -1
    return 0;
  }

  // 找首节点和尾节点
  vector<int> head_nodes; // 存首节点
  vector<int> tail_nodes; // 存尾节点

  for (const auto& node : nodes) {
    if (in_degree[node] == 0) {
      head_nodes.push_back(node);
    }
    if (out_degree[node] == 0) {
      tail_nodes.push_back(node);
    }
  }

  // 只需要一个头节点，尾节点按从小到大排序
  sort(tail_nodes.begin(), tail_nodes.end()); // 按从小到大排序

  // 输出结果
  cout << head_nodes[0]; // 输出首节点
  for (int tail : tail_nodes) {
    cout << " " << tail; // 输出尾节点
  }
  cout << endl;

  return 0;
}