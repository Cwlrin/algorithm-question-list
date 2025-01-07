#include <bits/stdc++.h>

using namespace std;
// 检查是否为异常考勤
bool IsAbnormalAttendance(const string& status) {
  return status == "absent" || status == "late" || status == "leaveearly";
}
// 检查单次考勤是否符合奖励条件
bool CheckAttendance(const vector<string>& records) {
  int absent_count = 0;          // 缺勤计数
  int seven_days_bad_count = 0;  // 7天内的异常计数
  int consecutive_bad_count = 0; // 连续迟到或早退的计数
  // 检查连续迟到早退和 7 天内的异常情况
  for (size_t i = 0; i < records.size(); ++i) {
    // 缺勤计数
    if (records[i] == "absent") {
      absent_count++;
    }
    // 检查缺勤次数是否超过 1
    if (absent_count > 1) {
      return false;
    }
    // 检查 7 天内的异常状态
    if (IsAbnormalAttendance(records[i])) {
      seven_days_bad_count++;
    }
    // 处理连续的迟到或者早退
    if (records[i] == "late" || records[i] == "leaveearly") {
      consecutive_bad_count++;
      // 如果发现连续
      if (consecutive_bad_count > 1) {
        return false;
      }
    } else {
      consecutive_bad_count = 0;
    }
    // 检查 7 天窗口的异常计数
    if (i >= 7) {
      // 如果超出窗口的考勤是异常的，降低异常计数
      if (IsAbnormalAttendance(records[i - 7])) {
        seven_days_bad_count--;
      }
    }
    // 如果 7 天内异常达到三次，则不合法
    if (seven_days_bad_count > 3) {
      return false;
    }
  }
  return true;
}
int main() {
  int n;
  cin >> n;
  cin.ignore();

  for (int i = 0; i < n; ++i) {
    string s;
    getline(cin, s);
    stringstream ss(s);
    vector<string> records;
    string status;

    while (ss >> status) {
      records.push_back(status);
    }
    cout << (CheckAttendance(records) ? "true" : "false") << " ";
  }
  cout << endl;
  return 0;
}