#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// 检查当前桶容量是否可以装下所有球
bool CanAllocateBalls(int idx, const vector<int>& balls, vector<int>& buckets, int limit, int n) {
  if (idx == balls.size()) return true; // 所有球都成功分配

  const int current_ball = balls[idx];

  // 尝试将当前球分配给每个桶
  for (int i = 0; i < n; i++) {
    // 如果当前桶容量能够容纳该球
    if (buckets[i] + current_ball <= limit) {
      buckets[i] += current_ball; // 将球装入桶中

      // 递归尝试分配下一个球
      if (CanAllocateBalls(idx + 1, balls, buckets, limit, n)) {
        return true; // 成功分配
      }

      // 回溯：撤销操作
      buckets[i] -= current_ball;
    }
    // 剪枝：如果当前桶没有装入任何球，后面的桶也不应该再装此球
    if (buckets[i] == 0) break;
  }

  return false; // 无法分配
}

int main() {
  vector<int> balls;
  int num;

  // 读取球的工作量
  while (cin >> num) {
    balls.push_back(num);
    if (cin.peek() == '\n') break; // 当输入结束时（换行）跳出
  }

  // 读取开发人员数量
  int n;
  cin >> n;

  // 对工作量进行降序排序
  sort(balls.begin(), balls.end(), greater<int>());

  // 二分查找的上下界
  int low = balls[0]; // 至少需要最大工作量的容量
  int high = accumulate(balls.begin(), balls.end(), 0); // 总工作量

  int best_capacity = high; // 最优桶容量

  // 开始二分查找
  while (low <= high) {
    int mid = low + (high - low) / 2; // 中间桶容量
    vector<int> buckets(n, 0); // 初始化桶为0

    // 检查能否在此容量下完成分配
    if (CanAllocateBalls(0, balls, buckets, mid, n)) {
      best_capacity = mid; // 更新最优解
      high = mid - 1; // 尝试更小的容量
    } else {
      low = mid + 1; // 增加桶容量
    }
  }

  // 输出结果
  cout << best_capacity << endl;

  return 0;
}