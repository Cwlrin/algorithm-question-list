#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
  string s;
  cin >> s; // 读取输入  

  unordered_map<char, int> count;
  // 统计每个字符的数量  
  for (char c : s) {
    count[c]++;
  }

  // 计算每个字母应有的数量  
  int n = s.length() / 4;          // 每种字符的目标数量  
  unordered_map<char, int> excess; // 记录多余的字符  

  // 计算每种字符有多少个超出目标数量  
  for (char c : "WASD") {
    if (count[c] > n) {
      excess[c] = count[c] - n; // 记录超过目标数量的部分  
    } else {
      excess[c] = 0; // 如果没有超出，设为0  
    }
  }

  // 双指针寻找最小覆盖子串  
  int min_length = numeric_limits<int>::max();
  int left = 0;
  int right = 0;
  unordered_map<char, int> current_count; // 当前窗口内的字符  

  while (right < s.length()) {
    // 扩大右边界，加入当前字符  
    current_count[s[right]]++;

    // 检查当前窗口是否有效  
    while ([&]() {
      for (char c : "WASD") {
        if (current_count[c] < excess[c]) {
          return false; // 如果不足以弥补，就无效  
        }
      }
      return true; // 当前窗口有效  
    }()) {
      // 有效后计算长度并更新最小长度  
      min_length = min(min_length, right - left + 1);
      // 收缩左边界，移除当前左边的字符  
      current_count[s[left]]--;
      left++;
    }

    right++;
  }

  // 如果没有找到有效的覆盖子串，返回 -1，表示无法平衡  
  cout << (min_length == numeric_limits<int>::max() ? -1 : min_length) << endl;
  return 0;
}