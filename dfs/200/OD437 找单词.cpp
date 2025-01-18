#include <bits/stdc++.h>
using namespace std;

bool dfs(vector<vector<char> >& grid, string& word, int row, int col, int index,
         vector<vector<bool> >& visited,
         vector<pair<int, int> >& current_path) {
  // 边界条件检查和是否匹配检查  
  if (index == word.length()) {
    return true;
  }

  // 检查是否越界、是否访问过、是否匹配  
  if (row < 0 || row >= grid.size() ||
      col < 0 || col >= grid[0].size() ||
      visited[row][col] ||
      grid[row][col] != word[index]) {
    return false;
  }

  // 标记当前单元格已访问  
  visited[row][col] = true;
  current_path.emplace_back(row, col);

  // 四个方向：上、右、下、左  
  int dx[4] = {-1, 0, 1, 0};
  int dy[4] = {0, 1, 0, -1};

  // 尝试四个方向  
  for (int i = 0; i < 4; i++) {
    int new_row = row + dx[i];
    int new_col = col + dy[i];

    if (dfs(grid, word, new_row, new_col, index + 1, visited, current_path)) {
      return true;
    }
  }

  // 回溯：取消标记  
  visited[row][col] = false;
  current_path.pop_back();
  return false;
}

int main() {
  int n;
  cin >> n;

  // 读取二维数组  
  vector<vector<char> > grid(n, vector<char>(n));
  for (int i = 0; i < n; i++) {
    string line;
    cin >> line;

    // 解析每一行  
    istringstream ss(line);
    string cell;
    int j = 0;
    while (getline(ss, cell, ',')) {
      grid[i][j++] = cell[0];
    }
  }

  // 读取目标字符串  
  string word;
  cin >> word;

  // 存储结果路径  
  vector<pair<int, int> > final_path;
  bool found = false;

  // 遍历每个起始点  
  for (int i = 0; i < n && !found; i++) {
    for (int j = 0; j < n && !found; j++) {
      // 起始字符匹配  
      if (grid[i][j] == word[0]) {
        // 访问标记数组  
        vector<vector<bool> > visited(n, vector<bool>(n, false));
        vector<pair<int, int> > current_path;

        // 如果找到路径  
        if (dfs(grid, word, i, j, 0, visited, current_path)) {
          found = true;
          final_path = current_path;
        }
      }
    }
  }

  // 输出路径  
  if (found) {
    for (int i = 0; i < final_path.size(); i++) {
      cout << final_path[i].first << "," << final_path[i].second;
      if (i < final_path.size() - 1) {
        cout << ",";
      }
    }
    cout << endl;
  } else {
    cout << "N" << endl;
  }

  return 0;
}