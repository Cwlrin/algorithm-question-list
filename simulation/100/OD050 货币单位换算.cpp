#include <bits/stdc++.h>

using namespace std;

int main() {
  // 定义正则表达式，匹配数字和货币单位
  regex currency_pattern(
      "(\\d+)(CNY|JPY|HKD|EUR|GBP|fen|cents|sen|eurocents|pence)");

  // 创建汇率映射表
  unordered_map<string, double> exchange_rates;
  exchange_rates["CNY"] = 100.0;               // 1 CNY = 100 fen
  exchange_rates["JPY"] = 100.0 / 1825 * 100;  // JPY 换算到 fen
  exchange_rates["HKD"] = 100.0 / 123 * 100;   // HKD 换算到 fen
  exchange_rates["EUR"] = 100.0 / 14 * 100;    // EUR 换算到 fen
  exchange_rates["GBP"] = 100.0 / 12 * 100;    // GBP 换算到 fen

  // 最小单位
  exchange_rates["fen"] = 1.0;
  exchange_rates["cents"] = 100.0 / 123;     // HKD cents
  exchange_rates["sen"] = 100.0 / 1825;      // JPY sen
  exchange_rates["eurocents"] = 100.0 / 14;  // EUR cents
  exchange_rates["pence"] = 100.0 / 12;      // GBP pence

  // 存储最终结果
  double total_amount = 0;

  // 读取输入数量
  int n;
  cin >> n;

  // 处理每一行输入
  for (int i = 0; i < n; i++) {
    string input;
    cin >> input;

    // 使用正则表达式迭代器匹配所有货币单位
    sregex_iterator currency_iterator(input.begin(), input.end(),
                                      currency_pattern);
    sregex_iterator end_iterator;

    // 遍历匹配到的所有货币单位
    while (currency_iterator != end_iterator) {
      // 获取匹配结果
      smatch currency_match = *currency_iterator;

      // 转换数量和单位
      double currency_amount = stod(currency_match[1]);
      string currency_unit = currency_match[2];

      // 累加转换后的结果
      total_amount += currency_amount * exchange_rates[currency_unit];

      // 移动到下一个匹配
      currency_iterator++;
    }
  }

  // 输出结果（向下取整）
  cout << static_cast<int>(total_amount) << endl;

  return 0;
}