#include <bits/stdc++.h>
using namespace std;

int main() {
  int min_average_lost;
  cin >> min_average_lost;

  vector<int> failure_rates;
  int rate;
  while (cin >> rate) {
    failure_rates.push_back(rate);
  }

  int n = failure_rates.size();
  vector<int> prefix_sum(n + 1, 0);
  vector<string> result;

  // 计算前缀和  
  for (int i = 0; i < n; ++i) {
    prefix_sum[i + 1] = prefix_sum[i] + failure_rates[i];
  }

  // 从最长子数组开始遍历  
  for (int len = n; len >= 1; --len) {
    bool found = false;
    for (int i = 0; i <= n - len; ++i) {
      int sum = prefix_sum[i + len] - prefix_sum[i];
      double average = static_cast<double>(sum) / len;
      if (average <= min_average_lost) {
        result.push_back(to_string(i) + "-" + to_string(i + len - 1));
        found = true;
      }
    }
    // 如果找到满足条件的子数组，直接输出  
    if (found) {
      for (const string& period : result) {
        cout << period << " ";
      }
      cout << endl;
      return 0;
    }
  }

  // 如果未找到满足条件的子数组，输出 NULL  
  cout << "NULL" << endl;
  return 0;
}