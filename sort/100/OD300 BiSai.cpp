#include <bits/stdc++.h>

using namespace std;

int main() {
  int m, n;
  char input[256];

  cin.getline(input, 256);
  sscanf(input, "%d,%d", &m, &n);

  // 检查 m 和 n 的有效性
  if (m < 3 || n < 3 || m > 10 || n > 100) {
    cout << "-1" << endl;
    return 0;
  }

  // 打分存储
  vector<vector<int> > scores(m, vector<int>(n));
  for (int i = 0; i < m; ++i) {
    cin.getline(input, 256);
    char* token = strtok(input, ",");
    for (int j = 0; j < n; ++j) {
      if (token == nullptr) {
        cout << "-1" << endl;
        return 0;
      }
      int score = atoi(token);
      // 检查每个评分是否在合法范围
      if (score < 1 || score > 10) {
        cout << "-1" << endl;
        return 0;
      }
      scores[i][j] = score;
      token = strtok(nullptr, ",");
    }
  }

  // 计算学生的总分
  vector<tuple<int, int, vector<int> > > results(n);
  for (int j = 0; j < n; ++j) {
    int total_score = 0;
    vector<int> count(11, 0); // 记录每个得分出现的次数
    for (int i = 0; i < m; ++i) {
      total_score += scores[i][j];
      count[scores[i][j]]++;
    }
    results[j] = make_tuple(total_score, j + 1, count); // 总分、选手编号、各分数计数
  }

  // 自定义排序，首先按总分降序，然后按各分数计数降序
  ranges::sort(results, [](const auto& a, const auto& b) {
    if (get<0>(a) != get<0>(b))
      return get<0>(a) > get<0>(b);

    // 如果总分相同，比较各分数的频率
    for (int i = 10; i >= 1; --i) {
      if (get<2>(a)[i] != get<2>(b)[i])
        return get<2>(a)[i] > get<2>(b)[i];
    }
    return false;
  });

  // 输出前 3 名选手编号
  for (int i = 0; i < 3; ++i) {
    cout << get<1>(results[i]);
    if (i < 2) cout << ",";
  }
  cout << endl;
  return 0;
}