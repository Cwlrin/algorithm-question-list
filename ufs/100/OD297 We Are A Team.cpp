#include <bits/stdc++.h>

using namespace std;

class UnionFind {
  private:
  vector<int> parent_;

  public:
  UnionFind(int n) {
    parent_.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
      parent_[i] = i;  // 初始化每个节点的父节点为自己
    }
  }

  int find(int x) {
    if (parent_[x] != x) {
      parent_[x] = find(parent_[x]);  // 路径压缩
    }
    return parent_[x];
  }

  void unite(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);
    if (root_x != root_y) {
      parent_[root_x] = root_y;  // 合并两个集合
    }
  }

  bool is_connected(int x, int y) {
    return find(x) == find(y);  // 判断是否在同一个集合
  }
};

int main() {
  int n, m;
  cin >> n >> m;

  // 检查 n 和 m 的范围
  if (n < 1 || n >= 100000 || m < 1 || m >= 100000) {
    cout << "NULL" << endl;
    return 0;
  }

  UnionFind uf(n);  // 初始化并查集

  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;

    // 检查 a 和 b 的范围
    if (a < 1 || a > n || b < 1 || b > n) {
      cout << "da pian zi" << endl;
      continue;
    }

    if (c == 0) {
      uf.unite(a, b);  // 合并 a 和 b
    } else if (c == 1) {
      if (uf.is_connected(a, b)) {
        cout << "we are a team" << endl;
      } else {
        cout << "we are not a team" << endl;
      }
    } else {
      cout << "da pian zi" << endl;
    }
  }

  return 0;
}