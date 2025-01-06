#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);
  stringstream ss(input);
  string number;
  vector<string> numbers;

  while (getline(ss, number, ',')) {
    numbers.push_back(number);
  }

  sort(numbers.begin(), numbers.end(), [](const auto& a, const auto& b) {
    return stoi(a) < stoi(b);
  });

  if (numbers.size() > 3) {
    numbers.resize(3);
  }

  sort(numbers.begin(), numbers.end(), [](const auto& a, const auto& b) {
    return a + b <= b + a;
  });

  for (string& num : numbers) {
    cout << num;
  }

  return 0;
}