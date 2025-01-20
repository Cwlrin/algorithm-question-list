#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
  // 读取输入  
  string input;
  getline(cin, input);
  int sum;
  cin >> sum;

  // 解析输入序列  
  vector<int> nums;
  stringstream ss(input);
  string token;

  while (getline(ss, token, ',')) {
    nums.push_back(stoi(token)); // 将字符串转换为整数并添加到向量中  
  }

  int n = nums.size();
  int longest_length = -1; // 记录最长子序列的长度  

  // 使用双指针法查找最长连续子序列  
  for (int start = 0; start < n; start++) {
    int current_sum = 0; // 当前窗口的和  
    for (int end = start; end < n; end++) {
      current_sum += nums[end]; // 扩展窗口  

      if (current_sum == sum) {
        // 更新最长长度  
        longest_length = max(longest_length, end - start + 1);
      }
    }
  }

  cout << longest_length << endl; // 输出结果  
  return 0;
}