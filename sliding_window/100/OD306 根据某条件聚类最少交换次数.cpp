#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // 读取数组  
  vector<int> nums;
  int num;
  while (cin >> num) {
    nums.push_back(num);
    if (cin.get() == '\n')
      break;
  }

  // 读取 K 值  
  int k;
  cin >> k;

  // 统计小于 K 的数字个数  
  int small_count = 0;
  for (int x : nums) {
    if (x < k) {
      small_count++;
    }
  }

  // 如果没有小于 K 的数字，返回 0  
  if (small_count == 0) {
    cout << 0 << endl;
    return 0;
  }

  // 使用滑动窗口计算最少交换次数  
  int window_small_count = 0;
  for (int i = 0; i < small_count; i++) {
    if (nums[i] < k) {
      window_small_count++;
    }
  }

  int max_window_small_count = window_small_count;

  // 滑动窗口  
  for (int i = small_count; i < nums.size(); i++) {
    if (nums[i - small_count] < k) {
      window_small_count--;
    }
    if (nums[i] < k) {
      window_small_count++;
    }
    max_window_small_count = max(max_window_small_count, window_small_count);
  }

  // 最少交换次数 = 窗口大小 - 窗口内小于K的数字个数  
  int min_swaps = small_count - max_window_small_count;

  cout << min_swaps << endl;

  return 0;
}