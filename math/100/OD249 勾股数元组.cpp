#include <bits/stdc++.h>

using namespace std;

// 自定义函数用于计算最大公约数（GCD）  
int gcd(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

// 用于检查三个数字是否两两互质  
bool AreCoprime(int a, int b, int c) {
  return gcd(a, b) == 1 && gcd(a, c) == 1 && gcd(b, c) == 1;
}

int main() {
  int n, m;
  cin >> n >> m; // 输入范围  

  vector<tuple<int, int, int> > coprime_tuples; // 用于存放满足条件的勾股数元组  

  // 查找 (a, b, c) 所有可能的组合  
  for (int c = n; c <= m; ++c) {
    for (int a = n; a < c; ++a) {
      int b_square = c * c - a * a;             // 计算 b 的平方  
      int b = static_cast<int>(sqrt(b_square)); // 计算 b  

      // 检查 b 是否合适  
      if (b > a && b <= m && b * b == b_square) {
        // b 应该大于 a，且小于等于 M  
        // 检查是否两两互质  
        if (AreCoprime(a, b, c)) {
          coprime_tuples.emplace_back(a, b, c); // 记录元组  
        }
      }
    }
  }

  // 如果没有找到结果，输出 NA  
  if (coprime_tuples.empty()) {
    cout << "NA" << endl;
    return 0;
  }

  // 排序元组  
  sort(coprime_tuples.begin(), coprime_tuples.end());

  // 输出结果  
  for (const auto& t : coprime_tuples) {
    int a, b, c;
    tie(a, b, c) = t;
    cout << a << " " << b << " " << c << endl;
  }

  return 0;
}