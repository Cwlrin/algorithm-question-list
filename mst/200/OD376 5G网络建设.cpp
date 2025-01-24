#include <bits/stdc++.h>

using namespace std;

// 并查集数据结构
class UnionFind {
  public:
    vector<int> parent_;
    vector<int> rank_;

    explicit UnionFind(int n) {
      parent_.resize(n + 1);
      rank_.resize(n + 1, 1);
      for (int i = 1; i <= n; ++i) {
        parent_[i] = i;
      }
    }

    int find(int x) {
      if (parent_[x] != x) {
        parent_[x] = find(parent_[x]);
      }
      return parent_[x];
    }

    bool unite(int x, int y) {
      int root_x = find(x);
      int root_y = find(y);
      if (root_x == root_y) {
        return false;
      }
      if (rank_[root_x] < rank_[root_y]) {
        parent_[root_x] = root_y;
      } else {
        parent_[root_y] = root_x;
        if (rank_[root_x] == rank_[root_y]) {
          rank_[root_x]++;
        }
      }
      return true;
    }
};

int main() {
  int n, m;
  cin >> n >> m;

  // 存储所有边的信息
  vector<vector<int> > edges;

  for (int i = 0; i < m; ++i) {
    int x, y, z, p;
    cin >> x >> y >> z >> p;
    if (p == 1) {
      // 如果已经连接，成本为0
      edges.push_back({0, x, y});
    } else {
      // 如果未连接，成本为Z
      edges.push_back({z, x, y});
    }
  }

  // 按成本从小到大排序
  sort(edges.begin(), edges.end());

  UnionFind uf(n);
  int total_cost = 0;
  int connected_edges = 0;

  // Kruskal算法
  for (const auto& edge : edges) {
    int cost = edge[0];
    int u = edge[1];
    int v = edge[2];

    if (uf.unite(u, v)) {
      total_cost += cost;
      connected_edges++;
    }
  }

  // 检查是否所有基站都连通
  if (connected_edges == n - 1) {
    cout << total_cost << endl;
  } else {
    cout << -1 << endl;
  }

  return 0;
}