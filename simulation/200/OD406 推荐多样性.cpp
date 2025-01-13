#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k;
  cin >> n >> k;
  cin.ignore();

  vector<vector<int>> lists;
  string line;

  // 读取列表
  while (getline(cin, line)) {
    vector<int> current_list;
    istringstream ss(line);
    int num;
    while (ss >> num) {
      current_list.push_back(num);
    }
    lists.push_back(current_list);
  }

  int size = k * n;
  vector<int> windows(size);
  int idx = 0;
  int level = 0;

  while (idx < size) {
    bool flag = false;

    // 从每个列表中选择 n 个元素
    for (int i = 0; i < n; i++) {
      if (!lists[level].empty()) {
        windows[idx++] = lists[level].front();
        lists[level].erase(lists[level].begin());

        // 如果当前列表为空，删除并调整
        if (lists[level].empty() && lists.size() > 1) {
          lists.erase(lists.begin() + level);
          level %= lists.size();
          flag = true;
        }
      }
    }

    // 如果没有发生"借"动作，切换到下一行
    if (!flag) {
      level = (level + 1) % lists.size();
    }
  }

  // 按列输出
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < k; i++) {
      cout << windows[i * n + j];
      if (i * n + j < size - 1)
        cout << " ";
    }
  }
  cout << endl;

  return 0;
}