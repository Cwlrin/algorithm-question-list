#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; // 苹果数量
  cin >> n; // 输入苹果数量

  vector<int> weights(n); // 存储每个苹果的重量
  int total_xor = 0; // 初始化异或结果
  int total_weight = 0; // 初始化总重量

  // 输入每个苹果的重量
  for (int i = 0; i < n; i++) {
    cin >> weights[i];
    total_xor ^= weights[i]; // 计算异或
    total_weight += weights[i]; // 计算总重量
  }

  // 根据 A 的规则判断结果
  if (total_xor != 0) {
    cout << -1 << endl; // 无法满足 A 的要求
  } else {
    // 在 total_xor 为 0 的情况下，B希望尽量得到最多
    // 计算 B 得到的最多的苹果重量
    // 这里只需要去掉最轻的苹果，剩余重量即为 B 获取的量
    int min_weight = *min_element(weights.begin(), weights.end());
    cout << total_weight - min_weight << endl; // B 获取的苹果总重量
  }

  return 0;
}