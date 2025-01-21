#include <bits/stdc++.h>

using namespace std;

int main() {
  string scrambled;
  int sequence_length;

  // 读取打乱字符串和序列长度  
  cin >> scrambled >> sequence_length;

  // 统计打乱字符串中的字符频率  
  unordered_map<char, int> scrambled_count;
  for (char c : scrambled) {
    scrambled_count[c]++;
  }

  // 遍历可能的连续正整数序列  
  for (int start = 1; start <= 100000; start++) {
    // 当前窗口对应的数字序列  
    string generated;
    for (int i = 0; i < sequence_length; i++) {
      generated += to_string(start + i);
    }

    // 统计当前生成字符串的字符频率  
    unordered_map<char, int> generatedCount;
    for (char c : generated) {
      generatedCount[c]++;
    }

    // 比较当前生成窗口的字符频率是否和打乱字符串的字符频率一致  
    if (scrambled_count == generatedCount) {
      cout << start << endl; // 输出最小的起始数字  
      return 0;              // 找到后结束程序  
    }
  }

  cout << -1 << endl; // 如果没有找到有效序列，输出 -1  
  return 0;
}