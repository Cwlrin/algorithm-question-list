// OD205. 数组组成的最小数字
// 题目描述：
// 给定一个整型数组，请从该数组中选择 3 个元素组成最小数字并输出
// （如果数组长度小于 3，则选择数组中所有元素来组成最小数字）。
// 输入描述：
// 一行用半角逗号分割的字符串记录的整型数组，0 < 数组长度 <= 100，0 < 整数的取值范围 <= 10000。
// 输出描述：
// 由 3 个元素组成的最小数字，如果数组长度小于 3，则选择数组中所有元素来组成最小数字。
// 用例 1：
// 输入：
// ```
// 21,30,62,5,31
// ```
// 输出：
// ```
// 21305
// ```
// 说明：数组长度超过 3，需要选 3 个元素组成最小数字，21305 由 21,30,5 三个元素组成的数字，为所有组合中最小的数字。
// 用例 2：
// 输入：
// ```
// 5,21
// ```
// 输出：
// ```
// 215
// ```
// 说明：数组长度小于 3， 选择所有元素来组成最小值，215 为最小值。
// 难度：中等
// 标签：数组、字符串、排序、贪心

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

  ranges::sort(numbers, [](const auto& a, const auto& b) {
    return stoi(a) < stoi(b);
  });

  if (numbers.size() > 3) {
    numbers.resize(3);
  }

  ranges::sort(numbers, [](const auto& a, const auto& b) {
    return a + b <= b + a;
  });

  for (string& num : numbers) {
    cout << num;
  }

  return 0;
}