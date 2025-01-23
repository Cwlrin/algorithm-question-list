#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int main() {
  int n;
  cin >> n; // 输入线段数量

  vector<vector<int> > ranges(n, vector<int>(2));
  for (int i = 0; i < n; ++i) {
    char comma;
    cin >> ranges[i][0] >> comma >> ranges[i][1];
  }

  // 按照起点升序排序
  sort(ranges.begin(), ranges.end(),
       [](const vector<int>& a, const vector<int>& b) {
         return a[0] < b[0];
       });

  deque<vector<int> > stack;
  stack.push_back(ranges[0]); // 将第一个区间压入栈

  for (int i = 1; i < ranges.size(); ++i) {
    const vector<int>& current = ranges[i];

    while (true) {
      if (stack.empty()) {
        stack.push_back(current);
        break;
      }

      vector<int> top = stack.back();
      int top_start = top[0];
      int top_end = top[1];

      int current_start = current[0];
      int current_end = current[1];

      if (current_start <= top_start) {
        if (current_end <= top_start) {
          // 当前区间在栈顶区间左侧且无重叠
          break;
        }
        if (current_end < top_end) {
          // 当前区间被栈顶区间完全包含
          break;
        }
        // 当前区间覆盖栈顶区间，弹出栈顶
        stack.pop_back();
      } else if (current_start < top_end) {
        if (current_end <= top_end) {
          // 当前区间与栈顶区间有重叠但被包含
          break;
        }
        // 当前区间与栈顶区间有重叠但不完全包含
        stack.push_back({top_end, current_end});
        break;
      } else {
        // 当前区间与栈顶区间无重叠
        stack.push_back(current);
        break;
      }
    }
  }

  cout << stack.size() << endl; // 输出最少需要的线段数量
  return 0;
}