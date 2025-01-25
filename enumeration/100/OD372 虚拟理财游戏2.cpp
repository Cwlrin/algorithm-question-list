#include <iostream>
#include <vector>
#include <algorithm>

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

  // 枚举所有可能的单个产品和两个产品组合  
  for (int i = 0; i < m; i++) {
    // 单个产品  
    if (risks[i] <= x) {
      int investment = min(max_investments[i], n);
      int total_return = returns[i] * investment;

      if (total_return > max_return) {
        max_return = total_return;
        fill(best_investment.begin(), best_investment.end(), 0);
        best_investment[i] = investment;
      }
    }

    // 两个产品组合  
    for (int j = i + 1; j < m; j++) {
      int total_risk = risks[i] + risks[j];
      if (total_risk > x)
        continue;

      // 动态调整投资额  
      int max_investment1 = min(max_investments[i], n);
      int max_investment2 = min(max_investments[j], n - max_investment1);

      int total_return = returns[i] * max_investment1 + returns[j] *
                        max_investment2;

      if (total_return > max_return) {
        max_return = total_return;
        fill(best_investment.begin(), best_investment.end(), 0);
        best_investment[i] = max_investment1;
        best_investment[j] = max_investment2;
      }

      // 交换投资优先级，重新计算  
      max_investment2 = min(max_investments[j], n);
      max_investment1 = min(max_investments[i], n - max_investment2);

      total_return = returns[i] * max_investment1 + returns[j] * max_investment2;

      if (total_return > max_return) {
        max_return = total_return;
        fill(best_investment.begin(), best_investment.end(), 0);
        best_investment[i] = max_investment1;
        best_investment[j] = max_investment2;
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