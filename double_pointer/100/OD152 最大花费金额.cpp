#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input); // 读取价格数组

  // 解析输入的价格数组
  vector<int> prices;
  stringstream ss(input);
  string token;

  while (getline(ss, token, ',')) {
    prices.push_back(stoi(token)); // 将字符串转换为整数
  }

  int budget;
  cin >> budget; // 读取预算

  int n = prices.size();
  sort(prices.begin(), prices.end()); // 对数组进行升序排序

  int max_expense = -1; // 初始化最大花费金额为-1，表示未找到

  // 遍历所有可能的 I 指针
  for (int i = 0; i < n - 2; i++) {
    // I 的上限是 n-2，避免越界
    int l = i + 1; // L 指向 I 后一个元素
    int r = n - 1; // R 指向最后一个元素

    while (l < r) {
      // 当 L < R 时，继续尝试组合
      int sum = prices[i] + prices[l] + prices[r];

      if (sum == budget) {
        // 如果找到了恰好等于预算的组合
        cout << sum << endl;
        return 0;
      }

      if (sum < budget) {
        // 记录当前组合并尝试更大的组合
        max_expense = max(max_expense, sum);
        l++; // 增大当前和
      } else {
        r--; // 减小当前和
      }
    }
  }

  cout << max_expense << endl; // 输出结果
  return 0;
}