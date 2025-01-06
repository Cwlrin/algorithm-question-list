#include <bits/stdc++.h>

using namespace std;

struct Student {
  string name;
  vector<int> scores;

  int get_score(const string& subject, const vector<string>& subjects) const {
    const auto it = find(subjects.begin(), subjects.end(), subject);
    if (it != subjects.end()) {
      return scores[it - subjects.begin()]; // 返回相应科目的成绩
    }
    return accumulate(scores.begin(), scores.end(), 0); // 返回总分
  }
};

int main() {
  int n, m;
  cin >> n >> m;
  cin.ignore();

  vector<string> subjects(m);
  for (int i = 0; i < m; i++) {
    cin >> subjects[i];
  }

  vector<Student> students(n);
  for (int i = 0; i < n; i++) {
    students[i].scores.resize(m);
    cin >> students[i].name;
    for (int j = 0; j < m; j++) {
      cin >> students[i].scores[j];
    }
  }

  string ranking_subject;
  cin >> ranking_subject;

  // 排序学生
  sort(students.begin(), students.end(),
       [&](const Student& a, const Student& b) {
         int score_a = a.get_score(ranking_subject, subjects);
         int score_b = b.get_score(ranking_subject, subjects);

         if (score_a != score_b) return score_a > score_b; // 成绩排序
         return a.name < b.name;                           // 姓名排序
       });

  // 输出结果
  for (const auto& student : students) {
    cout << student.name << " ";
  }
  cout << endl;

  return 0;
}