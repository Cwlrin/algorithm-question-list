#include <bits/stdc++.h>

using namespace std;

void dfs(const vector<int>& tree, int index, vector<int>& path, int& min_leaf,
         vector<int>& min_path) {
  if (index >= tree.size() || tree[index] == -1) {
    return;
  }

  path.push_back(tree[index]);

  int left = 2 * index;
  int right = 2 * index + 1;

  // 检查当前节点是否为叶子
  bool is_leaf = true;
  if (left < tree.size() && tree[left] != -1) {
    is_leaf = false;
    dfs(tree, left, path, min_leaf, min_path);
  }
  if (right < tree.size() && tree[right] != -1) {
    is_leaf = false;
    dfs(tree, right, path, min_leaf, min_path);
  }

  if (is_leaf && tree[index] < min_leaf) {
    min_leaf = tree[index];
    min_path = path;
  }

  path.pop_back(); // 回溯
}

vector<int> FindMinLeafPath(const vector<int>& tree) {
  int min_leaf = INT_MAX;
  vector<int> min_path;
  vector<int> path;
  dfs(tree, 1, path, min_leaf, min_path); // 从根开始（索引 1）
  return min_path;
}

int main() {
  string line;
  getline(cin, line);
  stringstream ss(line);
  vector<int> tree;
  tree.push_back(-1); // 索引 0 未使用

  int val;
  while (ss >> val) {
    tree.push_back(val);
  }

  vector<int> min_path = FindMinLeafPath(tree);

  for (size_t i = 0; i < min_path.size(); ++i) {
    cout << min_path[i];
    if (i != min_path.size() - 1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}