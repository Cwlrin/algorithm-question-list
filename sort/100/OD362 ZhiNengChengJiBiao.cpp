// OD362 智能成绩表
// 题目描述：
// 小明来到某学校当老师，需要将学生按考试总分或单科分数进行排名，你能帮帮他吗？
// 输入描述：
// 第 1 行输入两个整数，学生人数 n 和科目数量 m。
// - 0 < n < 100
// - 0 < m < 10
// 第 2 行输入 m 个科目名称，彼此之间用空格隔开。
// - 科目名称只由英文字母构成，单个长度不超过 10 个字符。
// - 科目的出现顺序和后续输入的学生成绩一一对应。
// - 不会出现重复的科目名称。
// 第 3 行开始的 n 行，每行包含一个学生的姓名和该生 m 个科目的成绩（空格隔开）
// - 学生不会重名。
// - 学生姓名只由英文字母构成，长度不超过 10 个字符。
// - 成绩是 0~100 的整数，依次对应第 2 行种输入的科目。
// 第 n + 2 行，输入用作排名的科目名称。若科目不存在，则按总分进行排序。
// 输出描述：
// 输出一行，按成绩排序后的学生名字，空格隔开。成绩相同的按照学生姓名字典顺序排序。
// 用例 1：
// 输入：
// ```
// 3 2
// yuwen shuxue
// fangfang 95 90
// xiaohua 88 95
// minmin 100 82
// shuxue
// ```
// 输出： 
// ```
// xiaohua fangfang minmin
// ```
// 说明：按 shuxue 成绩排名，依次是 xiaohua、fangfang、minmin
// 难度：中等
// 标签：排序

#include <bits/stdc++.h>

using namespace std;

struct Student {
  string name;
  vector<int> scores;

  int get_score(const string& subject, const vector<string>& subjects) const {
    if (const auto it = ranges::find(subjects, subject);
      it != subjects.end()) {
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
  ranges::sort(students, [&](const Student& a, const Student& b) {
    int score_a = a.get_score(ranking_subject, subjects);
    int score_b = b.get_score(ranking_subject, subjects);

    if (score_a != score_b) return score_a > score_b; // 成绩排序
    return a.name < b.name; // 姓名排序
  });

  // 输出结果
  for (const auto& student : students) {
    cout << student.name << " ";
  }
  cout << endl;

  return 0;
}