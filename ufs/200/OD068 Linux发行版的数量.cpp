#include <bits/stdc++.h>

using namespace std;

void dfs(int node, vector<vector<int> >& is_connected, vector<bool>& visited) {
  visited[node] = true; // 标记当前节点为已访问  
  for (int i = 0; i < is_connected.size(); i++) {
    if (is_connected[node][i] == 1 && !visited[i]) {
      // 如果有连接且未访问  
      dfs(i, is_connected, visited); // 递归访问连接的节点  
    }
  }
}

int main() {
  int n;
  cin >> n;                                            // 输入发行版数量  
  vector<vector<int> > is_connected(n, vector<int>(n)); // 创建邻接矩阵  

  // 输入邻接矩阵  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> is_connected[i][j];
    }
  }

  vector<bool> visited(n, false); // 访问状态数组  
  int max_count = 0;              // 记录最大的连通分量  

  // 遍历所有节点  
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      // 仅当节点未访问时进行 DFS  
      int count = 0; // 当前连通分量的大小  
      dfs(i, is_connected, visited);
      for (int j = 0; j < n; j++) {
        if (visited[j]) {
          count++; // 统计当前连通分量大小  
        }
      }
      max_count = max(max_count, count);           // 更新最大连通分量  
      fill(visited.begin(), visited.end(), false); // 重置访问状态  
    }
  }

  // 输出结果  
  cout << max_count << endl;

  return 0;
}