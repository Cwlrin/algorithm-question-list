#include <bits/stdc++.h>

using namespace std;

int main() {
  int m, n, x;
  cin >> m >> n >> x;

  vector<int> returns(m);
  for (int i = 0; i < m; i++) {
    cin >> returns[i];
  }

  vector<int> risks(m);
  for (int i = 0; i < m; i++) {
    cin >> risks[i];
  }

  vector<int> max_investments(m);
  for (int i = 0; i < m; i++) {
    cin >> max_investments[i];
  }

  int max_return = 0;
  vector<int> best_investment(m, 0);

  // 先考虑单个产品的情况  
  for (int i = 0; i < m; i++) {
    if (risks[i] <= x) {
      int investment = min(max_investments[i], n); // 单个产品可以投资的金额  
      int total_return = returns[i] * investment;

      if (total_return > max_return) {
        max_return = total_return;
        fill(best_investment.begin(), best_investment.end(), 0);
        best_investment[i] = investment;
      }
    }
  }

  // 考虑两个产品的组合  
  for (int i = 0; i < m; i++) {
    for (int j = i + 1; j < m; j++) {
      int total_risk = risks[i] + risks[j];
      if (total_risk > x)
        continue; // 如果总风险超过可接受范围，跳过  

      // 动态调整投资额  
      for (int investment1 = 0; investment1 <= max_investments[i] && investment1
                                <= n; investment1++) {
        int investment2 = min(max_investments[j], n - investment1);
        // 保证两者投资不超出总额  

        int total_return = returns[i] * investment1 + returns[j] * investment2;
        if (total_return > max_return) {
          max_return = total_return;
          fill(best_investment.begin(), best_investment.end(), 0);
          best_investment[i] = investment1;
          best_investment[j] = investment2;
        }
      }
    }
  }

  // 输出结果  
  for (int i = 0; i < m; i++) {
    cout << best_investment[i] << " ";
  }
  cout << endl;

  return 0;
}