#include <bits/stdc++.h>

using namespace std;

// 判断数字是否是7的倍数或包含7
bool IsSeven(int num) {
  if (num % 7 == 0)
    return true;
  while (num > 0) {
    if (num % 10 == 7)
      return true;
    num /= 10;
  }
  return false;
}

int main() {
  vector<int> counts;
  int num;
  while (cin >> num) {
    counts.push_back(num);
  }

  int n = counts.size();    // 人数
  vector<int> result(n, 0); // 初始化结果数组

  int total_passes = 0;
  for (int count : counts) {
    total_passes += count;
  }

  int current_number = 1;
  int current_player = 0;
  int passes_counted = 0;

  while (passes_counted < total_passes) {
    if (IsSeven(current_number)) {
      result[current_player]++;
      passes_counted++;
    }
    current_number++;
    current_player = (current_player + 1) % n;
  }

  for (int i = 0; i < n; i++) {
    cout << result[i] << " ";
  }
  cout << endl;

  return 0;
}