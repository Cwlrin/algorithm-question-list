#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);
  stringstream ss(input);

  vector<string> nums;
  string num;

  while (ss >> num) {
    nums.push_back(num);
  }

  sort(nums.begin(), nums.end(), [](const string& a, const string& b) {
    return a + b > b + a;
  });

  string result;
  for (const string& n : nums) {
    result += n;
  }

  // 处理边界情况
  if (result[0] == '0') {
    cout << "0" << endl; // 如果最高位是 0，则结果是 0
  } else {
    cout << result << endl;
  }

  return 0;
}