#include <bits/stdc++.h>

using namespace std;

int main() {
  int M, N;
  string config;

  // 1. 读取输入
  cin >> M >> N >> config;

  // 2. 定义资源分配数组
  vector<vector<int>> chip_resources(N, vector<int>(M, 0));

  // 配置资源消耗映射
  int config_consume[3] = {1, 2, 8};  // A, B, C 对应的资源占用

  // 3. 遍历用户配置序列
  for (char c : config) {
    // 计算当前配置需要的资源数量
    int consume = 0;
    if (c == 'A')
      consume = 1;
    else if (c == 'B')
      consume = 2;
    else if (c == 'C')
      consume = 8;

    // 4. 尝试分配资源
    bool allocated = false;
    for (int i = 0; i < N; ++i) {
      // 统计当前芯片已使用的资源
      int used_resources = 0;
      for (int j = 0; j < M; ++j) {
        used_resources += chip_resources[i][j];
      }

      // 检查是否有足够的剩余资源
      if (M - used_resources >= consume) {
        // 分配资源
        int start = 0;
        while (start < M && chip_resources[i][start] == 1)
          start++;

        for (int j = start; j < start + consume; ++j) {
          chip_resources[i][j] = 1;
        }

        allocated = true;
        break;
      }
    }

    // 如果无法分配，则丢弃当前配置
    if (!allocated) {
      continue;
    }
  }

  // 5. 输出资源分配结果
  for (const auto& chip : chip_resources) {
    for (int resource : chip) {
      cout << resource;
    }
    cout << endl;
  }

  return 0;
}