#include <bits/stdc++.h>
using namespace std;

// 后序遍历函数
void PostOrderTraversal(const vector<int>& tree, int index,
                        vector<int>& result) {
  if (index >= tree.size()) {
    return;
  }

  // 左子树
  PostOrderTraversal(tree, 2 * index + 1, result);

  // 右子树
  PostOrderTraversal(tree, 2 * index + 2, result);

  // 如果当前节点是非叶子节点，加入结果
  if (2 * index + 1 < tree.size() || 2 * index + 2 < tree.size() || index ==
      0) {
    result.push_back(tree[index]);
  }
}

int main() {
  // 读取输入
  string input;
  getline(cin, input);
  stringstream ss(input);

  vector<int> tree;
  int value;
  while (ss >> value) {
    tree.push_back(value);
  }

  // 后序遍历非叶子节点
  vector<int> result;
  PostOrderTraversal(tree, 0, result);

  // 输出结果
  for (int i = 0; i < result.size(); ++i) {
    if (i > 0) {
      cout << " ";
    }
    cout << result[i];
  }
  cout << endl;

  return 0;
}