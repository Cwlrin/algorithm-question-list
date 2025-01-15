#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<vector<int> > resources(n, vector<int>(3));
  for (int i = 0; i < n; i++) {
    cin >> resources[i][0] >> resources[i][1] >> resources[i][2];
  }

  int last_pos = -1;
  int total_cost = 0;

  for (int i = 0; i < n; i++) {
    // 寻找可选策略的最小值
    int min_cost = INT_MAX;
    int min_pos = -1;

    for (int j = 0; j < 3; j++) {
      // 如果当前策略位置与上一个用户不同
      if (j != last_pos) {
        // 如果当前策略消耗更小，或者消耗相等但位置更靠后
        if (resources[i][j] < min_cost ||
            (resources[i][j] == min_cost && j > min_pos)) {
          min_cost = resources[i][j];
          min_pos = j;
        }
      }
    }

    // 添加消耗并更新上一个选择的位置
    total_cost += min_cost;
    last_pos = min_pos;
  }

  cout << total_cost << endl;

  return 0;
}