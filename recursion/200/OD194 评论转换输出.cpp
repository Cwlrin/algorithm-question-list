#include <bits/stdc++.h>

using namespace std;

// 树节点结构
struct Node {
  string val;
  int replies;
};

void dfs(queue<Node>& q, int depth, vector<vector<string> >& tree) {
  // 队列为空，返回
  if (q.empty())
    return;

  // 获取当前节点
  Node node = q.front();
  q.pop();

  // 扩展树层容器
  while (tree.size() <= depth) {
    tree.push_back({});
  }

  // 将当前节点加入对应层
  tree[depth].push_back(node.val);

  // 处理子节点
  for (int i = 0; i < node.replies; i++) {
    if (!q.empty()) {
      dfs(q, depth + 1, tree);
    }
  }
}

int main() {
  string input;
  getline(cin, input);

  // 用队列存储节点信息
  queue<Node> q;

  // 解析输入到队列
  stringstream ss(input);
  string val, replies_str;
  while (getline(ss, val, ',') && getline(ss, replies_str, ',')) {
    q.push({val, stoi(replies_str)});
  }

  // 树层容器
  vector<vector<string> > tree;

  // 深搜遍历
  while (!q.empty()) {
    dfs(q, 0, tree);
  }

  // 输出最大深度
  cout << tree.size() << endl;

  // 输出每层节点
  for (const auto& level : tree) {
    for (size_t i = 0; i < level.size(); ++i) {
      cout << level[i] << (i == level.size() - 1 ? "\n" : " ");
    }
  }

  return 0;
}