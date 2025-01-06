#include <bits/stdc++.h>

using namespace std;

// 将容量字符串解析为以 M 为单位的总容量
long long parase_capacity(const string& s) {
  long long total = 0;
  int num = 0;
  for (char i : s) {
    if (isdigit(i)) {
      num = num * 10 + (i - '0'); // 累计数字
    } else {
      // 根据单位累加总容量
      if (i == 'M') {
        total += num;
      } else if (i == 'G') {
        total += num * 1024LL;
      } else if (i == 'T') {
        total += num * 1024LL * 1024LL;
      }
      num = 0; // 重置数字部分
    }
  }
  return total;
}

int main() {
  int n;
  cin >> n;
  cin.ignore(); // 忽略换行符
  vector<pair<string, long long> > disks;

  // 读取输入并解析容量
  for (int i = 0; i < n; ++i) {
    string disk;
    getline(cin, disk);
    long long capacity = parase_capacity(disk);
    disks.emplace_back(disk, capacity);
  }

  // 按照容量排序，使用稳定排序保持输入排序
  stable_sort(disks.begin(), disks.end(), [](const auto& a, const auto& b) {
    return a.second < b.second; // 按容量升序
  });

  // 输出排序后的结果
  for (const auto& disk : disks) {
    cout << disk.first << endl;
  }

  return 0;
}