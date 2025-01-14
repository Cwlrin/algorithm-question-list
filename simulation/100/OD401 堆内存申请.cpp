#include <bits/stdc++.h>
using namespace std;

int main() {
  // 申请内存大小
  int request_size;
  cin >> request_size;

  // 定义堆内存总空间
  vector<int> memory(100, 0);

  // 读取已分配内存信息并标记
  int offset, size;
  while (cin >> offset >> size) {
    // 检查输入的合法性
    if (offset < 0 || size <= 0 || offset + size > 100) {
      cout << -1 << endl;
      return 0;
    }

    // 标记内存并检查是否重复分配
    for (int i = offset; i < offset + size; i++) {
      if (memory[i] == 1) {
        cout << -1 << endl;
        return 0;
      }
      memory[i] = 1;
    }
  }

  // 寻找满足条件的连续空闲内存
  int best_start = -1;      // 最佳起始位置
  int best_diff = INT_MAX;  // 最小差值
  int curr_start = -1;      // 当前连续空闲内存起始位置
  int curr_size = 0;        // 当前连续空闲内存大小

  for (int i = 0; i < 100; i++) {
    if (memory[i] == 0) {
      // 如果是第一个空闲位置
      if (curr_start == -1) {
        curr_start = i;
      }
      curr_size++;
    } else {
      // 处理一段连续空闲内存
      if (curr_size >= request_size) {
        int diff = curr_size - request_size;
        // 更新最佳起始位置
        if (diff < best_diff) {
          best_start = curr_start;
          best_diff = diff;
        }
      }
      // 重置当前空闲内存信息
      curr_start = -1;
      curr_size = 0;
    }
  }

  // 处理最后一段连续空闲内存
  if (curr_size >= request_size) {
    int diff = curr_size - request_size;
    if (diff < best_diff) {
      best_start = curr_start;
    }
  }

  // 输出结果
  if (best_start != -1) {
    cout << best_start << endl;
  } else {
    cout << -1 << endl;
  }

  return 0;
}