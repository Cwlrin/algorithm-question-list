#include <bits/stdc++.h>
using namespace std;

int main() {
  int number, days;
  cin >> number >> days;

  vector<int> item(number);
  for (int i = 0; i < number; i++) {
    cin >> item[i];
  }

  vector<vector<int> > item_price(number, vector<int>(days));
  for (int i = 0; i < number; i++) {
    for (int j = 0; j < days; j++) {
      cin >> item_price[i][j];
    }
  }

  int total_profit = 0;

  for (int i = 0; i < number; i++) {
    int max_profit = 0;
    for (int j = 0; j < days - 1; j++) {
      if (item_price[i][j + 1] > item_price[i][j]) {
        max_profit += (item_price[i][j + 1] - item_price[i][j]) * item[i];
      }
    }
    total_profit += max_profit;
  }

  cout << total_profit << endl;

  return 0;
}