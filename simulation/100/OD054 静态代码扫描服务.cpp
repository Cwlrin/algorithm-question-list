#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  // 读取缓存一个报告的金币数
  int M;
  cin >> M;

  // 文件标识序列
  vector<int> files;
  int file;
  while (cin >> file) {
    files.push_back(file);
    if (cin.get() == '\n')
      break;
  }

  // 文件大小序列
  vector<int> sizes;
  int size;
  while (cin >> size) {
    sizes.push_back(size);
    if (cin.get() == '\n')
      break;
  }

  // 统计每个文件的出现次数
  map<int, int> count;
  // 记录每个文件的大小
  map<int, int> file_sizes;

  // 遍历输入序列
  for (int i = 0; i < files.size(); i++) {
    int file_id = files[i];

    // 统计文件出现次数
    count[file_id]++;

    // 记录文件大小（只记录第一次出现的大小）
    if (file_sizes.find(file_id) == file_sizes.end()) {
      file_sizes[file_id] = sizes[i];
    }
  }

  // 计算最小金币数
  int total_cost = 0;
  for (const auto& [file_id, file_count] : count) {
    // 两种方案：
    // 1. 每次都重新扫描的成本
    // 2. 扫描一次 + 缓存的成本
    int scan_all_cost = file_count * file_sizes[file_id];
    int cache_cost = file_sizes[file_id] + M;

    // 选择成本较低的方案
    total_cost += min(scan_all_cost, cache_cost);
  }

  // 输出最小金币数
  cout << total_cost << endl;

  return 0;
}