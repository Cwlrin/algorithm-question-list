#include <bits/stdc++.h>

using namespace std;

int main() {
  // 输入酒店数量、筛选数量和目标价位
  int n, k, x;
  cin >> n >> k >> x;

  // 读取酒店价格数组
  vector<int> hotels(n);
  for (int i = 0; i < n; i++) {
    cin >> hotels[i];
  }

  // 自定义比较函数
  // 优先按照与目标价位的绝对差值排序
  // 差值相同时按照价格升序排序
  auto cmp = [x](int a, int b) {
    int diff_a = abs(a - x);
    int diff_b = abs(b - x);

    // 差值不同时，按差值升序
    if (diff_a != diff_b) {
      return diff_a < diff_b;
    }

    // 差值相同时，按价格升序
    return a < b;
  };

  // 对酒店价格数组排序
  sort(hotels.begin(), hotels.end(), cmp);

  // 选择前 k 个元素
  vector<int> selected(hotels.begin(), hotels.begin() + k);

  // 对选定元素升序排序
  sort(selected.begin(), selected.end());

  // 输出结果
  for (int price : selected) {
    cout << price << " ";
  }
  cout << endl;

  return 0;
}