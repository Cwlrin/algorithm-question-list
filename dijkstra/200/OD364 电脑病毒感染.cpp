#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  // 读取网络连接信息
  vector<vector<pair<int, int> > > graph(n + 1); // 邻接表存储图
  for (int i = 0; i < m; ++i) {
    int u, v, t;
    cin >> u >> v >> t;
    graph[u].emplace_back(v, t); // u -> v，感染时间为 t
  }

  int k; // 病毒源点
  cin >> k;

  // Dijkstra 算法
  vector<int> dist(n + 1, INT_MAX); // 存储从源点到每个节点的最短距离
  dist[k] = 0;                      // 源点到自身的距离为 0
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<
                   int, int> > > pq; // 小根堆
  pq.emplace(0, k);          // {距离, 节点}

  while (!pq.empty()) {
    pair<int, int> top = pq.top(); // 取出当前距离最小的节点
    pq.pop();
    int d = top.first;
    int u = top.second;
    if (d > dist[u])
      continue; // 如果当前距离不是最短，跳过
    for (const auto& edge : graph[u]) {
      // 遍历 u 的所有邻接节点
      int v = edge.first;
      int t = edge.second;
      if (dist[v] > dist[u] + t) {
        // 如果通过 u 到 v 的距离更短
        dist[v] = dist[u] + t;          // 更新距离
        pq.emplace(dist[v], v); // 将 v 加入优先队列
      }
    }
  }

  // 找到最大距离
  int max_time = 0;
  for (int i = 1; i <= n; ++i) {
    if (dist[i] == INT_MAX) {
      // 如果有电脑无法被感染
      cout << -1 << endl;
      return 0;
    }
    max_time = max(max_time, dist[i]); // 更新最大距离
  }

  cout << max_time << endl; // 输出结果
  return 0;
}