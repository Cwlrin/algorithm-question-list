#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  // 建立映射关系
  unordered_map<string, vector<string>> tree;
  set<string> nodes;

  // 读取树的节点关系
  for (int i = 0; i < n; i++) {
    string child, parent;
    cin >> child >> parent;

    tree[parent].push_back(child);
    nodes.insert(child);
    nodes.insert(parent);
  }

  // 查询节点
  string query;
  cin >> query;

  // 存储查询结果的集合
  set<string> result;

  // 深度优先搜索查找所有下层节点
  function<void(string)> dfs = [&](string node) {
    // 如果该节点没有子节点，直接返回
    if (tree.count(node) == 0) return;

    // 遍历所有子节点
    for (string child : tree[node]) {
      result.insert(child);
      // 递归查找子节点的下层节点
      dfs(child);
    }
  };

  // 执行深度优先搜索
  dfs(query);

  // 输出结果
  for (string node : result) {
    cout << node << endl;
  }

  return 0;
}