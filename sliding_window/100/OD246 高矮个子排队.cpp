#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
  string input;
  getline(cin, input); // 读取输入

  // 将输入字符串转换为整型数组
  vector<int> heights;
  stringstream ss(input);
  int height;

  while (ss >> height) {
    heights.push_back(height);
  }

  // 检查输入是否合法
  if (heights.empty()) {
    cout << "[ ]" << endl;
    return 0;
  }

  int n = heights.size();

  // 按照高矮排列方法
  for (int i = 0; i < n - 1; i++) {
    // 偶数位置：应该是高位置，满足 arr[i] >= arr[i + 1]
    if (i % 2 == 0) {
      if (heights[i] < heights[i + 1]) {
        // 交换 heights[i] 和 heights[i + 1]
        swap(heights[i], heights[i + 1]);
      }
    }
    // 奇数位置：应该是矮位置，满足 arr[i] <= arr[i + 1]
    else {
      if (heights[i] > heights[i + 1]) {
        // 交换 heights[i] 和 heights[i + 1]
        swap(heights[i], heights[i + 1]);
      }
    }
  }

  // 输出结果
  for (int i = 0; i < heights.size(); i++) {
    cout << heights[i];
    if (i < heights.size() - 1) {
      cout << " "; // 打印空格分隔
    }
  }
  cout << endl;

  return 0;
}