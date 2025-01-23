#include <bits/stdc++.h>

using namespace std;

int main() {
  string num; // 输入的正整数  
  int k;      // 需要移除的数字个数  

  // 读取输入  
  cin >> num >> k;

  // 特殊情况处理  
  if (k == 0) {
    cout << num << endl; // 如果不移除，直接输出原数字  
    return 0;
  }
  if (k >= num.length()) {
    cout << "0" << endl; // 如果要移除的数量大于或等于数字长度，输出0  
    return 0;
  }

  stack<char> st;    // 用于存储最小结果的栈
  int to_remove = k; // 记录还需要移除的数字个数  

  // 遍历每个数字  
  for (char digit : num) {
    while (!st.empty() && to_remove > 0 && st.top() > digit) {
      // 如果当前数字小于栈顶元素，且还可以移除数字  
      st.pop();    // 移除栈顶元素
      to_remove--; // 减少移除计数  
    }
    st.push(digit); // 当前数字入栈  
  }

  // 如果还有多余的数字需要移除，继续从栈中移除  
  while (to_remove > 0) {
    st.pop();
    to_remove--;
  }

  // 构建结果字符串
  string result;
  while (!st.empty()) {
    result = st.top() + result; // 逆序入结果字符串  
    st.pop();
  }

  // 移除前导零  
  int start = 0;
  while (start < result.length() && result[start] == '0') {
    start++;
  }

  // 如果结果为空，返回0；否则返回结果字符串  
  cout << (result.substr(start).empty() ? "0" : result.substr(start)) << endl;

  return 0;
}