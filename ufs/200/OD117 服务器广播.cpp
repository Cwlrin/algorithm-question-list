#include <bits/stdc++.h>

using namespace std;

// 并查集类
class UnionFindSet {
  private:
    vector<int> parent_; // 父节点数组
    vector<int> rank_;   // 秩（用于优化合并操作）

  public:
    // 构造函数，初始化并查集
    explicit UnionFindSet(int n) {
      parent_.resize(n);
      rank_.resize(n, 0);
      for (int i = 0; i < n; i++) {
        parent_[i] = i; // 初始时每个节点的父节点是自己
      }
    }

    // 查找根节点，使用路径压缩优化
    int find(int x) {
      if (parent_[x] != x) {
        parent_[x] = find(parent_[x]);
      }
      return parent_[x];
    }

    // 合并两个集合
    void merge(int x, int y) {
      int root_x = find(x);
      int root_y = find(y);

      if (root_x == root_y)
        return; // 已经在同一个集合

      // 按秩合并，降低树的高度
      if (rank_[root_x] < rank_[root_y]) {
        parent_[root_x] = root_y;
      } else if (rank_[root_x] > rank_[root_y]) {
        parent_[root_y] = root_x;
      } else {
        parent_[root_y] = root_x;
        rank_[root_x]++;
      }
    }

    // 判断两个节点是否属于同一个集合
    bool is_same_set(int x, int y) {
      return find(x) == find(y);
    }

    // 获取集合数量
    int get_set_count(int n) {
      unordered_set<int> roots;
      for (int i = 0; i < n; i++) {
        roots.insert(find(i));
      }
      return roots.size();
    }
};

int main() {
  vector<vector<int> > matrix;

  // 读取输入
  while (cin) {
    string line;
    getline(cin, line);

    // 如果输入为空，则退出
    if (line.empty())
      break;

    // 解析输入行
    vector<int> row;
    stringstream ss(line);
    int num;
    while (ss >> num) {
      row.push_back(num);
    }

    // 检查是否为方阵
    if (!matrix.empty() && row.size() != matrix[0].size()) {
      break;
    }

    matrix.push_back(row);
  }

  int n = matrix.size(); // 服务器数量

  // 创建并查集
  UnionFindSet ufs(n);

  // 合并直接连接的服务器
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] == 1) {
        ufs.merge(i, j);
      }
    }
  }

  // 计算需要广播的服务器数量（集合的数量）
  int broadcast_count = ufs.get_set_count(n);
  cout << broadcast_count << endl;

  return 0;
}