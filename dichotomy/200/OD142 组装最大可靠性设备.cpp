#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Component {
  int reliability;
  int price;
};

bool CanAssemble(int minReliability,
                 const vector<vector<Component> >& components, int budget,
                 int N) {
  int total_price = 0;

  for (int type = 0; type < N; ++type) {
    int min_price = INT_MAX;
    bool found = false;

    // 寻找当前类型中可靠性 >= minReliability 的组件，并记录最小价格
    for (const auto& component : components[type]) {
      if (component.reliability >= minReliability) {
        found = true;
        min_price = min(min_price, component.price);
      }
    }

    if (!found)
      return false; // 如果没找到符合要求的组件

    total_price += min_price; // 统计购买所满足的最小价格

    if (total_price > budget)
      return false; // 超过预算
  }

  return total_price <= budget; // 返回是否在预算之内
}

int main() {
  int s, n; // S为预算，N为元件种类
  cin >> s >> n;

  int total; // 总部件数
  cin >> total;

  // 创建一个二维数组记录不同类型的组件
  vector<vector<Component> > components(n);

  for (int i = 0; i < total; ++i) {
    int type, reliability, price;
    cin >> type >> reliability >> price;
    components[type].push_back({reliability, price});
  }

  // 对每种类型的组件按可靠性从高到低排序
  for (int type = 0; type < n; ++type) {
    sort(components[type].begin(), components[type].end(),
         [](const Component& a, const Component& b) {
           return a.reliability > b.reliability; // 按可靠性降序排序
         });
  }

  // 二分查找可靠性
  int left = 1, right = 100000; // 根据可靠性的题目约束
  int best_reliability = -1;

  // 特殊情况处理: 当 N == 0 时不能构造设备
  if (n == 0) {
    cout << -1 << endl;
    return 0;
  }

  while (left <= right) {
    int mid = (left + right) / 2;

    if (CanAssemble(mid, components, s, n)) {
      best_reliability = mid; // 记录当前可以实现的最佳可靠性
      left = mid + 1;         // 尝试寻找更高的可靠性
    } else {
      right = mid - 1; // 减少可靠性
    }
  }

  // 如果无法满足设备的所有类型，则返回 -1
  if (best_reliability == -1) {
    cout << -1 << endl;
  } else {
    cout << best_reliability << endl; // 输出最大可靠性
  }

  return 0;
}