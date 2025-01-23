#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Group {
  int last_r;  // 最后一个区间的结束位置
  int first_r; // 第一个区间的结束位置
  int size;    // 缓存的区间数量

  // 自定义比较函数，用于优先队列，优先选择last_r最小的分组
  bool operator>(const Group& other) const {
    return last_r > other.last_r;
  }
};

int main() {
  int m, n;
  cin >> m >> n; // 输入面试官最多面试人次和总面试场次

  vector<pair<int, int> > interviews(n);
  for (int i = 0; i < n; ++i) {
    cin >> interviews[i].first >> interviews[i].second;
  }

  // 按起始位置升序排序
  sort(interviews.begin(), interviews.end());

  // 使用优先队列管理分组，last_r小的分组优先
  priority_queue<Group, vector<Group>, greater<Group> > groups;

  for (const auto& interview : interviews) {
    bool grouped = false;

    // 临时存储不匹配的分组
    vector<Group> temp;
    while (!groups.empty()) {
      Group curr_group = groups.top();
      groups.pop();

      // 检查是否与当前分组有交集
      if (interview.first >= curr_group.last_r) {
        // 无交集，可以加入分组
        if (curr_group.size < m) {
          curr_group.last_r = interview.second;
          curr_group.size++;
          groups.push(curr_group);
          grouped = true;
          break;
        }
        // 分组已饱和，保留一个区间的结束位置
        temp.push_back(curr_group);
      } else {
        // 有交集的分组放回临时数组
        temp.push_back(curr_group);
      }
    }

    // 将其他分组放回优先队列
    for (const auto& g : temp) {
      groups.push(g);
    }

    // 如果未加入任何分组，创建新分组
    if (!grouped) {
      Group new_group = {
          interview.second, // last_r
          interview.second, // first_r
          1                 // size
      };
      groups.push(new_group);
    }
  }

  // 输出分组数量
  cout << groups.size() << endl;

  return 0;
}