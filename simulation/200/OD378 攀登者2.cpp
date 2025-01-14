#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int count_climbable(vector<int>& heights, int strength) {
    unordered_set<int> climbable_peaks;

    // 正向和逆向两次遍历
    explore_peaks(heights, strength, climbable_peaks, true);

    // 逆序后再次遍历
    reverse(heights.begin(), heights.end());
    explore_peaks(heights, strength, climbable_peaks, false);

    return climbable_peaks.size();
  }

 private:
  void explore_peaks(vector<int>& heights, int strength,
                     unordered_set<int>& climbable_peaks, bool is_forward) {
    int n = heights.size();

    // 找到第一个地面起点
    int start_index = 0;
    while (start_index < n && heights[start_index] != 0) {
      start_index++;
    }

    int cumulative_cost = 0;

    for (int i = start_index + 1; i < n; i++) {
      // 重置起点
      if (heights[i] == 0) {
        cumulative_cost = 0;
        continue;
      }

      int height_diff = heights[i] - heights[i - 1];

      // 根据坡度计算体力消耗
      if (height_diff > 0) {
        // 上坡
        cumulative_cost += height_diff * 3;

        // 判断是否为山峰
        if (i + 1 >= n || heights[i] > heights[i + 1]) {
          if (cumulative_cost < strength) {
            // 根据遍历方向映射正确的山峰索引
            int peak_index = is_forward ? i : (n - i - 1);
            climbable_peaks.insert(peak_index);
          }
        }
      } else if (height_diff < 0) {
        // 下坡
        cumulative_cost -= height_diff * 3;
        // 下坡不可能是山峰
      }
    }
  }
};

int main() {
  vector<int> heights;

  string s;
  getline(cin, s);

  stringstream ss(s);
  string token;

  while (getline(ss, token, ',')) {
    heights.emplace_back(stoi(token));
  }

  int strength;
  cin >> strength;

  cout << Solution().count_climbable(heights, strength) << endl;

  return 0;
}