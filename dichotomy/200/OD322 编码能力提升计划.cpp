#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// 检查是否可以在 m 天内完成所有题目  
bool Finish(const vector<int>& times, int m, int t) {
  int sum_cost = 0;     // 当前总耗时
  int max_cost = 0;     // 当前耗时最多的题目
  int day = 1;          // 当前天数
  bool can_help = true; // 是否可以申请帮助  

  for (int time : times) {
    sum_cost += time;
    max_cost = max(max_cost, time);

    if (sum_cost > t) {
      if (can_help) {
        // 申请帮助，减去当天最耗时的题目  
        sum_cost -= max_cost;
        can_help = false; // 将申请帮助机会用完  
      } else {
        // 不能申请帮助，进入新的一天  
        day++;
        sum_cost = time; // 当前题目作为下一天的开始  
        max_cost = time; // 清空并重置最大耗时  
        can_help = true; // 重置帮助机会
      }
    }

    // 如果今天的时间超限，并且当前总耗时超过最大限制，进入新的一天  
    if (sum_cost > t && !can_help) {
      day++;
      sum_cost = time; // 当前题目作为下一天的开始  
      max_cost = time; // 清空并重置最大耗时  
      can_help = true; // 重置帮助机会
    }
  }

  return day <= m; // 检查是否在规定天数内完成  
}

int main() {
  vector<int> times;
  string input;
  getline(cin, input);

  // 解析输入  
  stringstream ss(input);
  string num;
  int sum_time = 0, max_time = 0;

  while (getline(ss, num, ',')) {
    int time = stoi(num);
    times.push_back(time);
    sum_time += time;
    max_time = max(max_time, time);
  }

  int m;
  cin >> m;

  // T 的初始取值范围  
  int low = 0;
  int high = sum_time - max_time;

  // 二分查找寻找最小的 T  
  while (low < high) {
    int mid = (low + high) / 2;

    if (Finish(times, m, mid)) {
      high = mid; // 尝试更小的 T  
    } else {
      low = mid + 1; // 尝试更大的 T  
    }
  }

  cout << low << endl; // 输出结果  
  return 0;
}