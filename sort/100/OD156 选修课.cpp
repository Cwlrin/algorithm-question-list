// OD156. 选修课
// 题目描述：
// 现有两门选修课，每门选修课都有一部分学生选修，每个学生都有选修课的成绩，需要你找出同时选修了两门选修课的学生，先按照班级进行划分，班级编号小的先输出，每个班级按照两门选修课成绩和的降序排序，成绩相同时按照学生的学号升序排序。
// 输入描述：
// 第一行为第一门选修课学生的成绩，
// 第二行为第二门选修课学生的成绩，
// 每行数据中学生之间以英文分号分隔，每个学生的学号和成绩以英文逗号分隔，
// 学生学号的格式为 8 位数字：2 位院系编号 + 入学年份后 2 位 + 院系内部 1 位专业编号 + 所在班级 3 位学号
// 学生成绩的取值范围为 [0,100] 之间的整数，
// 两门选修课选修学生数的取值范围为 [1-2000] 之间的整数。
// 输出描述：
// 同时选修了两门选修课的学生的学号，如果没有同时选修两门选修课的学生输出NULL，
// 否则，先按照班级划分，班级编号小的先输出，每个班级先输出班级编号（学号前五位），
// 然后另起一行输出这个班级同时选修两门选修课的学生学号，学号按照要求排序（按照两门选修课成绩和的降序，成绩和相同时按照学号升序学生之间以英文分号分隔）。
// 用例：
// 输入 1：
// 01202021,75;01201033,95;01202008,80;01203006,90;01203088,100
// 01202008,70;01203088,85;01202111,80;01202021,75;01201100,88
// 输出 1：
// 01202
// 01202008;
// 01202021
// 01203
// 01203088
// 说明：每个字符出现的个数都是 2，故 x 排在 y 之前，而小写字母 x 排在 X 之前
// 输入 2： abababb
// 输出 2： b:4;a:3
// 说明： b 出现的个数比 a 多，故 b 排在 a 之前
// 难度：中等
// 标签：哈希、 排序

#include <bits/stdc++.h>

using namespace std;

struct Student {
  string id;
  int score1;
  int score2;
  int total_score;
};

int main() {
  string input1, input2;
  getline(cin, input1);
  getline(cin, input2);

  map<string, int> scores1, scores2; // 存储学号和成绩的映射
  vector<Student> common_students;   // 存储同时选修两门课的学生

  // 解析第一门选修课的成绩
  stringstream ss1(input1);
  string student_data;
  while (getline(ss1, student_data, ';')) {
    size_t pos = student_data.find(',');
    string id = student_data.substr(0, pos);
    int score = stoi(student_data.substr(pos + 1));
    scores1[id] = score;
  }
  // 解析第二门选修课的成绩
  stringstream ss2(input2);
  while (getline(ss2, student_data, ';')) {
    size_t pos = student_data.find(',');
    string id = student_data.substr(0, pos);
    int score = stoi(student_data.substr(pos + 1));
    scores2[id] = score;
  }

  // 找出同时选修了两门选修课的学生
  for (const auto& entry : scores1) {
    const string& id = entry.first;
    // if (scores2.contains(id)) {
    if (scores2.find(id) != scores2.end()) {
      // 学号存在于第二门课
      common_students.push_back({id, entry.second, scores2[id],
                                 entry.second + scores2[id]});
    }
  }

  // 如果没有共同选修的学生，输出 NULL
  if (common_students.empty()) {
    cout << "NULL" << endl;
    return 0;
  }

  // 按照班级编号分组并排序
  map<string, vector<Student> > grouped_students;
  for (const auto& student : common_students) {
    string class_id = student.id.substr(0, 5); // 获取班级编号
    grouped_students[class_id].push_back(student);
  }

  // 排序并输出结果
  // for (auto &[class_id, students]: class_map) {
  for (auto& entry : grouped_students) {
    string class_id = entry.first;
    vector<Student>& students = entry.second;

    // 排序
    ranges::sort(students, [](const Student& a, const Student& b) {
      if (a.total_score != b.total_score)
        return a.total_score > b.total_score; // 总成绩降序
      return a.id < b.id;                     // 学号升序
    });

    // 输出班级编号
    cout << class_id << endl;

    // 输出学生学号
    for (size_t i = 0; i < students.size(); ++i) {
      if (i > 0) cout << ";";
      cout << students[i].id;
    }
    cout << endl;
  }

  return 0;
}

