#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 存储演出信息的结构体
struct Performance {
  int start_time; // 演出开始时间
  int duration;   // 演出持续时间
  int end_time;   // 演出结束时间
};

int main() {
  int n;
  cin >> n; // 输入演出场数

  vector<Performance> performances(n);

  for (int i = 0; i < n; ++i) {
    int start, length;
    cin >> start >> length;
    performances[i] = {start, length, start + length};
  }

  // 按照结束时间进行排序，使用 Lambda 函数
  sort(performances.begin(), performances.end(),
       [](const Performance& a, const Performance& b) {
         return a.end_time < b.end_time;
       });

  int count = 0;           // 能观看的演出数量
  int last_end_time = -15; // 初始值设置为 -15，确保第一个演出可以观看

  for (const auto& performance : performances) {
    if (performance.start_time >= last_end_time + 15) {
      count++;                              // 可以观看该演出
      last_end_time = performance.end_time; // 更新上次演出结束时间
    }
  }

  cout << count << endl; // 输出最多能观看的演出场数
  return 0;
}