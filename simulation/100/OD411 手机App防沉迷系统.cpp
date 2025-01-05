#include <bits/stdc++.h>

using namespace std;

// 将时间转换为分钟
int TimeToMinutes(const string& time) {
  int hours = stoi(time.substr(0, 2));
  int minutes = stoi(time.substr(3, 2));
  return hours * 60 + minutes;
}

int main() {
  int n;
  cin >> n;
  // 存储 App 信息的结构：{名称，优先级，开始时间，结束时间}
  vector<vector<string> > apps;
  // 注册 App
  for (int i = 0; i < n; ++i) {
    string name, start_time, end_time;
    int priority;
    cin >> name >> priority >> start_time >> end_time;
    // 检查是否可以注册
    bool can_register = true;
    for (auto it = apps.begin(); it != apps.end();) {
      // 时间是否冲突
      int start1 = TimeToMinutes(start_time);
      int end1 = TimeToMinutes(end_time);
      int start2 = TimeToMinutes((*it)[2]);
      int end2 = TimeToMinutes((*it)[3]);

      bool time_conflict = !(end1 <= start2 || end2 <= start1);

      if (time_conflict) {
        // 比较优先级
        int new_priority = priority;
        int exist_priority = stoi((*it)[1]);

        if (new_priority > exist_priority) {
          // 新 app 优先级高，移除已存在的 app
          it = apps.erase(it);
        } else if (new_priority < exist_priority) {
          // 新 app 优先级低，不能注册
          can_register = false;
          break;
        } else {
          // 优先级相同，后注册的不能注册
          can_register = false;
          break;
        }
      } else {
        ++it;
      }
    }

    // 注册 app
    if (can_register) {
      apps.push_back({name, to_string(priority), start_time, end_time});
    }
  }
  // 查询时间点
  string query_time;
  cin >> query_time;
  int query_minutes = TimeToMinutes(query_time);
  // 查找可用 app
  string result = "NA";
  int max_priority = -1;

  for (const auto& app: apps) {
    int start_minutes = TimeToMinutes(app[2]);
    int end_minutes = TimeToMinutes(app[3]);
    // 检查时间是否在 app 的时间段内（不包括结束时间）
    if (query_minutes >= start_minutes && query_minutes < end_minutes) {
      int current_priority = stoi(app[1]);
      if (current_priority > max_priority) {
        max_priority = current_priority;
        result = app[0];
      }
    }
  }
  cout << result << endl;
  return 0;
}