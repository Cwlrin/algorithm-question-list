#include <bits/stdc++.h>

using namespace std;

void dfs(vector<int>& link, int level, int index, vector<int>& path,
         vector<vector<int> >& res) {
  if (path.size() == level) {
    res.push_back(path);
    return;
  }

  for (int i = index; i < link.size(); i++) {
    path.push_back(link[i]);
    dfs(link, level, i + 1, path, res);
    path.pop_back();
  }
}

int main() {
  vector<int> link1;
  vector<int> link2;

  getchar(); // 读取第一行的开头 '['

  int id;
  while (cin >> id) {
    if (id < 4) {
      link1.push_back(id);
    } else {
      link2.push_back(id);
    }

    if (getchar() != ',') {
      // 读取每个处理器数字id后面的逗号
      break;
    }

    getchar(); // 读取空格
  }

  int num;
  cin >> num;

  sort(link1.begin(), link1.end());
  sort(link2.begin(), link2.end());

  map<int, vector<int> > dic;
  dic[1] = vector<int>{1, 3, 2, 4};
  dic[2] = vector<int>{2, 4, 3};
  dic[4] = vector<int>{4};

  vector<vector<int> > res;

  if (num == 8) {
    if (link1.size() == 4 && link2.size() == 4) {
      link2.insert(link2.begin(), link1.begin(), link1.end());
      res.push_back(link2);
    }
  } else {
    vector<int> path;
    for (const int& val : dic[num]) {
      if (link1.size() == val || link2.size() == val) {
        if (link1.size() == val) {
          dfs(link1, num, 0, path, res);
        }

        if (link2.size() == val) {
          dfs(link2, num, 0, path, res);
        }

        break; // 找到最优选择策略了，所以无需继续
      }
    }
  }

  // 输出打印
  cout << "[";

  for (size_t i = 0; i < res.size(); i++) {
    cout << "[";

    for (size_t j = 0; j < res[i].size(); j++) {
      cout << res[i][j];

      if (j < res[i].size() - 1) {
        cout << ", ";
      }
    }

    cout << "]";

    if (i < res.size() - 1) {
      cout << ", ";
    }
  }

  cout << "]";

  return 0;
}