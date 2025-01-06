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
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
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

