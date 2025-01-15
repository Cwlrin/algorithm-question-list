#include <bits/stdc++.h>
using namespace std;

int main() {
  // 读取座位总数
  int seat_num;
  cin >> seat_num;
  cin.ignore(); // 忽略换行符

  // 读取进出顺序
  string line;
  getline(cin, line);

  // 解析输入数组
  vector<int> seat_or_leave;
  stringstream ss(line);
  string item;

  // 去掉首尾中括号
  if (!line.empty() && line[0] == '[')
    line = line.substr(1);
  if (!line.empty() && line.back() == ']')
    line.pop_back();

  ss.clear();
  ss.str(line);

  while (getline(ss, item, ',')) {
    seat_or_leave.push_back(stoi(item));
  }

  // 座位集合
  set<int> occupied_seats;
  int last_seat = -1;

  // 处理每个操作
  for (int action : seat_or_leave) {
    if (action == 1) {
      // 检查座位是否已满
      if (occupied_seats.size() == seat_num) {
        last_seat = -1;
        break;
      }

      // 第一个人直接坐在0号座位
      if (occupied_seats.empty()) {
        occupied_seats.insert(0);
        last_seat = 0;
        continue;
      }

      // 找最大社交距离的座位
      int max_distance = 0;
      int selected_seat = 0;

      // 考虑首座位左侧
      if (*occupied_seats.begin() > 0) {
        int distance = *occupied_seats.begin();
        if (distance > max_distance) {
          max_distance = distance;
          selected_seat = 0;
        }
      }

      // 考虑末座位右侧
      if (*occupied_seats.rbegin() < seat_num - 1) {
        int distance = seat_num - 1 - *occupied_seats.rbegin();
        if (distance > max_distance) {
          max_distance = distance;
          selected_seat = seat_num - 1;
        }
      }

      // 遍历已占座位之间的间隔
      auto it = occupied_seats.begin();
      int prev_seat = *it;
      ++it;

      for (; it != occupied_seats.end(); ++it) {
        int curr_seat = *it;
        int distance = (curr_seat - prev_seat) / 2;

        if (distance > max_distance) {
          max_distance = distance;
          selected_seat = prev_seat + distance;
        }

        prev_seat = curr_seat;
      }

      // 记录最后一个座位
      last_seat = selected_seat;
      occupied_seats.insert(selected_seat);
    } else {
      // 离开座位
      occupied_seats.erase(abs(action));
    }
  }

  // 输出最后一个进入的座位
  cout << last_seat << endl;

  return 0;
}