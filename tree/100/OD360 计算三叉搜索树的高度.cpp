#include <bits/stdc++.h>

using namespace std;

class TreeNode {
  public:
    int value_;
    TreeNode* left_;
    TreeNode* middle_;
    TreeNode* right_;

    explicit TreeNode(int val) : value_(val), left_(nullptr), middle_(nullptr),
                                 right_(nullptr) {}
};

class TernarySearchTree {
  TreeNode* root_;

  void insert(TreeNode*& node, int val) {
    if (node == nullptr) {
      node = new TreeNode(val);
    } else if (val < node->value_ - 500) {
      insert(node->left_, val);
    } else if (val > node->value_ + 500) {
      insert(node->right_, val);
    } else {
      insert(node->middle_, val);
    }
  }

  int height(const TreeNode* node) {
    if (node == nullptr) {
      return 0;
    }
    int left_height = height(node->left_);
    int middle_height = height(node->middle_);
    int right_height = height(node->right_);
    return 1 + max(left_height, max(middle_height, right_height));
  }

  public:
    TernarySearchTree() : root_(nullptr) {}

    void Insert(int val) {
      insert(root_, val);
    }

    int Height() {
      return height(root_);
    }
};

int main() {
  int n;
  cin >> n;

  TernarySearchTree tree;
  vector<int> numbers(n);

  for (int i = 0; i < n; ++i) {
    cin >> numbers[i];
    tree.Insert(numbers[i]);
  }

  cout << tree.Height() << endl;

  return 0;
}