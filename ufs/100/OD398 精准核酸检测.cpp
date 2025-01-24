#include <bits/stdc++.h>
using namespace std;

// 并查集类  
class UnionFind {
  private:
    vector<int> parent_; // 父节点数组  
    vector<int> size_;   // 每个连通分量的大小  

  public:
    explicit UnionFind(int n) {
      parent_.resize(n);
      size_.resize(n, 1);
      for (int i = 0; i < n; ++i) {
        parent_[i] = i; // 初始化每个节点的父节点为自己  
      }
    }

    // 查找根节点  
    int find(int x) {
      if (parent_[x] != x) {
        parent_[x] = find(parent_[x]); // 路径压缩  
      }
      return parent_[x];
    }

    // 合并两个节点  
    void unite(int x, int y) {
      int root_x = find(x);
      int root_y = find(y);
      if (root_x != root_y) {
        if (size_[root_x] < size_[root_y]) {
          swap(root_x, root_y);
        }
        parent_[root_y] = root_x;      // 将小树合并到大树  
        size_[root_x] += size_[root_y]; // 更新连通分量大小  
      }
    }

    // 获取连通分量大小  
    int GetSize(int x) {
      return size_[find(x)];
    }
};

int main() {
  int n;
  cin >> n;

  // 读取确诊病例  
  string confirmed;
  cin.ignore(); // 忽略换行符  
  getline(cin, confirmed);
  stringstream ss(confirmed);
  vector<int> confirmed_cases;
  string temp;
  while (getline(ss, temp, ',')) {
    confirmed_cases.push_back(stoi(temp));
  }

  // 读取接触矩阵  
  vector<vector<int> > contact_matrix(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    string row;
    getline(cin, row); // 读取一行  
    stringstream row_stream(row);
    string cell;
    for (int j = 0; j < n; ++j) {
      getline(row_stream, cell, ','); // 读取逗号分隔的值  
      contact_matrix[i][j] = stoi(cell);
    }
  }

  // 初始化并查集  
  UnionFind uf(n);

  // 合并接触关系  
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      // 只遍历对角线一边  
      if (contact_matrix[i][j] == 1) {
        uf.unite(i, j); // 合并 i 和 j  
      }
    }
  }

  // 统计需要做核酸检测的人数  
  unordered_set<int> roots; // 记录确诊病例所在连通分量的根  
  for (int case_id : confirmed_cases) {
    roots.insert(uf.find(case_id)); // 找到确诊病例的根  
  }

  // 统计所有与确诊病例在同一连通分量中的人数  
  int total = 0;
  for (int i = 0; i < n; ++i) {
    for (int root : roots) {
      if (uf.find(i) == root) {
        total++;
        break; // 避免重复统计  
      }
    }
  }

  // 减去确诊病例的数量  
  total -= confirmed_cases.size();

  cout << total << endl;
  return 0;
}