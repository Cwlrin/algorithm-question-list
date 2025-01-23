#include <bits/stdc++.h>

using namespace std;

class TreeNode {
  public:
    int weight_;
    TreeNode* left_;
    TreeNode* right_;

    explicit TreeNode(int w) : weight_(w), left_(nullptr), right_(nullptr) {}

    // 计算树的高度
    int height() const {
      if (!left_ && !right_)
        return 1;
      const int left_height = left_ ? left_->height() : 0;
      const int right_height = right_ ? right_->height() : 0;
      return 1 + max(left_height, right_height);
    }
};

class Compare {
  public:
    bool operator()(TreeNode* a, TreeNode* b) const {
      if (a->weight_ == b->weight_) {
        // 如果权值相同，则比较高度
        return a->height() > b->height(); // 高度较小的优先
      }
      return a->weight_ > b->weight_; // 小的权值优先
    }
};

// 中序遍历并输出
void inorder(TreeNode* node, vector<int>& result) {
  if (!node)
    return;
  inorder(node->left_, result);
  result.push_back(node->weight_);
  inorder(node->right_, result);
}

int main() {
  int n;
  cin >> n;

  priority_queue<TreeNode*, vector<TreeNode*>, Compare> min_heap;
  vector<int> weights(n);

  // 读取权值
  for (int i = 0; i < n; ++i) {
    cin >> weights[i];
    min_heap.push(new TreeNode(weights[i])); // 将权值放入最小堆
  }

  // 构建哈夫曼树
  while (min_heap.size() > 1) {
    TreeNode* left = min_heap.top();
    min_heap.pop();
    TreeNode* right = min_heap.top();
    min_heap.pop();

    // 创建新节点
    auto* parent = new TreeNode(left->weight_ + right->weight_);
    if (left->weight_ < right->weight_ || (
          left->weight_ == right->weight_ && left->height() <= right->
          height())) {
      parent->left_ = left;
      parent->right_ = right;
    } else {
      parent->left_ = right;
      parent->right_ = left;
    }

    // 将新节点放回最小堆
    min_heap.push(parent);
  }

  // 只剩下一个节点，就是根节点
  TreeNode* root = min_heap.top();

  // 中序遍历
  vector<int> result;
  inorder(root, result);

  // 输出结果
  for (size_t i = 0; i < result.size(); ++i) {
    cout << result[i];
    if (i != result.size() - 1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}