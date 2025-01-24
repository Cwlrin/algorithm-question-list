#include <bits/stdc++.h>

using namespace std;

int main() {
  // 动态读取输入
  string line;
  getline(cin, line); // 读取整行输入

  // 解析输入
  vector<vector<int> > books;
  stringstream ss(line);
  char ch;
  int l, w;

  // 跳过开头的 '['
  ss >> ch;

  // 解析每本书的尺寸
  while (ss >> ch && ch == '[') {
    ss >> l >> ch >> w >> ch; // 读取长度和宽度
    books.push_back({l, w});
    ss >> ch; // 跳过 ',' 或 ']'
  }

  // 按长度升序排序，长度相同按宽度降序排序
  sort(books.begin(), books.end(),
       [](const vector<int>& a, const vector<int>& b) {
         if (a[0] == b[0]) {
           return a[1] > b[1];
         }
         return a[0] < b[0];
       });

  // 提取宽度序列
  vector<int> widths;
  for (const auto& book : books) {
    widths.push_back(book[1]);
  }

  // 使用二分查找求解最长递增子序列
  vector<int> dp;
  for (int width : widths) {
    auto it = lower_bound(dp.begin(), dp.end(), width);
    if (it == dp.end()) {
      dp.push_back(width);
    } else {
      *it = width;
    }
  }

  // 输出结果
  cout << dp.size() << endl;

  return 0;
}