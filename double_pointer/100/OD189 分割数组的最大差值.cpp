#include <iostream>
#include <vector>
#include <cstdlib> // for abs  

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<long long> nums(n); // 使用 long long 来避免溢出  
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  long long total_sum = 0;
  for (long long num : nums) {
    total_sum += num; // 计算整个数组的和  
  }

  long long left_sum = 0;
  long long max_diff = 0;

  // 遍历数组，找到最大差值  
  for (int i = 0; i < n - 1; i++) {
    // 注意分割点只到 n-1，保证左右非空  
    left_sum += nums[i];
    long long right_sum = total_sum - left_sum; // 右部分的和  
    max_diff = max(max_diff, abs(left_sum - right_sum));
  }

  cout << max_diff << endl; // 输出结果  
  return 0;
}