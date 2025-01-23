#include <bits/stdc++.h>

using namespace std;

// 深度优先搜索，标记待删除的目录及其子目录
void dfs(int id, unordered_map<int, vector<int> >& children,
         unordered_set<int>& to_delete) {
  to_delete.insert(id); // 标记当前目录为待删除
  for (int child : children[id]) {
    dfs(child, children, to_delete); // 递归处理子目录
  }
}

int main() {
  int m;
  cin >> m;                             // 读取父子关系表的长度
  vector<pair<int, int> > relations(m); // 存储父子关系对
  for (int i = 0; i < m; ++i) {
    cin >> relations[i].first >> relations[i].second; // 读取每个父子关系对
  }
  int delete_id;
  cin >> delete_id; // 读取待删除的目录 ID

  // 构建目录树
  unordered_map<int, vector<int> > children; // 存储每个目录的子目录
  unordered_set<int> all_ids;                // 存储所有目录的 ID

  for (auto& relation : relations) {
    int child_id = relation.first;
    int parent_id = relation.second;
    children[parent_id].push_back(child_id); // 添加子目录
    all_ids.insert(child_id);                // 记录所有目录 ID
    all_ids.insert(parent_id);
  }

  // 标记待删除的目录及其子目录
  unordered_set<int> to_delete;
  dfs(delete_id, children, to_delete);

  // 收集剩余的目录 ID
  vector<int> remaining;
  for (int id : all_ids) {
    // 如果目录未被标记为删除，并且不是根目录 0，则加入剩余列表
    if (to_delete.find(id) == to_delete.end() && id != 0) {
      remaining.push_back(id);
    }
  }

  // 排序并输出结果
  sort(remaining.begin(), remaining.end());
  for (size_t i = 0; i < remaining.size(); ++i) {
    cout << remaining[i];
    if (i != remaining.size() - 1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}