#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    string str;
    cin >> str;
    int length = str.length();

    // 生成偏移数组  
    vector<int> a(length, 0);
    if (length >= 1)
      a[0] = 1;
    if (length >= 2)
      a[1] = 2;
    if (length >= 3)
      a[2] = 4;
    for (int j = 3; j < length; ++j) {
      a[j] = (a[j - 1] + a[j - 2] + a[j - 3]) % 26; // 确保偏移量在 0 到 25 之间  
    }

    // 加密字符串  
    string encrypted_str;
    for (int j = 0; j < length; ++j) {
      char encrypted_char = (str[j] - 'a' + a[j]) % 26 + 'a';
      encrypted_str.push_back(encrypted_char);
    }

    // 输出结果  
    cout << encrypted_str << endl;
  }

  return 0;
}