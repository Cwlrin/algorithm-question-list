#include <bits/stdc++.h>
using namespace std;

// 按照 上、左、右、下 的优先级顺序  
vector<vector<int> > directions = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

bool dfs(vector<vector<int> >& book, vector<int>& data, int index,
         int row, int col, vector<pair<int, int> >& current_path,
         vector<vector<bool> >& visited) {
  // 如果已经匹配了所有字符  
  if (index == data.size()) {
    return true;
  }

  // 按照 上、左、右、下 的优先级搜索  
  for (auto& dir : directions) {
    int new_row = row + dir[0];
    int new_col = col + dir[1];

    // 检查新坐标是否合法  
    if (new_row >= 0 && new_row < book.size() &&
        new_col >= 0 && new_col < book[0].size() &&
        !visited[new_row][new_col] &&
        book[new_row][new_col] == data[index]) {

      // 标记为已访问  
      visited[new_row][new_col] = true;
      current_path.emplace_back(new_row, new_col);

      // 继续搜索下一个字符  
      if (dfs(book, data, index + 1, new_row, new_col, current_path, visited)) {
        return true;
      }

      // 回溯  
      visited[new_row][new_col] = false;
      current_path.pop_back();
    }
  }

  return false;
}

int main() {
  int n; // 明文长度
  cin >> n;

  vector<int> data(n);
  for (int i = 0; i < n; i++) {
    cin >> data[i];
  }

  int m; // 密码本大小
  cin >> m;

  vector<vector<int> > book(m, vector<int>(m));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      cin >> book[i][j];
    }
  }

  vector<vector<pair<int, int> > > all_paths;

  // 遍历所有可能的起始位置
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (book[i][j] == data[0]) {
        vector<vector<bool> > visited(m, vector<bool>(m, false));
        vector<pair<int, int> > current_path;

        // 初始化起始位置  
        visited[i][j] = true;
        current_path.emplace_back(i, j);

        // 尝试从该位置开始搜索  
        if (dfs(book, data, 1, i, j, current_path, visited)) {
          all_paths.push_back(current_path);
        }
      }
    }
  }

  // 输出结果  
  if (all_paths.empty()) {
    cout << "error" << endl;
  } else {
    // 由于已经按照优先级搜索，第一个路径就是最优解  
    for (auto& pos : all_paths[0]) {
      cout << pos.first << " " << pos.second << " ";
    }
    cout << endl;
  }

  return 0;
}