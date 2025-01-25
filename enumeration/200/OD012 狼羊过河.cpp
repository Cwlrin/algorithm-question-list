#include <bits/stdc++.h>

using namespace std;

// DFS 函数的实现
void dfs(int sheep, int wolf, int boat, int oppo_sheep, int oppo_wolf,
         int count, int& ans) {
  // 如果岸上的羊和狼全都运送完，更新最小运输次数
  if (sheep == 0 && wolf == 0) {
    ans = min(ans, count);
    return;
  }

  // 检查能否在本次运输中全部运完
  if (sheep + wolf <= boat) {
    ans = min(ans, count + 1);
    return;
  }

  // 尝试运送不同数量的羊和狼
  for (int sheep_on_boat = 0; sheep_on_boat <= min(boat, sheep); ++sheep_on_boat) {
    for (int wolves_on_boat = 0; wolves_on_boat <= min(boat - sheep_on_boat, wolf); ++
         wolves_on_boat) {
      // 如果不运送任何动物，则跳过
      if (sheep_on_boat + wolves_on_boat == 0)
        continue;

      // 确保不会超载
      if (sheep_on_boat + wolves_on_boat > boat)
        break;

      // 检查当前岸的羊和狼的数量
      if (sheep - sheep_on_boat <= wolf - wolves_on_boat && sheep - sheep_on_boat !=
          0)
        continue;

      // 检查对岸羊和狼的数量
      if (oppo_sheep + sheep_on_boat <= oppo_wolf + wolves_on_boat && oppo_sheep +
          sheep_on_boat != 0)
        break;

      // 确保对岸不会超过狼超过羊
      if (oppo_sheep + sheep_on_boat == 0 && oppo_wolf + wolves_on_boat >= boat)
        break;

      // 递归到下一个状态
      dfs(sheep - sheep_on_boat, wolf - wolves_on_boat, boat,
          oppo_sheep + sheep_on_boat, oppo_wolf + wolves_on_boat, count + 1, ans);
    }
  }
}
int main() {
  int m, n, x; // m: 羊的数量, n: 狼的数量, x: 船的容量
  cin >> m >> n >> x;

  int ans = INT_MAX; // 最小运输次数

  // 调用 DFS 函数
  dfs(m, n, x, 0, 0, 0, ans);

  cout << (ans == INT_MAX ? 0 : ans) << endl; // 如果没有找到有效方案，输出 0
  return 0;
}

