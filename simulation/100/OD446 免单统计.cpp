#include <bits/stdc++.h>
using namespace std;

// 提取时间的秒数部分（不含毫秒）
string GetSecond(const string& time) {
  return time.substr(0, time.length() - 4); // 去掉.fff部分
}

int main() {
  int n;
  cin >> n;
  cin.ignore(); // 处理换行符

  // 用于存储按秒分组的订单
  map<string, vector<string> > orders_by_second;

  // 读取所有订单
  for (int i = 0; i < n; i++) {
    string time;
    getline(cin, time);
    // 按秒分组存储完整时间
    orders_by_second[GetSecond(time)].push_back(time);
  }

  int free_orders = 0;

  // 处理每一秒的订单
  for (const auto& second_orders : orders_by_second) {
    const vector<string>& orders = second_orders.second;

    // 找出当前秒内最早的订单时间
    string earliest_time = *min_element(orders.begin(), orders.end());

    // 统计与最早订单时间相同的订单数量
    free_orders += count(orders.begin(), orders.end(), earliest_time);
  }

  cout << free_orders << endl;

  return 0;
}