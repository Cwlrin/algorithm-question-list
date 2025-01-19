#include <bits/stdc++.h>
using namespace std;

// 马可以跳跃的8个方向
const int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
const int dy[] = {2, -2, 1, -1, 2, -2, 1, -1};

int main() {
  int m, n;
  cin >> m >> n;

  vector<vector<char> > board(m, vector<char>(n));
  vector<pair<int, int> > horses; // 记录马的位置
  vector<int> levels;             // 记录马的等级

  // 读取棋盘数据并记录每匹马的位置和等级
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];
      if (isdigit(board[i][j])) {
        // 检查是否是马
        horses.emplace_back(i, j);
        levels.push_back(board[i][j] - '0');
      }
    }
  }

  // 如果只有一匹马，不需要跳动，直接返回0
  if (horses.size() == 1) {
    cout << 0 << endl;
    return 0;
  }

  // 初始化 stepMap，记录每个位置的马所花费的最小步数之和
  vector<vector<int> > step_map(m, vector<int>(n, 0));

  // reach集合用于记录所有马都能跳到的公共位置
  unordered_set<int> reach;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      reach.insert(i * n + j); // 初始化为棋盘上的所有位置
    }
  }

  // 操作每匹马
  for (int k = 0; k < horses.size(); k++) {
    int x = horses[k].first;
    int y = horses[k].second;
    int level = levels[k];

    // BFS 初始化
    queue<pair<int, int> > q;
    q.emplace(x, y);

    // 记录该马能到达的位置
    unordered_set<int> vis;
    vis.insert(x * n + y);

    // 记录该马能跳到的位置
    unordered_set<int> current_reach;
    current_reach.insert(x * n + y);

    // BFS过程
    for (int step = 1; step <= level; step++) {
      int q_size = q.size(); // 当前层的节点数量

      for (int j = 0; j < q_size; j++) {
        auto [curr_x, curr_y] = q.front();
        q.pop();

        // 从当前位置出发，进行跳跃
        for (int direction = 0; direction < 8; direction++) {
          int new_x = curr_x + dx[direction];
          int new_y = curr_y + dy[direction];

          // 检查步数是否越界
          if (new_x >= 0 && new_x < m && new_y >= 0 && new_y < n) {
            int pos_index = new_x * n + new_y;

            // 如果该位置未被访问，将其加入队列并更新
            if (vis.find(pos_index) == vis.end()) {
              q.emplace(new_x, new_y);
              vis.insert(pos_index);
              step_map[new_x][new_y] += step; //步数累加
              current_reach.insert(pos_index);
            }
          }
        }
      }
    }

    // 更新公共 reachable 位置集
    unordered_set<int> updated_reach;
    for (int pos : reach) {
      if (current_reach.find(pos) != current_reach.end()) {
        updated_reach.insert(pos);
      }
    }
    reach = updated_reach; // 更新 reachable 集合为交集
  }

  // 如果没有公共位置，返回-1
  if (reach.empty()) {
    cout << -1 << endl;
    return 0;
  }

  // 计算所有公共位置中的最小步数和
  int min_total_steps = INT_MAX;
  for (int pos : reach) {
    int rx = pos / n; // 行索引
    int ry = pos % n; // 列索引
    min_total_steps = min(min_total_steps, step_map[rx][ry]);
  }

  cout << min_total_steps << endl; // 输出结果
  return 0;
}