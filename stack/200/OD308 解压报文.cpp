#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
  string input;
  cin >> input; // 读取输入的压缩报文  

  stack<int> count_stack;     // 用于存储重复次数  
  stack<string> result_stack; // 用于存储构建的字符串  
  string current_string; // 当前构建的字符串  
  int idx = 0;               // 用于遍历的索引  

  while (idx < input.size()) {
    if (isdigit(input[idx])) {
      // 如果是数字，解析出完整的数字  
      int count = 0;
      while (isdigit(input[idx])) {
        count = count * 10 + (input[idx] - '0'); // 处理多位数  
        idx++;
      }
      count_stack.push(count); // 将数字入栈  
    } else if (input[idx] == '[') {
      // 遇到左括号，将当前字符串入栈  
      result_stack.push(current_string); // 将当前字符串保存到栈中  
      current_string = "";              // 重置当前字符串  
      idx++;                           // 移动到下一个字符  
    } else if (input[idx] == ']') {
      // 遇到右括号，构建字符串  
      string temp = current_string;        // 暂存当前字符串  
      current_string = result_stack.top();  // 取出栈顶的字符串  
      result_stack.pop();                  // 弹出栈顶  
      int repeat_count = count_stack.top(); // 取出重复次数  
      count_stack.pop();                   // 弹出重复次数  

      // 将 temp 字符串重复 repeatCount 次并拼接到 currentString  
      for (int i = 0; i < repeat_count; ++i) {
        current_string += temp;
      }
      idx++; // 移动到下一个字符  
    } else {
      // 处理字母字符，直接加入当前字符串  
      current_string += input[idx];
      idx++;
    }
  }

  // 输出解压后的字符串  
  cout << current_string << endl;

  return 0;
}