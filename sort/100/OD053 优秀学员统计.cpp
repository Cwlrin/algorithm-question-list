#include <bits/stdc++.h>

using namespace std;

struct Employee {
  int id;
  int count;
  int first_day;
};

int main() {
  int n;
  cin >> n;

  // 每天打卡人数
  vector<int> daily_count(30);
  for (int i = 0; i < 30; i++) {
    cin >> daily_count[i];
  }

  // 统计每个员工的打卡次数和首次打卡时间
  unordered_map<int, Employee> stats;

  // 读取打卡记录
  for (int day = 0; day < 30; day++) {
    for (int i = 0; i < daily_count[day]; ++i) {
      int id;
      cin >> id;
      // if (!stats.contains(id)) {
      if (stats.find(id) == stats.end()) {
        // 初始化员工数据
        stats[id] = {id, 0, day};
      }
      // 增加打卡次数
      stats[id].count++;
    }
  }

  // 转换为向量以便排序
  vector<Employee> employees;
  for (const auto& entry : stats) {
    employees.push_back(entry.second);
  }

  sort(employees.begin(), employees.end(), [](const auto& a, const auto& b) {
    if (a.count != b.count) return a.count > b.count;
    if (a.first_day != b.first_day) return a.first_day < b.first_day;
    return a.id < b.id;
  });

  for (int i = 0; i < min(5, (int)employees.size()); i++) {
    if (i > 0) cout << " ";
    cout << employees[i].id;
  }
  cout << endl;

  return 0;
}