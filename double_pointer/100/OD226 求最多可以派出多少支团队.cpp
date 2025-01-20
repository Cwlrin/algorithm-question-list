#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n;
  cin >> n; // 总人数

  vector<int> abilities(n);
  for (int i = 0; i < n; i++) {
    cin >> abilities[i]; // 读取每个人的能力
  }

  int min_cap;
  cin >> min_cap; // 团队要求的最低能力值

  vector<int> remaining; // 用于存储不符合单人要求的人
  int team_count = 0;    // 记录可以组建的团队数量

  // 筛选出能力值至少为 minCap 的人
  for (int i = 0; i < n; i++) {
    if (abilities[i] >= min_cap) {
      team_count++; // 单独可成队
    } else {
      remaining.push_back(abilities[i]); // 将不符合的能力值放入 remaining
    }
  }

  // 对剩余人员进行排序
  sort(remaining.begin(), remaining.end());

  // 双指针方法对剩余人员进行组队
  int k = remaining.size(); // 剩余人员数量
  int l = 0, r = k - 1;     // 初始化指针

  while (l < r) {
    if (remaining[l] + remaining[r] >= min_cap) {
      team_count++; // 能够组成一个团队
      l++;          // 移动低能力值指针
      r--;          // 移动高能力值指针
    } else {
      // 低能力值无法和高能力值组成团队，移动 L
      l++;
    }
  }

  cout << team_count << endl; // 输出可以派出的团队数量
  return 0;
}