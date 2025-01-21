#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n, x;
  cin >> n >> x;

  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  long long count = 0;       // 用于记录符合条件的子数组数量  
  int start = 0;             // 窗口的起始指针  
  long long current_sum = 0; // 当前子数组和  

  for (int end = 0; end < n; end++) {
    current_sum += nums[end]; // 增加当前元素到和中  

    // 当且仅当 current_sum >= x 时，统计符合条件的子数组  
    while (current_sum >= x && start <= end) {
      count += (n - end);         // 所有以 start 开头的有效子数组  
      current_sum -= nums[start]; // 移动 start，缩小窗口  
      start++;                    // 移动窗口的起始位置  
    }
  }

  cout << count << endl; // 输出结果  
  return 0;
}