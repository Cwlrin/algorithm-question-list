#include <bits/stdc++.h>

using namespace std;

class TreeNode {
  public:
    int val_;
    TreeNode* left_;
    TreeNode* right_;

    explicit TreeNode(int x) : val_(x), left_(nullptr), right_(nullptr) {}
};

// 构建二叉树
TreeNode* buildTree(const vector<int>& nodes, int index) {
  if (index >= nodes.size() || nodes[index] == -1) {
    return nullptr;
  }
  auto* root = new TreeNode(nodes[index]);
  root->left_ = buildTree(nodes, 2 * index + 1);
  root->right_ = buildTree(nodes, 2 * index + 2);
  return root;
}

// 深度优先搜索，计算最大路径和
int dfs(TreeNode* root, int currentSum) {
  if (!root)
    return 0;
  currentSum += root->val_;
  if (!root->left_ && !root->right_) {
    return currentSum;
  }
  int left_sum = dfs(root->left_, currentSum);
  int right_sum = dfs(root->right_, currentSum);
  return max(left_sum, right_sum);
}

int main() {
  string input;
  getline(cin, input); // 读取一行输入
  stringstream ss(input);
  vector<int> nodes;
  int val;
  while (ss >> val) {
    nodes.push_back(val);
  }

  TreeNode* root = buildTree(nodes, 0);
  int max_time = dfs(root, 0);
  cout << max_time << endl;

  return 0;
}