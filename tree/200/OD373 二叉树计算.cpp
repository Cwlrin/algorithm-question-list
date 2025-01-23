#include <bits/stdc++.h>

using namespace std;

class TreeNode {
  public:
    int val_;
    TreeNode* left_;
    TreeNode* right_;

    explicit TreeNode(int x) : val_(x), left_(nullptr), right_(nullptr) {}
};

// 根据中序遍历和前序遍历构建二叉树
TreeNode* BuildTree(vector<int>& inorder, vector<int>& preorder) {
  if (preorder.empty())
    return nullptr;

  auto* root = new TreeNode(preorder[0]);
  stack<TreeNode*> stk;
  stk.push(root);
  int inorder_index = 0;

  for (int i = 1; i < preorder.size(); ++i) {
    TreeNode* node = stk.top();
    if (node->val_ != inorder[inorder_index]) {
      node->left_ = new TreeNode(preorder[i]);
      stk.push(node->left_);
    } else {
      while (!stk.empty() && stk.top()->val_ == inorder[inorder_index]) {
        node = stk.top();
        stk.pop();
        ++inorder_index;
      }
      node->right_ = new TreeNode(preorder[i]);
      stk.push(node->right_);
    }
  }

  return root;
}

// 生成求和树
int GenerateSumTree(TreeNode* root) {
  if (!root)
    return 0;
  int left_sum = GenerateSumTree(root->left_);
  int right_sum = GenerateSumTree(root->right_);
  int original_val = root->val_;
  root->val_ = left_sum + right_sum;
  return original_val + left_sum + right_sum;
}

// 中序遍历二叉树
void InorderTraversal(TreeNode* root, vector<int>& result) {
  stack<TreeNode*> stk;
  TreeNode* curr = root;

  while (curr || !stk.empty()) {
    while (curr) {
      stk.push(curr);
      curr = curr->left_;
    }
    curr = stk.top();
    stk.pop();
    result.push_back(curr->val_);
    curr = curr->right_;
  }
}

int main() {
  vector<int> inorder, preorder;
  string line;

  getline(cin, line);
  stringstream ss(line);
  int val;
  while (ss >> val) {
    inorder.push_back(val);
  }

  getline(cin, line);
  ss.clear();
  ss.str(line);
  while (ss >> val) {
    preorder.push_back(val);
  }

  TreeNode* root = BuildTree(inorder, preorder);
  GenerateSumTree(root);

  vector<int> result;
  InorderTraversal(root, result);

  for (size_t i = 0; i < result.size(); ++i) {
    cout << result[i];
    if (i != result.size() - 1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}