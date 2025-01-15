#include <bits/stdc++.h>
using namespace std;

int main() {
  string input;
  getline(cin, input);

  // 用于存储学生信息的向量
  vector<int> nums;   // 存储学生编号
  vector<char> flags; // 存储Y/N标记

  // 解析输入
  stringstream ss(input);
  string token;
  while (ss >> token) {
    int pos = token.find('/');
    int num = stoi(token.substr(0, pos));
    char flag = token[pos + 1];

    // 检查编号范围
    if (num <= 0 || num > 999) {
      cout << "ERROR" << endl;
      return 0;
    }

    nums.push_back(num);
    flags.push_back(flag);
  }

  // 检查总人数
  if (nums.size() > 999) {
    cout << "ERROR" << endl;
    return 0;
  }

  // 检查第一个学生的标记必须是N
  if (nums.empty() || flags[0] == 'Y') {
    cout << "ERROR" << endl;
    return 0;
  }

  // 使用set存储两个班级的学生
  set<int> class1, class2;
  bool error = false;

  // 第一个学生默认放入第一个班
  class1.insert(nums[0]);

  // 处理剩余学生
  for (int i = 1; i < nums.size() && !error; i++) {
    int curr_num = nums[i];
    int prev_num = nums[i - 1];

    if (flags[i] == 'Y') {
      // 如果前一个人在class1，当前人也应该在class1
      if (class1.count(prev_num)) {
        if (class2.count(curr_num)) {
          error = true;
        }
        class1.insert(curr_num);
      }
      // 如果前一个人在class2，当前人也应该在class2
      else if (class2.count(prev_num)) {
        if (class1.count(curr_num)) {
          error = true;
        }
        class2.insert(curr_num);
      }
    } else {
      // flags[i] == 'N'
      // 如果前一个人在class1，当前人应该在class2
      if (class1.count(prev_num)) {
        if (class1.count(curr_num)) {
          error = true;
        }
        class2.insert(curr_num);
      }
      // 如果前一个人在class2，当前人应该在class1
      else if (class2.count(prev_num)) {
        if (class2.count(curr_num)) {
          error = true;
        }
        class1.insert(curr_num);
      }
    }
  }

  // 检查错误情况
  if (error) {
    cout << "ERROR" << endl;
    return 0;
  }

  // 如果所有学生都在一个班级，那是合法的
  if (class2.empty()) {
    // 输出class1
    bool first = true;
    for (int num : class1) {
      if (!first)
        cout << " ";
      cout << num;
      first = false;
    }
    cout << endl << endl;
    return 0;
  }

  // 确保第一行是编号较小的班级
  if (*class1.begin() > *class2.begin()) {
    swap(class1, class2);
  }

  // 输出第一个班
  bool first = true;
  for (int num : class1) {
    if (!first)
      cout << " ";
    cout << num;
    first = false;
  }
  cout << endl;

  // 输出第二个班
  first = true;
  for (int num : class2) {
    if (!first)
      cout << " ";
    cout << num;
    first = false;
  }
  cout << endl;

  return 0;
}