## 排序

### 100 分

#### 数组去重和排序

**题目描述**：

给定一个乱序的数组，删除所有的重复元素，使得每个元素只出现一次，并且按照出现的次数从高到低进行排序，相同出现次数按照第一次出现顺序进行先后排序

**输入描述**：

一个数组

**输出描述**：

去重排序后的数组

**用例 1**：

输入：

```
1,3,3,3,2,4,4,4,5
```

输出：

```
3,4,1,2,5
```

难度：中等

标签：数组、哈希、排序

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);

  // 去除输入字符串中的空格，并按逗号分割成数组
  stringstream ss(input);
  string token;
  vector<int> arr;
  while (getline(ss, token, ',')) {
    arr.push_back(stoi(token));
  }

  // 创建一个哈希表来存储每个元素的出现次数和第一次出现的位置
  unordered_map<int, pair<int, int> > count_map;
  for (int i = 0; i < arr.size(); ++i) {
    if (count_map.find(arr[i]) == count_map.end()) {
      count_map[arr[i]] = {0, i};
    }
    count_map[arr[i]].first++;
  }

  // 将哈希表转换为向量
  vector<pair<int, pair<int, int> > > sorted_arr;
  // for (const auto& entry : count_map) {
  //   sorted_arr.push_back({entry.first, entry.second});
  // }
  for (const auto& [fst, snd] : count_map) {
    sorted_arr.emplace_back(fst, snd);
  }

  // 排序
  // sort(sort_arr.begin(), sort_arr.end());
  sort(sorted_arr.begin(), sorted_arr.end(), [](const auto& a, const auto& b) {
    if (a.second.first == b.second.first) {
      return a.second.second < b.second.second;
    }
    return a.second.first > b.second.first;
  });

  for (int i = 0; i < sorted_arr.size(); ++i) {
    if (i > 0) {
      cout << ",";
    }
    cout << sorted_arr[i].first;
  }
  cout << endl;
}
```

#### 字符统计及重排

**题目描述**：

给出一个仅包含字母的字符串，不包含空格，统计字符串中各个字母（区分大小写）出现的次数，并按照字母出现次数从大到小的顺序。

输出各个字母及其出现次数。如果次数相同，按照自然顺序进行排序，且小写字母在大写字母之前。

**输入描述**：

输入一行，为一个仅包含字母的字符串。

**输出描述**：

按照字母出现次数从大到小的顺序输出各个字母和字母次数，用英文分号分隔，注意末尾的分号；

字母和次数间用英文冒号分隔。

**用例 1**：

输入：

```
xyxyXX
```

输出：

```
x:2;y:2;X:2;
```

**说明**：每个字符出现的个数都是 2，故 x 排在 y 之前，而小写字母 x 在 X 之前

**用例 2**：

输入：

```
abababb
```

输出：

```
b:4;a:3;
```

说明：b 的出现个数比 a 多，故 b 排在 a 之前

难度：中等

标签：字符串、哈希、排序

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  cin >> input;

  // 创建一个哈希表来存储每个字符的出现次数
  unordered_map<char, int> count_map;
  for (char c : input) {
    count_map[c]++;
  }

  // 将哈希表转换为向量
  vector<pair<char, int> > sorted_chars(count_map.begin(), count_map.end());

  // 排序
  sort(sorted_chars.begin(), sorted_chars.end(),
       [](const auto& a, const auto& b) {
         if (a.second == b.second) {
           if (islower(a.first) && !islower(b.first)) {
             return true; // 小写字母优先
           }
           if (!islower(a.first) && islower(b.first)) {
             return false; // 大写字母不优先
           }
           return a.first < b.first; // 自然顺序排序，小写字母在大写字母之前
         }
         return a.second > b.second; // 按出现次数降序排列
       });

  // 输出结果
  for (int i = 0; i < sorted_chars.size(); ++i) {
    if (i > 0) {
      cout << ";";
    }
    cout << sorted_chars[i].first << ":" << sorted_chars[i].second;
  }
  cout << ";" << endl;
}
```

#### 选修课

**题目描述**：

现有两门选修课，每门选修课都有一部分学生选修，每个学生都有选修课的成绩，需要你找出同时选修了两门选修课的学生，先按照班级进行划分，班级编号小的先输出，每个班级按照两门选修课成绩和的降序排序，成绩相同时按照学生的学号升序排序。

**输入描述**：

第一行为第一门选修课学生的成绩，

第二行为第二门选修课学生的成绩，

每行数据中学生之间以英文分号分隔，每个学生的学号和成绩以英文逗号分隔，

学生学号的格式为 8 位数字

> 2 位院系编号 + 入学年份后 2 位 + 院系内部 1 位专业编号 + 所在班级 3 位学号

学生成绩的取值范围为 [0,100] 之间的整数，

两门选修课选修学生数的取值范围为 [1-2000] 之间的整数。

**输出描述**：

同时选修了两门选修课的学生的学号，如果没有同时选修两门选修课的学生输出 NULL，

否则，先按照班级划分，班级编号小的先输出，每个班级先输出班级编号 (学号前五位)，

然后另起一行输出这个班级同时选修两门选修课的学生学号，学号按照要求排序 ( 按照两门选修课成绩和的降序，成绩和相同时按照学号升序学生之间以英文分号分隔。

**用例 1**：

输入：

```
01202021,75;01201033,95;01202008,80;01203006,90;01203088,100
01202008,70;01203088,85;01202111,80;01202021,75;01201100,88
```

输出：

```
01202
01202008;01202021
01203
01203088
```

说明：

同时选修了两选修课的学生 01202021、01202008、01203088，这三个学生两门选修课的成绩和分别为 150、150、185，

01202021、01202008 属于 01202 班的学生，按照成绩和降序，成绩相同时按学号升序输出的结果为 01202008; 01202021,

01203088 属于 01203 班的学生，按照成绩和降序，成绩相同时按学号升序输出的结果为 01203088，

01202 的班级编号小于 01203 的班级编号，需要先输出。

**用例 2**：

输入：

```
01201022,75;01202033,95;01202018,80;01203006,90;01202066,100
01202008,70;01203102,85;01202111,80;01201021,75;01201100,88
```

输出：

```
NULL
```

说明：没有同时选修了两门选修课的学生，输出 NULL.

难度：中等

标签：哈希、排序

```cpp
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
```

#### 热点网站统计

**题目描述**：

企业路由器的统计页面，有一个功能需要动态统计公司访问最多的网页 URL top N。

请设计一个算法，可以高效动态统计 Top N 的页面。

**输入描述**：

每一行都是一个 URL 或一个数字，如果是 URL，代表一段时间内的网页访问； 如果是一个数字 N，代表本次需要输出的 Top N 个 URL。

输入约束：

1. 总访问网页数量小于 5000 个，单网页访问次数小于 65535 次；
2. 网页 URL 仅由字母，数字和点分隔符组成，且长度小于等于 127 字节；
3. 数字是正整数，小于等于 10 且小于当前总访问网页数；

**输出描述**：

每行输入要对应一行输出，输出按访问次数排序的前 N 个 URL，用逗号分隔。

输出要求：

1. 每次输出要统计之前所有输入，不仅是本次输入；
2. 如果有访问次数相等的 URL，按 URL 的字符串字典序升序排列，输出排序靠前的 URL；

**用例 1**：

输入：

```
news.qq.com
news.sina.com.cn
news.qq.com
news.qq.com
game.163.com
game.163.com
www.huawei.com
www.cctv.com
3
www.huawei.com
www.cctv.com
www.huawei.com
www.cctv.com
www.huawei.com
www.cctv.com
www.huawei.com
www.cctv.com
www.huawei.com
3
```

输出：

```
news.qq.com,game.163.com,news.sina.com.cn
www.huawei.com,www.cctv.com,news.qq.com
```

**用例 2**：

输入：

```
news.qq.com
www.cctv.com
1
www.huawei.com
www.huawei.com
2
3
```

输出：

```
news.qq.com
www.huawei.com,news.qq.com
www.huawei.com,news.qq.com,www.cctv.com
```

难度：中等

标签：哈希、排序

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  unordered_map<string, int> url_count;
  while (getline(cin, input)) {
    // 判断是否输入是数字
    if (isdigit(input[0])) {
      const int n = stoi(input);
      vector<pair<string, int> > url_list(url_count.begin(), url_count.end());

      // 对 url 进行排序
      sort(url_list.begin(), url_list.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) {
          return a.second > b.second; // 按照访问次数排序
        }
        return a.first < b.first; // 访问次数相同时按照字母序排序
      });

      // 输出前 n 个 URL
      for (int i = 0; i < n; ++i) {
        if (i > 0) {
          cout << ",";
        }
        cout << url_list[i].first;
      }
      cout << endl;
    } else {
      // 输入 url，更新统计数据
      url_count[input]++;
    }
  }
  return 0;
}
```

#### 磁盘容量排序

**题目描述**：

磁盘的容量单位常用的有 M，G，T 这三个等级，

它们之间的换算关系为 1T = 1024G，1G = 1024M，

现在给定 n 块磁盘的容量，请对它们按从小到大的顺序进行稳定排序，

例如给定 5 块盘的容量，1T，20M，3G，10G6T，3M12G9M

排序后的结果为 20M，3G，3M12G9M，1T，10G6T。

注意单位可以重复出现，上述 3M12G9M 表示的容量即为 3M+12G+9M，和 12M12G 相等。

**输入描述**：

输入第一行包含一个整数 n(2 <= n <= 100)，表示磁盘的个数，

接下的 n 行，每行一个字符串 (长度大于 2，小于 30)，

表示磁盘的容量，由一个或多个格式为 mv 的子串组成，

其中 m 表示容量大小，v 表示容量单位，例如 20M，1T，30G，10G6T，3M12G9M。

磁盘容量 m 的范围为 1 到 1024 的正整数，

容量单位 v 的范围只包含题目中提到的 M，G，T 三种，换算关系如题目描述。

**输出描述**：

输出 n 行，表示 n 块磁盘容量排序后的结果。

**用例 1**：

输入：

```
3
1G
2G
1024M
```

输出：

```
1G
1024M
2G
```

说明：1G 和 1024M 容量相等，稳定排序要求保留它们原来的相对位置，故 1G 在 1024M 之前。

**用例 2**：

输入：

```
3
2G4M
3M2G
1T
```

输出：

```
3M2G
2G4M
1T
```

说明：1T 的容量大于 2G4M，2G4M 的容量大于 3M2G

难度：中等

标签：字符串、排序

```cpp
#include <bits/stdc++.h>

using namespace std;

// 将容量字符串解析为以 M 为单位的总容量
long long parase_capacity(const string& s) {
  long long total = 0;
  int num = 0;
  for (char i : s) {
    if (isdigit(i)) {
      num = num * 10 + (i - '0'); // 累计数字
    } else {
      // 根据单位累加总容量
      if (i == 'M') {
        total += num;
      } else if (i == 'G') {
        total += num * 1024LL;
      } else if (i == 'T') {
        total += num * 1024LL * 1024LL;
      }
      num = 0; // 重置数字部分
    }
  }
  return total;
}

int main() {
  int n;
  cin >> n;
  cin.ignore(); // 忽略换行符
  vector<pair<string, long long> > disks;

  // 读取输入并解析容量
  for (int i = 0; i < n; ++i) {
    string disk;
    getline(cin, disk);
    long long capacity = parase_capacity(disk);
    disks.emplace_back(disk, capacity);
  }

  // 按照容量排序，使用稳定排序保持输入排序
  stable_sort(disks.begin(), disks.end(), [](const auto& a, const auto& b) {
    return a.second < b.second; // 按容量升序
  });

  // 输出排序后的结果
  for (const auto& disk : disks) {
    cout << disk.first << endl;
  }

  return 0;
}
```

#### 优秀学员统计

**题目描述**：

公司某部门软件教导团正在组织新员工每日打卡学习活动，他们开展这项学习活动已经一个月了，所以想统计下这个月优秀的打卡员工。每个员工会对应一个 id，每天的打卡记录记录当天打卡员工的 id 集合，一共 30 天。

请你实现代码帮助统计出打卡次数 top5 的员工。加入打卡次数相同，将较早参与打卡的员工排在前面，如果开始参与打卡的时间还是一样，将 id 较小的员工排在前面。

注：不考虑并列的情况，按规则返回前 5 名员工的 id 即可，如果当月打卡的员工少于 5 个，按规则排序返回所有有打卡记录的员工 id。

**输入描述**：

第一行输入为新员工数量 N，表示新员工编号 id 为 0 到 N-1，N 的范围为 [1,100]

第二行输入为 30 个整数，表示每天打卡的员工数量，每天至少有 1 名员工打卡。

之后 30 行为每天打卡的员工 id 集合，id 不会重复。

**输出描述**：

按顺序输出打卡 top5 员工的 id，用空格隔开。

**用例 1**：

输入：

```
11
4 4 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2
0 1 7 10
0 1 6 10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
10
6 10
7 10
```

输出：

```
10 0 1 7 6
```

说明：员工编号范围为 0~10，id 为 10 的员工连续打卡 30 天，排第一，id 为 0,1,6,7 的员工打卡都是两天，id 为 0,1,7 的员工在第一天就打卡，比 id 为 6 的员工早，排在前面，0,1,7 按 id 升序排列，所以输出 [10,0,1,7,6]

**用例 2**：

输入：

```
7
6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
0 1 2 3 4 5
```

输出：

```
0 1 2 3 4
```

说明：员工编号范围为 0-6，id 为 0，1，2，3，4，5 的员工打卡次数相同，最早开始打卡的时间也一样，所以按 id 升序返回前 5 个 id

**用例 3**：

输入：

```
2
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
0 1
0 1
```

输出：

```
1 0
```

说明：只有两名员工参与打卡，按规则排序输出两名员工的 id

难度：中等

标签：哈希、排序、数组

```cpp
#include <bits/stdc++.h>

using namespace std;

struct Employee {
  int id;
  int count;
  int first_day;
};

int main() {
  int n;
  cin >> n;

  // 每天打卡人数
  vector<int> daily_count(30);
  for (int i = 0; i < 30; i++) {
    cin >> daily_count[i];
  }

  // 统计每个员工的打卡次数和首次打卡时间
  unordered_map<int, Employee> stats;

  // 读取打卡记录
  for (int day = 0; day < 30; day++) {
    for (int i = 0; i < daily_count[day]; ++i) {
      int id;
      cin >> id;
      // if (!stats.contains(id)) {
      if (stats.find(id) == stats.end()) {
        // 初始化员工数据
        stats[id] = {id, 0, day};
      }
      // 增加打卡次数
      stats[id].count++;
    }
  }

  // 转换为向量以便排序
  vector<Employee> employees;
  for (const auto& entry : stats) {
    employees.push_back(entry.second);
  }

  sort(employees.begin(), employees.end(), [](const auto& a, const auto& b) {
    if (a.count != b.count) return a.count > b.count;
    if (a.first_day != b.first_day) return a.first_day < b.first_day;
    return a.id < b.id;
  });

  for (int i = 0; i < min(5, (int)employees.size()); i++) {
    if (i > 0) cout << " ";
    cout << employees[i].id;
  }
  cout << endl;

  return 0;
}
```

#### 数组组成的最小数字

**题目描述**：

给定一个整型数组，请从该数组中选择 3 个元素组成最小数字并输出

（如果数组长度小于 3，则选择数组中所有元素来组成最小数字）。

**输入描述**：

一行用半角逗号分割的字符串记录的整型数组，0 < 数组长度 <= 100，0 < 整数的取值范围 <= 10000。

**输出描述**：

由 3 个元素组成的最小数字，如果数组长度小于 3，则选择数组中所有元素来组成最小数字。

**用例 1**：

输入：

```
21,30,62,5,31
```

输出：

```
21305
```

说明：数组长度超过 3，需要选 3 个元素组成最小数字，21305 由 21,30,5 三个元素组成的数字，为所有组合中最小的数字。

**用例 2**：

输入：

```
5,21
```

输出：

```
215
```

说明：数组长度小于 3， 选择所有元素来组成最小值，215 为最小值。

难度：中等

标签：数组、字符串、排序

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);
  stringstream ss(input);
  string number;
  vector<string> numbers;

  while (getline(ss, number, ',')) {
    numbers.push_back(number);
  }

  sort(numbers.begin(), numbers.end(), [](const auto& a, const auto& b) {
    return stoi(a) < stoi(b);
  });

  if (numbers.size() > 3) {
    numbers.resize(3);
  }

  sort(numbers.begin(), numbers.end(), [](const auto& a, const auto& b) {
    return a + b <= b + a;
  });

  for (string& num : numbers) {
    cout << num;
  }

  return 0;
}
```

#### 日志排序

**题目描述**：

运维工程师采集到某产品线网运行一天产生的日志 n 条，现需根据日志时间先后顺序对日志进行排序，日志时间格式为 H: M: S.N。

- H 表示小时 (0~23)
- M 表示分钟 (0~59)
- S 表示秒 (0~59)
- N 表示毫秒 (0~999)

时间可能并没有补全，也就是说，01:01:01.001 也可能表示为 1:1:1.1。

**输入描述**：

第一行输入一个整数 n 表示日志条数，1 <= n <= 100000，接下来 n 行输入 n 个时间。

**输出描述**：

按时间升序排序之后的时间，如果有两个时间表示的时间相同，则保持输入顺序。

**用例 1**：

输入：

```
2
01:41:8.9
1:1:09.211
```

输出：

```
1:1:09.211
01:41:8.9
```

**用例 2**：

输入：

```
3
23:41:08.023
1:1:09.211
08:01:22.0
```

输出：

```
1:1:09.211
08:01:22.0
23:41:08.023
```

**用例 3**：

输入：

```
2
22:41:08.023
22:41:08.23
```

输出：

```
22:41:08.023
22:41:08.23
```

说明：两个时间表示的时间相同，保持输入顺序

难度：中等

标签：字符串、排序

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<string> logs(n);
  for (int i = 0; i < n; i++) {
    cin >> logs[i];
  }

  stable_sort(logs.begin(), logs.end(), [](const auto& a, const auto& b) {
    int h1, h2, m1, m2, s1, s2, n1, n2;
    sscanf(a.c_str(), "%d:%d:%d.%d", &h1, &m1, &s1, &n1);
    sscanf(b.c_str(), "%d:%d:%d.%d", &h2, &m2, &s2, &n2);

    // 直接分别比较时分秒毫秒，避免计算后数据过大
    if (h1 != h2) return h1 < h2;
    if (m1 != m2) return m1 < m2;
    if (s1 != s2) return s1 < s2;
    return n1 < n2;
  });

  for (const auto& log : logs) {
    cout << log << endl;
  }

  return 0;
}
```

#### 智能成绩表

**题目描述**：

小明来到某学校当老师，需要将学生按考试总分或单科分数进行排名，你能帮帮他吗？

**输入描述**：

第 1 行输入两个整数，学生人数 n 和科目数量 m。

- 0 < n < 100
- 0 < m < 10

第 2 行输入 m 个科目名称，彼此之间用空格隔开。

- 科目名称只由英文字母构成，单个长度不超过 10 个字符。
- 科目的出现顺序和后续输入的学生成绩一一对应。
- 不会出现重复的科目名称。

第 3 行开始的 n 行，每行包含一个学生的姓名和该生 m 个科目的成绩（空格隔开）

- 学生不会重名。
- 学生姓名只由英文字母构成，长度不超过 10 个字符。
- 成绩是 0~100 的整数，依次对应第 2 行种输入的科目。

第 n + 2 行，输入用作排名的科目名称。若科目不存在，则按总分进行排序。

**输出描述**：

输出一行，按成绩排序后的学生名字，空格隔开。成绩相同的按照学生姓名字典顺序排序。

**用例 1**：

输入：

```
3 2
yuwen shuxue
fangfang 95 90
xiaohua 88 95
minmin 100 82
shuxue
```

输出：

```
xiaohua fangfang minmin
```

说明：按 shuxue 成绩排名，依次是 xiaohua、fangfang、minmin

难度：中等

标签：排序

```cpp
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
```

#### 比赛

**题目描述**：

一个有 N 个选手参加比赛，选手编号为 1~N（3 <= N <= 100），有 M（3 <= M <= 10）个评委对选手进行打分。

打分规则为每个评委对选手打分，最高分 10 分，最低分 1 分。

请计算得分最多的 3 位选手的编号。 如果得分相同，则得分高分值最多的选手排名靠前

(10 分数量相同，则比较 9 分的数量，以此类推，用例中不会出现多个选手得分完全相同的情况)。

**输入描述**：

第一行为半角逗号分割的两个正整数，第一个数字表示 M（3 <= M <= 10）个评委，第二个数字表示 N（3 <= N <= 100）个选手。

第 2 到 M+1 行是半角逗号分割的整数序列，表示评委为每个选手的打分，0 号下标数字表示 1 号选手分数，1 号下标数字表示 2 号选手分数，依次类推。

**输出描述**：

选手前 3 名的编号。

注：若输入为异常，输出 -1，如 M、N、打分不在范围内。

**用例 1**：

输入：

```
4,5
10,6,9,7,6
9,10,6,7,5
8,10,6,5,10
9,10,8,4,9
```

输出：

```
2,1,5
```

说明：

第一行代表有 4 个评委，5 个选手参加比赛

矩阵代表是 4\*5，每个数字是选手的编号，每一行代表一个评委对选手的打分排序，

2 号选手得分 36 分排第 1，1 号选手 36 分排第 2，5 号选手 30 分 (2 号 10 分值有 3 个，1 号 10 分值只有 1 个，所以 2 号排第一)

**用例 2**：

输入：

```
2,5
7,3,5,4,2
8,5,4,4,3
```

输出：

```
-1
```

说明：只有 2 个评委，要求最少为 3 个评委

**用例 3**：

输入：

```
4,2
8,5
5,6
10,4
8,9
```

输出：

```
-1
```

说明：只有 2 名选手参加，要求最少为 3 名

**用例 4**：

输入：

```
4,5
11,6,9,7,8
9,10,6,7,8
8,10,6,9,7
9,10,8,6,7
```

输出：

```
-1
```

说明：第一个评委给第一个选手打分 11，无效分数

难度：中等

标签：排序、数组

```cpp
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
```

#### 字符串重新排序

**题目描述**：

给定一个字符串 s，s 包括以空格分隔的若干个单词，请对 s 进行如下处理后输出：

1. 单词内部调整：对每个单词字母重新按字典序排序

2. 单词间顺序调整：
   1. 统计每个单词出现的次数，并按次数降序排列
   2. 次数相同，按单词长度升序排列
   3. 次数和单词长度均相同，按字典升序排列

请输出处理后的字符串，每个单词以一个空格分隔。

**输入描述**：

一行字符串，每个字符取值范围：[a-zA-z0-9] 以及空格，字符串长度范围：[1，1000]

**输出描述**：

输出处理后的字符串，每个单词以一个空格分隔。

**用例 1**：

输入：

```
This is an apple
```

输出：

an is This aelpp

**用例 2**：

输入：

```
My sister is in the house not in the yard
```

输出：

```
in in eht eht My is not adry ehosu eirsst
```

难度：中等

标签：字符串、排序、哈希

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);

  // 分割字符串为单词，并对单词内部字母进行排序
  istringstream ss(input);
  vector<string> words;
  string word;

  auto sort_word = [](const string& word) {
    string sorted_word = word;
    ranges::sort(sorted_word);
    return sorted_word;
  };

  while (ss >> word) {
    words.push_back(sort_word(word));
  }

  // 统计每个单词出现的次数
  map<string, int> word_count;
  for (const auto& w : words) {
    word_count[w]++;
  }

  // 转换为向量，方便排序
  vector<pair<string, int> > count_vec(word_count.begin(), word_count.end());

  ranges::sort(count_vec, [](const auto& a, const auto& b) {
    if (a.second != b.second) {
      return a.second > b.second; // 按出现次数降序
    }
    if (a.first.length() != b.first.length()) {
      return a.first.length() < b.first.length(); // 按照长度升序
    }
    return a.first < b.first; // 按照字典序升序
  });

  vector<string> result;
  for (const auto &p : count_vec) {
    // 按次数输出单词
    for (int i = 0; i < p.second; i++) {
      result.push_back(p.first);
    }
  }

  cout << result[0];
  for (size_t i = 1; i < result.size(); i++) {
    cout << " " << result[i];
  }
  cout << endl;

  return 0;
}
```

#### 字符串解密

**题目描述**：

给定两个字符串 string1 和 string2。 string1 是一个被加扰的字符串。

string1 由小写英文字母（'a'~ 'z'）和数字字符（'0'~ '9'）组成，而加扰字符串由'0'~ '9'、'a'~'f'组成。

string1 里面可能包含 0 个或多个加扰子串，剩下可能有 0 个或多个有效子串，这些有效子串被加扰子串隔开。

string2 是一个参考字符串，仅由小写英文字母（'a'~'z'）组成。

你需要在 string1 字符串里找到一个有效子串，这个有效子串要同时满足下面两个条件：

1. 这个有效子串里不同字母的数量不超过且最接近于 string2 里不同字母的数量，即小于或等于 string2 里不同字母的数量的同时且最大。

2. 这个有效子串是满足条件（1）里的所有子串（如果有多个的话）里字典序最大的一个。

如果没有找到合适条件的子串的话，请输出 "Not Found"

**输入描述**：

input_string1 input_string2

**输出描述**：

output_string

**用例 1**：

输入：

```
123admyffc79pt
ssyy
```

输出：

```
pt
```

说明：

将输入字符串 1 里的加扰子串 "123ad"、"ffc79" 去除后得到有效子串序列："my"、"pt"，其中 "my" 里不同字母的数量为 2（有'm'和'y'两个不同字母），"pt" 里不同字母的数量为 2（有'p'和't'两个不同字母）；输入字符串 2 里不同字母的数量为 2（有's'和'y'两个不同字母）。

可得到最终输出结果为 "pt"，其不同字母的数量最接近与 "ssyy" 里不同字母的数量的同时字典序最大。

**用例 2**：

输入：

```
123admyffc79ptaagghi2222smeersst88mnrt
ssyyfgh
```

输出：

```
mnrt
```

说明：

将输入字符串 1 里的加扰子串 "123ad"、"ffc79"、"aa"、"2222" "ee"、"88" 去除后得到有效子串序列："my"、"pt"、"gghi"、"sm"、"rsst"、"mnrt"；输入字符串 2 里不同字母的数量为 5（有's'、'y'、'f'、'g'、'h'5 个不同字母）。可得到最终输出结果为 "mnrt"，其不同字母的数量（为 4）最接近于 "ssyyfgh" 里不同字母的数量，其他有效子串不同字母的数量都小于 "mnrt"。

**用例 3**：

输入：

```
abcmnq
rt
```

输出：

```
Not Found
```

说明：

将输入字符串 1 里的加扰子串 "abc" 去除后得到有效子串序列："mnq"；输入字符串 2 里不同字母的数量为 2（有 'r'、't'两个不同的字母）。可得到最终的输出结果为 "Not Found"，没有符合要求的有效子串，因有效子串里的不同字母的数量（为 3），大于输入字符串 2 里的不同字母的数量。

难度：困难

标签：字符串、排序、哈希、动态规划

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input1, input2;
  cin >> input1 >> input2;

  // 计算 input2 中的不同字母的数量
  set<char> unique_chars2(input2.begin(), input2.end());
  int target_count = unique_chars2.size();

  // 使用正则表达式分割字符串，提取仅含有字母的有效子串
  const regex non_letter_pattern("[0-9a-f]+");
  sregex_token_iterator it(input1.begin(), input1.end(), non_letter_pattern,
                           -1);
  sregex_token_iterator end;

  vector<string> vaild_substrings;
  for (; it != end; ++it) {
    // 移除空串
    string substring = it->str();
    if (!substring.empty()) {
      vaild_substrings.push_back(substring);
    }
  }

  string best_substring = "Not Found";
  int best_count = -1;

  // 遍历有效子串
  for (const string& substring : vaild_substrings) {
    // 计算当前子串中不同字母的数量
    set<char> unique_chars(substring.begin(), substring.end());
    int current_count = unique_chars.size();

    // 判断是否满足条件
    if (current_count <= target_count) {
      // 更新最佳子串的条件
      if (best_count == -1 || current_count > best_count || (
            current_count == best_count && substring > best_substring)) {
        best_substring = substring;
        best_count = current_count;
      }
    }
  }

  cout << best_substring << endl;
  return 0;
}
```

### 200 分

#### 最大值

**题目描述**：

给定一组整数（非负），重排顺序后输出一个最大的整数。

示例 1

输入：[10,9]

输出：910

说明: 输出结果可能非常大，所以你需要返回一个字符串而不是整数。

**输入描述**：

数字组合

**输出描述**：

最大的整数

**用例 1**：

输入：

```
10 9
```

输出：

```
910
```

难度：中等

标签：贪心、排序、字符串、数组

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);
  stringstream ss(input);

  vector<string> nums;
  string num;

  while (ss >> num) {
    nums.push_back(num);
  }

  sort(nums.begin(), nums.end(), [](const string& a, const string& b) {
    return a + b > b + a;
  });

  string result;
  for (const string& n : nums) {
    result += n;
  }

  // 处理边界情况
  if (result[0] == '0') {
    cout << "0" << endl; // 如果最高位是 0，则结果是 0
  } else {
    cout << result << endl;
  }

  return 0;
}
```

## 模拟

### 100 分

#### 流浪地球

**题目描述**：

流浪地球计划在赤道上均匀部署了 N 个转向发动机，按位置顺序编号为 0 ~ N

1. 初始状态下所有的发动机都是未启动状态
2. 发动机启动的方式分为 "手动启动" 和 "关联启动" 两种方式
3. 如果在时刻 1 一个发动机被启动，下一个时刻 2 与之相邻的两个发动机就会被 "关联启动"
4. 如果准备启动某个发动机时，它已经被启动了，则什么都不用做
5. 发动机 0 与发动机 N-1 是相邻的

地球联合政府准备挑选某些发动机在某些时刻进行 "手动启动"。当然最终所有的发动机都会被启动。哪些发动机最晚被启动呢？

**输入描述**：

第一行两个数字 N 和 E，中间有空格

- N 代表部署发动机的总个数，1 < N ≤ 1000
- E 代表计划手动启动的发动机总个数，1 ≤ E ≤ 1000，E ≤ N

接下来共 E 行，每行都是两个数字 T 和 P，中间有空格

- T 代表发动机的手动启动时刻，0 ≤ T ≤ N
- P 代表次发动机的位置编号，0 ≤ P < N

**输出描述**：

第一行一个数字 N， 以回车结束

- N 代表最后被启动的发动机个数

第二行 N 个数字，中间有空格，以回车结束

- 每个数字代表发动机的位置编号，从小到大排序

**用例 1**：

输入：

```
8 2
0 2
0 6
```

输出：

```
2
0 4
```

说明：

8 个发动机；
时刻 0 启动（2,6）;
时刻 1 启动（1,3,5,7）（其中 1,3 被 2 关联启动，5,7 被 6 关联启动）；
时刻 2 启动（0,4）（其中 0 被 1,7 关联启动，4 被 3,5 关联启动）；
至此所有发动机都被启动，最后被启动的有 2 个，分别是 0 和 4。

难度：困难

标签：数组、图、广度优先搜索、模拟

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, e;
  cin >> n >> e;

  // 发动机状态数组：是否启动、启动时间
  vector<bool> started(n, false);
  vector<int> start_time(n, -1);

  // 记录手动启动事件
  map<int, set<int> > manual_start_events;

  // 读取手动启动事件
  for (int i = 0; i < e; ++i) {
    int t, p;
    cin >> t >> p;
    manual_start_events[t].insert(p);
  }

  // 记录每个时刻的启动事件
  int max_start_time = 0;

  // 处理所有时刻的启动事件
  for (int t = 0; t <= n * 2; ++t) {
    // 手动启动事件
    // if (manual_start_events.contains(t)) {
    if (manual_start_events.find(t) != manual_start_events.end()) {
      for (int p : manual_start_events[t]) {
        if (!started[p]) {
          started[p] = true;
          start_time[p] = t;
          max_start_time = max(max_start_time, t);
        }
      }
    }

    // 关联启动
    vector<int> to_start;
    for (int i = 0; i < n; ++i) {
      if (!started[i]) {
        // 检查左右相邻发动机
        int left = (i - 1 + n) % n;
        int right = (i + 1) % n;

        // 左右任一已启动，则准备启动
        if (started[left] || started[right]) {
          to_start.push_back(i);
        }
      }
    }

    // 执行关联启动
    for (int p : to_start) {
      started[p] = true;
      start_time[p] = t + 1;
      max_start_time = max(max_start_time, t + 1);
    }
  }

  // 找出最后被启动的发动机
  vector<int> last_started;
  for (int i = 0; i < n; ++i) {
    if (start_time[i] == max_start_time) {
      last_started.push_back(i);
    }
  }

  cout << last_started.size() << endl;
  sort(last_started.begin(), last_started.end());
  for (int engine : last_started) {
    cout << engine << " ";
  }
  cout << endl;

  return 0;
}
```

#### 敏感字段加密

**题目描述**：

给定一个由多个命令字组成的命令字符串：

1. 字符串长度小于等于 127 字节，只包含大小写字母，数字，下划线和偶数个双引号；
2. 命令字之间以一个或多个下划线\_进行分割；
3. 可以通过两个双引号 "" 来标识包含下划线\_的命令字或空命令字（仅包含两个双引号的命令字），双引号不会在命令字内部出现；

请对指定索引的敏感字段进行加密，替换为 \*\*\*\*\*\*（6 个 \*），并删除命令字前后多余的下划线 \_。 如果无法找到指定索引的命令字，输出字符串 ERROR。

**输入描述**：

输入为两行，第一行为命令字索引 K（从 0 开始），第二行为命令字符串 S。

**输出描述**：

输出处理后的命令字符串，如果无法找到指定索引的命令字，输出字符串 ERROR

**用例 1**：

输入：

```
1
password__a12345678_timeout_100
```

输出：

```
password_******_timeout_100
```

**用例 2**：

输入：

```
2
aaa_password_"a12_45678"_timeout__100_""_
```

输出：

```
aaa_password_******_timeout_100_""
```

难度：中等

标签：字符串、模拟

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  int k;
  string s;
  cin >> k >> s;
  vector<string> commands;
  string current;
  bool in_quotes = false;

  for (char c : s) {
    if (c == '"') {
      // 只有在非引号状态，开始新的引导命令字
      if (!in_quotes) {
        // 如果当前有命令字，先加入
        if (!current.empty()) {
          commands.push_back(current);
          current.clear();
        }
        current += c;
      }
      // 已经在引号内，关闭引号
      else {
        current += c;
        commands.push_back(current);
        current.clear();
      }
      // 切换引号状态
      in_quotes = !in_quotes;
    }
    // 不在引号内处理下划线
    else if (!in_quotes && c == '_') {
      // 只有当前命令字非空时才加入
      if (!current.empty()) {
        commands.push_back(current);
        current.clear();
      }
    } else {
      current += c;
    }
  }
  // 处理最后一个命令字
  if (!current.empty()) {
    commands.push_back(current);
  }
  // 检查索引是否有效
  if (k < 0 || k >= commands.size()) {
    cout << "ERROR" << endl;
    return 0;
  }

  // 替换指定索引的命令字
  commands[k] = "******";
  // 重新构建字符串
  string result;
  for (int i = 0; i < commands.size(); ++i) {
    if (i > 0) {
      result += '_';
    }
    result += commands[i];
  }
  cout << result << endl;
  return 0;
}
```

#### TLV 解码

**题目描述**：

TLV 编码是按 [Tag Length Value] 格式进行编码的，一段码流中的信元用 Tag 标识，Tag 在码流中唯一不重复，Length 表示信元 Value 的长度，Value 表示信元的值。

码流以某信元的 Tag 开头，Tag 固定占一个字节，Length 固定占两个字节，字节序为小端序。

现给定 TLV 格式编码的码流，以及需要解码的信元 Tag，请输出该信元的 Value。

输入码流的 16 进制字符中，不包括小写字母，且要求输出的 16 进制字符串中也不要包含小写字母；码流字符串的最大长度不超过 50000 个字节。

**输入描述**：

- 输入的第一行为一个字符串，表示待解码信元的 Tag；
- 输入的第二行为一个字符串，表示待解码的 16 进制码流，字节之间用空格分隔。

**输出描述**：

- 输出一个字符串，表示待解码信元以 16 进制表示的 Value。

**用例 1**：

输入：

```
31
32 01 00 AE 90 02 00 01 02 30 03 00 AB 32 31 31 02 00 32 33 33 01 00 CC
```

输出：

```
32 33
```

说明：

需要解析的信元的 Tag 是 31，

从码流的起始处开始匹配，

第一个信元的 Tag 是 32，信元长度为 1（01 00，小端序表示为 1）；

第二个信元的 Tag 是 90，其长度为 2；

第三个信元的 Tag 是 30，其长度为 3；

第四个信元的 Tag 是 31，其长度为 2（02 00），

所以返回长度后面的两个字节即可，即 32 33。

难度：中等

标签：数组、字符串、位运算

(14/15)

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string target_tag, tlv_stream, token;
  vector<unsigned char> bytes;
  // 读取目标 tag
  getline(cin, target_tag);
  // 读取 TLV 码流并转换为字节数组
  getline(cin, tlv_stream);
  stringstream ss(tlv_stream);
  // 将 16 进制字符串转换为字节数组
  while (ss >> token) {
    bytes.push_back(stoi(token, nullptr, 16));
  }
  // 将目标 tag 转换为数值
  unsigned char tag = stoi(target_tag, nullptr, 16);

  // 遍历码流
  for (size_t i = 0; i < bytes.size();) {
    // 当前信元的 tag
    unsigned char current_tag = bytes[i];
    // 检查是否匹配目标 tag
    if (current_tag == tag) {
      // 小端序读取长度（两个字节）
      unsigned short length = bytes[i + 2] * 256 + bytes[i + 1];
      // 输出对应的 value
      for (size_t j = i + 3; j < i + 3 + length; ++j) {
        cout << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(
          bytes[j]);
        // 最后一个字节不加空格
        if (j < i + 2 + length) {
          cout << " ";
        }
      }
      cout << endl;
      // 成功找到并输出后直接退出
      return 0;
    }
    // 小端序读取长度
    unsigned short length = bytes[i + 2] * 256 + bytes[i + 1];
    // 移动到下一个信元
    i += 3 + length;
  }
  return 0;
}
```

#### 手机 App 防沉迷系统

**题目描述**：

智能手机方便了我们生活的同时，也侵占了我们不少的时间。

"手机 App 防沉迷系统" 能够让我们每天合理地规划手机 App 使用时间，在正确的时间做正确的事。

它的大概原理是这样的：

1. 在一天 24 小时内，可以注册每个 App 的允许使用时段 ![image](https://hydro.ac/d/HWOD2023/p/413/file/1jJgJ9z8n1lkTtsP74WvM.png)

2. 一个时间段只能使用一个 App，举例说明：不能同时在 9:00-10:00 注册 App2 和 App3 ![image](https://hydro.ac/d/HWOD2023/p/413/file/Yl1eXCM07dQINo5Bid_I6.png)

3. App 有优先级，数值越高，优先级越高。注册使用时段时，如果高优先级的 App 时间和低优先级的时段有冲突，则系统会自动注销低优先级的时段，如果 App 的优先级相同，则后添加的 App 不能注册。

   举例 1：

   1. 注册 App3 前 ![image](https://hydro.ac/d/HWOD2023/p/413/file/O7exD1gJHTpKYzpfMs0hz.png)
   2. App3 注册时段和 App2 有冲突 ![image](https://hydro.ac/d/HWOD2023/p/413/file/7BAxn4dCGlYxZBRGU1bCf.png)
   3. App3 优先级高，系统接受 App3 的注册，自动注销 App2 的注册 ! [image](https://hydro.ac/d/HWOD2023/p/413/file/2Cs7XMOF0hXJXV9bTH1o1.png

举例 2：

1. 注册 App4 ![image](https://hydro.ac/d/HWOD2023/p/413/file/DUqee-wcSw5UZlsG22ft9.png)
2. App4 和 App2 及 App3 都有冲突，优先级比 App2 高，但比 App3 低，这种场景下 App4 注册不上，最终的注册效果如下 ![image](https://hydro.ac/d/HWOD2023/p/413/file/2ENHqcC-5gnIiyhbegQIn.png)

3. 一个 App 可以在一天内注册多个时段 ![image](https://hydro.ac/d/HWOD2023/p/413/file/0uizC1CHqpz3kBQECPU21.png)

请编程实现，根据输入数据注册 App，并根据输入的时间点，返回时间点使用的 App 名称，如果该时间点没有注册任何 App，请返回字符串 "NA"。

**输入描述**：

第一行表示注册的 App 数量 N（N ≤ 100）

第二部分包括 N 行，每行表示一条 App 注册数据

最后一行输入一个时间点，程序即返回该时间点使用的 App

```
2
App1 1 09:00 10:00
App2 2 11:00 11:30
09:30
```

数据说明如下：

1. N 行注册数据以空格分隔，四项数依次表示：App 名称、优先级、起始时间、结束时间
2. 优先级 1~5，数字越大，优先级越高
3. 时间格式 HH: MM，小时和分钟都是两位，不足两位前面补 0
4. 起始时间需小于结束时间，否则注册不上
5. 注册信息中的时间段包含起始时间点，不包含结束时间点

**输出描述**：

输出一个字符串，表示 App 名称，或 NA 表示空闲时间

备注：

- 用例保证时间都介于 00:00 - 24:00 之间；
- 用例保证数据格式都是正确的，不用考虑数据输入行数不够、注册信息不完整、字符串非法、优先级超限、时间格式不正确的问题；

**用例 1**：

输入：

```
1
App1 1 09:00 10:00
09:30
```

输出：

```
App1
```

说明：

App1 注册在 9 点到 10 点间，9 点半可用的应用名是 App1

**用例 2**：

输入：

```
2
App1 1 09:00 10:00
App2 2 09:10 09:30
09:20
```

输出：

```
App2
```

**用例 3**：

输入：

```
2
App1 1 09:00 10:00
App2 2 09:10 09:30
09:50
```

输出：

```
NA
```

难度：中等

标签：数组、设计

```cpp
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
```

#### 字符串分割

**题目描述**：

给定一个非空字符串 S，其被 N 个 '-' 分隔成 N+1 的子串，给定正整数 K，要求除第一个子串外，其余的子串每 K 个字符组成新的子串，并用 '-' 分隔。

对于新组成的每一个子串，如果它含有的小写字母比大写字母多，则将这个子串的所有大写字母转换为小写字母；

反之，如果它含有的大写字母比小写字母多，则将这个子串的所有小写字母转换为大写字母；大小写字母的数量相等时，不做转换。

**输入描述**：

输入为两行，第一行为参数 K，第二行为字符串 S。

**输出描述**：

输出转换后的字符串。

**用例 1**：

输入：

```
3
12abc-abCABc-4aB@
```

输出：

```
12abc-abc-ABC-4aB-@
```

说明：

子串为 12abc、abCABc、4aB@，第一个子串保留，

后面的子串每 3 个字符一组为 abC、ABc、4aB、@，

abC 中小写字母较多，转换为 abc，

ABc 中大写字母较多，转换为 ABC，

4aB 中大小写字母都为 1 个，不做转换，

@ 中没有字母，连起来即 12abc-abc-ABC-4aB-@

**用例 2**：

输入：

```
12
12abc-abCABc-4aB@
```

输出：

```
12abc-abCABc4aB@
```

说明：

子串为 12abc、abCABc、4aB@，第一个子串保留，

后面的子串每 12 个字符一组为 abCABc4aB@，

这个子串中大小写字母都为 4 个，不做转换，

连起来即 12abc-abCABc4aB@

难度：中等

标签：字符串

```cpp
#include <bits/stdc++.h>

using namespace std;

void convert(string& s) {
  int lower_count = 0;
  int upper_count = 0;

  for (const auto& c : s) {
    if (islower(c)) lower_count++;
    else if (isupper(c)) upper_count++;
  }

  if (lower_count > upper_count) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
  } else if (lower_count < upper_count) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
  }
}

int main() {
  int k;
  string s;
  cin >> k;
  cin >> s;
  // 存储最终结果
  string result;
  // 第一步：按 '-' 分割字符串
  stringstream ss(s);
  string token, new_str;
  // 处理第一个子串的标志
  bool first = true;
  // 分割并处理子串
  while (getline(ss, token, '-')) {
    if (first) {
      // 第一个子串直接保留
      result += token;
      first = false;
    } else {
      // 合并后续子串
      new_str += token;
    }
  }
  // 处理后续子串
  for (size_t i = 0; i < new_str.size(); i += k) {
    // 获取 K 个字符的子串
    string group = new_str.substr(i, k);
    // 转换大小写
    convert(group);
    // 添加分隔符和处理后的子串
    result += "-" + group;
  }
  cout << result << endl;
  return 0;
}
```

#### 英文输入法

**题目描述**：

主管期望你来实现英文输入法单词联想功能。

需求如下：

- 依据用户输入的单词前缀，从已输入的英文语句中联想出用户想输入的单词，按字典序输出联想到的单词序列，
- 如果联想不到，请输出用户输入的单词前缀。

注意：

1. 英文单词联想时，区分大小写
2. 缩略形式如 "don't"，判定为两个单词，"don" 和 "t "
3. 输出的单词序列，不能有重复单词，且只能是英文单词，不能有标点符号

**输入描述**：

输入为两行。

首行输入一段由英文单词 word 和标点符号组成的语句 str；

接下来一行为一个英文单词前缀 pre。

- 0 < word.length() <= 20
- 0 < str.length <= 10000
- 0 < pre <= 20

**输出描述**：

输出符合要求的单词序列或单词前缀，存在多个时，单词之间以单个空格分割

**用例 1**：

输入：

```
I love you
He
```

输出：

```
He
```

说明：

从用户已输入英文语句 "I love you" 中提炼出 "I"、"love"、"you" 三个单词，接下来用户输入 "He"，

从已输入信息中无法联想到任何符合要求的单词，因此输出用户输入的单词前缀。

**用例 2**：

输入：

```
The furthest distance in the world, Is not between life and death, But when I stand in front of you, Yet you don't know that I love you.
f
```

输出：

```
front furthest
```

难度：中等

标签：字符串

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string sentence, prefix;
  getline(cin, sentence);
  cin >> prefix;
  // 使用 set 自动去重
  set<string> unique_words;
  string current_word;
  // 分割句子为单词，特别处理带撇号的单词
  for (char c : sentence) {
    if (isalpha(c) || c == '\'') {
      current_word += c;
    } else {
      if (!current_word.empty()) {
        // 特殊处理带撇号的单词
        if (current_word.find('\'') != string::npos) {
          size_t pos = current_word.find('\'');
          string first = current_word.substr(0, pos);
          string second = current_word.substr(pos + 1);
          // 确保非空的单词被添加
          if (!first.empty()) unique_words.insert(first);
          if (!second.empty()) unique_words.insert(second);
        } else {
          unique_words.insert(current_word);
        }
        current_word.clear();
      }
    }
  }
  // 添加最后一个单词
  if (!current_word.empty()) {
    if (current_word.find('\'') != string::npos) {
      size_t pos = current_word.find('\'');
      string first = current_word.substr(0, pos);
      string second = current_word.substr(pos + 1);
      if (!first.empty()) unique_words.insert(first);
      if (!second.empty()) unique_words.insert(second);
    } else {
      unique_words.insert(current_word);
    }
  }
  // 查找匹配前缀的单词
  vector<string> matched_words;
  // 查找以前缀开头的单词
  for (const auto& w : unique_words) {
    // 单词开头匹配
    // 添加长度检查，避免substr越界
    if (w.length() >= prefix.length() && w.substr(0, prefix.length()) ==
        prefix) {
      matched_words.push_back(w);
    }
  }
  // 去重
  sort(matched_words.begin(), matched_words.end());
  matched_words.erase(unique(matched_words.begin(), matched_words.end()),
                     matched_words.end());
  // 只在没有找到任何匹配时，输出前缀
  if (matched_words.empty()) {
    cout << prefix << endl;
  } else {
    // 输出结果
    for (size_t i = 0; i < matched_words.size(); ++i) {
      cout << matched_words[i];
      if (i < matched_words.size() - 1) cout << " ";
    }
    cout << endl;
  }
  return 0;
}
```

#### 连续字母长度

**题目描述**：

给定一个字符串，只包含大写字母，求在包含同一字母的子串中，长度第 k 长的子串的长度，相同字母只取最长的那个子串。

**输入描述**：

第一行有一个子串(1 < 长度 <= 100)，只包含大写字母。

第二行为 k 的值

**输出描述**：

输出连续出现次数 **第 k 多** 的字母的次数。

**用例 1**：

输入：

```
AAAAHHHBBCDHHHH
3
```

输出：

```
2
```

说明：

同一字母连续出现的最多的是 A 和 H，四次；

第二多的是 H，3 次，但是 H 已经存在 4 个连续的，故不考虑；

下个最长子串是 BB，所以最终答案应该输出 2。

**用例 2**：

输入：

```
AABAAA
2

```

输出：

```
1
```

说明：

同一字母连续出现的最多的是 A，三次；

第二多的还是 A，两次，但 A 已经存在最大连续次数三次，故不考虑；

下个最长子串是 B，所以输出 1。

**用例 3**：

输入：

```
ABC
4
```

输出：

```
-1
```

说明：

只含有 3 个包含同一字母的子串，小于 k，输出-1

**用例 4**：

输入：

```
ABC
2
```

输出：

```
1
```

说明：

三个子串长度均为 1，所以此时 k = 1，k = 2，k = 3 这三种情况均输出 1。特此说明，避免歧义。

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  // 读取输入字符串和 k 值
  string s;
  int k;
  cin >> s >> k;
  // 特殊情况处理：字符串长度小于等于1
  if (s.length() <= 1) {
    cout << 1 << endl;
    return 0;
  }
  if (k >= 26 || k <= 0) {
    cout << "-1" << endl;
    return 0;
  }
  // 存储每个字母最大出现次数
  unordered_map<char, int> max_lengths;
  // 遍历字符串，统计每个字母的最大连续长度
  for (int i = 0; i < s.length();) {
    char current_char = s[i];
    int count = 0;
    // 统计当前字母的连续出现次数
    while (i < s.length() && s[i] == current_char) {
      count++;
      i++;
    }
    // 更新对应字母的最大长度
    if (max_lengths.find(current_char) == max_lengths.end()) {
      max_lengths[current_char] = count;
    } else {
      max_lengths[current_char] = max(max_lengths[current_char], count);
    }
  }
  // 存储所有不同的最长长度
  vector<int> lengths;
  for (auto& entry : max_lengths) {
    lengths.push_back(entry.second);
  }
  // 对长度进行排序，降序
  sort(lengths.begin(), lengths.end(), greater<int>());
  // 处理 k 大于有效长度数量的情况
  if (k > lengths.size()) {
    cout << -1 << endl;
    return 0;
  }
  // 选择第 k 大的长度并输出
  cout << lengths[k - 1] << endl;
  return 0;
}
```

#### 考勤信息

**题目描述**：

公司用一个字符串来表示员工的出勤信息

- absent：缺勤
- late：迟到
- leaveearly：早退
- present：正常上班

现需根据员工出勤信息，判断本次是否能获得出勤奖，能获得出勤奖的条件如下：

- 缺勤不超过一次；
- 没有连续的迟到/早退；
- 任意连续 7 次考勤，缺勤/迟到/早退不超过 3 次。

**输入描述**：

用户的考勤数据字符串

- 记录条数 >= 1；
- 输入字符串长度 < 10000；
- 不存在非法输入；

**输出描述**：

根据考勤数据字符串，如果能得到考勤奖，输出 "true"；否则输出 "false"。

**用例 1**：

输入：

```
2
present
present present
```

输出：

```
true true
```

**用例 2**：

输入：

```
2
present
present absent present present leaveearly present absent
```

输出：

```
true false
```

难度：中等

标签：数组、字符串、滑动窗口

```cpp
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
```

#### 字符串变换最小字符串

**题目描述**：

给定一个字符串 s，最多只能进行一次变换，返回变换后能得到的最小字符串（按照字典序进行比较）。

变换规则：交换字符串中任意两个不同位置的字符。

**输入描述**：

一串小写字母组成的字符串 s

**输出描述**：

一串小写字母组成的字符串 s

备注:

- s 是都是小写字符组成
- 1 ≤ s.length ≤ 1000

**用例 1**：

输入：

```
abcdef
```

输出：

```
abcdef
```

说明：abcdef 已经是最小字符串，不需要交换。

**用例 2**：

输入：

```
bcdefa
```

输出：

```
acdefb
```

说明：a 和 b 进行位置交换，可以得到最小字符串

难度：中等

标签：贪心、字符串、排序

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  cin >> input; // 读取输入字符串S
  string result = input; // 初始化结果为原字符串
  // 遍历字符串的每一个字符
  for (int i = 0; i < input.length(); ++i) {
    // 在当前字符后寻找可以交换的最小字符
    for (int j = i + 1; j < input.length(); ++j) {
      // 检查是否需要进行交换
      if (input[j] < input[i]) {
        // 交换后构造新的序列
        string new_string = input;
        swap(new_string[i], new_string[j]);
        // 如果新的字符串字典序更小，则更新结果
        if (new_string < result) {
          result = new_string;
        }
      }
    }
  }

  // 输出变换后的最小字符串
  cout << result << endl;
  return 0;
}
```

#### 整数对最小和

**题目描述**：

给定两个整数数组 array1、array2，数组元素按升序排列。

假设从 array1、array2 中分别取出一个元素可构成一对元素，现在需要取出 k 对元素，

并对取出的所有元素求和，计算和的最小值。

注意：

两对元素如果对应于 array1、array2 中的两个下标均相同，则视为同一对元素

**输入描述**：

输入两行数组 array1、array2，每行首个数字为数组大小 size(0 < size <= 100);

0 < array1 [i] <= 1000

0 < array2 [i] <= 1000

接下来一行为正整数 k

0 < k <= array1.size() \* array2.size()

**输出描述**：

满足要求的最小和

**用例 1**：

输入：

```
3 1 1 2
3 1 2 3
2
```

输出：

```
4
```

说明：

用例中，需要取 2 对元素

取第一个数组第 0 个元素与第二个数组第 0 个元素组成 1 对元素 [1,1];

取第一个数组第 1 个元素与第二个数组第 0 个元素组成 1 对元素 [1,1];

求和为 1+1+1+1 = 4，为满足要求的最小和。

难度：中等

标签：堆（优先队列）、数组

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  int size1, size2;
  cin >> size1;
  vector<int> array1(size1);
  for (int i = 0; i < size1; ++i) {
    cin >> array1[i];
  }
  cin >> size2;
  vector<int> array2(size2);
  for (int i = 0; i < size2; ++i) {
    cin >> array2[i];
  }
  int k;
  cin >> k;
  // 最小堆来存储元素对及其对应的和
  priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >
                 , greater<pair<int, pair<int, int> > > > min_heap;
  // 将所有可能的初始对放入堆中
  for (int i = 0; i < size1; ++i) {
    // 先将每个 array1 的元素与 array2 的第一个元素配对
    min_heap.push({array1[i] + array2[0], {i, 0}});
  }
  int min_sum = 0;
  // 取出 k 对
  for (int count = 0; count < k; ++count) {
    auto current_pair = min_heap.top();
    min_heap.pop();
    min_sum += current_pair.first; // 加上当前最小和
    int index1 = current_pair.second.first;
    int index2 = current_pair.second.second;
    // 如果当前对的第二个元素还有更多可能的配对，进行入堆
    if (index2 + 1 < size2) {
      min_heap.push({array1[index1] + array2[index2 + 1],
                     {index1, index2 + 1}});
    }
  }
  cout << min_sum << endl;
  return 0;
}
```

#### 计算面积

**题目描述**：

绘图机器的绘图笔初始位置在原点(0,0)机器启动后按照以下规则来进行绘制直线。

1. 尝试沿着横线坐标正向绘制直线直到给定的终点 E
2. 期间可以通过指令在纵坐标轴方向进行偏移，offsetY 为正数表示正向偏移, 为负数表示负向偏移

给定的横坐标终点值 E 以及若干条绘制指令，

请计算绘制的直线和横坐标轴以及 x = E 的直线组成的图形面积。

**输入描述**：

首行为两个整数 N 和 E

表示有 N 条指令, 机器运行的横坐标终点值 E

接下来 N 行 每行两个整数表示一条绘制指令 x offsetY

用例保证横坐标 x 以递增排序的方式出现

且不会出现相同横坐标 x

取值范围

- 0 < N <= 10000
- 0 <= x <= E <= 20000
- -10000 <= offsetY <= 10000

**输出描述**：

一个整数表示计算得到的面积 用例保证结果范围在 0 到 4294967295 之内。

**用例 1**：

输入：

```
4 10
1 1
2 1
3 1
4 -2
```

输出：

```
12
```

**用例 2**：

输入：

```
2 4
0 1
2 -2
```

输出：

```
4
```

难度：中等

标签：几何、数学

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, e;
  cin >> n >> e;
  // 存储指令
  vector<pair<int, int> > instructions(n + 1);
  // 添加起点 (0, 0)
  instructions[0] = {0, 0};
  for (int i = 1; i <= n; ++i) {
    cin >> instructions[i].first >> instructions[i].second;
  }
  // 计算面积
  int area = 0, current_y = 0;
  // 遍历指令计算面积
  for (int i = 1; i <= n; ++i) {
    // 计算当前区域的宽度
    int width = instructions[i].first - instructions[i - 1].first;
    // 使用上一个点的纵坐标
    area += width * abs(current_y);
    // 更新当前纵坐标
    current_y += instructions[i].second;
  }
  // 处理最后一个点到终点 e 的区间
  area += (e - instructions[n].first) * abs(current_y);
  cout << area << endl;
  return 0;
}
```

#### 响应报文时间

**题目描述**：

IGMP 协议中，有一个字段称作最大响应时间 (Max Response Time) ，HOST 收到查询报文，解折出 MaxResponsetime 字段后，需要在 (0，MaxResponseTime] 时间 (s) 内选取随机时间回应一个响应报文，如果在随机时间内收到一个新的查询报文，则会根据两者时间的大小，选取小的一方刷新回应时间。

最大响应时间有如下计算方式：

- 当 Max Resp Code < 128, Max Resp Time = Max Resp Code；
- 当 Max Resp Code ≥ 128,

![image](https://hydro.ac/d/HWOD2023/p/176/file/nkb_h5V9315GCAucikXq3.png)

> Max Resp Time = (mant | 0x10) << (exp + 3)；

注: exp 最大响应时间的高 5~7 位: mant 为最大响应时间的低 4 位。

其中接收到的 MaxRespCode 最大值为 255，以上出现所有字段均为无符号数。

现在我们认为 HOST 收到查询报文时，选取的随机时间必定为最大值，现给出 HOST 收到查询报文个数 C，HOST 收到该报文的时间 T，以及查询报文的最大响应时间字段值 M，请计算出 HOST 发送响应报文的时间。

**输入描述**：

第一行为查询报文个数 C，后续每行分别为 HOST 收到报文时间 T，及最大响应时间 M，以空格分割。

**输出描述**：

HOST 发送响应报文的时间。

用例确定只会发送一个响应报文， 不存在计时结束后依然收到查询报文的情况。

**用例 1**：

输入：

```
3
0 20
1 10
8 20
```

输出：

```
11
```

说明：

收到 3 个报文，

第 0 秒收到第 1 个报文，响应时间为 20 秒，则要到 0+20 = 20 秒响应；

第 1 秒收到第 2 个报文，响应时间为 10 秒，则要到 1+10 = 11 秒响应，与上面的报文的响应时间比较获得响应时间最小为 11 秒；

第 8 秒收到第 3 个报文，响应时间为 20 秒，则要到 8+20 = 28 秒响应，与第上面的报文的响应时间比较获得响应时间最小为 11 秒；

最终得到最小响应报文时间为 11 秒

**用例 2**：

输入：

```
2
0 255
200 60
```

输出：

```
260
```

说明：

收到 2 个报文，

第 0 秒收到第 1 个报文，响应时间为 255 秒，则要到(15 | 0x10) << (7 + 3)= 31744 秒响应; (mant = 15，exp = 7)

第 200 秒收到第 2 个报文，响应时间为 60 秒，则要到 200+60-260 秒响应，与第上面的报文的响应时间比较获得响应时间最小为 260 秒:

最终得到最小响应报文时间为 260 秒

难度：困难

标签：位运算

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  int c;
  cin >> c;
  // 记录最小响应时间
  int min_resp_time = INT_MAX;
  // 处理每个报文
  for (int i = 0; i < c; ++i) {
    int t, m;
    cin >> t >> m;
    // 计算最大响应时间
    int resp_time;
    if (m < 128) {
      // 直接使用 m 为响应时间
      resp_time = t + m;
    } else {
      int exp = m >> 4 & 0x07; // 高 5~7 位
      int mant = m & 0x0f;     // 低 4 位
      // 按照公式计算
      resp_time = t + ((mant | 0x10) << exp + 3);
    }
    // 更新最小响应时间
    min_resp_time = min(min_resp_time, resp_time);
  }
  cout << min_resp_time << endl;
  return 0;
}
```

#### 跳房子 I

**题目描述**：

跳房子，也叫跳飞机，是一种世界性的儿童游戏。

游戏参与者需要分多个回合按顺序跳到第 1 格直到房子的最后一格。

跳房子的过程中，可以向前跳，也可以向后跳。

假设房子的总格数是 count，小红每回合可能连续跳的步教都放在数组 steps 中，请问数组中是否有一种步数的组合，可以让小红两个回合跳到量后一格?

如果有，请输出索引和最小的步数组合。

注意：

- 数组中的步数可以重复，但数组中的元素不能重复使用。
- 提供的数据保证存在满足题目要求的组合，且索引和最小的步数组合是唯一的。

**输入描述**：

第一行输入为房子总格数 count，它是 int 整数类型。 第二行输入为每回合可能连续跳的步数，它是 int 整数数组类型。

**输出描述**：

返回索引和最小的满足要求的步数组合（顺序保持 steps 中原有顺序）

- count ≤ 1000
- 0 ≤ steps.length ≤ 5000
- -100000000 ≤ steps ≤ 100000000

**用例 1**：

输入：

```
[1,4,5,2,2]
7
```

输出：

```
[5, 2]
```

**用例 2**：

输入：

```
[-1,2,4,9,6]
8
```

输出：

```
[-1, 9]
```

此样例有多种组合满足两回合跳到最后，譬如：[-1,9], [2,6]，其中 [-1,9] 的索引和为 0 + 3 = 3，[2,6] 的索和为 1 + 4 = 5，所以索引和最小的步数组合 [-1,9]

难度：中等

标签：数组

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string line;
  getline(cin, line);
  line = line.substr(1, line.length() - 2);
  // 解析步数
  vector<int> steps;
  stringstream ss(line);
  string num;
  while (getline(ss, num, ',')) {
    steps.push_back(stoi(num));
  }
  int count;
  cin >> count;
  // 记录最终结果的索引
  int result_index1 = 0, result_index2 = 0;
  // 记录最小索引和
  int min_index_sum = INT_MAX;
  // 遍历所有可能的两个步数之和
  for (int i = 0; i < steps.size(); ++i) {
    for (int j = 0; j < steps.size(); ++j) {
      // 忽略相同索引的组合
      if (i == j) continue;
      // 判断两个步数是否可以跳到目标格数
      if (steps[i] + steps[j] == count) {
        // 当前索引和
        int current_index_sum = i + j;
        // 更新最小索引和
        if (current_index_sum < min_index_sum) {
          min_index_sum = current_index_sum;
          result_index1 = steps[i];
          result_index2 = steps[j];
        }
      }
    }
  }
  cout << "[" << result_index1 << ", " << result_index2 << "]" <<
      endl;
  return 0;
}
```

#### 数组拼接

**题目描述**：

现在有多组整数数组，需要将它们合并成一个新的数组。

合并规则，从每个数组里按顺序取出固定长度的内容合并到新的数组中，取完的内容会删除掉，如果该行不足固定长度或者已经为空，则直接取出剩余部分的内容放到新的数组中，继续下一行。

**输入描述**：

第一行是每次读取的固定长度，0 < 长度 < 10

第二行是整数数组的数目，0 < 数目 < 1000

第 3-n 行是需要合并的数组，不同的数组用回车换行分隔，数组内部用逗号分隔，最大不超过 100 个元素。

**输出描述**：

输出一个新的数组，用逗号分隔。

**用例 1**：

输入：

```
3
2
2,5,6,7,9,5,7
1,7,4,3,4
```

输出：

```
2,5,6,1,7,4,7,9,5,3,4,7
```

说明：

1. 获得长度 3 和数组数目 2
2. 先遍历第一行，获得 2,5,6
3. 再遍历第二行，获得 1,7,4
4. 再循环回到第一行，获得 7,9,5
5. 再遍历第二行，获得 3,4
6. 再回到第一行，获得 7，按顺序拼接成最终结果

**用例 2**：

输入：

```
4
3
1,2,3,4,5,6
1,2,3
1,2,3,4
```

输出：

```
1,2,3,4,1,2,3,1,2,3,4,5,6
```

难度：中等

标签：数组、字符串、链表、队列

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  int k;
  cin >> k;
  int n;
  cin >> n;
  cin.ignore();
  // 存储输入数组
  vector<vector<int> > arrays(n);
  // 读取数组
  for (int i = 0; i < n; ++i) {
    string line;
    getline(cin, line);
    stringstream ss(line);
    string num;
    while (getline(ss, num, ',')) {
      // 跳过空字符串
      if (!num.empty()) {
        arrays[i].push_back(stoi(num));
      }
    }
  }
  // 存储结果的数组
  vector<int> result;
  // 记录每个数组的当前索引
  vector<int> indices(n, 0);
  // 标记是否仍有未处理完的数组
  bool has_remaining = true;
  // 循环知道所有数组处理完毕
  while (has_remaining) {
    has_remaining = false;
    // 遍历每个数组
    for (int i = 0; i < n; ++i) {
      // 当前数组还有元素
      if (indices[i] < arrays[i].size()) {
        has_remaining = true;
        // 尝试读取 k 个元素
        int count = 0;
        while (count < k && indices[i] < arrays[i].size()) {
          result.push_back(arrays[i][indices[i]]);
          indices[i]++;
          count++;
        }
      }
    }
  }
  for (int i = 0; i < result.size(); ++i) {
    cout << result[i];
    if (i < result.size() - 1) {
      cout << ',';
    }
  }
  cout << endl;
  return 0;
}
```

#### 最长子字符串的长度(一)

**题目描述**：

给你一个字符串 s，首尾相连成一个环形，请你在环中找出 'o' 字符出现了偶数次最长子字符串的长度。

**输入描述**：

输入是一个小写字母组成的字符串

**输出描述**：

输出是一个整数

- 1 ≤ s.length ≤ 500000
- s 只包含小写英文字母

**用例 1**：

输入：

```
alolobo
```

输出：

```
6
```

说明：最长子字符串之一是 "alolob"，它包含 2 个'o'

**用例 2**：

输入：

```
looxdolx
```

输出：

```
7
```

最长子字符串 "oxdolxl"，由于是首尾连接一起的，所以最后一个'x'和开头的'l'是连接在一起的，此字符串包含 2 个'o'

**用例 3**：

输入：

```
bcbcbc
```

输出：

```
6
```

这个示例中，字符串 "bcbcbc" 本身就是最长的，因为'o'都出现了 0 次。

难度：中等

标签：字符串、滑动窗口、脑筋急转弯、前缀和、哈希表

(18/23) 5 个超时

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string s;
  cin >> s;
  // 处理空字符串
  if (s.empty()) {
    cout << 0 << endl;
    return 0;
  }
  // 扩展字符串，模拟环形
  s += s;
  int n = s.size() / 2;
  int max_len = 0;
  // 遍历所有可能的子字符串
  for (int i = 0; i < n; ++i) {
    int o_count = 0;
    int current_len = 0;
    // 从当前位置开始统计
    for (int j = i; j < i + n; ++j) {
      // 统计 'o' 字符数量
      if (s[j] == 'o') {
        o_count++;
      }
      current_len++;
      // 如果 'o' 数量为偶数，更新最大长度
      if (o_count % 2 == 0) {
        max_len = max(max_len, current_len);
      }
    }
  }
  cout << max_len << endl;
  return 0;
}
```

找规律，100%

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  // 读取输入字符串
  string s;
  cin >> s;

  // 统计 'o' 的数量
  int o_count = 0;
  for (char c : s) {
    if (c == 'o') {
      o_count++;
    }
  }

  // 根据 'o' 数量的奇偶性返回结果
  cout << (o_count % 2 == 0 ? s.length() : s.length() - 1) << endl;

  return 0;
}
```

#### 判断一组不等式是否满足约束并输出最大差

**题目描述**：

给定一组不等式，判断是否成立并输出不等式的最大差(输出浮点数的整数部分)

要求:

1. 不等式系数为 double 类型，是一个二维数组
2. 不等式的变量为 int 类型，是一维数组;
3. 不等式的目标值为 double 类型，是一维数组
4. 不等式约束为字符串数组，只能是: ">", ">=", "<", "<=", "="，

例如，不等式组:

```none
a11x1+a12x2+a13x3+a14x4+a15x5<=b1;
a21x1+a22x2+a23x3+a24x4+a25x5<=b2;
a31x1+a32x2+a33x3+a34x4+a35x5<=b3;
最大差 = max{(a11x1+a12x2+a13x3+a14x4+a15x5-b1),(a21x1+a22x2+a23x3+a24x4+ a25x5-b2),(a31x1+a32x2+a33x3+a34x4+a35x5-b3)},
```

类型为整数(输出浮点数的整数部分)

**输入描述**：

a11, a12, a13, a14, a15, a21, a22, a23, a24, a25, a31, a32, a33, a34, a35, x1, x2, x3, x4, x5, b1, b2, b3,<=,<=,<=

1. 不等式组系数(double 类型):

   a11, a12, a13, a14, a15

   a21, a22, a23, a24, a25

   a31, a32, a33, a34, a35

2. 不等式变量(int 类型): x1, x2, x3, x4, x5

3. 不等式目标值(double 类型): b1, b2, b3

4. 不等式约束(字符串类型):<=,<=,<=

**输出描述**：

true 或者 false，最大差

**用例 1**：

输入：

```
2.3,3,5.6,7,6;11,3,8.6,25,1;0.3,9,5.3,66,7.8;1,3,2,7,5;340,670,80.6;<=,<=,<=
```

输出：

```
false 458
```

**用例 2**：

输入：

```
2.36,3,6,7.1,6;1,30,8.6,2.5,21;0.3,69,5.3,6.6,7.8;1,13,2,17,5;340,67,300.6;<=,>=,<=
```

输出：

```
false 758
```

难度：中等

标签：字符串、数学

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);

  // 存储解析后的数据
  vector<vector<double> > coefficients(3, vector<double>(5));
  vector<int> variables(5);
  vector<double> target_values(3);
  vector<string> constraints(3);

  // 使用 stringstream 处理输入
  stringstream ss(input);
  string section;

  // 解析系数矩阵
  for (int i = 0; i < 3; i++) {
    getline(ss, section, ';');
    stringstream coeff_ss(section);
    string coeff;
    int j = 0;
    while (getline(coeff_ss, coeff, ',')) {
      coefficients[i][j++] = stod(coeff);
    }
  }

  // 解析变量
  getline(ss, section, ';');
  stringstream var_ss(section);
  string var;
  int j = 0;
  while (getline(var_ss, var, ',')) {
    variables[j++] = stoi(var);
  }

  // 解析目标值
  getline(ss, section, ';');
  stringstream target_ss(section);
  j = 0;
  while (getline(target_ss, var, ',')) {
    target_values[j++] = stod(var);
  }

  // 解析约束条件
  getline(ss, section, ';');
  stringstream constraint_ss(section);
  j = 0;
  while (getline(constraint_ss, var, ',')) {
    constraints[j++] = var;
  }

  // 检查不等式并计算最大差
  bool all_satisfied = true;
  double max_difference = -numeric_limits<double>::max();

  for (int i = 0; i < 3; i++) {
    // 计算左边表达式的值
    double left_side = 0.0;
    for (int j = 0; j < 5; j++) {
      left_side += coefficients[i][j] * variables[j];
    }

    // 检查不等式是否满足
    bool satisfied = false;
    double difference = left_side - target_values[i]; // 计算差异

    if (constraints[i] == "<=") satisfied = left_side <= target_values[i];
    else if (constraints[i] == "<") satisfied = left_side < target_values[i];
    else if (constraints[i] == ">=") satisfied = left_side >= target_values[i];
    else if (constraints[i] == ">") satisfied = left_side > target_values[i];
    else if (constraints[i] == "=")
      satisfied = abs(left_side - target_values[i]) < 1e-9;

    if (!satisfied) {
      all_satisfied = false;
    }

    // 更新最大差值
    max_difference = max(max_difference, difference); // 最大差的绝对值
  }

  // 输出结果
  cout << (all_satisfied ? "true" : "false") << " "
      << static_cast<int>(max_difference) << endl;

  return 0;
}
```

#### 找终点

**题目描述**：

给定一个正整数数组，设为 nums，最大为 100 个成员，求从第一个成员开始，正好走到数组最后一个成员，所使用的最少步骤数。

要求：

1. 第一步必须从第一元素开始，且 1 <= 第一步的步长 < len/2;（len 为数组的长度，需要自行解析）。
2. 从第二步开始，只能以所在成员的数字走相应的步数，不能多也不能少, 如果目标不可达返回-1，只输出最少的步骤数量。
3. 只能向数组的尾部走，不能往回走。

**输入描述**：

由正整数组成的数组，以空格分隔，数组长度小于 100，请自行解析数据数量。

**输出描述**：

正整数，表示最少的步数，如果不存在输出-1

**用例 1**：

输入：

```
7 5 9 4 2 6 8 3 5 4 3 9
```

输出：

```
2
```

说明：

第一步： 第一个可选步长选择 2，从第一个成员 7 开始走 2 步，到达 9；

第二步： 从 9 开始，经过自身数字 9 对应的 9 个成员到最后。

**用例 2**：

输入：

```
1 2 3 7 1 5 9 3 2 1
```

输出：

```
-1
```

难度：中等

标签：数组

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);
  vector<int> nums;
  int num;
  stringstream ss(input);
  while (ss >> num) {
    nums.push_back(num);
  }
  int n = nums.size();
  // 如果数组为空或者仅有一个元素，无法移动
  if (n <= 1) {
    cout << -1 << endl;
    return 0;
  }
  int min_steps = INT_MAX;
  // 尝试所有可能的第一步步长
  for (int first_step = 0; first_step < n / 2; ++first_step) {
    // 第一步的目标位置
    int current_pos = first_step;
    // 如果第一步已经越界，则跳过
    if (current_pos >= n) {
      break;
    }
    // 步数计数器
    int steps = 1;
    // 继续移动直到达成越界
    while (current_pos < n - 1) {
      // 获取当前位置的步长
      int next_step = nums[current_pos];
      // 计算下一个位置
      current_pos += next_step;
      // 步数增加
      steps++;
      // 如果越界，则当前尝试失败
      if (current_pos >= n) {
        break;
      }
    }
    // 如果成功到达最后一个元素
    if (current_pos == n - 1) {
      min_steps = min(min_steps, steps);
    }
  }
  cout << (min_steps == INT_MAX ? -1 : min_steps) << endl;
  return 0;
}
```

#### 一种字符串压缩表示的解压

**题目描述**：

有一种简易压缩算法：针对全部由小写英文字母组成的字符串，将其中连续超过两个相同字母的部分压缩为连续个数加该字母，其他部分保持原样不变。

例如：字符串 "aaabbccccd" 经过压缩成为字符串 "3abb4cd"。

请您编写解压函数，根据输入的字符串，判断其是否为合法压缩过的字符串，

若输入合法则输出解压缩后的字符串，否则输出字符串 "! error" 来报告错误。

**输入描述**：

输入一行，为一个 ASCII 字符串，长度不会超过 100 字符，用例保证输出的字符串长度也不会超过 100 字符。

**输出描述**：

若判断输入为合法的经过压缩后的字符串，则输出压缩前的字符串；

若输入不合法，则输出字符串 "**! error**"。

**用例 1**：

输入：

```
4dff
```

输出：

```
ddddff
```

说明：4d 扩展为 dddd，故解压后的字符串为 ddddff。

**用例 2**：

输入：

```
2dff
```

输出：

```
!error
```

**用例 2**：

输入：

```
4d@A
```

输出：

```
!error
```

说明：全部由小写英文字母组成的字符串压缩后不会出现特殊字符@和大写字母 A，故输入不合法。

难度：中等

标签：字符串

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);
  string result;
  // 逐个字符处理输入
  for (int i = 0; i < input.size();) {
    // 处理数字部分
    if (isdigit(input[i])) {
      // 解析数字
      int count = 0;
      bool has_leading_zero = (input[i] == 0);
      while (i < input.size() && isdigit(input[i])) {
        // 检查前导 0
        if (count == 0 && input[i] == '0') {
          has_leading_zero = true;
        }
        count = count * 10 + (input[i] - '0');
        i++;
      }
      if ((count > 0 && count < 3) || i >= input.size() || !islower(input[i]) || has_leading_zero) {
        cout << "!error" << endl;
        return 0;
      }
      // 重复字母
      result.append(count, input[i]);
      i++;
    }
    // 处理普通字母
    else if (islower(input[i])) {
      result += input[i];
      i++;
    }
    // 非法字符
    else {
      cout << "!error" << endl;
      return 0;
    }
  }
  // 如果解压成功，检查重新压缩后是否与输入一致
  string recompressed;
  int count = 1;
  for (int i = 1; i <= result.size(); ++i) {
    // 如果是连续字符，计数器增加
    if (i < result.size() && result[i] == result[i - 1]) {
      count++;
    }
    // 遇到不同字符或者到达末尾
    else {
      // 只有连续三个以上才压缩
      if (count >= 3) {
        recompressed += to_string(count) + result[i - 1];
      }
      // 少于三个则正常输出
      else {
        recompressed.append(count, result[i - 1]);
      }
      // 重置计数器
      count = 1;
    }
  }
  // 检查解压后再次压缩的结果是否与原始输入一致
  if (recompressed == input) {
    cout << result << endl;
  } else {
    cout << "!error" << endl;
  }
  return 0;
}
```

#### 最小的调整次数

**题目描述**：

有一个特异性的双端队列，该队列可以从头部或尾部添加数据，但是只能从头部移出数据。

小 A 依次执行 2n 个指令往队列中添加数据和移出数据。其中 n 个指令是添加数据（可能从头部添加、也可能从尾部添加），依次添加 1 到 n；n 个指令是移出数据。

现在要求移除数据的顺序为 1 到 n。

为了满足最后输出的要求，小 A 可以在任何时候调整队列中数据的顺序。

请问 小 A 最少需要调整几次才能够满足移除数据的顺序正好是 1 到 n；

**输入描述**：

第一行一个数据 n，表示数据的范围。

接下来的 2n 行，其中有 n 行为添加数据，指令为：

- "head add x" 表示从头部添加数据 x，
- "tail add x" 表示从尾部添加数据 x，

另外 n 行为移出数据指令，指令为："remove" 的形式，表示移出 1 个数据；

1 ≤ n ≤ 3 \* 10^5。

所有的数据均合法。

**输出描述**：

一个整数，表示 小 A 要调整的最小次数。

**用例 1**：

输入：

```
5
head add 1
tail add 2
remove
head add 3
tail add 4
head add 5
remove
remove
remove
remove
```

输出：

```
1
```

难度：困难

标签：队列、贪心

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
  int n;
  cin >> n;

  bool is_sorted = true; // 队列初始有序
  int count = 0;         // 记录调整顺序的次数
  int size = 0;          // 当前队列大小（元素个数）

  for (int i = 0; i < 2 * n; ++i) {
    string operation;
    cin >> operation;

    if (operation == "head") {
      int x;
      cin >> operation >> x; // 读取 "add x"
      if (size != 0) {
        // 队列不为空
        is_sorted = false; // head add 会破坏顺序性
      }
      size++; // 添加元素后，队列大小增加
    } else if (operation == "tail") {
      int x;
      cin >> operation >> x; // 读取 "add x"
      size++;                // 添加元素后，队列大小增加
      // tail add 不会破坏有序性
    } else if (operation == "remove") {
      if (!is_sorted) {
        // 如果当前队列不有序
        count++;          // 需要调整，增加计数
        is_sorted = true; // 调整后重置有序性
      }
      if (size > 0) size--; // 移除元素时，队列大小减少
    }
  }

  cout << count << endl; // 输出调整次数
  return 0;
}
```

#### 预订酒店

**题目描述**：

放暑假了，小明决定到某旅游景点游玩，他在网上搜索到了各种价位的酒店（长度为 n 的数组 A），他的心理价位是 x 元，

请帮他筛选出 k 个最接近 x 元的酒店（n ≥ k > 0），并由低到高打印酒店的价格。

备注

- 酒店价格数组 A 和小明的心理价位 x 均为整型数据（0 < n, k, x < 10000）
- 优先选择价格最接近心理价位的酒店，若两家酒店距离心理价位差价相同，则选择价格较低的酒店。（比如 100 元和 300 元距离心理价位 200 元同样接近，此时选择 100 元）
- 酒店价格可能相同重复

**输入描述**：

第一行：n, k, x

第二行：A [0] A [1] A [2]…A [n-1]

**输出描述**：

从低到高打印筛选出的酒店价格

**用例 1**：

输入：

```
10 5 6
1 2 3 4 5 6 7 8 9 10
```

输出：

```
4 5 6 7 8
```

说明：

数组长度 n = 10，筛选个数 k = 5，目标价位 x = 6

**用例 2**：

输入：

```
10 4 6
10 9 8 7 6 5 4 3 2 1
```

输出：

```
4 5 6 7
```

说明：

数组长度 n = 10，筛选个数 k = 4，目标价位 x = 6

当 4 和 8 时距离 x 相同时，优先选择价格低的 4

**用例 3**：

输入：

```
6 3 1000
30 30 200 500 70 300
```

输出：

```
200 300 500
```

难度：中等

标签：排序、数组

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  // 输入酒店数量、筛选数量和目标价位
  int n, k, x;
  cin >> n >> k >> x;

  // 读取酒店价格数组
  vector<int> hotels(n);
  for (int i = 0; i < n; i++) {
    cin >> hotels[i];
  }

  // 自定义比较函数
  // 优先按照与目标价位的绝对差值排序
  // 差值相同时按照价格升序排序
  auto cmp = [x](int a, int b) {
    int diff_a = abs(a - x);
    int diff_b = abs(b - x);

    // 差值不同时，按差值升序
    if (diff_a != diff_b) {
      return diff_a < diff_b;
    }

    // 差值相同时，按价格升序
    return a < b;
  };

  // 对酒店价格数组排序
  sort(hotels.begin(), hotels.end(), cmp);

  // 选择前 k 个元素
  vector<int> selected(hotels.begin(), hotels.begin() + k);

  // 对选定元素升序排序
  sort(selected.begin(), selected.end());

  // 输出结果
  for (int price : selected) {
    cout << price << " ";
  }
  cout << endl;

  return 0;
}
```

#### 找数字

**题目描述**：

给一个二维数组 nums，对于每一个元素 nums [i]，找出距离最近的且值相等的元素，

输出横纵坐标差值的绝对值之和，如果没有等值元素，则输出-1。

例如：

输入数组 nums 为

> 0 3 5 4 2
> 2 5 7 8 3
> 2 5 4 2 4

输出为：

> -1 4 2 3 3
> 1 1 -1 -1 4
> 1 1 2 3 2

- 对于 nums [0][0] = 0，不存在相等的值。
- 对于 nums [0][1] = 3，存在一个相等的值，最近的坐标为 nums [1][4]，最小距离为 4。
- 对于 nums [0][2] = 5，存在两个相等的值，最近的坐标为 nums [1][1]，故最小距离为 2。
- ...
- 对于 nums [1][1] = 5，存在两个相等的值，最近的坐标为 nums [2][1]，故最小距离为 1。
- ...

**输入描述**：

输入第一行为二维数组的行

输入第二行为二维数组的列

输入的数字以空格隔开。

**输出描述**：

数组形式返回所有坐标值。

- 针对数组 nums [i][j]，满足 0 < i ≤ 100，0 < j ≤ 100
- 对于每个数字，最多存在 100 个与其相等的数字

**用例 1**：

输入：

```
3
5
0 3 5 4 2
2 5 7 8 3
2 5 4 2 4
```

输出：

```
[[-1, 4, 2, 3, 3], [1, 1, -1, -1, 4], [1, 1, 2, 3, 2]]
```

难度：困难

标签：数组、矩阵

```cpp
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // 读取矩阵行数和列数
  int rows, cols;
  cin >> rows >> cols;

  // 创建二维数组存储输入
  vector<vector<int>> nums(rows, vector<int>(cols));

  // 读取矩阵元素
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cin >> nums[i][j];
    }
  }

  // 创建结果矩阵
  vector<vector<int>> result(rows, vector<int>(cols));

  // 遍历每个元素
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int min_dist = INT_MAX;

      // 在整个矩阵中查找值相同的元素
      for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
          // 跳过自身
          if (i == x && j == y) continue;

          // 找到值相同的元素
          if (nums[i][j] == nums[x][y]) {
            // 计算曼哈顿距离
            int dist = abs(i - x) + abs(j - y);
            // 更新最小距离
            min_dist = min(min_dist, dist);
          }
        }
      }

      // 更新结果矩阵
      result[i][j] = (min_dist == INT_MAX) ? -1 : min_dist;
    }
  }

  cout << "[";
  for (int i = 0; i < rows; i++) {
    cout << "[";
    for (int j = 0; j < cols; j++) {
      cout << result[i][j];
      if (j < cols - 1) cout << ", ";
    }
    cout << "]";
    if (i < rows - 1) cout << ", ";
  }
  cout << "]" << endl;

  return 0;
}
```

#### 猜字谜

**题目描述**：

小王设计了一个简单的猜字谜游戏，游戏的谜面是一个错误的单词，比如 nesw，玩家需要猜出谜底库中正确的单词。猜中的要求如下： 对于某个谜面和谜底单词，满足下面任一条件都表示猜中：

1. 变换顺序以后一样的，比如通过变换 w 和 e 的顺序，"nwes" 跟 "news" 是可以完全对应的；
2. 字母去重以后是一样的，比如 "woood" 和 "wood" 是一样的，它们去重后都是 "wod"

请你写一个程序帮忙在谜底库中找到正确的谜底。谜面是多个单词，都需要找到对应的谜底，如果找不到的话，返回 "not found"

**输入描述**：

1. 谜面单词列表，以 "," 分隔
2. 谜底库单词列表，以 "," 分隔

**输出描述**：

- 匹配到的正确单词列表，以 "," 分隔
- 如果找不到，返回 "not found"
- 单词的数量 N 的范围：0 < N < 1000
- 词汇表的数量 M 的范围：0 < M < 1000
- 单词的长度 P 的范围：0 < P < 20
- 输入的字符只有小写英文字母，没有其他字符

**用例 1**：

输入：

```
conection
connection,today
```

输出：

```
connection
```

**用例 2**：

输入：

```
bdni,wooood
bind,wrong,wood
```

输出：

```
bind,wood
```

难度：中等

标签：字符串、排序

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  // 输入谜面和谜底
  string puzzlesInput, wordsInput;
  getline(cin, puzzlesInput);
  getline(cin, wordsInput);

  // 结果集
  vector<string> results;

  // 分割输入字符串的 lambda 函数
  auto split = [](const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
      tokens.push_back(token);
    }
    return tokens;
  };

  // 标准化单词的 lambda 函数
  auto normalizeWord = [](string word) {
    sort(word.begin(), word.end());
    return word;
  };

  // 去重标准化单词的 lambda 函数
  auto deduplicateWord = [](string word) {
    set<char> uniqueChars(word.begin(), word.end());
    string result(uniqueChars.begin(), uniqueChars.end());
    sort(result.begin(), result.end());
    return result;
  };

  // 分割谜面和谜底
  vector<string> puzzles = split(puzzlesInput, ',');
  vector<string> words = split(wordsInput, ',');

  // 遍历每个谜面
  for (const string& puzzle : puzzles) {
    // 用于存储当前谜面的所有匹配单词
    vector<string> currentMatchedWords;

    // 标准化谜面
    string normalizedPuzzle = normalizeWord(puzzle);
    string deduplicatedPuzzle = deduplicateWord(puzzle);

    // 遍历谜底库
    for (const string& word : words) {
      // 标准化谜底
      string normalizedWord = normalizeWord(word);
      string deduplicatedWord = deduplicateWord(word);

      // 匹配规则：顺序可调换或去重后相同
      if (normalizedPuzzle == normalizedWord ||
          deduplicatedPuzzle == deduplicatedWord) {
        currentMatchedWords.push_back(word);
      }
    }

    // 如果没找到匹配，加入 "not found"
    if (currentMatchedWords.empty()) {
      results.push_back("not found");
    } else {
      // 将所有匹配的单词以逗号分隔加入结果
      string matchResult;
      for (size_t i = 0; i < currentMatchedWords.size(); ++i) {
        matchResult += currentMatchedWords[i];
        if (i < currentMatchedWords.size() - 1) {
          matchResult += ",";
        }
      }
      results.push_back(matchResult);
    }
  }

  // 输出结果
  for (size_t i = 0; i < results.size(); ++i) {
    cout << results[i];
    if (i < results.size() - 1) cout << ",";
  }
  cout << endl;

  return 0;
}
```

#### 单词接龙

**题目描述**：

单词接龙的规则是：

- 可用于接龙的单词首字母必须要前一个单词的尾字母相同；
- 当存在多个首字母相同的单词时，取长度最长的单词，如果长度也相等，则取字典序最小的单词；已经参与接龙的单词不能重复使用。

现给定一组全部由小写字母组成单词数组，并指定其中的一个单词作为起始单词，进行单词接龙，

请输出最长的单词串，单词串是单词拼接而成，中间没有空格。

**输入描述**：

- 输入的第一行为一个非负整数，表示起始单词在数组中的索引 K，0 <= K < N ；
- 输入的第二行为一个非负整数，表示单词的个数 N；
- 接下来的 N 行，分别表示单词数组中的单词

**输出描述**：

- 输出一个字符串，表示最终拼接的单词串。
- 单词个数 N 的取值范围为 [1, 20]；
- 单个单词的长度的取值范围为 [1, 30]；

**用例 1**：

输入：

```
0
6
word
dd
da
dc
dword
d
```

输出：

```
worddwordda
```

说明：

先确定起始单词 word，再接以 d 开头的且长度最长的单词 dword，剩余以 d 开头且长度最长的有 dd、da、dc，则取字典序最小的 da，所以最后输出 worddwordda。

**用例 2**：

输入：

```
4
6
word
dd
da
dc
dword
d
```

输出：

```
dwordda
```

说明：

先确定起始单词 dword，剩余以 d 开头且长度最长的有 dd、da、dc，则取字典序最小的 da，所以最后输出 dwordda。

难度：中等

标签：贪心、字符串、哈希表

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  // 输入起始单词的索引和单词数量
  int start_index, word_count;
  cin >> start_index >> word_count;

  // 读取单词数组
  vector<string> word_list(word_count);
  for (int i = 0; i < word_count; i++) {
    cin >> word_list[i];
  }

  // 取出起始单词
  string chain = word_list[start_index];

  // 创建前缀字典，存储以首字母为键的单词集合
  unordered_map<char, vector<string>> prefix;

  // 填充前缀字典
  for (int i = 0; i < word_count; i++) {
    if (i != start_index) {  // 不加入起始单词
      prefix[word_list[i][0]].push_back(word_list[i]);
    }
  }

  // 按照长度和字典序排序每个字母对应的单词
  for (auto& pair : prefix) {
    sort(pair.second.begin(), pair.second.end(),
         [](const string& a, const string& b) {
           if (a.length() != b.length()) {
             return a.length() > b.length();  // 长度优先
           }
           return a < b;  // 字典序优先
         });
  }

  // 开始接龙
  while (true) {
    char last_char = chain.back();  // 得到当前链的尾字符

    // 找到以last_char为首字母的单词
    if (prefix.find(last_char) == prefix.end() || prefix[last_char].empty()) {
      break;  // 如果不存在可接的单词，退出循环
    }

    // 取出首字母相同的优先级最高的单词
    string next_word = prefix[last_char].front();
    chain += next_word;  // 拼接到chain字符串

    // 从字典中移除已使用的单词
    prefix[last_char].erase(prefix[last_char].begin());
  }

  // 输出结果
  cout << chain << endl;

  return 0;
}
```

#### 水仙花数

**题目描述**：

所谓水仙花数，是指一个 n 位的正整数，其各位数字的 n 次方和等于该数本身。

例如 153 是水仙花数，153 是一个 3 位数，并且 153 = 1^3 + 5^3 + 3^3。

**输入描述**：

第一行输入一个整数 n，表示一个 n 位的正整数。n 在 3 到 7 之间，包含 3 和 7。

第二行输入一个整数 m，表示需要返回第 m 个水仙花数。

**输出描述**：

返回长度是 n 的第 m 个水仙花数。个数从 0 开始编号。

若 m 大于水仙花数的个数，返回最后一个水仙花数和 m 的乘积。

若输入不合法，返回-1。

**用例 1**：

输入：

```
3
0
```

输出：

```
153
```

说明：153 是第一个水仙花数

**用例 2**：

输入：

```
9
1
```

输出：

```
-1
```

说明：9 超出范围

难度：中等

标签：数学、位运算

暴力，部分超时

```cpp
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // 读取输入的位数和序号
  int digit_count, sequence_index;
  cin >> digit_count >> sequence_index;

  // 输入合法性检查
  if (digit_count < 3 || digit_count > 7) {
    cout << -1 << endl;
    return 0;
  }

  // 初始化存储水仙花数的容器
  vector<int> narcissistic_numbers;

  // 计算 n 位数的起始和结束范围
  int start = pow(10, digit_count - 1);
  int end = pow(10, digit_count) - 1;

  // 遍历范围查找水仙花数
  for (int number = start; number <= end; number++) {
    // 水仙花数判断的局部变量
    int temp_number = number;
    int sum = 0;

    // 逐位计算 n 次方和
    while (temp_number > 0) {
      int digit = temp_number % 10;
      sum += pow(digit, digit_count);
      temp_number /= 10;
    }

    // 判断是否为水仙花数并记录
    if (sum == number) {
      narcissistic_numbers.push_back(number);
    }
  }

  // 处理查找结果
  if (narcissistic_numbers.empty()) {
    // 没有找到水仙花数
    cout << -1 << endl;
  } else if (sequence_index < narcissistic_numbers.size()) {
    // 正常返回第 m 个水仙花数
    cout << narcissistic_numbers[sequence_index] << endl;
  } else {
    // m 超过水仙花数个数，返回最后一个水仙花数和 m 的乘积
    cout << narcissistic_numbers.back() * sequence_index << endl;
  }

  return 0;
}
```

剪枝+快速幂

```cpp
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // 读取输入的位数和序号
  int digit_count, sequence_index;
  cin >> digit_count >> sequence_index;

  // 输入合法性检查
  if (digit_count < 3 || digit_count> 7) {
    cout << -1 << endl;
    return 0;
  }

  // 序号合法性检查
  if (sequence_index < 0) {
    cout << -1 << endl;
    return 0;
  }

  // 预计算最大可能值
  int upper_bound = pow(9, digit_count) * digit_count;

  // 存储水仙花数的容器
  vector<long long> narcissistic_numbers;

  // 计算 n 位数的起始和结束范围
  long long start = pow(10, digit_count - 1);
  long long end = min(static_cast<long long>(pow(10, digit_count) - 1),
                      static_cast<long long>(upper_bound));

  // 快速幂预处理
  vector<int> power_cache(10);
  for (int i = 0; i < 10; ++i) {
    power_cache[i] = pow(i, digit_count);
  }

  // 遍历范围查找水仙花数
  for (long long number = start; number <= end; number++) {
    // 快速剪枝：数字各位数字最大和限制
    long long temp = number;
    long long sum = 0;
    bool valid = true;

    while (temp> 0) {
      int digit = temp % 10;
      sum += power_cache[digit];

      // 提前剪枝：和已经超过原数
      if (sum> number) {
        valid = false;
        break;
      }

      temp /= 10;
    }

    // 判断是否为水仙花数并记录
    if (valid && sum == number) {
      narcissistic_numbers.push_back(number);
    }
  }

  // 处理查找结果
  if (narcissistic_numbers.empty()) {
    cout << -1 << endl;
  } else if (sequence_index < narcissistic_numbers.size()) {
    cout <<narcissistic_numbers[sequence_index] << endl;
  } else {
    // 处理大索引情况
    long long last_narcissistic = narcissistic_numbers.back();
    // 使用 long long 避免溢出
    long long result =
        last_narcissistic * static_cast<long long>(sequence_index);
    cout << result << endl;
  }

  return 0;
}
```

#### VLAN 资源池

**题目描述**：

VLAN 是一种对局域网设备进行逻辑划分的技术，为了标识不同的 VLAN，引入 VLAN ID(1-4094 之间的整数)的概念。

定义一个 VLAN ID 的资源池(下称 VLAN 资源池)，资源池中连续的 VLAN 用开始 VLAN-结束 VLAN 表示，不连续的用单个整数表示，所有的 VLAN 用英文逗号连接起来。

现在有一个 VLAN 资源池，业务需要从资源池中申请一个 VLAN，需要你输出从 VLAN 资源池中移除申请的 VLAN 后的资源池。

**输入描述**：

第一行为字符串格式的 VLAN 资源池，第二行为业务要申请的 VLAN，VLAN 的取值范围为 [1,4094] 之间的整数。

**输出描述**：

从输入 VLAN 资源池中移除申请的 VLAN 后字符串格式的 VLAN 资源池，输出要求满足题目描述中的格式，并且按照 VLAN 从小到大升序输出。

如果申请的 VLAN 不在原 VLAN 资源池内，输出原 VLAN 资源池升序排序后的字符串即可。

输入 VLAN 资源池中 VLAN 的数量取值范围为 [2-4094] 间的整数，资源池中 VLAN 不重复且合法([1,4094] 之间的整数)，输入是乱序的。

**用例 1**：

输入：

```
1-5
2
```

输出：

```
1,3-5
```

说明：原 VLAN 资源池中有 VLAN 1、2、3、4、5，从资源池中移除 2 后，剩下 VLAN 1、3、4、5，按照题目描述格式并升序后的结果为 1,3-5。

**用例 2**：

输入：

```
20-21,15,18,30,5-10
15
```

输出：

```
5-10,18,20-21,30
```

说明：原 VLAN 资源池中有 VLAN 5、6、7、8、9、10、15、18、20、21、30，从资源池中移除 15 后，资源池中剩下的 VLAN 为 5、6、7、8、9、10、18、20、21、30，按照题目描述格式并升序后的结果为 5-10,18,20-21,30。

**用例 3**：

输入：

```
5,1-3
10
```

输出：

```
1-3,5
```

说明：原 VLAN 资源池中有 VLAN 1、2、3，5，申请的 VLAN 10 不在原资源池中，将原资源池按照题目描述格式并按升序排序后输出的结果为 1-3,5。

难度：中等

标签：字符串、排序

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  // 读取 VLAN 资源池字符串和申请的 VLAN
  string vlan_pool_str;
  int requested_vlan;
  getline(cin, vlan_pool_str);
  cin >> requested_vlan;

  // 存储所有 VLAN 的集合
  vector<int> vlan_set;

  // 解析 VLAN 资源池字符串
  stringstream ss(vlan_pool_str);
  string segment;
  while (getline(ss, segment, ',')) {
    // 检查是否为范围
    size_t dash_pos = segment.find('-');
    if (dash_pos != string::npos) {
      // 解析范围
      int start = stoi(segment.substr(0, dash_pos));
      int end = stoi(segment.substr(dash_pos + 1));

      // 添加范围内的所有 VLAN
      for (int i = start; i <= end; ++i) {
        vlan_set.push_back(i);
      }
    } else {
      // 添加单个 VLAN
      vlan_set.push_back(stoi(segment));
    }
  }

  // 排序并去重
  sort(vlan_set.begin(), vlan_set.end());
  vlan_set.erase(unique(vlan_set.begin(), vlan_set.end()), vlan_set.end());

  // 移除申请的 VLAN（如果存在）
  auto it = find(vlan_set.begin(), vlan_set.end(), requested_vlan);
  if (it != vlan_set.end()) {
    vlan_set.erase(it);
  }

  // 重新格式化输出
  string result;
  for (size_t i = 0; i < vlan_set.size(); ++i) {
    // 寻找连续范围的起始和结束
    int start = vlan_set[i], end = vlan_set[i];
    while (i + 1 < vlan_set.size() && vlan_set[i + 1] == end + 1) {
      end = vlan_set[++i];
    }

    // 构造输出片段
    if (!result.empty()) result += ",";
    if (start == end) {
      result += to_string(start);
    } else {
      result += to_string(start) + "-" + to_string(end);
    }
  }

  // 输出结果
  cout << result << endl;

  return 0;
}
```

#### 货币单位换算

**题目描述**：

记账本上记录了若干条多国货币金额，需要转换成人民币分（fen），汇总后输出。

每行记录一条金额，金额带有货币单位，格式为数字+单位，可能是单独元，或者单独分，或者元与分的组合。

要求将这些货币全部换算成人民币分（fen）后进行汇总，汇总结果仅保留整数，小数部分舍弃。

元和分的换算关系都是 1:100，如下：

1CNY = 100fen（1 元 = 100 分）

1HKD = 100cents（1 港元 = 100 港分）

1JPY = 100sen（1 日元 = 100 仙）

1EUR = 100eurocents（1 欧元 = 100 欧分）

1GBP = 100pence（1 英镑 = 100 便士）

汇率表如下：

| CNY | JPY  | HKD | EUR | GBP |
| :-- | :--- | :-- | :-- | :-- |
| 100 | 1825 | 123 | 14  | 12  |

即：100CNY = 1825JPY = 123HKD = 14EUR = 12GBP

**输入描述**：

第一行输入为 N，N 表示记录数。0 < N < 100

之后 N 行，每行表示一条货币记录，且该行只会是一种货币。

**输出描述**：

将每行货币转换成人民币分（fen）后汇总求和，只保留整数部分。

输出格式只有整数数字，不带小数，不带单位。

**用例 1**：

输入：

```
1
100CNY
```

输出：

```
10000
```

说明：100CNY 转换后是 10000fen，所以输出结果为 10000

**用例 2**：

输入：

```
1
3000fen
```

输出：

```
3000
```

说明：3000fen，结果就是 3000

**用例 2**：

输入：

```
1
3000fen
```

输出：

```
3000
```

说明：3000fen，结果就是 3000

**用例 3**：

输入：

```
1
123HKD
```

输出：

```
10000
```

说明：HKD 与 CNY 的汇率关系是 123:100，所以换算后，输出结果为 10000

**用例 4**：

输入：

```
2
20CNY53fen
53HKD87cents
```

输出：

```
6432
```

说明：20 元 53 分 + 53 港元 87 港分，换算成人民币分后汇总，为 6432

难度：中等

标签：字符串

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  // 定义正则表达式，匹配数字和货币单位
  regex currency_pattern(
      "(\\d+)(CNY|JPY|HKD|EUR|GBP|fen|cents|sen|eurocents|pence)");

  // 创建汇率映射表
  unordered_map<string, double> exchange_rates;
  exchange_rates["CNY"] = 100.0;               // 1 CNY = 100 fen
  exchange_rates["JPY"] = 100.0 / 1825 * 100;  // JPY 换算到 fen
  exchange_rates["HKD"] = 100.0 / 123 * 100;   // HKD 换算到 fen
  exchange_rates["EUR"] = 100.0 / 14 * 100;    // EUR 换算到 fen
  exchange_rates["GBP"] = 100.0 / 12 * 100;    // GBP 换算到 fen

  // 最小单位
  exchange_rates["fen"] = 1.0;
  exchange_rates["cents"] = 100.0 / 123;     // HKD cents
  exchange_rates["sen"] = 100.0 / 1825;      // JPY sen
  exchange_rates["eurocents"] = 100.0 / 14;  // EUR cents
  exchange_rates["pence"] = 100.0 / 12;      // GBP pence

  // 存储最终结果
  double total_amount = 0;

  // 读取输入数量
  int n;
  cin >> n;

  // 处理每一行输入
  for (int i = 0; i < n; i++) {
    string input;
    cin >> input;

    // 使用正则表达式迭代器匹配所有货币单位
    sregex_iterator currency_iterator(input.begin(), input.end(),
                                      currency_pattern);
    sregex_iterator end_iterator;

    // 遍历匹配到的所有货币单位
    while (currency_iterator != end_iterator) {
      // 获取匹配结果
      smatch currency_match = *currency_iterator;

      // 转换数量和单位
      double currency_amount = stod(currency_match[1]);
      string currency_unit = currency_match[2];

      // 累加转换后的结果
      total_amount += currency_amount * exchange_rates[currency_unit];

      // 移动到下一个匹配
      currency_iterator++;
    }
  }

  // 输出结果（向下取整）
  cout << static_cast<int>(total_amount) << endl;

  return 0;
}
```

#### 数字涂色

**题目描述**：

疫情过后，希望小学终于又重新开学了，三年二班开学第一天的任务是将后面的黑板报重新制作。

黑板上已经写上了 N 个正整数，同学们需要给这每个数分别上一种颜色。

为了让黑板报既美观又有学习意义，老师要求同种颜色的所有数都可以被这种颜色中最小的那个数整除。

现在请你帮帮小朋友们，算算最少需要多少种颜色才能给这 N 个数进行上色。

**输入描述**：

第一行有一个正整数 N，其中。

第二行有 N 个 int 型数(保证输入数据在 [1,100] 范围中)，表示黑板上各个正整数的值。

**输出描述**：

输出只有一个整数，为最少需要的颜色种数。

**用例 1**：

输入：

```
3
2 4 6
```

输出：

```
1
```

说明：所有数都能被 2 整除

**用例 2**：

输入：

```
4
2 3 4 9
```

输出：

```
2
```

说明：

2 与 4 涂一种颜色，4 能被 2 整除；3 与 9 涂另一种颜色，9 能被 3 整除。不能 4 个数涂同一个颜色，因为 3 与 9 不能被 2 整除。所以最少的颜色是两种。

难度：中等

标签：数组、贪心、数学

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  // 读取输入
  int n;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  // 排序，方便处理
  sort(nums.begin(), nums.end());

  // 存储每个颜色组的最小值
  vector<int> color_groups;

  // 遍历每个数字
  for (int num : nums) {
    bool found_group = false;

    // 检查是否可以加入现有的组
    for (int min_num : color_groups) {
      if (num % min_num == 0) {
        found_group = true;
        break;
      }
    }

    // 如果不能加入任何现有组，创建新组
    if (!found_group) {
      color_groups.push_back(num);
    }
  }

  // 输出颜色组数量
  cout << color_groups.size() << endl;

  return 0;
}
```

#### IPv4 地址转换成整数

**题目描述**：

存在一种虚拟 IPv4 地址，由 4 小节组成，每节的范围为 0~255，以#号间隔，虚拟 IPv4 地址可以转换为一个 32 位的整数，例如：

- 128#0#255#255，转换为 32 位整数的结果为 2147549183（0x8000FFFF）
- 1#0#0#0，转换为 32 位整数的结果为 16777216（0x01000000）

现以字符串形式给出一个虚拟 IPv4 地址，限制第 1 小节的范围为 1 ~ 128，即每一节范围分别为(1 ~ 128)#(0~255)#(0~255)#(0~255)，要求每个 IPv4 地址只能对应到唯一的整数上。

如果是非法 IPv4，返回 invalid IP

**输入描述**：

输入一行，虚拟 IPv4 地址格式字符串

**输出描述**：

输出一行，按照要求输出整型或者特定字符

输入不能确保是合法的 IPv4 地址，需要对非法 IPv4（空串，含有 IP 地址中不存在的字符，非合法的#分十进制，十进制整数不在合法区间内）进行识别，返回特定错误

**用例 1**：

输入：

```
100#101#1#5
```

输出：

```
1684340997
```

**用例 2**：

输入：

```
1#2#3
```

输出：

```
invalid IP
```

难度：中等

标签：字符串

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  string ip;
  getline(cin, ip);

  // 检查空输入
  if (ip.empty()) {
    cout << "invalid IP" << endl;
    return 0;
  }

  // 用于存储四个数字
  vector<int> nums;
  size_t start = 0;

  // 分割并验证每个部分
  for (int i = 0; i < 4; i++) {
    // 找到下一个#号位置
    size_t end = (i < 3) ? ip.find('#', start) : ip.length();

    // 检查格式
    if (i < 3 && end == string::npos) {
      cout << "invalid IP" << endl;
      return 0;
    }

    // 获取当前部分
    string section = ip.substr(start, end - start);

    // 检查部分是否为空或过长
    if (section.empty() || section.length() > 3) {
      cout << "invalid IP" << endl;
      return 0;
    }

    // 检查前导零
    if (section.length() > 1 && section[0] == '0') {
      cout << "invalid IP" << endl;
      return 0;
    }

    // 验证是否都是数字
    for (char c : section) {
      if (!isdigit(c)) {
        cout << "invalid IP" << endl;
        return 0;
      }
    }

    // 转换为数字
    int num = stoi(section);

    // 检查范围
    if (i == 0 && (num < 1 || num > 128)) {
      cout << "invalid IP" << endl;
      return 0;
    }
    if (i != 0 && (num < 0 || num > 255)) {
      cout << "invalid IP" << endl;
      return 0;
    }

    nums.push_back(num);
    start = end + 1;
  }

  // 检查是否有多余的字符
  if (start < ip.length() + 1) {
    cout << "invalid IP" << endl;
    return 0;
  }

  // 计算结果
  unsigned int result = 0;
  for (int num : nums) {
    result = (result << 8) | num;
  }

  cout << result << endl;

  return 0;
}
```

#### 求字符串中所有整数的最小和

**题目描述**：

输入字符串 s，输出 s 中包含所有整数的最小和。

说明：

字符串 s，只包含 a-z A-Z ±

合法的整数包括

1. 正整数：一个或者多个 0-9 组成，如 0 2 3 002 102
2. 负整数：负号 – 开头，数字部分由一个或者多个 0-9 组成，如 -0 -012 -23 -00023

**输入描述**：

包含数字的字符串

**输出描述**：

所有整数的最小和

**用例 1**：

输入：

```
bb1234aa
```

输出：

```
10
```

**用例 2**：

输入：

```
bb12-34aa
```

输出：

```
-31
```

说明：1+2+(-34) = 31

难度：中等

标签：字符串、贪心

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;

  long long sum = 0;  // 使用long long避免溢出
  int len = s.length();
  int i = 0;

  while (i < len) {
    // 跳过非数字且非负号的字符
    if (!isdigit(s[i]) && s[i] != '-') {
      i++;
      continue;
    }

    // 处理负数
    if (s[i] == '-') {
      i++;  // 移到负号后面
      string num;
      // 收集负号后的所有数字
      while (i < len && isdigit(s[i])) {
        num += s[i];
        i++;
      }
      // 如果负号后有数字
      if (!num.empty()) {
        // 去除前导零
        while (num.length() > 1 && num[0] == '0') {
          num = num.substr(1);
        }
        sum -= stoll(num);
      }
    }
    // 处理正数
    else if (isdigit(s[i])) {
      // 对于正数，逐位相加
      while (i < len && isdigit(s[i])) {
        sum += (s[i] - '0');
        i++;
      }
    }
  }

  cout << sum << endl;
  return 0;
}
```

#### 螺旋数字矩阵

**题目描述**：

疫情期间，小明隔离在家，百无聊赖，在纸上写数字玩。他发明了一种写法：

给出数字个数 n （0 < n ≤ 999）和行数 m（0 < m ≤ 999），从左上角的 1 开始，按照顺时针螺旋向内写方式，依次写出 2,3,...., n，最终形成一个 m 行矩阵。

小明对这个矩阵有些要求：

1. 每行数字的个数一样多
2. 列的数量尽可能少
3. 填充数字时优先填充外部
4. 数字不够时，使用单个 \* 号占位

**输入描述**：

两个整数，空格隔开，依次表示 n、m

**输出描述**：

符合要求的唯一矩阵

**用例 1**：

输入：

```
9 4
```

输出：

```
1 2 3
* * 4
9 * 5
8 7 6
```

说明：9 个数字写出 4 行，最少需要 3 列

**用例 2**：

输入：

```
3 5
```

输出：

```
1
2
3
*
*
```

说明：3 个数字写 5 行，只有一列，数字不够用\*号填充

**用例 3**：

输入：

```
120 7
```

输出：

```
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 19
45 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 63 20
44 83 114 115 116 117 118 119 120 * * * * * * 99 64 21
43 82 113 112 111 110 109 108 107 106 105 104 103 102 101 100 65 22
42 81 80 79 78 77 76 75 74 73 72 71 70 69 68 67 66 23
41 40 39 38 37 36 35 34 33 32 31 30 29 28 27 26 25 24
```

说明：9 个数字写出 4 行，最少需要 3 列

难度: 中等

标签：数组

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  // 计算最小列数（向上取整）
  int cols = (n + m - 1) / m;

  // 创建矩阵并初始化为*
  vector<vector<string>> matrix(m, vector<string>(cols, "*"));

  // 定义四个方向：右、下、左、上
  const int dx[] = {0, 1, 0, -1};
  const int dy[] = {1, 0, -1, 0};

  int x = 0, y = 0;  // 当前位置
  int dir = 0;       // 当前方向
  int num = 1;       // 当前要填入的数字

  // 填充数字
  while (num <= n) {
    // 填入当前数字
    matrix[x][y] = to_string(num++);

    // 计算下一个位置
    int nextX = x + dx[dir];
    int nextY = y + dy[dir];

    // 检查是否需要改变方向
    if (nextX < 0 || nextX >= m || nextY < 0 || nextY >= cols ||
        matrix[nextX][nextY] != "*") {
      dir = (dir + 1) % 4;
      nextX = x + dx[dir];
      nextY = y + dy[dir];
    }

    x = nextX;
    y = nextY;
  }

  // 输出矩阵
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < cols; j++) {
      if (j > 0)
        cout << " ";
      cout << matrix[i][j];
    }
    cout << endl;
  }

  return 0;
}
```

#### 免单统计

**题目描述**：

华为商城举办了一个促销活动，如果某顾客是某一秒内最早时刻下单的顾客（可能是多个人），则可以获取免单。

请你编程计算有多少顾客可以获取免单。

**输入描述**：

输入为 n 行数据，每一行表示一位顾客的下单时间以（年-月-日 时-分-秒.毫秒）形式给出。

> yyyy-MM-dd HH:mm:ss.fff

- 0 < n < 50000
- 2000 < yyyy < 2020
- 0 < MM ≤ 12
- 0 < dd ≤ 28
- 0 ≤ HH ≤ 23
- 0 ≤ mm ≤ 59
- 0 ≤ ss ≤ 59
- 0 ≤ fff ≤ 999

所有输入保证合法。

**输出描述**：

输出一个整数，表示有多少顾客可以获取免单。

**用例 1**：

输入：

```
3
2019-01-01 00:00:00.001
2019-01-01 00:00:00.002
2019-01-01 00:00:00.003
```

输出：

```
1
```

说明：样例 1 中，三个订单都是同一秒内下单，只有第一个订单最早下单，可以免单。

**用例 2**：

输入：

```
3
2019-01-01 08:59:00.123
2019-01-01 08:59:00.123
2018-12-28 10:08:00.999
```

输出：

```
3
```

说明：样例 2 中，前两个订单是同一秒内同一时刻（也是最早）下单，都可免单，第三个订单是当前秒内唯一一个订单（也是最早），也可免单。

**用例 3**：

输入：

```
5
2019-01-01 00:00:00.004
2019-01-01 00:00:00.004
2019-01-01 00:00:01.006
2019-01-01 00:00:01.006
2019-01-01 00:00:01.005
```

输出：

```
3
```

说明：样例 3 中，前两个订单是同一秒内同一时刻（也是最早）下单，第三第四个订单不是当前秒内最早下单，不可免单，第五个订单可以免单。

难度：中等

标签：字符串、排序

```cpp
#include <bits/stdc++.h>
using namespace std;

// 提取时间的秒数部分（不含毫秒）
string getSecond(const string& time) {
  return time.substr(0, time.length() - 4);  // 去掉.fff部分
}

int main() {
  int n;
  cin >> n;
  cin.ignore();  // 处理换行符

  // 用于存储按秒分组的订单
  map<string, vector<string>> orders_by_second;

  // 读取所有订单
  for (int i = 0; i < n; i++) {
    string time;
    getline(cin, time);
    // 按秒分组存储完整时间
    orders_by_second[getSecond(time)].push_back(time);
  }

  int free_orders = 0;

  // 处理每一秒的订单
  for (const auto& second_orders : orders_by_second) {
    const vector<string>& orders = second_orders.second;

    // 找出当前秒内最早的订单时间
    string earliest_time = *min_element(orders.begin(), orders.end());

    // 统计与最早订单时间相同的订单数量
    free_orders += count(orders.begin(), orders.end(), earliest_time);
  }

  cout << free_orders << endl;

  return 0;
}
```

#### 分班

**题目描述**：

幼儿园两个班的小朋友在排队时混在了一起，每位小朋友都知道自己是否与前面一位小朋友同班，请你帮忙把同班的小朋友找出来。

小朋友的编号是整数，与前一位小朋友同班用 Y 表示，不同班用 N 表示。

**输入描述**：

输入为空格分开的小朋友编号和是否同班标志。

比如：6/N 2/Y 3/N 4/Y，表示 4 位小朋友，2 和 6 同班，3 和 2 不同班，4 和 3 同班。

其中，小朋友总数不超过 999，每个小朋友编号大于 0，小于等于 999。

不考虑输入格式错误问题。

**输出描述**：

输出为两行，每一行记录一个班小朋友的编号，编号用空格分开，且：

1. 编号需按照大小升序排列，分班记录中第一个编号小的排在第一行。
2. 若只有一个班的小朋友，第二行为空行。
3. 若输入不符合要求，则直接输出字符串 ERROR。

**用例 1**：

输入：

```
1/N 2/Y 3/N 4/Y
```

输出：

```
1 2
3 4
```

说明：2 的同班标记为 Y，因此和 1 同班。 3 的同班标记为 N，因此和 1、2 不同班。 4 的同班标记为 Y，因此和 3 同班。 所以 1、2 同班，3、4 同班，输出为 1 2 3 4

**用例 2**：

输入：

```
1/N 2/Y 3/N 4/Y 5/Y
```

输出：

```
1 2
3 4 5
```

难度：中等

标签：字符串、图论、并查集

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  string input;
  getline(cin, input);

  // 用于存储学生信息的向量
  vector<int> nums;    // 存储学生编号
  vector<char> flags;  // 存储Y/N标记

  // 解析输入
  stringstream ss(input);
  string token;
  while (ss >> token) {
    int pos = token.find('/');
    int num = stoi(token.substr(0, pos));
    char flag = token[pos + 1];

    // 检查编号范围
    if (num <= 0 || num > 999) {
      cout << "ERROR" << endl;
      return 0;
    }

    nums.push_back(num);
    flags.push_back(flag);
  }

  // 检查总人数
  if (nums.size() > 999) {
    cout << "ERROR" << endl;
    return 0;
  }

  // 检查第一个学生的标记必须是N
  if (nums.empty() || flags[0] == 'Y') {
    cout << "ERROR" << endl;
    return 0;
  }

  // 使用set存储两个班级的学生
  set<int> class1, class2;
  bool error = false;

  // 第一个学生默认放入第一个班
  class1.insert(nums[0]);

  // 处理剩余学生
  for (int i = 1; i < nums.size() && !error; i++) {
    int curr_num = nums[i];
    int prev_num = nums[i - 1];

    if (flags[i] == 'Y') {
      // 如果前一个人在class1，当前人也应该在class1
      if (class1.count(prev_num)) {
        if (class2.count(curr_num)) {
          error = true;
        }
        class1.insert(curr_num);
      }
      // 如果前一个人在class2，当前人也应该在class2
      else if (class2.count(prev_num)) {
        if (class1.count(curr_num)) {
          error = true;
        }
        class2.insert(curr_num);
      }
    } else {  // flags[i] == 'N'
      // 如果前一个人在class1，当前人应该在class2
      if (class1.count(prev_num)) {
        if (class1.count(curr_num)) {
          error = true;
        }
        class2.insert(curr_num);
      }
      // 如果前一个人在class2，当前人应该在class1
      else if (class2.count(prev_num)) {
        if (class2.count(curr_num)) {
          error = true;
        }
        class1.insert(curr_num);
      }
    }
  }

  // 检查错误情况
  if (error) {
    cout << "ERROR" << endl;
    return 0;
  }

  // 如果所有学生都在一个班级，那是合法的
  if (class2.empty()) {
    // 输出class1
    bool first = true;
    for (int num : class1) {
      if (!first)
        cout << " ";
      cout << num;
      first = false;
    }
    cout << endl << endl;
    return 0;
  }

  // 确保第一行是编号较小的班级
  if (*class1.begin() > *class2.begin()) {
    swap(class1, class2);
  }

  // 输出第一个班
  bool first = true;
  for (int num : class1) {
    if (!first)
      cout << " ";
    cout << num;
    first = false;
  }
  cout << endl;

  // 输出第二个班
  first = true;
  for (int num : class2) {
    if (!first)
      cout << " ";
    cout << num;
    first = false;
  }
  cout << endl;

  return 0;
}
```

#### 用户调度问题

**题目描述**：

在通信系统中，一个常见的问题是对用户进行不同策略的调度，会得到不同的系统消耗和性能。

假设当前有 n 个待串行调度用户，每个用户可以使用 A/B/C 三种不同的调度策略，不同的策略会消耗不同的系统资源。请你根据如下规则进行用户调度，并返回总的消耗资源数。

规则：

1. 相邻的用户不能使用相同的调度策略，例如，第 1 个用户使用了 A 策略，则第 2 个用户只能使用 B 或者 C 策略。
2. 对单个用户而言，不同的调度策略对系统资源的消耗可以归一化后抽象为数值。例如，某用户分别使用 A/B/C 策略的系统消耗分别为 15/8/17。
3. 每个用户依次选择当前所能选择的对系统资源消耗最少的策略（局部最优），如果有多个满足要求的策略，选最后一个。

**输入描述**：

第一行表示用户个数 n

接下来每一行表示一个用户分别使用三个策略的系统消耗 resA resB resC

**输出描述**：

最优策略组合下的总的系统资源消耗数

**用例 1**：

输入：

```
3
15 8 17
12 20 9
11 7 5
```

输出：

```
24
```

说明：1 号用户使用 B 策略，2 号用户使用 C 策略，3 号用户使用 B 策略。系统资源消耗: 8 + 9 + 7 = 24。

难度：中等

标签：动态规划、贪心、数组

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<vector<int>> resources(n, vector<int>(3));
  for (int i = 0; i < n; i++) {
    cin >> resources[i][0] >> resources[i][1] >> resources[i][2];
  }

  int last_pos = -1;
  int total_cost = 0;

  for (int i = 0; i < n; i++) {
    // 寻找可选策略的最小值
    int min_cost = INT_MAX;
    int min_pos = -1;

    for (int j = 0; j < 3; j++) {
      // 如果当前策略位置与上一个用户不同
      if (j != last_pos) {
        // 如果当前策略消耗更小，或者消耗相等但位置更靠后
        if (resources[i][j] < min_cost ||
            (resources[i][j] == min_cost && j > min_pos)) {
          min_cost = resources[i][j];
          min_pos = j;
        }
      }
    }

    // 添加消耗并更新上一个选择的位置
    total_cost += min_cost;
    last_pos = min_pos;
  }

  cout << total_cost << endl;

  return 0;
}
```

#### 字符串摘要

**题目描述**：

给定一个字符串的摘要算法，请输出给定字符串的摘要值

1. 去除字符串中非字母的符号。
2. 如果出现连续字符(不区分大小写) ，则输出：该字符 (小写) + 连续出现的次数。
3. 如果是非连续的字符(不区分大小写)，则输出：该字符(小写) + 该字母之后字符串中出现的该字符的次数
4. 对按照以上方式表示后的字符串进行排序：字母和紧随的数字作为一组进行排序，数字大的在前，数字相同的，则按字母进行排序，字母小的在前。

**输入描述**：

一行字符串，长度为 [1,200]

**输出描述**：

摘要字符串

**用例 1**：

输入：

```
aabbcc
```

输出：

```
a2b2c2
```

**用例 2**：

输入：

```
bAaAcBb
```

输出：

```
a3b2b2c0
```

说明：

bAaAcBb: 第一个 b 非连续字母，该字母之后字符串中还出现了 2 次(最后的两个 Bb) ，所以输出 b2

a 连续出现 3 次，输出 a3， c 非连续，该字母之后字符串再没有出现过 c，输出 c0

Bb 连续 2 次，输出 b2

对 b2a3c0b2 进行排序，最终输出 a3b2b2c0

难度：中等

标签：哈希表、字符串、排序

```cpp
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  string input;
  getline(cin, input);

  // 1. 预处理：统计所有字母出现次数（不区分大小写）
  unordered_map<char, int> count;
  string cleaned;
  for (char c : input) {
    if (isalpha(c)) {
      cleaned += tolower(c);
      count[tolower(c)]++;
    }
  }

  // 2. 存储摘要信息的数组
  vector<pair<char, int>> summary;

  // 3. 遍历字符串，处理连续和非连续字符
  for (int i = 0; i < cleaned.length();) {
    char current = cleaned[i];
    int consecutive_count = 0;

    // 统计连续字符
    while (i < cleaned.length() && cleaned[i] == current) {
      consecutive_count++;
      count[current]--;
      i++;
    }

    // 处理连续字符和非连续字符
    if (consecutive_count > 1) {
      // 连续字符
      summary.push_back({current, consecutive_count});
    } else if (consecutive_count == 1) {
      // 非连续字符，统计后续出现次数
      summary.push_back({current, count[current]});
    }
  }

  // 4. 排序
  sort(summary.begin(), summary.end(), [](const auto& a, const auto& b) {
    // 按数字降序排序
    if (a.second != b.second) {
      return a.second > b.second;
    }
    // 数字相同时按字母升序排序
    return a.first < b.first;
  });

  // 5. 生成并输出最终字符串
  string result;
  for (const auto& item : summary) {
    result += item.first;
    result += to_string(item.second);
  }

  cout << result << endl;

  return 0;
}
```

#### ai 面板识别

**题目描述**：

AI 识别到面板上有 N（1 ≤ N ≤ 100）个指示灯，灯大小一样，任意两个之间无重叠。

由于 AI 识别误差，每次别到的指示灯位置可能有差异，以 4 个坐标值描述 AI 识别的指示灯的大小和位置(左上角 x1, y1，右下角 x2, y2)，

请输出先行后列排序的指示灯的编号，排序规则：

每次在尚未排序的灯中挑选最高的灯作为的基准灯， 找出和基准灯属于同一行所有的灯进行排序。两个灯高低偏差不超过灯半径算同一行（即两个灯坐标的差 ≤ 灯高度的一半）。

**输入描述**：

第一行为 N，表示灯的个数 接下来 N 行，每行为 1 个灯的坐标信息，格式为：

> 编号 x1 y1 x2 y2

- 编号全局唯一
- 1 ≤ 编号 ≤ 100
- 0 ≤ x1 < x2 ≤ 1000
- 0 ≤ y1 < y2 ≤ 1000

**输出描述**：

排序后的编号列表，编号之间以空格分隔

**用例 1**：

输入：

```
5
1 0 0 2 2
2 6 1 8 3
3 3 2 5 4
5 5 4 7 6
4 0 4 2 6
```

输出：

```
1 2 3 4 5
```

说明：

![image](https://hydro.ac/d/HWOD2023/p/132/file/WL94MgYyceSjWFXwKNmgO.png)

难度：中等

标签：数组、排序、贪心

```cpp
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// 定义灯的结构体
struct Light {
  int id;             // 编号
  int x1, y1;         // 左上角坐标
  int x2, y2;         // 右下角坐标
  int centerX;        // 中心x坐标
  int centerY;        // 中心y坐标
  int height;         // 灯的高度
  bool used = false;  // 是否已经被使用
};

int main() {
  int N;
  cin >> N;

  vector<Light> lights(N);

  // 读取输入
  for (int i = 0; i < N; i++) {
    cin >> lights[i].id >> lights[i].x1 >> lights[i].y1 >> lights[i].x2 >>
        lights[i].y2;

    // 计算中心坐标
    lights[i].centerX = (lights[i].x1 + lights[i].x2) / 2;
    lights[i].centerY = (lights[i].y1 + lights[i].y2) / 2;

    // 计算高度
    lights[i].height = lights[i].y2 - lights[i].y1;
  }

  // 存储最终排序结果
  vector<int> result;

  while (result.size() < N) {
    // 找出未使用的最高的灯（y坐标最小的）
    int highest_index = -1;
    for (int i = 0; i < N; i++) {
      if (!lights[i].used) {
        if (highest_index == -1 ||
            lights[i].centerY < lights[highest_index].centerY) {
          highest_index = i;
        }
      }
    }

    // 找出同一行的灯
    vector<Light*> current_row;
    current_row.push_back(&lights[highest_index]);
    lights[highest_index].used = true;

    // 找出和最高灯坐标相差小于等于灯半径的灯
    for (int i = 0; i < N; i++) {
      if (!lights[i].used) {
        bool same_row = true;
        for (auto* row_light : current_row) {
          if (abs(lights[i].centerY - row_light->centerY) >
              row_light->height / 2) {
            same_row = false;
            break;
          }
        }

        if (same_row) {
          current_row.push_back(&lights[i]);
          lights[i].used = true;
        }
      }
    }

    // 对同一行的灯按x坐标排序
    sort(
        current_row.begin(), current_row.end(),
        [](const Light* a, const Light* b) { return a->centerX < b->centerX; });

    // 将同一行的灯id加入结果
    for (auto* light : current_row) {
      result.push_back(light->id);
    }
  }

  // 输出排序后的编号
  for (int i = 0; i < N; i++) {
    cout << result[i];
    if (i < N - 1)
      cout << " ";
  }
  cout << endl;

  return 0;
}
```

#### 静态代码扫描服务

**题目描述**：

静态扫描可以快速识别源代码的缺陷，静态扫描的结果以扫描报告作为输出：

1、文件扫描的成本和文件大小相关，如果文件大小为 N，则扫描成本为 N 个金币

2、扫描报告的缓存成本和文件大小无关，每缓存一个报告需要 M 个金币

3、扫描报告缓存后，后继再碰到该文件则不需要扫描成本，直接获取缓存结果

给出源代码文件标识序列和文件大小序列，求解采用合理的缓存策略，最少需要的金币数。

**输入描述**：

第一行为缓存一个报告金币数 M，L <= M <= 100

第二行为文件标识序列：F1, F2, F3,...., Fn。

第三行为文件大小序列：S1, S2, S3,...., Sn。

**输出描述**：

采用合理的缓存策略，需要的最少金币数

- 1 <= N <= 10000
- 1 <= Fi <= 1000
- 1 <= Si <= 10

**用例 1**：

输入：

```
5
1 2 2 1 2 3 4
1 1 1 1 1 1 1
```

输出：

```
7
```

说明：文件大小相同，扫描成本均为 1 个金币。缓存任意文件均不合算，因而最少成本为 7 金币。

**用例 2**：

输入：

```
5
2 2 2 2 2 5 2 2 2
3 3 3 3 3 1 3 3 3
```

输出：

```
5
2 2 2 2 2 5 2 2 2
3 3 3 3 3 1 3 3 3
```

难度：中等

标签：动态规划、数组

```cpp
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  // 读取缓存一个报告的金币数
  int M;
  cin >> M;

  // 文件标识序列
  vector<int> files;
  int file;
  while (cin >> file) {
    files.push_back(file);
    if (cin.get() == '\n')
      break;
  }

  // 文件大小序列
  vector<int> sizes;
  int size;
  while (cin >> size) {
    sizes.push_back(size);
    if (cin.get() == '\n')
      break;
  }

  // 统计每个文件的出现次数
  map<int, int> count;
  // 记录每个文件的大小
  map<int, int> file_sizes;

  // 遍历输入序列
  for (int i = 0; i < files.size(); i++) {
    int file_id = files[i];

    // 统计文件出现次数
    count[file_id]++;

    // 记录文件大小（只记录第一次出现的大小）
    if (file_sizes.find(file_id) == file_sizes.end()) {
      file_sizes[file_id] = sizes[i];
    }
  }

  // 计算最小金币数
  int total_cost = 0;
  for (const auto& [file_id, file_count] : count) {
    // 两种方案：
    // 1. 每次都重新扫描的成本
    // 2. 扫描一次 + 缓存的成本
    int scan_all_cost = file_count * file_sizes[file_id];
    int cache_cost = file_sizes[file_id] + M;

    // 选择成本较低的方案
    total_cost += min(scan_all_cost, cache_cost);
  }

  // 输出最小金币数
  cout << total_cost << endl;

  return 0;
}
```

#### 箱子之字形摆放

**题目描述**：

有一批箱子（形式为字符串，设为 str）， 要求将这批箱子按从上到下以之字形的顺序摆放在宽度为 n 的空地，请输出箱子的摆放位置。

例如：箱子 ABCDEFG，空地宽度为 3，摆放结果如图：

![image](https://hydro.ac/d/HWOD2023/p/22/file/qmHDgdIcE8iftnX0aOutT.png)

则输出结果为：

```none
AFG
BE
CD
```

**输入描述**：

输入一行字符串，通过空格分隔，前面部分为字母或数字组成的字符串 str，表示箱子； 后面部分为数字 n，表示空地的宽度。例如： `ABCDEFG 3`

**输出描述**：

箱子摆放结果，如题目示例所示

```none
AFG
BE
CD
```

1. 请不要在最后一行输出额外的空行
2. str 只包含字母和数字，1 <= len(str) <= 1000
3. 1 <= n <= 1000

**用例 1**：

输入：

```
ABCDEFG 3
```

输出：

```
AFG
BE
CD
```

难度：简单

标签：数学、数组

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  // 输入字符串和宽度
  string s;
  int n;
  cin >> s >> n;

  // 创建n行的字符串向量
  vector<string> matrix(n);

  // 控制方向的标志
  bool reverse = true;

  // 遍历输入字符串
  for (int i = 0; i < s.length(); i++) {
    // 计算基础行号
    int k = i % n;

    // 每当 i % n == 0 时，切换方向
    if (k == 0) {
      reverse = !reverse;
    }

    // 如果是反向，则行号需要反转
    if (reverse) {
      k = n - 1 - k;
    }

    // 将字符添加到对应行
    matrix[k] += s[i];
  }

  // 输出结果
  for (const auto& line : matrix) {
    cout << line << endl;
  }

  return 0;
}
```

#### 寻找关键钥匙

**题目描述**：

小强正在参加《密室逃生》游戏，当前关卡要求找到符合给定 密码 K（升序的不重复小写字母组成） 的箱子，并给出箱子编号，箱子编号为 1~N 。

每个箱子中都有一个 字符串 s ，字符串由大写字母、小写字母、数字、标点符号、空格组成，需要在这些字符串中找到所有的字母，忽略大小写后排列出对应的密码串，并返回匹配密码的箱子序号。

提示：满足条件的箱子不超过 1 个。

**输入描述**：

第一行为 key 的字符串，

第二行为箱子 boxes，为数组样式，以空格分隔

- 箱子 N 数量满足 1 ≤ N ≤ 10000,
- s 长度满足 0 ≤ s.length ≤ 50，
- 密码为仅包含小写字母的升序字符串，且不存在重复字母，
- 密码 K 长度 1 ≤ K.length ≤ 26

**输出描述**：

返回对应箱子编号

如不存在符合要求的密码箱，则返回 -1。

箱子中字符拼出的字符串与密码的匹配忽略大小写，且要求与密码完全匹配，如密码 abc 匹配 aBc，但是密码 abc 不匹配 abcd

**用例 1**：

输入：

```
abc
s,sdf134 A2c4b
```

输出：

```
2
```

说明：第 2 个箱子中的 Abc ，符合密码 abc。

**用例 2**：

输入：

```
abc
s,sdf134 A2c4bd 523[]
```

输出：

```
-1
```

说明：第 2 个箱子中的 Abcd，与密码不完全匹配，不符合要求

难度：中等

标签：哈希表、字符串、数组

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
  // 读取密码
  string key;
  cin >> key;

  // 读取箱子数组并处理
  string line;
  cin.ignore();  // 忽略换行符
  getline(cin, line);

  // 箱子遍历和处理
  int boxNum = 1;
  int start = 0, end = 0;
  while (start < line.length()) {
    // 找到下一个箱子字符串
    end = line.find(' ', start);
    if (end == string::npos)
      end = line.length();

    // 提取当前箱子字符串
    string box = line.substr(start, end - start);

    // 统计密码中字母数量
    unordered_map<char, int> keyCount;
    for (char c : key) {
      keyCount[c]++;
    }

    // 提取并处理字母
    bool match = true;
    for (char c : box) {
      if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        char lowerC = tolower(c);
        // 如果字母不在密码中，或已经超过密码中的数量
        if (keyCount.count(lowerC) == 0 || keyCount[lowerC] == 0) {
          match = false;
          break;
        }
        keyCount[lowerC]--;
      }
    }

    // 检查是否所有密码字母都被使用
    if (match) {
      for (const auto& pair : keyCount) {
        if (pair.second > 0) {
          match = false;
          break;
        }
      }
    }

    // 如果匹配，返回箱子编号
    if (match) {
      cout << boxNum << endl;
      return 0;
    }

    // 移动到下一个箱子
    start = end + 1;
    boxNum++;
  }

  // 未找到匹配的箱子
  cout << -1 << endl;
  return 0;
}
```

#### 寻找密码

**题目描述**：

小王在进行游戏大闯关，有一个关卡需要输入一个密码才能通过，密码获得的条件如下：

> 在一个密码本中，每一页都有一个由 26 个小写字母组成的若干位密码，每一页的密码不同，需要从这个密码本中寻找这样一个最长的密码，从它的末尾开始依次去掉一位得到的新密码也在密码本中存在。

请输出符合要求的密码，如果有多个符合要求的密码，则返回字典序最大的密码。

若没有符合要求的密码，则返回空字符串。

**输入描述**：

密码本由一个字符串数组组成，不同元素之间使用空格隔开，每一个元素代表密码本每一页的密码。

**输出描述**：

一个字符串

- 1 ≤ 密码本的页数 ≤ 10^5
- 1 ≤ 每页密码的长度 ≤ 10^5

**用例 1**：

输入：

```
h he hel hell hello
```

输出：

```
hello
```

说明："hello" 从末尾依次去掉一位得到的 "hell"，"hel"，"he" 和 "h" 在密码本中都存在。

**用例 2**：

输入：

```
b ereddred bw bww bwwl bwwlm bwwln
```

输出：

```
bwwln
```

说明："bwwlm " 和 "bwwln" 从末尾开始依次去掉一位得到密码在密码本中都存在。但是 "bwwln" 比 "bwwlm" 字典序排序大，所以应该返回 "bwwln"

难度：困难

标签：哈希、回溯、字符串、数组、排序、动态规划

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
  // 读取密码本
  string line;
  getline(cin, line);

  // 存储密码本
  vector<string> passwords;
  unordered_set<string> passwordSet;

  // 解析密码本
  size_t pos = 0;
  while ((pos = line.find(' ')) != string::npos) {
    string password = line.substr(0, pos);
    passwords.push_back(password);
    passwordSet.insert(password);
    line.erase(0, pos + 1);
  }
  // 处理最后一个密码
  if (!line.empty()) {
    passwords.push_back(line);
    passwordSet.insert(line);
  }

  // 按长度降序排序，长度相同时按字典序降序
  sort(passwords.begin(), passwords.end(),
       [](const string& a, const string& b) {
         if (a.length() != b.length()) {
           return a.length() > b.length();
         }
         return a > b;  // 长度相同时按字典序降序
       });

  // 寻找符合条件的最长密码
  for (const string& password : passwords) {
    bool valid = true;
    string current = password;

    // 逐步去掉末尾字符
    while (current.length() > 1) {
      current = current.substr(0, current.length() - 1);
      if (passwordSet.find(current) == passwordSet.end()) {
        valid = false;
        break;
      }
    }

    // 检查最后一个字符
    if (valid && passwordSet.find(current) != passwordSet.end()) {
      cout << password << endl;
      return 0;
    }
  }

  // 没有找到符合条件的密码
  cout << "" << endl;
  return 0;
}
```

#### 任务总执行时长

**题目描述**：

任务编排服务负责对任务进行组合调度。

参与编排的任务有两种类型，其中一种执行时长为 taskA，另一种执行时长为 taskB。

任务一旦开始执行不能被打断，且任务可连续执行。

服务每次可以编排 num 个任务。

请编写一个方法，生成每次编排后的任务所有可能的总执行时长。

**输入描述**：

第 1 行输入分别为

- 第 1 种任务执行时长 taskA
- 第 2 种任务执行时长 taskB
- 这次要编排的任务个数 num

以逗号分隔。

**输出描述**：

数组形式返回所有总执行时时长，需要按从小到大排列。

注：每种任务的数量都大于本次可以编排的任务数量

- 0 < taskA
- 0 < taskB
- 0 <= num <= 100000

**用例 1**：

输入：

```
1,2,3
```

输出：

```
[3, 4, 5, 6]
```

说明：可以执行 3 次 taskA，得到结果 3；执行 2 次 taskA 和 1 次 taskB，得到结果 4 。以此类推，得到最终结果。

难度：中等

标签：数学、排序、哈希表、数组

```cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
  // 读取输入
  string input;
  getline(cin, input);

  // 解析输入
  int taskA, taskB, num;
  sscanf(input.c_str(), "%d,%d,%d", &taskA, &taskB, &num);

  // 特殊处理：如果任务数为0，直接输出空数组
  if (num == 0) {
    cout << "[]" << endl;
    return 0;
  }

  // 存储所有可能的总执行时长
  set<int> results;

  // 遍历可能的执行组合
  for (int countA = 0; countA <= num; ++countA) {
    int countB = num - countA;
    int totalTime = countA * taskA + countB * taskB;
    results.insert(totalTime);
  }

  // 转换为有序vector并输出
  vector<int> finalResults(results.begin(), results.end());

  // 输出结果
  cout << "[";
  for (int i = 0; i < finalResults.size(); ++i) {
    cout << finalResults[i];
    if (i < finalResults.size() - 1)
      cout << ", ";
  }
  cout << "]" << endl;

  return 0;
}
```

#### 比赛的冠亚季军

**题目描述**：

有 N（3 ≤ N < 10000）个运动员，他们的 id 为 0 到 N-1, 他们的实力由一组整数表示。他们之间进行比赛，需要决出冠亚军。比赛的规则是 0 号和 1 号比赛，2 号和 3 号比赛，以此类推，每一轮，相邻的运动员进行比赛，获胜的进入下一轮；实力值大的获胜，实力值相等的情况，id 小的情况下获胜；轮空的直接进入下一轮。

**输入描述**：

输入一行 N 个数字代表 N 的运动员的实力值(0 <= 实力值 <= 10000000000)。

**输出描述**：

输出冠亚季军的 id，用空格隔开。

**用例 1**：

输入：

```
2 3 4 5
```

输出：

```
3 1 2
```

说明：

第一轮比赛，

id 为 0 实力值为 2 的运动员和 id 为 1 实力值为 3 的运动员比赛，1 号胜出进入下一轮争夺冠亚军，

id 为 2 的运动员和 id 为 3 的运动员比赛，3 号胜出进入下一轮争夺冠亚军，

冠亚军比赛，3 号胜 1 号，

故冠军为 3 号，亚军为 1 号，2 号与 0 号，比赛进行季军的争夺，2 号实力值为 4，0 号实力值 2，故 2 号胜出，得季军。冠亚季军为 3 1 2。

难度：中等

标签：数组、队列、排序、贪心

```cpp
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // 读取实力值
  vector<long> strengths;
  long strength;
  while (cin >> strength) {
    strengths.push_back(strength);
  }

  // 初始化运动员ID
  vector<int> sports;
  for (int i = 0; i < strengths.size(); ++i) {
    sports.push_back(i);
  }

  // 比赛分组队列
  deque<vector<int>> match_groups;
  match_groups.push_front(sports);

  // 进行淘汰赛
  while (match_groups.front().size() > 1) {
    // 取出当前分组
    vector<int> current_group = match_groups.front();
    match_groups.pop_front();

    // 胜者和败者分组
    vector<int> winners, losers;

    // 两两比赛
    for (int i = 1; i < current_group.size(); i += 2) {
      int id1 = current_group[i - 1];  // 序号小的选手
      int id2 = current_group[i];      // 序号大的选手

      // 比较规则：实力不同按实力，相同按id
      if (strengths[id1] > strengths[id2]) {
        winners.push_back(id1);
        losers.push_back(id2);
      } else if (strengths[id1] < strengths[id2]) {
        winners.push_back(id2);
        losers.push_back(id1);
      } else {
        // 实力相同，id小的获胜
        winners.push_back(id1);
        losers.push_back(id2);
      }
    }

    // 处理奇数情况
    if (current_group.size() % 2 != 0) {
      winners.push_back(current_group.back());
    }

    // 压入败者组和胜者组
    match_groups.push_front(losers);
    match_groups.push_front(winners);
  }

  // 确定冠军
  int first = match_groups[0][0];

  // 确定亚军
  int second = match_groups[1][0];

  // 确定季军（排序处理）
  sort(match_groups[2].begin(), match_groups[2].end(),
       [&strengths](int a, int b) {
         return strengths[a] != strengths[b] ? strengths[a] > strengths[b]
                                             : a < b;
       });
  int third = match_groups[2][0];

  // 输出结果
  cout << first << " " << second << " " << third << endl;

  return 0;
}
```

#### 最多提取子串数目

**题目描述**：

给定 [a-z]，26 个英文字母小写字符串组成的字符串 A 和 B，其中 A 可能存在重复字母，B 不会存在重复字母，现从字符串 A 中按规则挑选一些字母，可以组成字符串 B。

挑选规则如下：

1. 同一个位置的字母只能挑选一次

2. 被挑选字母的相对先后顺序不能被改变

求最多可以同时从 A 中挑选多少组能组成 B 的字符串。

**输入描述**：

输入为 2 行，第 1 行输入字符串 A，第 2 行输入字符串 B，行首行尾没有多余空格，其中：

1. A、B 均由 [a-z] 26 个英文小写字母组成

2. 0 < A.length < 100，A 中可能包含重复字母

3. 0 < B.length < 10，B 中不会出现重复字母

**输出描述**：

输出 1 行，包含 1 个数字，表示最多可以同时从 A 中挑选多少组能组成 B 的字符串

行末没有多余空格

无需验证输入格式和输入数据合法性
**用例 1**：

输入：

```
badc
bac
```

输出：

```
1
```

说明：从字符串 A（"badc"）中可以按字母相对先后顺序取出字符串 B（"bac"）

**用例 2**：

输入：

```
badc
abc
```

输出：

```
0
```

说明：从字符串 A（"badc"）中无法按字母相对先后顺序取出字符串 B（"bac"）

**用例 3**：

输入：

```
aabbcxd
abcd
```

输出：

```
1
```

说明：从字符串 A（"aabbcxd"）中挑选一组 B（"abcd"）后，A 中剩余字符串为 "abx"，无法再挑选出 "abcd"

**用例 4**：

输入：

```
ababcecfdc
abc
```

输出：

```
2
```

说明：

从按如下步骤（步骤不唯一），可以同时从字符串 A（"ababcecfdc"）中最多取出两个 B（"abc"），其中颜色标注的是每步提取的字母：

![img](https://hydro.ac/d/HWOD2023/p/35/file/mZPIagqxZn6-S0bU0-3QB.png)

剩余的 "efdc" 无法继续提取 "abc"，结果为 2

**用例 5**：

输入：

```
aaa
a
```

输出：

```
3
```

说明：从字符串 A（"aaa"）中可以挑选出 3 个字符串 B（"a"）

难度：中等

标签：哈希表、字符串、贪心、动态规划

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  // 读取输入字符串
  string source, target;
  cin >> source >> target;

  // 记录目标字符串中每个字符的所有位置
  unordered_map<char, vector<int>> charPositions;
  for (int i = 0; i < target.length(); ++i) {
    charPositions[target[i]].push_back(i);
  }

  // 记录每个字符匹配的计数
  vector<int> matchCount(target.length(), 0);

  // 遍历源字符串
  for (char currentChar : source) {
    // 检查当前字符是否在目标字符串中
    if (charPositions.count(currentChar)) {
      // 遍历该字符在目标字符串中的位置
      for (int pos : charPositions[currentChar]) {
        // 匹配条件：
        // 1. 首个字符直接匹配
        // 2. 非首个字符需要前一个位置已经匹配
        if (pos == 0 || matchCount[pos - 1] > matchCount[pos]) {
          matchCount[pos]++;
          break;  // 匹配成功后跳出
        }
      }
    }
  }

  // 输出最终匹配数量
  cout << matchCount.back() << endl;

  return 0;
}
```

### 200 分

#### 中文分词模拟器

**题目描述**：

给定一个连续不包含空格的字符串，该字符串仅包含英文小写字母及英文标点符号（逗号、分号、句号），同时给定词库，对该字符串进行精确分词。

说明：

1. 精确分词：字符串分词后，不会出现重叠。即 "ilovechina"，不同词库可分割为 "i, love, china"，"ilove, china"，不能分割出现重叠的 "i, ilove, china"，i 出现重叠

2. 标点符号不成词，仅用于断句

3. 词库：根据外部知识库统计出来的常用词汇例：dictionary = ["i", "love", "china", "lovechina", "ilove"]

4. 分词原则：采用分词顺序优先且最长匹配原则

   "ilovechina"，假设分词结果 [i, ilove, lo, love, ch, china, lovechina]，则输出 [ilove, china]

   错误输出：[i, lovechina]，原因："ilove" > 优先于 "lovechina" 成词

   错误输出：[i, love, china]，原因："ilove" > "i" 遵循最长匹配原则

**输入描述**：

第一行输入待分词语句 "ilovechina"

- 字符串长度限制：0 < length < 256

第二行输入中文词库 "i, love, china, ch, na, ve, lo, this, is, this, word"

- 词库长度限制：1 < length < 100000

**输出描述**：

按顺序输出分词结果 "i, love, china"

**用例 1**：

输入：

```
ilovechina
i,love,china,ch,na,ve,lo,this,is,the,word
```

输出：

```
i,love,china
```

**用例 2**：

输入：

```
iat
i,love,china,ch,na,ve,lo,this,is,the,word,beauti,tiful,ful
```

输出：

```
i,a,t
```

说明：

单个字母，

不在词库中且不成词则输出单个字母

**用例 3**：

输入：

```
ilovechina,thewordisbeautiful
i,love,china,ch,na,ve,lo,this,is,the,word,beauti,tiful,ful
```

输出：

```
i,love,china,the,word,is,beauti,ful
```

说明：标点符号为英文标点符号

难度：中等

标签：动态规划、字符串、贪心、哈希表

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  // ---------- 1. 读取输入 ----------
  string text, dict_str;
  getline(cin, text);
  getline(cin, dict_str);

  // ---------- 2. 构建可用词典 ----------
  // 这里用 multiset 或者 map 记录词频更灵活，方便控制每个词可使用几次
  // 如果只想用一次，用 set 也行，一旦匹配后就直接 erase
  multiset<string> dictionary;
  {
    stringstream ss(dict_str);
    string w;
    while (getline(ss, w, ',')) {
      // 去除可能的空格
      w.erase(remove_if(w.begin(), w.end(), ::isspace), w.end());
      if (!w.empty()) {
        dictionary.insert(w);
      }
    }
  }

  // ---------- 3. 分词处理 ----------
  vector<string> result;
  int n = text.size();
  int start = 0;
  while (start < n) {
    // 如果当前字符是标点，就跳过
    if (text[start] == ',' || text[start] == '.' || text[start] == ';') {
      start++;
      continue;
    }

    // 从大到小尝试，找最长匹配
    bool matched = false;
    for (int len = n - start; len > 0; len--) {
      string candidate = text.substr(start, len);
      // 如果字典中有这个候选词，则使用它
      auto it = dictionary.find(candidate);
      if (it != dictionary.end()) {
        result.push_back(candidate);
        // 用完就移除，使得后续不能再匹配到同一个词
        dictionary.erase(it);
        start += len;
        matched = true;
        break;
      }
    }

    // 如果没有匹配到，就把当前字符当作单字输出
    if (!matched) {
      result.push_back(string(1, text[start]));
      start++;
    }
  }

  // ---------- 4. 输出结果 ----------
  for (int i = 0; i < (int)result.size(); i++) {
    cout << result[i];
    if (i < (int)result.size() - 1) {
      cout << ",";
    }
  }
  cout << endl;

  return 0;
}
```

#### 最大社交距离

**题目描述**：

疫情期间需要大家保证一定的社交距离，公司组织开交流会议。

座位一排共 N 个座位，编号分别为 [0, N - 1] 。

要求员工一个接着一个进入会议室，并且可以在任何时候离开会议室。

满足：

- 每当一个员工进入时，需要坐到最大社交距离（最大化自己和其他人的距离的座位）；
- 如果有多个这样的座位，则坐到索引最小的那个座位。

**输入描述**：

会议室座位总数 seatNum

- 1 ≤ seatNum ≤ 500

员工的进出顺序 seatOrLeave 数组

- 元素值为 1，表示进场

- 元素值为负数，表示出场（特殊：位置 0 的员工不会离开）

  例如 -4 表示坐在位置 4 的员工离开（保证有员工坐在该座位上）

**输出描述**：

最后进来员工，他会坐在第几个位置，如果位置已满，则输出-1。

**用例 1**：

输入：

```
10
[1, 1, 1, 1, -4, 1]
```

输出：

```
5
```

说明：

seat -> 0, 空在任何位置都行，但是要给他安排索引最小的位置，也就是座位 0

seat -> 9, 要和旁边的人距离最远，也就是座位 9

seat -> 4, 要和旁边的人距离最远，应该坐到中间，也就是座位 4

seat -> 2, 员工最后坐在 2 号座位上

leave [4], 4 号座位的员工离开

seat -> 5, 员工最后坐在 5 号座位上

难度：中等

标签：堆（优先队列）、有序集合

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  // 读取座位总数
  int seat_num;
  cin >> seat_num;
  cin.ignore();  // 忽略换行符

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
      it++;

      for (; it != occupied_seats.end(); it++) {
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
```

#### 学生方阵

**题目描述**：

学校组织活动，将学生排成一个矩形方阵。

请在矩形方阵中找到最大的位置相连的男生数量。

这个相连位置在一个直线上，方向可以是水平的，垂直的，成对角线的或者呈反对角线的。

注：学生个数不会超过 10000

**输入描述**：

输入的第一行为矩阵的行数和列数，接下来的 n 行为矩阵元素，元素间用 "," 分隔。

**输出描述**：

输出一个整数，表示矩阵中最长的位置相连的男生个数。

**用例 1**：

输入：

```
3,4
F,M,M,F
F,M,M,F
F,F,F,M
```

输出：

```
3
```

说明：

![image](https://hydro.ac/d/HWOD2023/p/164/file/lymKEffZJQdvPyYvdAh6H.png)

难度：中等

标签：动态规划、数组、矩阵

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  // 读取矩阵大小
  string size_str;
  getline(cin, size_str);
  int pos = size_str.find(',');
  int rows = stoi(size_str.substr(0, pos));
  int cols = stoi(size_str.substr(pos + 1));

  // 定义方向数组
  const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  // 读取矩阵
  vector<vector<char>> matrix(rows, vector<char>(cols));
  for (int i = 0; i < rows; i++) {
    string row_str;
    getline(cin, row_str);

    // 解析每一行
    int start = 0;
    int col = 0;
    while (start < row_str.length()) {
      int comma_pos = row_str.find(',', start);
      if (comma_pos == string::npos) {
        matrix[i][col++] = row_str[start];
        break;
      }
      matrix[i][col++] = row_str.substr(start, comma_pos - start)[0];
      start = comma_pos + 1;
    }
  }

  // 最大连续男生数量
  int max_connected = 0;

  // 遍历每个位置作为起点
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      // 只有男生才开始搜索
      if (matrix[i][j] == 'M') {
        // 尝试八个方向
        for (int dir = 0; dir < 8; dir++) {
          int length = 1;
          int nx = i + dx[dir];
          int ny = j + dy[dir];

          // 延伸这个方向直到不再是男生为止
          while (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
                 matrix[nx][ny] == 'M') {
            length++;
            nx += dx[dir];
            ny += dy[dir];
          }

          // 更新最大值
          max_connected = max(max_connected, length);
        }
      }
    }
  }

  // 输出结果
  cout << max_connected << endl;

  return 0;
}
```

#### 转骰子

**题目描述**：

骰子是一个立方体，每个面一个数字，初始为左 1，右 2，前 3(观察者方向)，后 4，上 5，下 6，用 123456 表示这个状态，放置在平面上，

- 可以向左翻转(用 L 表示向左翻转 1 次)，
- 可以向右翻转(用 R 表示向右翻转 1 次)，
- 可以向前翻转(用 F 表示向前翻转 1 次)，
- 可以向后翻转(用 B 表示向后翻转 1 次)，
- 可以逆时针旋转(用 A 表示逆时针旋转 90 度)，
- 可以顺时针旋转(用 C 表示顺时针旋转 90 度)，

现从 123456 这个初始状态开始，根据输入的动作序列，计算得到最终的状态。

骰子的初始状态和初始状态转动后的状态如图所示。

![img](https://hydro.ac/d/HWOD2023/p/93/file/bhPDxGEz-gmfC1pHgxx38.png)

**输入描述**：

输入一行，为只包含 LRFBAC 的字母序列，最大长度为 50，字母可重复。

**输出描述**：

输出最终状态

**用例 1**：

输入：

```
LR
```

输出：

```
123456
```

说明：骰子先向左翻转，再向右翻转回来，故还是原来的状态 123456

**用例 2**：

输入：

```
FCR
```

输出：

```
342156
```

说明：骰子向前翻转，状态变为 125643，再顺时针旋转，状态变为 651243，最后向右翻转，状态变为 342156

难度：中等

标签：数组

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  // 定义骰子面的初始状态
  int left = 1, right = 2, front = 3, back = 4, top = 5, bottom = 6;

  // 读取输入的操作序列
  string moves;
  cin >> moves;

  // 处理每个操作
  for (char move : moves) {
    // 使用临时变量保存旋转前的状态
    int tmp;
    switch (move) {
      case 'L':  // 左翻转
        tmp = right;
        right = bottom;
        bottom = left;
        left = top;
        top = tmp;
        break;
      case 'R':  // 右翻转
        tmp = left;
        left = bottom;
        bottom = right;
        right = top;
        top = tmp;
        break;
      case 'F':  // 前翻转
        tmp = front;
        front = top;
        top = back;
        back = bottom;
        bottom = tmp;
        break;
      case 'B':  // 后翻转
        tmp = top;
        top = front;
        front = bottom;
        bottom = back;
        back = tmp;
        break;
      case 'A':  // 逆时针旋转
        tmp = right;
        right = front;
        front = left;
        left = back;
        back = tmp;
        break;
      case 'C':  // 顺时针旋转
        tmp = front;
        front = right;
        right = back;
        back = left;
        left = tmp;
        break;
    }
  }

  // 输出最终状态
  cout << left << right << front << back << top << bottom << endl;

  return 0;
}
```

#### 九宫格按键输入

**题目描述**：

九宫格按键输入，有英文和数字两个模式，默认是数字模式，数字模式直接输出数字，英文模式连续按同一个按键会依次出现这个按键上的字母，如果输入 "/" 或者其他字符，则循环中断，输出此时停留的字母。

数字和字母的对应关系如下，注意 0 只对应空格：

![img](https://hydro.ac/d/HWOD2023/p/70/file/CmTn6T1BrZ9Eix1siFqlk.png)

输入一串按键，要求输出屏幕显示

- \#用于切换模式，默认是数字模式，执行 # 后切换为英文模式；
- /表示延迟，例如在英文模式下，输入 22/222，显示为 bc，数字模式下 / 没有效果；
- 英文模式下，多次按同一键，例如输入 22222，显示为 b；

**输入描述**：

输入范围为数字 0~9 和字符’#’、’/’，输出屏幕显示，例如:

- 在数字模式下，输入 1234，显示 1234
- 在英文模式下，输入 1234，显示, adg

**输出描述**：

输出屏幕显示的字符

**用例 1**：

输入：

```
2222/22
```

输出：

```
222222
```

说明：默认数字模式，字符直接显示，数字模式下/无序

**用例 2**：

输入：

```
#2222/22
```

输出：

```
ab
```

说明：\#进入英文模式，连续的数字输入会循环选择字母，直至输入/，故第一段 2222 输入显示 a，第二段 22 输入显示 b

**用例 3**：

输入：

```
#222233
```

输出：

```
ae
```

说明：\#进入英文模式，连续的数字输入会循环选择字母，直至输入/，故第一段 2222 输入显示 a，第二段 22 输入显示 b

难度：中等

标签：数组

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  vector<string> dic = {" ",   ",.",  "abc",  "def", "ghi",
                        "jkl", "mno", "pqrs", "tuv", "wxyz"};

  string input_string;
  cin >> input_string;

  input_string += '/';

  string result;
  bool is_num_mode = true;
  int delay_num = -1;
  int delay_idx = -1;

  for (const auto& current_char : input_string) {
    // 处理模式切换
    if (current_char == '#') {
      is_num_mode = !is_num_mode;
    }

    // 处理中断情况
    if (current_char == '#' || current_char == '/') {
      // 如果之前有英文输入
      if (delay_num != -1) {
        result += dic[delay_num][delay_idx];
      }

      // 更新delay_num和delay_idx
      if (current_char == '#' || current_char == '/') {
        delay_num = -1;
        delay_idx = -1;
      } else {
        delay_num = current_char - '0';
        delay_idx = 0;
      }
    } else if (is_num_mode) {
      // 数字模式下, 数字直接录入结果
      result += current_char;
    } else if (current_char - '0' == delay_num) {
      // 英文模式下, 如果当前按键与上一次按键相同, 则进行英文字母切换
      delay_idx += 1;
      delay_idx %= dic[delay_num].length();
    } else {
      // 英文模式下, 如果当前按键与上一次按键不同, 则打断英文字母切换动作
      // 如果之前有英文输入
      if (delay_num != -1) {
        result += dic[delay_num][delay_idx];
      }

      // 更新delay_num和delay_idx
      delay_num = current_char - '0';
      delay_idx = 0;
    }
  }

  cout << result << endl;

  return 0;
}
```

#### 打印任务排序

**题目描述**：

某个打印机根据打印队列执行打印任务。打印任务分为九个优先级，分别用数字 1-9 表示，数字越大优先级越高。打印机每次从队列头部取出第一个任务 A，

然后检查队列余下任务中有没有比 A 优先级更高的任务，如果有比 A 优先级高的任务，则将任务 A 放到队列尾部，否则就执行任务 A 的打印。

请编写一个程序，根据输入的打印队列，输出实际的打印顺序。

**输入描述**：

输入一行，为每个任务的优先级，优先级之间用逗号隔开，优先级取值范围是 1~9。

**输出描述**：

输出一行，为每个任务的打印顺序，打印顺序从 0 开始，用逗号隔开

**用例 1**：

输入：

```
9,3,5
```

输出：

```
0,2,1
```

说明：

队列头部任务的优先级为 9，最先打印，故序号为 0；

接着队列头部任务优先级为 3，队列中还有优先级为 5 的任务，优先级 3 任务被移到队列尾部；

接着打印优先级为 5 的任务，故其序号为 1；

最后优先级为 3 的任务的序号为 2。

**用例 2**：

输入：

```
1,2,2
```

输出：

```
2,0,1
```

说明：

队列头部任务的优先级为 1，被移到队列尾部；接着顺序打印两个优先级为 2 的任务，故其序号分别为 0 和 1；最后打印剩下的优先级为 1 的任务，其序号为 2

难度：中等

标签：队列、贪心、数组

```cpp
#include <bits/stdc++.h>

using namespace std;

struct Task {
  int priority;  // 任务优先级
  int index;     // 原始索引
};

int main() {
  // 读取输入
  string input;
  cin >> input;

  // 解析输入
  vector<Task> tasks;
  stringstream ss(input);
  string priority;
  int idx = 0;

  // 解析优先级
  while (getline(ss, priority, ',')) {
    tasks.push_back({stoi(priority), idx++});
  }

  // 打印顺序
  vector<int> print_order(tasks.size());

  // 打印计数器
  int print_count = 0;

  // 任务队列
  queue<Task> task_queue;
  for (const auto& task : tasks) {
    task_queue.push(task);
  }

  // 模拟打印过程
  while (!task_queue.empty()) {
    // 当前任务
    Task current = task_queue.front();
    task_queue.pop();

    // 检查是否有更高优先级的任务
    bool has_higher_priority = false;
    queue<Task> temp_queue = task_queue;
    while (!temp_queue.empty()) {
      if (temp_queue.front().priority > current.priority) {
        has_higher_priority = true;
        break;
      }
      temp_queue.pop();
    }

    // 如果有更高优先级，放到队尾
    if (has_higher_priority) {
      task_queue.push(current);
    }
    // 否则打印任务
    else {
      print_order[current.index] = print_count++;
    }
  }

  // 输出打印顺序
  for (int i = 0; i < print_order.size(); ++i) {
    cout << print_order[i];
    if (i < print_order.size() - 1) {
      cout << ",";
    }
  }
  cout << endl;

  return 0;
}
```

#### 推荐多样性

**题目描述**：

推荐多样性需要从多个列表中选择元素，一次性要返回 N 屏数据（窗口数量），每屏展示 K 个元素（窗口大小），选择策略：

1. 各个列表元素需要做穿插处理，即先从第一个列表中为每屏选择一个元素，再从第二个列表中为每屏选择一个元素，依次类推

2. 每个列表的元素尽量均分为 N 份，如果不够 N 个，也要全部分配完，参考样例图：

   （1）从第一个列表中选择 4 条 0 1 2 3，分别放到 4 个窗口中

   （2）从第二个列表中选择 4 条 10 11 12 13，分别放到 4 个窗口中

   （3）从第三个列表中选择 4 条 20 21 22 23，分别放到 4 个窗口中

   （4）再从第一个列表中选择 4 条 4 5 6 7，分别放到 4 个窗口中

   ...

   （5）再从第一个列表中选择，由于数量不足 4 条，取剩下的 2 条，放到 窗口 1 和 窗口 2

   （6）再从第二个列表中选择，由于数量不足 4 条并且总的元素数达到窗口要求，取 18 19 放到 窗口 3 和 窗口 4

![image](https://hydro.ac/d/HWOD2023/p/408/file/vOXMJ3o5W6E1mjeor1InX.png)

**输入描述**：

第一行输入为 N，表示需要输出的窗口数量，取值范围 [1, 10]

第二行输入为 K，表示每个窗口需要的元素数量，取值范围 [1, 100]

之后的行数不定（行数取值范围 [1, 10]），表示每个列表输出的元素列表。元素之间以空格隔开，已经过排序处理，每个列表输出的元素数量取值范围 [1, 100]

**输出描述**：

输出元素列表，元素数量 = 窗口数量 \* 窗口大小，元素之间以空格分隔，多个窗口合并为一个列表输出，参考样例：

先输出窗口 1 的元素列表，再输出窗口 2 的元素列表，再输出窗口 3 的元素列表，最后输出窗口 4 的元素列表

1. 每个列表会保证元素数量满足窗口要求，不需要考虑元素不足情况
2. 每个列表的元素已去重，不需要考虑元素重复情况
3. 每个列表的元素列表均不为空，不需要考虑列表为空的情况
4. 每个列表的元素列表已经过排序处理，输出结果要保证不改变同一个列表的元素顺序
5. 每个列表的元素数量可能是不同的

**用例 1**：

输入：

```
4
7
0 1 2 3 4 5 6 7 8 9
10 11 12 13 14 15 16 17 18 19
20 21 22 23 24 25 26 27 28 29
```

输出：

```
0 10 20 4 14 24 8 1 11 21 5 15 25 9 2 12 22 6 16 26 18 3 13 23 7 17 27 19
```

难度：中等

标签：数组、贪心

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k;
  cin >> n >> k;
  cin.ignore();

  vector<vector<int>> lists;
  string line;

  // 读取列表
  while (getline(cin, line)) {
    vector<int> current_list;
    istringstream ss(line);
    int num;
    while (ss >> num) {
      current_list.push_back(num);
    }
    lists.push_back(current_list);
  }

  int size = k * n;
  vector<int> windows(size);
  int idx = 0;
  int level = 0;

  while (idx < size) {
    bool flag = false;

    // 从每个列表中选择 n 个元素
    for (int i = 0; i < n; i++) {
      if (!lists[level].empty()) {
        windows[idx++] = lists[level].front();
        lists[level].erase(lists[level].begin());

        // 如果当前列表为空，删除并调整
        if (lists[level].empty() && lists.size() > 1) {
          lists.erase(lists.begin() + level);
          level %= lists.size();
          flag = true;
        }
      }
    }

    // 如果没有发生"借"动作，切换到下一行
    if (!flag) {
      level = (level + 1) % lists.size();
    }
  }

  // 按列输出
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < k; i++) {
      cout << windows[i * n + j];
      if (i * n + j < size - 1)
        cout << " ";
    }
  }
  cout << endl;

  return 0;
}
```

#### 运输时间

**题目描述**：

M（1 ≤ M ≤ 20）辆车需要在一条不能超车的单行道到达终点，起点到终点的距离为 N（1 ≤ N ≤ 400）。

速度快的车追上前车后，只能以前车的速度继续行驶，求最后一辆车到达目的地花费的时间。

注：每辆车固定间隔 1 小时出发，比如第一辆车 0 时出发，第二辆车 1 时出发，依次类推

**输入描述**：

第一行两个数字：M N，分别代表车辆数和到终点的距离，以空格分隔

接下来 M 行，每行一个数字 S，代表每辆车的速度。0 < S < 30

**输出描述**：

最后一辆车到达目的地花费的时间

**用例 1**：

输入：

```
2 11
3
2
```

输出：

```
5.5
```

说明：2 辆车，距离 11，0 时出发的车速度快，1 时出发的车，到达目的地花费 5.5

难度：简单

标签：数组、贪心

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int M, N;
  cin >> M >> N;

  vector<double> arrive_times(M);

  // 读取每辆车的速度
  for (int i = 0; i < M; i++) {
    double speed;
    cin >> speed;

    // 正常情况下的到达时间
    double normal_arrive_time = (double)N / speed + i;

    // 如果不是第一辆车，需要比较是否被前车阻碍
    if (i > 0) {
      // 前一辆车的到达时间
      double prev_arrive_time = arrive_times[i - 1];

      // 如果正常行驶到达时间早于前车到达时间，则被阻碍
      arrive_times[i] = max(normal_arrive_time, prev_arrive_time);
    } else {
      // 第一辆车正常行驶
      arrive_times[i] = normal_arrive_time;
    }
  }
  // 输出最后一辆车的行驶时间（到达时刻 - 出发时刻）
  cout << fixed << setprecision(1) << arrive_times[M - 1] - (M - 1) << endl;

  return 0;
}
```

#### 最优资源分配

**题目描述**：

某块业务芯片最小容量单位为 1.25G，总容量为 M\*1.25G，对该芯片资源编号为 1，2，...，M。该芯片支持 3 种不同的配置，分别为 A、B、C。

- 配置 A：占用容量为 1.25 \* 1 = 1.25G
- 配置 B：占用容量为 1.25 \* 2 = 2.5G
- 配置 C：占用容量为 1.25 \* 8 = 10G 某块板卡上集成了 N 块上述芯片，对芯片编号为 1，2，...，N，各个芯片之间彼此独立，不能跨芯片占用资源。

给定板卡上芯片数量 N、每块芯片容量 M、用户按次序配置后，请输出芯片资源占用情况，保证消耗的芯片数量最少。

资源分配规则：按照芯片编号从小到大分配所需资源，芯片上资源如果被占用标记为 1，没有被占用标记为 0.

用户配置序列：用户配置是按次序依次配置到芯片中，如果用户配置序列种某个配置超过了芯片总容量，丢弃该配置，继续遍历用户后续配置。

**输入描述**：

M：每块芯片容量为 M \* 1.25G，取值范围为：1~256

N：每块板卡包含芯片数量，取值范围为 1~32

用户配置序列：例如 ACABA，长度不超过 1000

**输出描述**：

板卡上每块芯片的占用情况

用户配置是按次序依次配置到芯片中，如果用户配置序列种某个配置超过了芯片总容量，丢弃该配置，继续遍历用户后续配置。

**用例 1**：

输入：

```
8
2
ACABA
```

输出：

```
11111000
11111111
```

说明：

用户第 1 个配置 A：占用第 1 块芯片第 1 个资源，芯片占用情况为：

10000000

00000000

用户第 2 个配置 C：第 1 块芯片剩余 8.75G，配置 C 容量不够，只能占用第 2 块芯片，芯片占用情况为：

10000000

11111111

用户第 3 个配置 A：第 1 块芯片剩余 8.75G，还能继续配置，占用第 1 块芯片第 2 个资源，芯片占用情况为：

11000000

11111111

用户第 4 个配置 B：第 1 块芯片剩余 7.5G，还能继续配置，占用第 1 块芯片第 3、4 个资源，芯片占用情况为：

11110000

11111111

用户第 5 个配置 A：第 1 块芯片剩余 5G，还能继续配置，占用第 1 块芯片第 5 个资源，芯片占用情况为：

11111000

11111111

**用例 2**：

输入：

```
8
2
ACBCB
```

输出：

```
11111000
11111111
```

说明：

用户第 1 个配置 A：占用第 1 块芯片第 1 个资源，芯片占用情况为：

10000000

00000000

用户第 2 个配置 C：第 1 块芯片剩余 8.75G，配置 C 容量不够，只能占用第 2 块芯片，芯片占用情况为：

10000000

11111111

用户第 3 个配置 B：第 1 块芯片剩余 8.75G，还能继续配置，占用第 1 块芯片第 2、3 个资源，芯片占用情况为：

11100000

11111111

用户第 4 个配置 C：芯片资源不够，丢弃配置，继续下一个配置，本次配置后芯片占用情况保持不变：

11100000

11111111

用户第 5 个配置 B：第 1 块芯片剩余 6.25G, 还能继续配置，占用第 1 块芯片第 4、5 个资源，芯片占用情况为：

11111000

11111111

难度：中等

标签：贪心、数组

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  int M, N;
  string config;

  // 1. 读取输入
  cin >> M >> N >> config;

  // 2. 定义资源分配数组
  vector<vector<int>> chip_resources(N, vector<int>(M, 0));

  // 配置资源消耗映射
  int config_consume[3] = {1, 2, 8};  // A, B, C 对应的资源占用

  // 3. 遍历用户配置序列
  for (char c : config) {
    // 计算当前配置需要的资源数量
    int consume = 0;
    if (c == 'A')
      consume = 1;
    else if (c == 'B')
      consume = 2;
    else if (c == 'C')
      consume = 8;

    // 4. 尝试分配资源
    bool allocated = false;
    for (int i = 0; i < N; ++i) {
      // 统计当前芯片已使用的资源
      int used_resources = 0;
      for (int j = 0; j < M; ++j) {
        used_resources += chip_resources[i][j];
      }

      // 检查是否有足够的剩余资源
      if (M - used_resources >= consume) {
        // 分配资源
        int start = 0;
        while (start < M && chip_resources[i][start] == 1)
          start++;

        for (int j = start; j < start + consume; ++j) {
          chip_resources[i][j] = 1;
        }

        allocated = true;
        break;
      }
    }

    // 如果无法分配，则丢弃当前配置
    if (!allocated) {
      continue;
    }
  }

  // 5. 输出资源分配结果
  for (const auto& chip : chip_resources) {
    for (int resource : chip) {
      cout << resource;
    }
    cout << endl;
  }

  return 0;
}
```

#### 机房布局

**题目描述**：

小明正在规划一个大型数据中心机房，为了使得机柜上的机器都能正常满负荷工作，需要确保在每个机柜边上至少要有一个电箱。

为了简化题目，假设这个机房是一整排，M 表示机柜，I 表示间隔，请你返回这整排机柜，至少需要多少个电箱。 如果无解请返回 -1 。

**输入描述**：

cabinets = "MIIM"

其中 M 表示机柜，I 表示间隔

**输出描述**：

2

表示至少需要 2 个电箱

- 1 ≤ strlen(cabinets) ≤ 10000
- 其中 cabinets [i] = 'M' 或者 'I'

**用例 1**：

输入：

```
MIIM
```

输出：

```
2
```

**用例 2**：

输入：

```
MIM
```

输出：

```
1
```

**用例 3**：

输入：

```
M
```

输出：

```
-1
```

**用例 4**：

输入：

```
MMM
```

输出：

```
-1
```

**用例 5**：

输入：

```
I
```

输出：

```
0
```

难度：中等

标签：贪心、字符串

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
  string cabinets;
  cin >> cabinets;

  int n = cabinets.length();
  int electric_boxes = 0;

  // 特殊情况处理
  if (n == 1) {
    return cout << (cabinets[0] == 'I' ? 0 : -1), 0;
  }

  for (int i = 0; i < n;) {
    // 找到机柜
    while (i < n && cabinets[i] == 'I') {
      i++;
    }

    // 已经遍历完
    if (i >= n)
      break;

    // 优先在右侧放电箱
    if (i + 1 < n && cabinets[i + 1] == 'I') {
      electric_boxes++;
      i += 3;  // 跳过当前机柜和放电箱的间隔，以及下一个位置
    }
    // 在左侧放电箱
    else if (i > 0 && cabinets[i - 1] == 'I') {
      electric_boxes++;
      i++;
    }
    // 无法放置电箱
    else {
      return cout << -1, 0;
    }
  }

  cout << electric_boxes << endl;
  return 0;
}
```

#### 德州扑克

**题目描述**：

五张牌，每张牌由牌大小和花色组成，牌大小 2~10、J、Q、K、A，牌花色为红桃、黑桃、梅花、方块四种花色之一。

判断牌型:

- 牌型 1，同花顺：同一花色的顺子，如红桃 2 红桃 3 红桃 4 红桃 5 红桃 6。
- 牌型 2，四条：四张相同数字 + 单张，如红桃 A 黑桃 A 梅花 A 方块 A + 黑桃 K。
- 牌型 3，葫芦：三张相同数字 + 一对，如红桃 5 黑桃 5 梅花 5 + 方块 9 梅花 9。
- 牌型 4，同花：同一花色，如方块 3 方块 7 方块 10 方块 J 方块 Q。
- 牌型 5，顺子：花色不一样的顺子，如红桃 2 黑桃 3 红桃 4 红桃 5 方块 6。
- 牌型 6，三条：三张相同+两张单。

说明：

1. 五张牌里不会出现牌大小和花色完全相同的牌
2. 编号小的牌型较大，如同花顺比四条大，依次类推。
3. 包含 A 的合法的顺子只有 10 J Q K A 和 A 2 3 4 5; 类似 K A 2 3 4 的序列不认为是顺子。

**输入描述**：

输入由 5 行组成，每行为一张牌大小和花色，牌大小为 2~10、J、Q、K、A，花色分别用字符 H、S、C、D 表示红桃、黑桃、梅花、方块。

**输出描述**：

输出牌型序号，5 张牌符合多种牌型时，取最大的牌型序号输出。

**用例 1**：

输入：

```
4 H
5 S
6 C
7 D
8 D
```

输出：

```
5
```

说明：4 5 6 7 8 构成顺子，输出 5

**用例 2**：

输入：

```
9 S
5 S
6 S
7 S
8 S
```

输出：

```
1
```

说明：既是顺子又是同花，输出 1，同花顺

难度：中等

标签：数组、哈希表、排序

```cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  // 牌值转换映射
  unordered_map<string, int> cardValues = {
      {"2", 2}, {"3", 3},   {"4", 4},  {"5", 5},  {"6", 6},  {"7", 7}, {"8", 8},
      {"9", 9}, {"10", 10}, {"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}};

  // 读取牌面和花色
  vector<int> values;
  vector<char> suits;
  unordered_map<int, int> valueCount;
  unordered_map<char, int> suitCount;

  // 读入5张牌
  for (int i = 0; i < 5; i++) {
    string card;
    cin >> card;
    char suit;
    cin >> suit;

    // 转换牌面值
    int value = cardValues[card];
    values.push_back(value);
    suits.push_back(suit);

    // 统计牌面和花色数量
    valueCount[value]++;
    suitCount[suit]++;
  }

  // 排序牌面值
  sort(values.begin(), values.end());

  // 判断特殊顺子
  bool isSpecialStraight =
      (values == vector<int>{14, 2, 3, 4, 5}) ||    // A2345
      (values == vector<int>{10, 11, 12, 13, 14});  // 10JQKA

  // 判断普通顺子
  bool isStraight = (values.back() - values.front() == 4 &&
                     set<int>(values.begin(), values.end()).size() == 5) ||
                    isSpecialStraight;

  // 判断同花
  bool isFlush = suitCount.size() == 1;

  // 找出最大重复数和次大重复数
  int maxSameCount = 0, secondMaxSameCount = 0;
  for (const auto& [value, count] : valueCount) {
    if (count > maxSameCount) {
      secondMaxSameCount = maxSameCount;
      maxSameCount = count;
    } else if (count > secondMaxSameCount) {
      secondMaxSameCount = count;
    }
  }

  // 牌型判断（按优先级）
  int result = 7;  // 默认为最低级牌型
  if (isFlush && isStraight)
    result = 1;  // 同花顺
  else if (maxSameCount == 4)
    result = 2;  // 四条
  else if (maxSameCount == 3 && secondMaxSameCount == 2)
    result = 3;  // 葫芦
  else if (isFlush)
    result = 4;  // 同花
  else if (isStraight)
    result = 5;  // 顺子
  else if (maxSameCount == 3)
    result = 6;  // 三条

  // 输出结果
  cout << result << endl;

  return 0;
}
```

#### 堆内存申请

**题目描述**：

有一个总空间为 100 字节的堆，现要从中新申请一块内存，内存分配原则为：优先紧接着前一块已使用内存，分配空间足够且最接近申请大小的空闲内存。

**输入描述**：

第 1 行是 1 个整数，表示期望申请的内存字节数

第 2 到第 N 行是用空格分割的两个整数，表示当前已分配的内存的情况，每一行表示一块已分配的连续内存空间，每行的第 1 和第 2 个整数分别表示偏移地址和内存块大小，如：

> 0 1
>
> 3 2

表示 0 偏移地址开始的 1 个字节和 3 偏移地址开始的 2 个字节已被分配，其余内存空闲。

**输出描述**：

若申请成功，输出申请到内存的偏移；

若申请失败，输出 -1。

1. 若输入信息不合法或无效，则申请失败
2. 若没有足够的空间供分配，则申请失败
3. 堆内存信息有区域重叠或有非法值等都是无效输入

**用例 1**：

输入：

```
1
0 1
3 2
```

输出：

```
1
```

说明：堆中已使用的两块内存是偏移从 0 开始的 1 字节和偏移从 3 开始的 2 字节，空闲的两块内存是偏移从 1 开始 2 个字节和偏移从 5 开始 95 字节，根据分配原则，新申请的内存应从 1 开始分配 1 个字节，所以输出偏移为 1。

难度：中等

标签：数组、贪心

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  // 申请内存大小
  int request_size;
  cin >> request_size;

  // 定义堆内存总空间
  vector<int> memory(100, 0);

  // 读取已分配内存信息并标记
  int offset, size;
  while (cin >> offset >> size) {
    // 检查输入的合法性
    if (offset < 0 || size <= 0 || offset + size > 100) {
      cout << -1 << endl;
      return 0;
    }

    // 标记内存并检查是否重复分配
    for (int i = offset; i < offset + size; i++) {
      if (memory[i] == 1) {
        cout << -1 << endl;
        return 0;
      }
      memory[i] = 1;
    }
  }

  // 寻找满足条件的连续空闲内存
  int best_start = -1;      // 最佳起始位置
  int best_diff = INT_MAX;  // 最小差值
  int curr_start = -1;      // 当前连续空闲内存起始位置
  int curr_size = 0;        // 当前连续空闲内存大小

  for (int i = 0; i < 100; i++) {
    if (memory[i] == 0) {
      // 如果是第一个空闲位置
      if (curr_start == -1) {
        curr_start = i;
      }
      curr_size++;
    } else {
      // 处理一段连续空闲内存
      if (curr_size >= request_size) {
        int diff = curr_size - request_size;
        // 更新最佳起始位置
        if (diff < best_diff) {
          best_start = curr_start;
          best_diff = diff;
        }
      }
      // 重置当前空闲内存信息
      curr_start = -1;
      curr_size = 0;
    }
  }

  // 处理最后一段连续空闲内存
  if (curr_size >= request_size) {
    int diff = curr_size - request_size;
    if (diff < best_diff) {
      best_start = curr_start;
    }
  }

  // 输出结果
  if (best_start != -1) {
    cout << best_start << endl;
  } else {
    cout << -1 << endl;
  }

  return 0;
}
```

#### 相同数字组成图形的周长

**题目描述**：

有一个 64×64 的矩阵，每个元素的默认值为 0，现在向里面填充数字，相同的数字组成一个实心图形，如下图所示是矩阵的局部（空白表示填充 0）：

![image](https://hydro.ac/d/HWOD2023/p/80/file/l9kXoo1rb6_c1CWFVY4BX.png)

数字 1 组成了蓝色边框的实心图形，数字 2 组成了红色边框的实心图形。

单元格的边长规定为 1 个单位。

请根据输入，计算每个非 0 值填充出来的实心圆形的周长。

**输入描述**：

第一行输入 N，表示 N 个图形，N > 0 且 N < 64 × 64

矩阵左上角单元格坐标记作(0, 0)，第一个数字表示行号，第二个数字表示列号

接下来是 N 行，每行第一个数是矩阵单元格填充的数字， 后续每两个一组，表示填充该数字的单元格坐标

答题者无需考虑数据格式非法的场景，题目用例不考察数据格式

题目用例保证同一个填充值只会有一行输入数据

**输出描述**：

一共输出 N 个数值，每个数值表示某一行输入表示图形的周长

输出顺序需和输入的隔行顺序保持一致，即第 1 个数是输入的第 1 个图形的周长，第 2 个数是输入的第 2 个图形的周长，以此类推

**用例 1**：

输入：

```
2
1 1 3 2 2 2 3 2 4 3 2 3 3 3 4 4 1 4 2 4 3 4 4 5 2 5 3
2 3 7 3 8 4 5 4 6 4 7 4 8 5 4 5 5 5 6 5 7 5 8 6 4 6 5 6 6 6 7 6 8 7 4 7 5 7 6 7 7 7 8
```

输出：

```
18 20
```

难度：中等

标签：深度优先搜索、矩阵、数组

```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  cin.ignore();

  // 存储输入行的二维vector
  vector<vector<int>> lines;

  // 读取输入
  for (int i = 0; i < n; i++) {
    string line;
    getline(cin, line);

    // 解析每行
    stringstream ss(line);
    vector<int> row;
    int num;

    // 按空格读取数字
    while (ss >> num) {
      row.push_back(num);
    }

    lines.push_back(row);
  }

  // 定义64*64的矩阵，初始化为0
  vector<vector<int>> matrix(64, vector<int>(64, 0));

  // 向矩阵中填充数字
  for (const auto& line : lines) {
    // 第一个数是要填充的数字
    int num = line[0];

    // 后续每两个数一组，表示坐标
    for (int i = 1; i < line.size(); i += 2) {
      int x = line[i];
      int y = line[i + 1];
      matrix[x][y] = num;
    }
  }

  // 定义四个方向
  int offsets[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  // 遍历每个图形
  for (const auto& line : lines) {
    int num = line[0];
    int perimeter = 0;

    // 遍历当前图形的每个点
    for (int i = 1; i < line.size(); i += 2) {
      int x = line[i];
      int y = line[i + 1];

      // 检查四个方向
      for (const auto& offset : offsets) {
        int newX = x + offset[0];
        int newY = y + offset[1];

        // 如果越界或不是同一图形，周长+1
        if (newX < 0 || newX >= 64 || newY < 0 || newY >= 64 ||
            matrix[newX][newY] != num) {
          perimeter++;
        }
      }
    }

    // 输出周长
    cout << perimeter << (line == lines.back() ? "\n" : " ");
  }

  return 0;
}
```

#### 攀登者 2

**题目描述**：

攀登者喜欢寻找各种地图，并且尝试攀登到最高的山峰。

地图表示为一维数组，数组的索引代表水平位置，数组的元素代表相对海拔高度。其中数组元素 0 代表地面。

例如：[0,1,2,4,3,1,0,0,1,2,3,1,2,1,0]，代表如下图所示的地图，地图中有两个山脉位置分别为 1,2,3,4,5 和 8,9,10,11,12,13，最高峰高度分别为 4,3。最高峰位置分别为 3,10。

一个山脉可能有多座山峰(高度大于相邻位置的高度，或在地图边界且高度大于相邻的高度)。

![image](https://hydro.ac/d/HWOD2023/p/379/file/NIgOzDXZ9F4Fs059AtwZs.png)

登山时会消耗登山者的体力(整数)，

- 上山时，消耗相邻高度差两倍的体力
- 下山时，消耗相邻高度差一倍的体力
- 平地不消耗体力

登山者体力消耗到零时会有生命危险。

例如，上图所示的山峰：

- 从索引 0，走到索引 1，高度差为 1，需要消耗 2 \* 1 = 2 的体力，
- 从索引 2，走到索引 3，高度差为 2，需要消耗 2 \* 2 = 4 的体力。
- 从索引 3，走到索引 4，高度差为 1，需要消耗 1 \* 1 = 1 的体力。

攀登者想要评估一张地图内有多少座山峰可以进行攀登，且可以安全返回到地面，且无生命危险。

例如上图中的数组，有 3 个不同的山峰，登上位置在 3 的山可以从位置 0 或者位置 6 开始，从位置 0 登到山顶需要消耗体力 1 _ 2 + 1 _ 2 + 2 _ 2 = 8，从山顶返回到地面 0 需要消耗体力 2 _ 1 + 1 _ 1 + 1 _ 1 = 4 的体力，按照登山路线 0 → 3 → 0 需要消耗体力 12。攀登者至少需要 12 以上的体力（大于 12）才能安全返回。

**输入描述**：

第一行输入为地图一维数组

第二行输入为攀登者的体力

**输出描述**：

确保可以安全返回地面，且无生命危险的情况下，地图中有多少山峰可以攀登。

本题考试时为核心代码模式，非 ACM 模式，即无需自己解析输入数据。

**用例 1**：

输入：

```
0,1,4,3,1,0,0,1,2,3,1,2,1,0
13
```

输出：

```
3
```

说明：登山者只能登上位置 10 和 12 的山峰，7 → 10 → 7，14 → 12 → 14

**用例 2**：

输入：

```
1,4,3
999
```

输出：

```
0
```

说明：没有合适的起点和终点

难度：中等

标签：双指针、贪心、动态规划

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int count_climbable(vector<int>& heights, int strength) {
    unordered_set<int> climbable_peaks;

    // 正向和逆向两次遍历
    explore_peaks(heights, strength, climbable_peaks, true);

    // 逆序后再次遍历
    reverse(heights.begin(), heights.end());
    explore_peaks(heights, strength, climbable_peaks, false);

    return climbable_peaks.size();
  }

 private:
  void explore_peaks(vector<int>& heights, int strength,
                     unordered_set<int>& climbable_peaks, bool is_forward) {
    int n = heights.size();

    // 找到第一个地面起点
    int start_index = 0;
    while (start_index < n && heights[start_index] != 0) {
      start_index++;
    }

    int cumulative_cost = 0;

    for (int i = start_index + 1; i < n; i++) {
      // 重置起点
      if (heights[i] == 0) {
        cumulative_cost = 0;
        continue;
      }

      int height_diff = heights[i] - heights[i - 1];

      // 根据坡度计算体力消耗
      if (height_diff > 0) {
        // 上坡
        cumulative_cost += height_diff * 3;

        // 判断是否为山峰
        if (i + 1 >= n || heights[i] > heights[i + 1]) {
          if (cumulative_cost < strength) {
            // 根据遍历方向映射正确的山峰索引
            int peak_index = is_forward ? i : (n - i - 1);
            climbable_peaks.insert(peak_index);
          }
        }
      } else if (height_diff < 0) {
        // 下坡
        cumulative_cost -= height_diff * 3;
        // 下坡不可能是山峰
      }
    }
  }
};

int main() {
  vector<int> heights;

  string s;
  getline(cin, s);

  stringstream ss(s);
  string token;

  while (getline(ss, token, ',')) {
    heights.emplace_back(stoi(token));
  }

  int strength;
  cin >> strength;

  cout << Solution().count_climbable(heights, strength) << endl;

  return 0;
}
```

## 数学

### 100 分

#### 构成正方形的数量

**题目描述**：

输入 N 个互不相同的二维整数坐标，求这 N 个坐标可以构成的正方形数量。[内积为零的的两个向量垂直]

**输入描述**：

第一行输入为 N，N 代表坐标数量，N 为正整数。N <= 100

之后的 N 行输入为坐标 x y 以空格分隔，x，y 为整数，-10 <= x, y <= 10

**输出描述**：

输出可以构成的正方形数量

**用例 1**：

输入：

```
3
1 3
2 4
3 1
```

输出：

```
0
```

说明：3 个点不足以构成正方形

**用例 2**：

输入：

```
4
0 0
1 2
3 1
2 -1
```

输出：

```
1
```

说明：此 4 点可构成正方形

难度：中等

标签：几何、数学、枚举、哈希表

#### 靠谱的车

**题目描述**：

程序员小明打了一辆出租车去上班。出于职业敏感，他注意到这辆出租车的计费表有点问题，总是偏大。

出租车司机解释说他不喜欢数字 4，所以改装了计费表，任何数字位置遇到数字 4 就直接跳过，其余功能都正常。

比如：

1. 23 再多一块钱就变为 25；
2. 39 再多一块钱变为 50；
3. 399 再多一块钱变为 500； 小明识破了司机的伎俩，准备利用自己的学识打败司机的阴谋。

给出计费表的表面读数，返回实际产生的费用。

**输入描述**：

只有一行，数字 N，表示里程表的读数。

(1 <= N <= 888888888)。

**输出描述**：

一个数字，表示实际产生的费用。以回车结束。

**用例 1**：

输入：

```
5
```

输出：

```
4
```

说明：

5 表示计费表的表面读数。

4 表示实际产生的费用其实只有 4 块钱。

**用例 2**：

输入：

```
17
```

输出：

```
15
```

说明：

17 表示计费表的表面读数。

15 表示实际产生的费用其实只有 15 块钱。

**用例 3**：

输入：

```
100
```

输出：

```
81
```

说明：

100 表示计费表的表面读数。

81 表示实际产生的费用其实只有 81 块钱。

难度：中等

标签：数学、位运算

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  int actual = 0;
  int base = 1;

  while (N > 0) {
    int current_digit = N % 10;
    N /= 10;

    // 处理当前位
    if (current_digit < 4) {
      actual += current_digit * base;
    } else if (current_digit > 4) {
      actual += (current_digit - 1) * base;
    }

    // 更新基数
    base *= 9;
  }

  cout << actual << endl;

  return 0;
}
```

#### 矩形相交的面积

**题目描述**：

给出 3 组点坐标(x, y, w, h)，-1000 < x, y < 1000，w, h 为正整数。

(x, y, w, h)表示平面直角坐标系中的一个矩形：

x, y 为矩形左上角坐标点，w, h 向右 w，向下 h。

(x, y, w, h)表示 x 轴(x, x+w)和 y 轴(y, y-h)围成的矩形区域；

(0, 0, 2, 2)表示 x 轴(0, 2)和 y 轴(0, -2)围成的矩形区域；

(3, 5, 4, 6)表示 x 轴(3, 7)和 y 轴(5, -1)围成的矩形区域；

求 3 组坐标构成的矩形区域重合部分的面积。

**输入描述**：

3 行输入分别为 3 个矩形的位置，分别代表“左上角 x 坐标”，“左上角 y 坐标”，“矩形宽”，“矩形高” -1000 <= x, y < 1000

**输出描述**：

输出 3 个矩形相交的面积，不相交的输出 0。

**用例 1**：

输入：

```
1 6 4 4
3 5 3 4
0 3 7 3
```

输出：

```
2
```

说明：

![image](https://hydro.ac/d/HWOD2023/p/319/file/OowmieDp78x8p-BXd6WpZ.png)

难度：中等

标签：几何、数学

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  // 矩形坐标输入：左上角 x, 左上角 y, 宽度, 高度
  int x1, y1, w1, h1;
  int x2, y2, w2, h2;
  int x3, y3, w3, h3;

  // 输入 3 个矩形的坐标信息
  cin >> x1 >> y1 >> w1 >> h1;
  cin >> x2 >> y2 >> w2 >> h2;
  cin >> x3 >> y3 >> w3 >> h3;

  // 计算每个矩形的坐标范围
  // 注意：y 轴向下为正，所以右下角 y 坐标为 y + h
  int left = max({x1, x2, x3});            // x 轴最大左边界
  int right = min({x1 + w1, x2 + w2, x3 + w3});  // x 轴最小右边界

  int bottom = max({y1 - h1, y2 - h2, y3 - h3});  // y 轴最大下边界
  int top = min({y1, y2, y3});             // y 轴最小上边界

  // 计算重叠区域
  int width = max(0, right - left);
  int height = max(0, top - bottom);

  // 输出重叠面积
  cout << width * height << endl;

  return 0;
}
```

#### 分苹果

**题目描述**：

A、B 两个人把苹果分为两堆，A 希望按照他的计算规则等分苹果，他的计算规则是按照二进制加法计算，并且不计算进位 12+5 = 9（1100 + 0101 = 9），B 的计算规则是十进制加法，包括正常进位，B 希望在满足 A 的情况下获取苹果重量最多。

输入苹果的数量和每个苹果重量，输出满足 A 的情况下 B 获取的苹果总重量。

如果无法满足 A 的要求，输出-1。

**数据范围**

- 1 <= 总苹果数量 <= 20000
- 1 <= 每个苹果重量 <= 10000

**输入描述**：

输入第一行是苹果数量：3

输入第二行是每个苹果重量：3 5 6

**输出描述**：

输出第一行是 B 获取的苹果总重量：11

**用例 1**：

输入：

```
3
3 5 6
```

输出：

```
11
```

**用例 2**：

输入：

```
8
7258 6579 2602 6716 3050 3564 5396 1773
```

输出：

```
8
7258 6579 2602 6716 3050 3564 5396 1773
```

难度：简单

标签：位运算、数学、数组

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; // 苹果数量
  cin >> n; // 输入苹果数量

  vector<int> weights(n); // 存储每个苹果的重量
  int total_xor = 0; // 初始化异或结果
  int total_weight = 0; // 初始化总重量

  // 输入每个苹果的重量
  for (int i = 0; i < n; i++) {
    cin >> weights[i];
    total_xor ^= weights[i]; // 计算异或
    total_weight += weights[i]; // 计算总重量
  }

  // 根据 A 的规则判断结果
  if (total_xor != 0) {
    cout << -1 << endl; // 无法满足 A 的要求
  } else {
    // 在 total_xor 为 0 的情况下，B希望尽量得到最多
    // 计算 B 得到的最多的苹果重量
    // 这里只需要去掉最轻的苹果，剩余重量即为 B 获取的量
    int min_weight = *min_element(weights.begin(), weights.end());
    cout << total_weight - min_weight << endl; // B 获取的苹果总重量
  }

  return 0;
}
```

#### 工号不够用了怎么办

**题目描述**：

3020 年，空间通信集团的员工人数突破 20 亿人，即将遇到现有工号不够用的窘境。

现在，请你负责调研新工号系统。继承历史传统，新的工号系统由小写英文字母（a-z）和数字（0-9）两部分构成。

新工号由一段英文字母开头，之后跟随一段数字，比如”aaahw0001″,”a12345″,”abcd1″,”a00″。

注意新工号不能全为字母或者数字, 允许数字部分有前导 0 或者全为 0。

但是过长的工号会增加同事们的记忆成本，现在给出新工号至少需要分配的人数 X 和新工号中字母的长度 Y，求新工号中数字的最短长度 Z。

**输入描述**：

- 一行两个非负整数 X Y，用数字用单个空格分隔。
- 0 < X <= 2^50 – 1
- 0 < Y <= 5

**输出描述**：

- 输出新工号中数字的最短长度 Z

**用例 1**：

输入：

```
260 1
```

输出：

```
1
```

**用例 2**：

输入：

```
26 1
```

输出：

```
1
```

说明：数字长度不能为 0

**用例 3**：

输入：

```
2600 1
```

输出：

```
2
```

难度：简单

标签：数学、位运算

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  unsigned long long x, y; // 使用 unsigned long long 以处理最大值
  cin >> x >> y;

  // 计算可以生成的字母组合数
  unsigned long long letter_combinations = pow(26, y);

  int z = 1; // 从1开始，确保数字部分长度不为0
  while (letter_combinations * pow(10, z) < x) {
    z++; // 增加 Z 直到条件满足
  }

  cout << z << endl; // 输出最小 Z
  return 0;
}
```

#### 数据分类

**题目描述**：

对一个数据 a 进行分类，分类方法为：

此数据 a（四个字节大小）的四个字节相加对一个给定的值 b 取模，如果得到的结果小于一个给定的值 c，则数据 a 为有效类型，其类型为取模的值；如果得到的结果大于或者等于 c，则数据 a 为无效类型。

比如一个数据 a = 0x01010101，b = 3，按照分类方法计算（0x01+0x01+0x01+0x01）%3 = 1，

所以如果 c = 2，则此 a 为有效类型，其类型为 1，如果 c = 1，则此 a 为无效类型；

又比如一个数据 a = 0x01010103，b = 3，按照分类方法计算（0x01+0x01+0x01+0x03）%3 = 0，

所以如果 c = 2，则此 a 为有效类型，其类型为 0，如果 c = 0，则此 a 为无效类型。

输入 12 个数据，第一个数据为 c，第二个数据为 b，剩余 10 个数据为需要分类的数据，

请找到有效类型中包含数据最多的类型，并输出该类型含有多少个数据。

**输入描述**：

输入 12 个数据，用空格分隔，第一个数据为 c，第二个数据为 b，剩余 10 个数据为需要分类的数据。

**输出描述**：

输出最多数据的有效类型有多少个数据。

**用例 1**：

输入：

```
3 4 256 257 258 259 260 261 262 263 264 265
```

输出：

```
3
```

说明：

10 个数据 4 个字节相加后的结果分别为 1 2 3 4 5 6 7 8 9 10，

故对 4 取模的结果为 1 2 3 0 1 2 3 0 1 2，c 为 3，所以 0 1 2 都是有效类型，类型为 1 和 2 的有 3 个数据，类型为 0 的只有 2 个数据，故输出 3。

**用例 2**：

输入：

```
1 4 256 257 258 259 260 261 262 263 264 265
```

输出：

```
2
```

说明：

10 个数据 4 个字节相加后的结果分别为 1 2 3 4 5 6 7 8 9 10，

故对 4 取模的结果为 1 2 3 0 1 2 3 0 1 2，c 为 1，

所以只有 0 是有效类型，类型为 0 的有 2 个数据，故输出 2。

难度：中等

标签：位运算、哈希表、数组

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int c, b;
  cin >> c >> b;

  vector<int> data(10);
  unordered_map<int, int> type_count; // 记录每种有效类型的数据计数

  // 输入其余10个数据
  for (int i = 0; i < 10; i++) {
    cin >> data[i];
    // 拆分数据为4个字节
    int byte1 = (data[i] >> 24) & 0xFF;
    int byte2 = (data[i] >> 16) & 0xFF;
    int byte3 = (data[i] >> 8) & 0xFF;
    int byte4 = data[i] & 0xFF;

    // 字节求和并取模
    int sum = byte1 + byte2 + byte3 + byte4;
    int result = sum % b;

    // 判断有效性
    if (result < c) {
      type_count[result]++; // 增加该类型计数
    }
  }

  // 找到计数最多的有效类型
  int max_count = 0;
  for (const auto& entry : type_count) {
    max_count = max(max_count, entry.second);
  }

  cout << max_count << endl; // 输出最多数据的有效类型数量
  return 0;
}
```

#### 整数编码

**题目描述**：

实现一种整数编码方法，使得待编码的数字越小，编码后所占用的字节数越小。

编码规则如下:

1. 编码时 7 位一组，每个字节的低 7 位用于存储待编码数字的补码
2. 字节的最高位表示后续是否还有字节，置 1 表示后面还有更多的字节，置 0 表示当前字节为最后一个字节。
3. 采用小端序编码，低位和低字节放在低地址上。
4. 编码结果按 16 进制数的字符格式输出，小写字母需转换为大写字母

**输入描述**：

输入的为一个字符串表示的非负整数

**输出描述**：

输出一个字符串，表示整数编码的 16 进制码流

待编码的数字取值范围为 [0，1 << 64 - 1]

**用例 1**：

输入：

```
0
```

输出：

```
00
```

说明：输出的 16 进制字符，不足两位的前面补 0，如 00、01、02。

**用例 2**：

输入：

```
100
```

输出：

```
64
```

说明：100 的二进制表示为 0110 0100，只需要一个字节进行编码;

字节的最高位置 0，剩余 7 位存储数字 100 的低 7 位 (110 0100) ，所以编码后的输出为 64。

**用例 3**：

输入：

```
1000
```

输出：

```
E807
```

1000 的二进制表示为 0011 1110 1000，至少需要两个字节进行编码;

第一个字节最高位置 1，剩余的 7 位存储数字 1000 的第一个低 7 位 (1101000)，所以第一个字节的二进制为 1110 1000，即 E8;

第二个字节最高位置 0，剩余的 7 位存储数字 1000 的第二个低 7 位 (0000111)，所以第一个字节的二进制为 0000 0111，即 07;

采用小端序编码，所以低字节 E8 输出在前，高字节 07 输出在后。

难度：中等

标签：位运算、字符串

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  cin >> input; // 读取输入
  uint64_t number = stoull(input); // 将输入转换为无符号64位整数

  vector<uint8_t> encoded_bytes;

  // 编码过程
  do {
    uint8_t byte = number & 0x7F; // 取低7位
    number >>= 7; // 右移7位
    // 如果还有更多的字节，设置最高位为1
    if (number != 0) {
      byte |= 0x80; // 设置最高位为1
    }
    encoded_bytes.push_back(byte);
  } while (number != 0);

  // 使用小端序，把字节反转
  stringstream result;
  for (unsigned char encoded_byte : encoded_bytes) {
    // 输出为16进制格式，确保每个字节占2位，不足补0，转为大写
    result << uppercase << setfill('0') << setw(2) << hex << static_cast<int>(encoded_byte);
  }

  cout << result.str() << endl; // 输出编码结果

  return 0;
}
```

#### 勾股数元组

**题目描述**：

如果 3 个正整数(a, b, c)满足 a^2 + b^2 = c^2 的关系，则称(a, b, c)为勾股数（著名的勾三股四弦五），

为了探索勾股数的规律，我们定义如果勾股数(a, b, c)之间两两互质（即 a 与 b，a 与 c，b 与 c 之间均互质，没有公约数），则其为勾股数元组（例如(3,4,5)是勾股数元组，(6,8,10)则不是勾股数元组）。

请求出给定范围 [N, M] 内，所有的勾股数元组。

**输入描述**：

起始范围 N，1 <= N <= 10000

结束范围 M，N < M <= 10000

**输出描述**：

1. a, b, c 请保证 a < b < c, 输出格式：a b c；
2. 多组勾股数元组请按照 a 升序，b 升序，最后 c 升序的方式排序输出；
3. 给定范围中如果找不到勾股数元组时，输出”NA“。

**用例 1**：

输入：

```
1
20
```

输出：

```
3 4 5
5 12 13
8 15 17
```

说明：

[1,20] 范围内勾股数有：(3 4 5)，(5 12 13)，(6 8 10)，(8 15 17)，(9 12 15)，(12 16 20)；

其中，满足(a, b, c)之间两两互质的勾股数元组有：(3 4 5)，(5 12 13)，(8 15 17);

按输出描述中顺序要求输出结果。

**用例 2**：

输入：

```
5
10
```

输出：

```
NA
```

说明：

[5,10] 范围内勾股数有：(6 8 10)；

其中，没有满足(a, b, c)之间两两互质的勾股数元组；

给定范围中找不到勾股数元组，输出”NA“

难度：中等

标签：数学、枚举

```cpp
#include <bits/stdc++.h>

using namespace std;

// 自定义函数用于计算最大公约数（GCD）
int gcd(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

// 用于检查三个数字是否两两互质
bool AreCoprime(int a, int b, int c) {
  return gcd(a, b) == 1 && gcd(a, c) == 1 && gcd(b, c) == 1;
}

int main() {
  int n, m;
  cin >> n >> m; // 输入范围

  vector<tuple<int, int, int> > coprime_tuples; // 用于存放满足条件的勾股数元组

  // 查找 (a, b, c) 所有可能的组合
  for (int c = n; c <= m; ++c) {
    for (int a = n; a < c; ++a) {
      int b_square = c * c - a * a;             // 计算 b 的平方
      int b = static_cast<int>(sqrt(b_square)); // 计算 b

      // 检查 b 是否合适
      if (b > a && b <= m && b * b == b_square) {
        // b 应该大于 a，且小于等于 M
        // 检查是否两两互质
        if (AreCoprime(a, b, c)) {
          coprime_tuples.emplace_back(a, b, c); // 记录元组
        }
      }
    }
  }

  // 如果没有找到结果，输出 NA
  if (coprime_tuples.empty()) {
    cout << "NA" << endl;
    return 0;
  }

  // 排序元组
  sort(coprime_tuples.begin(), coprime_tuples.end());

  // 输出结果
  for (const auto& t : coprime_tuples) {
    int a, b, c;
    tie(a, b, c) = t;
    cout << a << " " << b << " " << c << endl;
  }

  return 0;
}
```

## 正则匹配

### 100 分

##### 火星文计算

**题目描述**：

已知火星人使用的运算符为\#、\$，其与地球人的等价公式如下：

x\#y = 4\*x+3\*y+2

x\$y = 2\*x+y+3

1. 其中 x、y 是无符号整数
2. 地球人公式按 C 语言规则计算
3. 火星人公式中，\#的优先级高于\$，相同的运算符，按从左到右的顺序计算

有一段火星人的字符串报文，请你来翻译并计算结果。

**输入描述**：

火星人字符串表达式（结尾不带回车换行）

输入的字符串说明： 字符串为仅由无符号整数和操作符（\#、\$）组成的计算表达式。例如：

> 123\#4\$5\#67\$78

1. 用例保证字符串中，操作数与操作符之间没有任何分隔符。

2. 用例保证操作数取值范围为 32 位无符号整数。

3. 保证输入以及计算结果不会出现整型溢出。

4. 保证输入的字符串为合法的求值报文，例如：123\#4\$5\#67\$78

5. 保证不会出现非法的求值报文，例如类似这样字符串：

   \#4\$5 //缺少操作数

   4\$5\# //缺少操作数

   4\#\$5 //缺少操作数

   4 \$5 //有空格

   3+4-5\*6/7 //有其它操作符

   12345678987654321\$54321 //32 位整数计算溢出

**输出描述**：

根据输入的火星人字符串输出计算结果（结尾不带回车换行）

**用例 1**：

输入：

```
7#6$5#12
```

输出：

```
157
```

说明：

7\#6\$5\#12

=(4\*7+3\*6+2)\$5\#12

= 48\$5\#12

= 48\$(4\*5+3\*12+2)

= 48\$58

= 2\*48+58+3

= 157

难度：中等

标签：栈、字符串、数学

```cpp
#include <bits/stdc++.h>

using namespace std;

// 计算 x # y 的函数
unsigned long long CalculateHash(unsigned long long x, unsigned long long y) {
  return 4 * x + 3 * y + 2;
}

// 计算 x $ y 的函数
unsigned long long CalculateDollar(unsigned long long x, unsigned long long y) {
  return 2 * x + y + 3;
}

int main() {
  string expression;
  cin >> expression; // 输入火星人的字符串表达式

  vector<unsigned long long> numbers; // 用于存储数字
  vector<char> operations; // 用于存储运算符

  // 解析表达式
  for (size_t i = 0; i < expression.size(); ) {
    size_t j = i;
    while (j < expression.size() && isdigit(expression[j])) {
      j++; // 找到数字的范围
    }
    // 提取数字并存入 numbers 中
    unsigned long long number = stoull(expression.substr(i, j - i));
    numbers.push_back(number);

    if (j < expression.size()) {
      operations.push_back(expression[j]); // 提取操作符
      j++; // 移动到下一个字符
    }
    i = j; // 更新 i
  }

  // 优先处理 #
  size_t pos = 0;

  while (pos < operations.size()) {
    if (operations[pos] == '#') {
      unsigned long long result = CalculateHash(numbers[pos], numbers[pos + 1]);
      // 更新 numbers 和 operations
      numbers[pos] = result; // 更新数字
      numbers.erase(numbers.begin() + pos + 1); // 删除下一个数字
      operations.erase(operations.begin() + pos); // 删除运算符
      // 从当前位置重新开始处理
      pos = 0;
    } else {
      pos++; // 移动到下一个操作符
    }
  }

  // 处理所有 $
  unsigned long long final_result = numbers[0];
  for (size_t i = 0; i < operations.size(); ++i) {
    if (operations[i] == '$') {
      final_result = CalculateDollar(final_result, numbers[i + 1]);
    }
  }

  // 输出最终结果
  cout << final_result << endl;

  return 0;
}
```

### 200 分

#### 文本统计分析

**题目描述**：

有一个文件，包含以一定规则写作的文本，请统计文件中包含的文本数量。

规则如下：

1. 文本以 ";" 分隔，最后一条可以没有 ";" ，但空文本不能算语句，比如

   > COMMAND A; ;

   只能算一条语句。 注意，无字符/空白字符/制表符都算作 "空" 文本；

2. 文本可以跨行，比如下面，是一条文本，而不是三条

   > COMMAND A
   >
   > AND
   >
   > COMMAND B;

3. 文本支持字符串，字符串为成对的单引号(')或者成对的双引号(")，字符串可能出现用转义字符(\)处理的单双引号(" your input is \"")和转义字符本身，比如

   > COMMAND A "Say \" hello \"";

4. 支持注释，可以出现在字符串之外的任意位置注释以”--“开头，到换行结束，比如

   > COMMAND A; -- this is comment
   >
   > COMMAND -- comment
   >
   > A AND COMMAND B;

   注意字符串内的”--“，不是注释。

**输入描述**：

文本文件

**输出描述**：

包含的文本数量

**用例 1**：

输入：

```
COMMAND TABLE IF EXISTS "UNITED STATE";
COMMAND A GREAT (
    ID ADSAB,
    download_length INTE-GER,  -- test
    file_name TEXT,
    guid TEXT,
    mime_type TEXT,
    notifica-tionid INTEGER,
    original_file_name TEXT,
    pause_reason_type INTEGER,
    resumable_flag INTEGER,
    start_time INTEGER,
    state INTEGER,
    folder TEXT,
    path TEXT,
    total_length INTE-GER,
    url TEXT
);
```

输出：

```
2
```

难度：中等
算法：字符串、模拟

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string line;
  string text;
  bool is_single_open = false;
  bool is_double_open = false;

  // 读取所有行
  while (getline(cin, line)) {
    for (size_t i = 0; i < line.size(); ++i) {
      // 处理单引号
      if (line[i] == '\'' && (i == 0 || line[i-1] != '\\')) {
        is_single_open = !is_single_open;
      }

      // 处理双引号
      if (line[i] == '"' && (i == 0 || line[i-1] != '\\')) {
        is_double_open = !is_double_open;
      }

      // 处于字符串内部，忽略字符串内容
      if (is_single_open || is_double_open) continue;

      // 处理注释
      if (line[i] == '-' && i + 1 < line.size() && line[i+1] == '-') {
        break; // 遇到注释，停止处理当前行后续字符
      }

      // 跳过空白字符
      if (line[i] == ' ' || line[i] == '\t') continue;

      // 记录有效文本
      text += line[i];
    }
  }

  // 如果最后一条没有分号，追加分号
  if (!text.empty() && text.back() != ';') {
    text += ';';
  }

  // 统计有效文本数量
  int count = 0;
  bool in_text = false;
  for (char c : text) {
    if (c == ';') {
      if (in_text) {
        count++;
      }
      in_text = false;
    } else if (c != ' ' && c != '\t') {
      in_text = true;
    }
  }

  // 输出结果
  cout << count << endl;

  return 0;
}
```

## 分治递归

### 100 分

#### 分披萨

**题目描述**：

"吃货" 和 "馋嘴" 两人到披萨店点了一份铁盘（圆形）披萨，并嘱咐店员将披萨按放射状切成大小相同的偶数个小块。但是粗心的服务员将披萨切成了每块大小都完全不同奇数块，且肉眼能分辨出大小。

由于两人都想吃到最多的披萨，他们商量了一个他们认为公平的分法：从 "吃货" 开始，轮流取披萨。除了第一块披萨可以任意选取外，其他都必须从缺口开始选。

他俩选披萨的思路不同。"馋嘴" 每次都会选最大块的披萨，而且 "吃货" 知道 "馋嘴" 的想法。

已知披萨小块的数量以及每块的大小，求 "吃货" 能分得的最大的披萨大小的总和。

**输入描述**：

第 1 行为一个正整数奇数 N，表示披萨小块数量。

3 ≤ N < 500
接下来的第 2 行到第 N + 1 行（共 N 行），每行为一个正整数，表示第 i 块披萨的大小

1 ≤ i ≤ N
披萨小块从某一块开始，按照一个方向次序顺序编号为 1 ~ N

每块披萨的大小范围为 [1, 2147483647]

**输出描述**：

"吃货" 能分得到的最大的披萨大小的总和。

**用例 1**：

输入：

```
5
8
2
10
5
7
```

输出：

```
19
```

说明：

此例子中，有 5 块披萨。每块大小依次为 8、2、10、5、7。

按照如下顺序拿披萨，可以使 "吃货" 拿到最多披萨：

"吃货" 拿大小为 10 的披萨

"馋嘴" 拿大小为 5 的披萨

"吃货" 拿大小为 7 的披萨

"馋嘴" 拿大小为 8 的披萨

"吃货" 拿大小为 2 的披萨

至此，披萨瓜分完毕，"吃货" 拿到的披萨总大小为 10 + 7 + 2 = 19

可能存在多种拿法，以上只是其中一种。

难度：困难

标签：动态规划、递归、记忆化搜索、博弈论

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510;
int n;
int pizza[MAXN];

// 记忆化数组，存储每个状态的最优解
vector<vector<long long> > memo;

// 环形数组边界处理
inline int bound(int x) {
  return (x + n) % n;
}

// 递归求解最大披萨分配
long long solve(int start, int remain, bool is_gamer) {
  // 如果只剩最后一块，吃货必定获得
  if (remain == 1) {
    return is_gamer ? pizza[start] : 0;
  }

  // 检查是否已缓存
  if (memo[start][remain] != -1) {
    return memo[start][remain];
  }

  long long result;
  if (!is_gamer) {
    // 馋嘴回合，选择最大块
    const int left_idx = bound(start);
    const int right_idx = bound(start + remain - 1);

    result = pizza[left_idx] > pizza[right_idx]
               ? solve(bound(start + 1), remain - 1, true)
               : solve(start, remain - 1, true);
  } else {
    // 吃货回合，选择最优解
    const long long take_left = solve(bound(start + 1), remain - 1, false) +
                                pizza[start];
    const long long take_right = solve(start, remain - 1, false) + pizza[bound(
                                     start + remain - 1)];
    result = max(take_left, take_right);
  }

  // 缓存结果
  memo[start][remain] = result;
  return result;
}

int main() {
  // 输入披萨数量
  cin >> n;

  // 输入披萨大小
  for (int i = 0; i < n; i++) {
    cin >> pizza[i];
  }

  // 初始化记忆化数组
  memo = vector<vector<long long> >(n, vector<long long>(n + 1, -1));

  long long max_pizza = 0;

  // 尝试从不同起点开始
  for (int i = 0; i < n; i++) {
    // 重置记忆化数组
    for (auto& row : memo) {
      fill(row.begin(), row.end(), -1);
    }

    // 计算从该起点开始的最大披萨值
    max_pizza = max(max_pizza, solve(i, n, true));
  }

  // 输出最终结果
  cout << max_pizza << endl;

  return 0;
}
```

#### 分糖果

**题目描述**：

小明从糖果盒中随意抓一把糖果，每次小明会取出一半的糖果分给同学们。

当糖果不能平均分配时，小明可以选择从糖果盒中（假设盒中糖果足够）取出一个糖果或放回一个糖果。

小明最少需要多少次（取出、放回和平均分配均记一次），能将手中糖果分至只剩一颗。

**输入描述**：

抓取的糖果数（< 10000000000）：15

**输出描述**：

最少分至一颗糖果的次数：5

**用例 1**：

输入：

```
15
```

输出：

```
5
```

说明：

15+1 = 16;

16/2 = 8;

8/2 = 4;

4/2 = 2;

2/2 = 1;

难度：中等

标签：数学、位运算、贪心

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  long long n;
  cin >> n;

  int ops = 0;
  while (n != 1) {
    // 偶数直接除2
    if (n % 2 == 0) {
      n /= 2;
    }
    // 奇数需要特殊处理
    else {
      // 对于 10 这种特殊数字
      if (n == 3) {
        ops += 2; // 3 需要特殊处理：3-1=2，再除2
        break;
      }

      // 对于奇数，判断+1或-1能更快到1
      if ((n + 1) % 4 == 0) {
        n++;
      } else {
        n--;
      }
    }
    ops++;
  }

  cout << ops << endl;

  return 0;
}
```

### 200 分

#### 评论转换输出

**题目描述**：

在一个博客网站上，每篇博客都有评论。

每一条评论都是一个非空英文字母字符串。

评论具有树状结构，除了根评论外，每个评论都有一个父评论。

当评论保存时，使用以下格式：

首先是评论的内容； 然后是回复当前评论的数量。 最后是当前评论的所有了评论。(子评论使用相同的格式嵌套存储) 所有元素之间都用单个逗号分隔。

例如，如果评论如下：

![image](https://hydro.ac/d/HWOD2023/p/195/file/D8KnFBkNI42WCD6QWrKpE.png)

第一条评论是 "helo,2, ok,0, bye,0"，第二条评论是 "test,0"，第三条评论是 "one,1, two,1, a,0"。

所有评论被保存成 "hello,2, ok,0.bye,0, test,0, one,1, two,1, a,0"。

对于上述格式的评论，请以另外一种格式打印：

- 首先打印评论嵌套的最大深度。
- 然后是打印 n 行，第 i (1 ≤ i ≤ n) 行对应于嵌套级别为 i 的评论 (根评论的嵌套级别为 1)。
- 对于第 i 行，嵌套级别为的评论按照它们出现的顺序打印，用空格分隔开。

**输入描述**：

一行评论。由英文字母、数字和英文逗号组成。

保证每个评论都是由英文字符组成的非空字符串。

每个评论的数量都是整数 (至少由一个数字组成)。

整个字符串的长度不超过 10^6。

给定的评论结构保证是合法的

**输出描述**：

按照给定的格式打印评论。对于每一级嵌套，评论应该按照输入中的顺序打印

**用例 1**：

输入：

```
hello,2,ok,0,bye,0,test,0,one,1,two,1,a,0
```

输出：

```
3
hello test one
ok bye two
a
```

说明：

如题目描述中图所示，最大嵌套级别为 3，嵌套级别为 1 的评论是 "hello test one"，嵌套级别为 2 的评论是 "ok bye two"，嵌套级别为 3 的评论为”a "”。

**用例 2**：

输入：

```
A,5,A,0,a,0,A,0,a,0,A,0
```

输出：

```
2
A
A a A a A
```

说明：

如下图所示，最大嵌套级别为 2，嵌套级别为 1 的评论是 "A”，嵌套级别为 2 的评论是" A a A a A "

![image](https://hydro.ac/d/HWOD2023/p/195/file/fwMQoVJpp3-m6OlZkx9y2.png)

**用例 3**：

输入：

```
A,3,B,2,C,0,D,1,E,0,F,1,G,0,H,1,I,1,J,0,K,1,L,0,M,2,N,0,O,1,P,0
```

输出：

```
4
A K M
B F H L N O
C D G I P
E J
```

说明：

如下图所示

![image](https://hydro.ac/d/HWOD2023/p/195/file/9JNhC_Z1hhlb3gJjGh33f.png)

难度：中等

标签：数、深度优先搜索、递归、字符串、队列

```cpp
#include <bits/stdc++.h>

using namespace std;

// 树节点结构
struct Node {
  string val;
  int replies;
};

void dfs(queue<Node>& q, int depth, vector<vector<string> >& tree) {
  // 队列为空，返回
  if (q.empty())
    return;

  // 获取当前节点
  Node node = q.front();
  q.pop();

  // 扩展树层容器
  while (tree.size() <= depth) {
    tree.push_back({});
  }

  // 将当前节点加入对应层
  tree[depth].push_back(node.val);

  // 处理子节点
  for (int i = 0; i < node.replies; i++) {
    if (!q.empty()) {
      dfs(q, depth + 1, tree);
    }
  }
}

int main() {
  string input;
  getline(cin, input);

  // 用队列存储节点信息
  queue<Node> q;

  // 解析输入到队列
  stringstream ss(input);
  string val, replies_str;
  while (getline(ss, val, ',') && getline(ss, replies_str, ',')) {
    q.push({val, stoi(replies_str)});
  }

  // 树层容器
  vector<vector<string> > tree;

  // 深搜遍历
  while (!q.empty()) {
    dfs(q, 0, tree);
  }

  // 输出最大深度
  cout << tree.size() << endl;

  // 输出每层节点
  for (const auto& level : tree) {
    for (size_t i = 0; i < level.size(); ++i) {
      cout << level[i] << (i == level.size() - 1 ? "\n" : " ");
    }
  }

  return 0;
}
```

## 回溯算法

### 100 分

#### 第 k 个排列

**题目描述**：

给定参数 n，从 1 到 n 会有 n 个整数：1,2,3,…, n, 这 n 个数字共有 n! 种排列。

按大小顺序升序列出所有排列的情况，并一一标记，当 n = 3 时, 所有排列如下:

- “123”
- “132”
- “213”
- “231”
- “312”
- “321”

给定 n 和 k，返回第 k 个排列。

**输入描述**：

输入两行，第一行为 n，第二行为 k，

给定 n 的范围是 [1, 9], 给定 k 的范围是 [1, n!]。

**输出描述**：

输出排在第 k 位置的数字。

**用例 1**：

输入：

```
3
3
```

输出：

```

```

说明：3 的排列有 123,132,213…, 那么第三位置就是 213

**用例 2**：

输入：

```
2
2
```

输出：

```
21
```

说明：2 的排列有 12,21，那么第二位置的为 21。

难度：中等

标签：数组、回溯

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
  // 读取输入
  int n, k;
  cin >> n >> k;

  // 阶乘预处理
  vector<int> factorial(n + 1, 1);
  for (int i = 1; i <= n; i++) {
    factorial[i] = factorial[i - 1] * i;
  }

  // 记录数字是否被使用
  vector<bool> used(n + 1, false);

  // 结果字符串
  string result;

  // k从1开始，需要减1调整
  k--;

  // 逐位确定
  for (int i = 1; i <= n; i++) {
    // 当前位的分组大小
    int group = factorial[n - i];

    // 计算当前位应该填入的数字
    for (int j = 1; j <= n; j++) {
      if (used[j])
        continue;

      // 如果当前数字组可以容纳k
      if (k >= group) {
        k -= group;
      } else {
        // 找到了当前位的数字
        result += to_string(j);
        used[j] = true;
        break;
      }
    }
  }

  // 输出结果
  cout << result << endl;

  return 0;
}
```

#### MVP 争夺战

**题目描述**：

在星球争霸篮球赛对抗赛中，最大的宇宙战队希望每个人都能拿到 MVP，MVP 的条件是单场最高分得分获得者。

可以并列所以宇宙战队决定在比赛中尽可能让更多队员上场，并且让所有得分的选手得分都相同，

然而比赛过程中的每 1 分钟的得分都只能由某一个人包揽。

**输入描述**：

输入第一行为一个数字 t ，表示为有得分的分钟数

- 1 ≤ t ≤ 50

第二行为 t 个数字，代表每一分钟的得分 p，

- 1 ≤ p ≤ 50

**输出描述**：

输出有得分的队员都是 MVP 时，最少得 MVP 得分。

**用例 1**：

输入：

```
9
5 2 1 5 2 1 5 2 1
```

输出：

```
6
```

说明：

样例解释 一共 4 人得分，分别都是 6 分

5 + 1 ， 5 + 1 ， 5 + 1 ， 2 + 2 + 2

难度：困难

标签：回溯、贪心、动态规划、排序、数组

（38/40）

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t; // 读入得分分钟数

  vector<int> scores(t);
  for (int i = 0; i < t; i++) {
    cin >> scores[i]; // 读入每分钟的得分
  }

  // 计算总得分
  const int total_score = accumulate(scores.begin(), scores.end(), 0);

  // 定义递归进行分配
  function<bool(deque<int>&, int, vector<int>&, int)> partition =
      [&](deque<int>& link, int index, vector<int>& buckets, int sub_sum) {
    // 如果所有得分都分配完，返回 true
    if (index == link.size())
      return true;

    int select = link[index];

    for (int i = 0; i < buckets.size(); i++) {
      if (i > 0 && buckets[i] == buckets[i - 1])
        continue; // 避免重复处理

      if (select + buckets[i] <= sub_sum) {
        buckets[i] += select; // 分配得分
        // 递归检查下一个得分
        if (partition(link, index + 1, buckets, sub_sum))
          return true;
        buckets[i] -= select; // 回退
      }
    }

    return false; // 无法分配
  };

  // 检查能否分配成 m 组
  const function<bool(deque<int>&, int, int)> can_partition_m_subsets =
      [&](deque<int>& link, int sum, int m) {
    if (sum % m != 0)
      return false; // 总分不能被 m 整除

    const int sub_sum = sum / m;

    // 若最大得分超过目标分数，无法分配
    if (sub_sum < link[0])
      return false;

    // 移除被完全占用的得分
    while (!link.empty() && link[0] == sub_sum) {
      link.pop_front();
      m--;
    }

    vector<int> buckets(m, 0);
    return partition(link, 0, buckets, sub_sum);
  };

  // 进行从总人数到最少人数的尝试
  int max_players = t;                                        // 初始设定最多人数
  sort(scores.begin(), scores.end(), greater<int>());         // 从大到小排序
  const deque<int> score_deque(scores.begin(), scores.end()); // 将分数转换为双端队列

  // 尝试从所有人数到1人，每次减少人数
  while (max_players >= 1) {
    // 复制分数队列以进行检查
    deque<int> link_cp = score_deque;
    if (can_partition_m_subsets(link_cp, total_score, max_players)) {
      cout << total_score / max_players << endl; // 输出最小MVP得分
      return 0;
    }
    max_players--;
  }

  // 理论上不会到达这里
  cout << total_score << endl;
  return 0;
}
```

#### 游戏分组

**题目描述**：

部门准备举办一场王者荣耀表演赛，有 10 名游戏爱好者参与，分为两队，每队 5 人。

每位参与者都有一个评分，代表着他的游戏水平。为了表演赛尽可能精彩，我们需要把 10 名参赛者分为示例尽量相近的两队。

一队的实力可以表示为这一队 5 名队员的评分总和。

现在给你 10 名参与者的游戏水平评分，请你根据上述要求分队，最后输出这两组的实力差绝对值。

例：10 名参赛者的评分分别为：5 1 8 3 4 6 7 10 9 2，分组为（1 3 5 8 10）和（2 4 6 7 9），两组实力差最小，差值为 1。有多种分法，但是实力差的绝对值最小为 1。

**输入描述**：

10 个整数，表示 10 名参与者的游戏水平评分。范围在 [1, 10000] 之间。

**输出描述**：

1 个整数，表示分组后两组实力差绝对值的最小值。

**用例 1**：

输入：

```
1 2 3 4 5 6 7 8 9 10
```

输出：

```
1
```

说明：

10 名队员分为两组，两组实力差绝对值最小为 1

难度：中等

标签：位运算、枚举、状态压缩

```cpp
#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // 存储10名选手的评分
  vector<int> scores(10);

  // 读取10个评分
  for (int i = 0; i < 10; i++) {
    cin >> scores[i];
  }

  // 最小实力差
  int min_diff = INT_MAX;

  // 枚举所有可能的组合
  // 使用二进制方式枚举选择5个人的所有方案
  for (int state = 0; state < (1 << 10); state++) {
    // 确保选择了5个人
    if (__builtin_popcount(state) != 5)
      continue;

    // 计算两组的总分
    int group1_sum = 0, group2_sum = 0;

    // 遍历所有选手
    for (int i = 0; i < 10; i++) {
      // 使用位运算判断选手归属
      if (state & (1 << i)) {
        group1_sum += scores[i];
      } else {
        group2_sum += scores[i];
      }
    }

    // 更新最小实力差
    min_diff = min(min_diff, abs(group1_sum - group2_sum));
  }

  // 输出结果
  cout << min_diff << endl;

  return 0;
}
```

#### AI 处理器组合

**题目描述**：

某公司研发了一款高性能 AI 处理器。每台物理设备具备 8 颗 AI 处理器，编号分别为 0、1、2、3、4、5、6、7。

编号 0-3 的处理器处于同一个链路中，编号 4-7 的处理器处于另外一个链路中，不通链路中的处理器不能通信。如下图所示：

![img](https://hydro.ac/d/HWOD2023/p/1/file/YaQlWX5dmRgeof1TtQ9LN.png)

现给定服务器可用的处理器编号数组 array，以及任务申请的处理器数量 num，找出符合下列亲和性调度原则的芯片组合。

如果不存在符合要求的组合，则返回空列表。

亲和性调度原则：

- 如果申请处理器个数为 1，则选择同一链路，剩余可用的处理器数量为 1 个的最佳，其次是剩余 3 个的为次佳，然后是剩余 2 个，最后是剩余 4 个。
- 如果申请处理器个数为 2，则选择同一链路剩余可用的处理器数量 2 个的为最佳，其次是剩余 4 个，最后是剩余 3 个。
- 如果申请处理器个数为 4，则必须选择同一链路剩余可用的处理器数量为 4 个。
- 如果申请处理器个数为 8，则申请节点所有 8 个处理器。

提示：

1. 任务申请的处理器数量只能是 1、2、4、8。
2. 编号 0-3 的处理器处于一个链路，编号 4-7 的处理器处于另外一个链路。
3. 处理器编号唯一，且不存在相同编号处理器。

**输入描述**：

输入包含可用的处理器编号数组 array，以及任务申请的处理器数量 num 两个部分。

第一行为 array，第二行为 num。例如：

```
[0, 1, 4, 5, 6, 7]
1
```

表示当前编号为 0、1、4、5、6、7 的处理器可用。任务申请 1 个处理器。

- 0 <= array.length <= 8
- 0 <= array [i] <= 7
- num in [1, 2, 4, 8]

**输出描述**：

输出为组合列表，当 array = [0，1，4，5，6，7]，num = 1 时，输出为 [[0], [1]]。

**用例 1**：

输入：

```
[0, 1, 4, 5, 6, 7]
1
```

输出：

```
[[0], [1]]
```

说明：

根据第一条亲和性调度原则，在剩余两个处理器的链路（0, 1, 2, 3）中选择处理器。

由于只有 0 和 1 可用，则返回任意一颗处理器即可。

**用例 2**：

输入：

```
[0, 1, 4, 5, 6, 7]
4
```

输出：

```
[[4, 5, 6, 7]]
```

说明：根据第三条亲和性调度原则，必须选择同一链路剩余可用的处理器数量为 4 个的环

难度：中等

标签：深度优先搜索、回溯、排序

```cpp
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
```

### 200 分

#### 项目排期

**题目描述**：

项目组共有 N 个开发人员，项目经理接到了 M 个独立的需求，每个需求的工作量不同，且每个需求只能由一个开发人员独立完成，不能多人合作。

假定各个需求直接无任何先后依赖关系，请设计算法帮助项目经理进行工作安排，使整个项目能用最少的时间交付。

**输入描述**：

第一行输入为 M 个需求的工作量，单位为天，用逗号隔开。

例如：

> X1 X2 X3 ... Xm

表示共有 M 个需求，每个需求的工作量分别为 X1 天，X2 天，...，Xm 天。其中：

- 0 < M < 30
- 0 < Xm < 200

第二行输入为项目组人员数量 N

例如：

> 5

表示共有 5 名员工，其中 0 < N < 10

**输出描述**：

最快完成所有工作的天数

例如：

> 25

表示最短需要 25 天完成所有工作

**用例 1**：

输入：

```
6 2 7 7 9 3 2 1 3 11 4
2
```

输出：

```
28
```

说明：共有两位员工，其中一位分配需求 6 2 7 7 3 2 1 共需要 28 天完成，另一位分配需求 9 3 11 4 共需要 27 天完成，故完成所有工作至少需要 28 天。

难度：困难

标签：二分查找、回溯、贪心、动态规划

（28/33）

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// 检查当前桶容量是否可以装下所有球
bool CanAllocateBalls(int idx, const vector<int>& balls, vector<int>& buckets, int limit, int n) {
  if (idx == balls.size()) return true; // 所有球都成功分配

  const int current_ball = balls[idx];

  // 尝试将当前球分配给每个桶
  for (int i = 0; i < n; i++) {
    // 如果当前桶容量能够容纳该球
    if (buckets[i] + current_ball <= limit) {
      buckets[i] += current_ball; // 将球装入桶中

      // 递归尝试分配下一个球
      if (CanAllocateBalls(idx + 1, balls, buckets, limit, n)) {
        return true; // 成功分配
      }

      // 回溯：撤销操作
      buckets[i] -= current_ball;
    }
    // 剪枝：如果当前桶没有装入任何球，后面的桶也不应该再装此球
    if (buckets[i] == 0) break;
  }

  return false; // 无法分配
}

int main() {
  vector<int> balls;
  int num;

  // 读取球的工作量
  while (cin >> num) {
    balls.push_back(num);
    if (cin.peek() == '\n') break; // 当输入结束时（换行）跳出
  }

  // 读取开发人员数量
  int n;
  cin >> n;

  // 对工作量进行降序排序
  sort(balls.begin(), balls.end(), greater<int>());

  // 二分查找的上下界
  int low = balls[0]; // 至少需要最大工作量的容量
  int high = accumulate(balls.begin(), balls.end(), 0); // 总工作量

  int best_capacity = high; // 最优桶容量

  // 开始二分查找
  while (low <= high) {
    int mid = low + (high - low) / 2; // 中间桶容量
    vector<int> buckets(n, 0); // 初始化桶为0

    // 检查能否在此容量下完成分配
    if (CanAllocateBalls(0, balls, buckets, mid, n)) {
      best_capacity = mid; // 更新最优解
      high = mid - 1; // 尝试更小的容量
    } else {
      low = mid + 1; // 增加桶容量
    }
  }

  // 输出结果
  cout << best_capacity << endl;

  return 0;
}
```

#### 字符串拼接

**题目描述**：

给定 M（0 < M ≤ 30）个字符（a-z），从中取出任意字符（每个字符只能用一次）拼接成长度为 N（0 < N ≤ 5）的字符串，

要求相同的字符不能相邻，计算出给定的字符列表能拼接出多少种满足条件的字符串，

输入非法或者无法拼接出满足条件的字符串则返回 0。

**输入描述**：

给定的字符列表和结果字符串长度，中间使用空格(" ")拼接

**输出描述**：
满足条件的字符串个数

**用例 1**：

输入：

```
abc 1
```

输出：

```
3
```

说明：给定的字符为 a, b, c，结果字符串长度为 1，可以拼接成 a, b, c，共 3 种

**用例 2**：

输入：

```
dde 2
```

输出：

```
2
```

说明：给定的字符为 dde，结果字符串长度为 2，可以拼接成 de, ed，共 2 种

难度：中等

标签：字符串、回溯

(32/33)

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// 计算满足条件的字符串数量
void backtrack(string& current, const int n, unordered_map<char, int>& char_count, int& result) {
  // 当生成的字符串达到目标长度时，增加计数
  if (current.length() == n) {
    result++;
    return;
  }

  // 遍历所有字符
  for (auto& entry : char_count) {
    char c = entry.first;
    if (entry.second > 0) {
      // 边界条件：不允许相同字符相邻
      if (current.empty() || current.back() != c) {
        // 选择当前字符
        current.push_back(c);
        char_count[c]--; // 使用一个字符

        backtrack(current, n, char_count, result); // 递归调用

        // 回溯
        current.pop_back();
        char_count[c]++; // 恢复字符数量
      }
    }
  }
}

int main() {
  string input;
  getline(cin, input); // 读取输入

  // 从输入中提取字符和字符串长度
  string characters = input.substr(0, input.size() - 2);
  const int n = input.back() - '0'; // 读取末尾的数字

  // 统计字符频率
  unordered_map<char, int> char_count;
  for (char c : characters) {
    char_count[c]++;
  }

  // 输入非法、无法拼接字符串或者所需长度大于可用字符总数
  if (n > characters.size() || n <= 0 || characters.empty()) {
    cout << 0 << endl;
    return 0;
  }

  // 计算结果
  int result = 0;
  string current;
  backtrack(current, n, char_count, result);

  // 输出结果
  cout << result << endl;

  return 0;
}
```

#### 字母组合

**题目描述**：

每个数字关联多个字母，关联关系如下：

- 0 关联 “a”,”b”,”c”
- 1 关联 “d”,”e”,”f”
- 2 关联 “g”,”h”,”i”
- 3 关联 “j”,”k”,”l”
- 4 关联 “m”,”n”,”o”
- 5 关联 “p”,”q”,”r”
- 6 关联 “s”,”t”
- 7 关联 “u”,”v”
- 8 关联 “w”,”x”
- 9 关联 “y”,”z”

输入一串数字后，通过数字和字母的对应关系可以得到多个字母字符串（要求按照数字的顺序组合字母字符串）；

屏蔽字符串：屏蔽字符串中的所有字母不能同时在输出的字符串出现，如屏蔽字符串是 abc，则要求字符串中不能同时出现 a, b, c，但是允许同时出现 a, b 或 a, c 或 b, c 等；

给定一个数字字符串和一个屏蔽字符串，输出所有可能的字符组合；

例如输入数字字符串 78 和屏蔽字符串 ux，输出结果为 uw，vw，vx；数字字符串 78，可以得到如下字符串 uw，ux，vw，vx；由于 ux 是屏蔽字符串，因此排除 ux，最终的输出是 uw，vw，vx;

**输入描述**：

第一行输入为一串数字字符串，数字字符串中的数字不允许重复，数字字符串的长度大于 0，小于等于 5；

第二行输入是屏蔽字符串，屏蔽字符串的长度一定小于数字字符串的长度，屏蔽字符串中字符不会重复；

**输出描述**：

输出可能的字符串组合

注：字符串之间使用逗号隔开，最后一个字符串后携带逗号

**用例 1**：

输入：

```
78
ux
```

输出：

```
uw,vw,vx,
```

**用例 2**：

输入：

```
78
x
```

输出：

```
uw,vw,
```

难度：中等

标签：回溯、深度优先搜索、字符串、枚举

```cpp
#include <bits/stdc++.h>
using namespace std;

// 数字到字母的映射
unordered_map<char, vector<char>> num_to_letters = {
  {'0', {'a','b','c'}},
  {'1', {'d','e','f'}},
  {'2', {'g','h','i'}},
  {'3', {'j','k','l'}},
  {'4', {'m','n','o'}},
  {'5', {'p','q','r'}},
  {'6', {'s','t'}},
  {'7', {'u','v'}},
  {'8', {'w','x'}},
  {'9', {'y','z'}}
};

int main() {
  string digits, shield;
  cin >> digits >> shield;

  vector<string> result;

  // 回溯函数，使用 lambda 实现
  function<void(string, int)> backtrack =
  [&](const string& current, int index) {
    // 递归终止条件：达到数字串长度
    if (index == digits.length()) {
      // 检查是否包含所有屏蔽字符
      bool is_valid_combination = true;
      for (const char shield_char : shield) {
        if (current.find(shield_char) == string::npos) {
          is_valid_combination = false;
          break;
        }
      }

      // 如果不包含所有屏蔽字符，则加入结果
      if (!is_valid_combination) {
        result.push_back(current);
      }
      return;
    }

    // 获取当前数字对应的字母列表
    vector<char>& letters = num_to_letters[digits[index]];

    for (char letter : letters) {
      // 递归生成组合
      backtrack(current + letter, index + 1);
    }
  };

  // 启动回溯
  backtrack("", 0);

  // 输出结果
  for (const string& combo : result) {
    cout << combo << ",";
  }
  cout << endl;

  return 0;
}
```

#### 数字排列

**题目描述**：

小明负责公司年会，想出一个趣味游戏：

屏幕给出 1 ~ 9 中任意 4 个不重复的数字，大家以最快时间给出这几个数字可拼成的数字从小到大排列位于第 N 位置的数字，其中 N 为给出数字中最大的（如果不到这么多数字则给出最后一个即可）。

注意：

- 2 可以当作 5 来使用，5 也可以当作 2 来使用进行数字拼接，且屏幕不能同时给出 2 和 5；
- 6 可以当作 9 来使用，9 也可以当作 6 来使用进行数字拼接，且屏幕不能同时给出 6 和 9。

如给出：1，4，8，7，则可以拼接的数字为：

1，4，7，8，14，17，18，41，47，48，71，74，78，81，84，87，147，148，178 ... (省略后面的数字)

那么第 N （即 8）个的数字为 41。

**输入描述**：

输入以逗号分隔的 4 个 int 类型整数的字符串。

**输出描述**：

输出为这几个数字可拼成的数字从小大大排列位于第 N （N 为输入数字中最大的数字）位置的数字，

如果输入的数字不在范围内或者有重复，则输出-1。

**用例 1**：

输入：

```
1,4,8,7
```

输出：

```
41
```

说明：可以构成的数字按从小到大排序为：

1，4，7，8，14，17，18，41，47，48，71，74，78，81，84，87，147，148，178 ... （省略后面的数字），

**用例 2**：

输入：

```
2,5,1
```

输出：

```
-1
```

说明：2 和 5 不能同时出现

**用例 3**：

输入：

```
3,0,9
```

输出：

```
-1
```

说明：0 不在 1 到 9 范围内

**用例 4**：

输入：

```
3,9,7,8
```

输出：

```
39
```

说明：注意 9 可以当 6 使用，所以可以构成的数字按从小到大排序为：3，6，7，8，9，36，37，38，39，63，67，68，73，76，78，79，83 ... （省略后面的数字），

故第 9 个为 39

难度：中等

标签：回溯、字符串、数组、排序

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  string input;
  getline(cin, input);

  // 解析输入
  vector<int> nums;
  stringstream ss(input);
  string item;
  while (getline(ss, item, ',')) {
    nums.push_back(stoi(item));
  }

  // 检查输入数量
  if (nums.size() != 4) {
    cout << "-1" << endl;
    return 0;
  }

  // 记录出现过的数字
  bool set[10] = {false};
  int n = INT_MIN;

  // 输入验证
  for (const auto& num : nums) {
    // 检查数字范围
    if (num < 1 || num > 9) {
      cout << "-1" << endl;
      return 0;
    }

    // 检查重复数字
    if (set[num]) {
      cout << "-1" << endl;
      return 0;
    }

    set[num] = true;
    // 找出最大数字
    n = max(n, num);
  }

  // 特殊数字冲突检查
  if (set[2] && set[5]) {
    cout << "-1" << endl;
    return 0;
  }
  if (set[6] && set[9]) {
    cout << "-1" << endl;
    return 0;
  }

  // 特殊数字替换映射
  map<int, int> dic = {
      {2, 5}, {5, 2},
      {6, 9}, {9, 6}
  };

  // 初始化
  vector<bool> vis(nums.size(), false);
  string path;
  vector<int> res;

  // DFS生成组合
  function<void(string)> dfs = [&](string path) {
    // 非空路径加入结果
    if (!path.empty()) {
      res.emplace_back(stoi(path));
    }

    // 深度限制
    if (path.size() == nums.size()) {
      return;
    }

    // 回溯生成组合
    for (int i = 0; i < nums.size(); i++) {
      if (vis[i])
        continue;

      vis[i] = true;

      // 尝试原数字
      dfs(path + to_string(nums[i]));

      // 尝试特殊替换数字
      if (dic.count(nums[i])) {
        dfs(path + to_string(dic[nums[i]]));
      }

      vis[i] = false;
    }
  };

  // 执行DFS
  dfs("");

  // 排序
  sort(res.begin(), res.end());

  // 返回结果
  if (n <= res.size()) {
    cout << res[n - 1] << endl;
  } else {
    cout << res.back() << endl;
  }

  return 0;
}
```

#### 最佳的出牌方法

**题目描述**：

手上有一副扑克牌，每张牌按牌面数字记分（J = 11, Q = 12, K = 13，没有大小王)，出牌时按照以下规则记分：

- 出单张，记牌面分数，例如出一张 2，得分为 2
- 出对或 3 张，记牌面分数总和再 x2，例如出 3 张 3，得分为(3+3+3)x2 = 18
- 出 5 张顺，记牌面分数总和再 x2，例如出 34567 顺，得分为(3+4+5+6+7)x2 = 50
- 出 4 张炸弹，记牌面分数总和再 x3，例如出 4 张 4，得分为 4x4x3 = 48

求出一副牌最高的得分数

**输入描述**：

按顺序排好的一副牌，最少 1 张，最多 15 张。

1-9 输入为数字 1-9，10 输入为数字 0，JQK 输入为大写字母 JQK.

无需考虑输入非法的情况，例如输入字符不在 [0-9JQK] 范围或某一张牌超过 4 张

**输出描述**：

最高的得分数

积分规则中没有的出牌方式不支持，例如不支持 3 带 1、4 带 2，不支持 5 张以上的顺，且 10JQKA (0JQK1) 不算顺。

**用例 1**：

输入：

```
33445677
```

输出：

```
67
```

说明：

出对 3、对 4、对 7，单张 5、6，得分为 67;

出 34567 顺，再出单张 3、4、7，得分为 64

因此最高得分是按对出，可得到最高分 67，输出结果 67

难度：困难

标签：动态规划、回溯、贪心

```cpp
#include <bits/stdc++.h>
using namespace std;

int max_score = 0;

void dfs(vector<int>& card_count, int start_idx, int current_score,
         int remaining_cards) {
  // 如果没有剩余牌，更新最大分数
  if (remaining_cards == 0) {
    max_score = max(max_score, current_score);
    return;
  }

  // 跳过没有牌的位置
  while (start_idx <= 13 && card_count[start_idx] == 0) {
    start_idx++;
  }

  // 已经遍历完所有位置
  if (start_idx > 13) {
    max_score = max(max_score, current_score);
    return;
  }

  // 尝试出单张
  if (card_count[start_idx] >= 1) {
    card_count[start_idx]--;
    dfs(card_count, start_idx, current_score + start_idx, remaining_cards - 1);
    card_count[start_idx]++;
  }

  // 尝试出对子
  if (card_count[start_idx] >= 2) {
    card_count[start_idx] -= 2;
    dfs(card_count, start_idx, current_score + start_idx * 2 * 2,
        remaining_cards - 2);
    card_count[start_idx] += 2;
  }

  // 尝试出三张
  if (card_count[start_idx] >= 3) {
    card_count[start_idx] -= 3;
    dfs(card_count, start_idx, current_score + start_idx * 3 * 2,
        remaining_cards - 3);
    card_count[start_idx] += 3;
  }

  // 尝试出炸弹
  if (card_count[start_idx] >= 4) {
    card_count[start_idx] -= 4;
    dfs(card_count, start_idx, current_score + start_idx * 4 * 3,
        remaining_cards - 4);
    card_count[start_idx] += 4;
  }

  // 尝试出顺子
  if (start_idx + 4 <= 13) {
    bool can_sequence = true;
    for (int j = 0; j < 5; j++) {
      if (card_count[start_idx + j] < 1) {
        can_sequence = false;
        break;
      }
    }

    if (can_sequence) {
      int seq_sum = start_idx + (start_idx + 1) + (start_idx + 2) + (
                            start_idx + 3) + (start_idx + 4);
      for (int j = 0; j < 5; j++) {
        card_count[start_idx + j]--;
      }
      dfs(card_count, start_idx, current_score + seq_sum * 2,
          remaining_cards - 5);
      for (int j = 0; j < 5; j++) {
        card_count[start_idx + j]++;
      }
    }
  }

  // 跳过当前位置
  dfs(card_count, start_idx + 1, current_score, remaining_cards);
}

int main() {
  string cards;
  cin >> cards;

  // 初始化card_count
  vector<int> card_count(14, 0);
  for (char c : cards) {
    int num = 0;
    if (c >= '1' && c <= '9')
      num = c - '0';
    else if (c == '0')
      num = 10;
    else if (c == 'J')
      num = 11;
    else if (c == 'Q')
      num = 12;
    else
      if (c == 'K')
        num = 13;
    card_count[num]++;
  }

  // 计算总的剩余牌数
  int total_cards = cards.length();

  // 重置最大分数
  max_score = 0;

  // 开始深度优先搜索，从第1个位置开始
  dfs(card_count, 1, 0, total_cards);

  // 输出最大分数
  cout << max_score << endl;

  return 0;
}
```

## 深度优先搜索

### 200 分

#### 找单词

**题目描述**：

给一个字符串和一个二维字符数组，如果该字符串存在于该数组中，则按字符串的字符顺序输出字符串每个字符所在单元格的位置下标字符串，如果找不到返回字符串“N”。

1.需要按照字符串的字符组成顺序搜索，且搜索到的位置必须是相邻单元格，其中“相邻单元格”是指那些水平相邻或垂直相邻的单元格。

2.同一个单元格内的字母不允许被重复使用。

3.假定在数组中最多只存在一个可能的匹配。

**输入描述**：

第 1 行为一个数字 N 指示二维数组在后续输入所占的行数。

第 2 行到第 N+1 行输入为一个二维大写字符数组，每行字符用半角, 分割。

第 N+2 行为待查找的字符串，由大写字符组成。

二维数组的大小为 N\*N，0 < N <= 100。

单词长度 K，0 < K < 1000。

**输出描述**：

输出一个位置下标字符串，拼接格式为：第 1 个字符行下标+”,”+第 1 个字符列下标+”,”+第 2 个字符行下标+”,”+第 2 个字符列下标… +”,”+第 N 个字符行下标+”,”+第 N 个字符列下标。

**用例 1**：

输入：

```
4
A,C,C,F
C,D,E,D
B,E,S,S
F,E,C,A
ACCESS
```

输出：

```
0,0,0,1,0,2,1,2,2,2,2,3
```

说明：ACCESS 分别对应二维数组的 [0,0] [0,1] [0,2] [1,2] [2,2] [2,3] 下标位置。

难度：中等

标签：深度优先搜索、数组、字符串、回溯、矩阵

```cpp
#include <bits/stdc++.h>
using namespace std;

bool dfs(vector<vector<char> >& grid, string& word, int row, int col, int index,
         vector<vector<bool> >& visited,
         vector<pair<int, int> >& current_path) {
  // 边界条件检查和是否匹配检查
  if (index == word.length()) {
    return true;
  }

  // 检查是否越界、是否访问过、是否匹配
  if (row < 0 || row >= grid.size() ||
      col < 0 || col >= grid[0].size() ||
      visited[row][col] ||
      grid[row][col] != word[index]) {
    return false;
  }

  // 标记当前单元格已访问
  visited[row][col] = true;
  current_path.emplace_back(row, col);

  // 四个方向：上、右、下、左
  int dx[4] = {-1, 0, 1, 0};
  int dy[4] = {0, 1, 0, -1};

  // 尝试四个方向
  for (int i = 0; i < 4; i++) {
    int new_row = row + dx[i];
    int new_col = col + dy[i];

    if (dfs(grid, word, new_row, new_col, index + 1, visited, current_path)) {
      return true;
    }
  }

  // 回溯：取消标记
  visited[row][col] = false;
  current_path.pop_back();
  return false;
}

int main() {
  int n;
  cin >> n;

  // 读取二维数组
  vector<vector<char> > grid(n, vector<char>(n));
  for (int i = 0; i < n; i++) {
    string line;
    cin >> line;

    // 解析每一行
    istringstream ss(line);
    string cell;
    int j = 0;
    while (getline(ss, cell, ',')) {
      grid[i][j++] = cell[0];
    }
  }

  // 读取目标字符串
  string word;
  cin >> word;

  // 存储结果路径
  vector<pair<int, int> > final_path;
  bool found = false;

  // 遍历每个起始点
  for (int i = 0; i < n && !found; i++) {
    for (int j = 0; j < n && !found; j++) {
      // 起始字符匹配
      if (grid[i][j] == word[0]) {
        // 访问标记数组
        vector<vector<bool> > visited(n, vector<bool>(n, false));
        vector<pair<int, int> > current_path;

        // 如果找到路径
        if (dfs(grid, word, i, j, 0, visited, current_path)) {
          found = true;
          final_path = current_path;
        }
      }
    }
  }

  // 输出路径
  if (found) {
    for (int i = 0; i < final_path.size(); i++) {
      cout << final_path[i].first << "," << final_path[i].second;
      if (i < final_path.size() - 1) {
        cout << ",";
      }
    }
    cout << endl;
  } else {
    cout << "N" << endl;
  }

  return 0;
}
```

### 加密算法

**题目描述**：

有一种特殊的加密算法，明文为一段数字串，经过密码本查找转换，生成另一段密文数字串。

规则如下：

1. 明文为一段数字串由 0~9 组成

2. 密码本为数字 0~9 组成的二维数组

3. 需要按明文串的数字顺序在密码本里找到同样的数字串，密码本里的数字串是由相邻的单元格数字组成，上下和左右是相邻的，注意：对角线不相邻，同一个单元格的数字不能重复使用。

4. 每一位明文对应密文即为密码本中找到的单元格所在的行和列序号（序号从 0 开始）组成的两个数宇。

   如明文第 i 位 Data [i] 对应密码本单元格为 Book [x][y]，则明文第 i 位对应的密文为 X Y，X 和 Y 之间用空格隔开。

如果有多条密文，返回字符序最小的密文。

如果密码本无法匹配，返回 "error"。

请你设计这个加密程序。

示例 1：

密码本：

> 0 0 2
>
> 1 3 4
>
> 6 6 4

明文："3"，密文："1 1"

示例 2：

密码本：

> 0 0 2
>
> 1 3 4
>
> 6 6 4

明文："0 3"，密文："0 1 1 1"

示例 3：

密码本：

> 0 0 2 4
>
> 1 3 4 6
>
> 3 4 1 5
>
> 6 6 6 5

明文："0 0 2 4"，密文："0 0 0 1 0 2 0 3" 和 "0 0 0 1 0 2 1 2"，返回字典序最小的 "0 0 0 1 0 2 0 3"

明文："8 2 2 3"，密文："error"，密码本中无法匹配

**输入描述**：

第一行输入 1 个正整数 N，代表明文的长度（1 ≤ N ≤ 200）

第二行输入 N 个明文组成的序列 Data [i]（0 ≤ Data [i] ≤ 9）

第三行输入 1 个正整数 M，代表密文的长度

接下来 M 行，每行 M 个数，代表密文矩阵

**输出描述**：

输出字典序最小密文，如果无法匹配，输出 "error"

**用例 1**：

输入：

```
2
0 3
3
0 0 2
1 3 4
6 6 4
```

输出：

```
0 1 1 1
```

说明：

**用例 2**：

输入：

```
2
0 5
3
0 0 2
1 3 4
6 6 4
```

输出：

```
error
```

说明：找不到 0 5 的序列，返回 error

难度：中等

标签：深度优先搜索、矩阵、回溯

```cpp
#include <bits/stdc++.h>
using namespace std;

// 按照 上、左、右、下 的优先级顺序
vector<vector<int> > directions = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

bool dfs(vector<vector<int> >& book, vector<int>& data, int index,
         int row, int col, vector<pair<int, int> >& current_path,
         vector<vector<bool> >& visited) {
  // 如果已经匹配了所有字符
  if (index == data.size()) {
    return true;
  }

  // 按照 上、左、右、下 的优先级搜索
  for (auto& dir : directions) {
    int new_row = row + dir[0];
    int new_col = col + dir[1];

    // 检查新坐标是否合法
    if (new_row >= 0 && new_row < book.size() &&
        new_col >= 0 && new_col < book[0].size() &&
        !visited[new_row][new_col] &&
        book[new_row][new_col] == data[index]) {

      // 标记为已访问
      visited[new_row][new_col] = true;
      current_path.emplace_back(new_row, new_col);

      // 继续搜索下一个字符
      if (dfs(book, data, index + 1, new_row, new_col, current_path, visited)) {
        return true;
      }

      // 回溯
      visited[new_row][new_col] = false;
      current_path.pop_back();
    }
  }

  return false;
}

int main() {
  int n; // 明文长度
  cin >> n;

  vector<int> data(n);
  for (int i = 0; i < n; i++) {
    cin >> data[i];
  }

  int m; // 密码本大小
  cin >> m;

  vector<vector<int> > book(m, vector<int>(m));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      cin >> book[i][j];
    }
  }

  vector<vector<pair<int, int> > > all_paths;

  // 遍历所有可能的起始位置
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (book[i][j] == data[0]) {
        vector<vector<bool> > visited(m, vector<bool>(m, false));
        vector<pair<int, int> > current_path;

        // 初始化起始位置
        visited[i][j] = true;
        current_path.emplace_back(i, j);

        // 尝试从该位置开始搜索
        if (dfs(book, data, 1, i, j, current_path, visited)) {
          all_paths.push_back(current_path);
        }
      }
    }
  }

  // 输出结果
  if (all_paths.empty()) {
    cout << "error" << endl;
  } else {
    // 由于已经按照优先级搜索，第一个路径就是最优解
    for (auto& pos : all_paths[0]) {
      cout << pos.first << " " << pos.second << " ";
    }
    cout << endl;
  }

  return 0;
}
```

## 广度优先搜索

### 200 分

#### 跳马

**题目描述**：

马是象棋（包括中国象棋和国际象棋）中的棋子，走法是每步直一格再斜一格，即先横着或者直者走一格，然后再斜着走一个对角线，可进可退，可越过河界，俗称 "马走日" 字。

给定 m 行 n 列的棋盘（网格图），棋盘上只有棋子象棋中的棋子“马”，并且每个棋子有等级之分，等级为 k 的马可以跳 1~k 步（走的方式与象棋中“马”的规则一样，不可以超出棋盘位置），问是否能将所有马跳到同一位置，如果存在，输出最少需要的总步数（每匹马的步数相加），不存在则输出-1。

注：允许不同的马在跳的过程中跳到同一位置，坐标为（x, y）的马跳一次可以跳到的坐标为：(x+1, y+2)，(x+1, y-2)，(x+2, y+1)，(x+2, y-1)，(x-1, y+2)，(x-1, y-2)，(x-2, y+1)，(x-2, y-1)，的格点上，但是不可以超出棋盘范围。

**输入描述**：

第一行输入 m，n，代表 m 行 n 列的网格图棋盘（1 ≤ m, n ≤ 25）

接下来输入 m 行 n 列的网格图棋盘，如果第 i 行，第 j 列的元素为 "." ，代表此格点没有棋子，如果为数字 k（1 ≤ k ≤ 9），代表此格点存在等级为 k 的“马”

**输出描述**：

输出最少需要的总步数（每匹马的步数相加），不存在则输出-1。

**用例 1**：

输入：

```
3 2
..
2.
..
```

输出：

```
0
```

说明：只有一匹马，不需要跳动

**用例 2**：

输入：

```
3 5
47.48
4744.
7....
```

输出：

```
17
```

难度：困难

标签：广度优先搜索、图论

```cpp
#include <bits/stdc++.h>
using namespace std;

// 马可以跳跃的8个方向
const int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
const int dy[] = {2, -2, 1, -1, 2, -2, 1, -1};

int main() {
  int m, n;
  cin >> m >> n;

  vector<vector<char> > board(m, vector<char>(n));
  vector<pair<int, int> > horses; // 记录马的位置
  vector<int> levels;             // 记录马的等级

  // 读取棋盘数据并记录每匹马的位置和等级
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];
      if (isdigit(board[i][j])) {
        // 检查是否是马
        horses.emplace_back(i, j);
        levels.push_back(board[i][j] - '0');
      }
    }
  }

  // 如果只有一匹马，不需要跳动，直接返回0
  if (horses.size() == 1) {
    cout << 0 << endl;
    return 0;
  }

  // 初始化 stepMap，记录每个位置的马所花费的最小步数之和
  vector<vector<int> > step_map(m, vector<int>(n, 0));

  // reach集合用于记录所有马都能跳到的公共位置
  unordered_set<int> reach;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      reach.insert(i * n + j); // 初始化为棋盘上的所有位置
    }
  }

  // 操作每匹马
  for (int k = 0; k < horses.size(); k++) {
    int x = horses[k].first;
    int y = horses[k].second;
    int level = levels[k];

    // BFS 初始化
    queue<pair<int, int> > q;
    q.emplace(x, y);

    // 记录该马能到达的位置
    unordered_set<int> vis;
    vis.insert(x * n + y);

    // 记录该马能跳到的位置
    unordered_set<int> current_reach;
    current_reach.insert(x * n + y);

    // BFS过程
    for (int step = 1; step <= level; step++) {
      int q_size = q.size(); // 当前层的节点数量

      for (int j = 0; j < q_size; j++) {
        auto [curr_x, curr_y] = q.front();
        q.pop();

        // 从当前位置出发，进行跳跃
        for (int direction = 0; direction < 8; direction++) {
          int new_x = curr_x + dx[direction];
          int new_y = curr_y + dy[direction];

          // 检查步数是否越界
          if (new_x >= 0 && new_x < m && new_y >= 0 && new_y < n) {
            int pos_index = new_x * n + new_y;

            // 如果该位置未被访问，将其加入队列并更新
            if (vis.find(pos_index) == vis.end()) {
              q.emplace(new_x, new_y);
              vis.insert(pos_index);
              step_map[new_x][new_y] += step; //步数累加
              current_reach.insert(pos_index);
            }
          }
        }
      }
    }

    // 更新公共 reachable 位置集
    unordered_set<int> updated_reach;
    for (int pos : reach) {
      if (current_reach.find(pos) != current_reach.end()) {
        updated_reach.insert(pos);
      }
    }
    reach = updated_reach; // 更新 reachable 集合为交集
  }

  // 如果没有公共位置，返回-1
  if (reach.empty()) {
    cout << -1 << endl;
    return 0;
  }

  // 计算所有公共位置中的最小步数和
  int min_total_steps = INT_MAX;
  for (int pos : reach) {
    int rx = pos / n; // 行索引
    int ry = pos % n; // 列索引
    min_total_steps = min(min_total_steps, step_map[rx][ry]);
  }

  cout << min_total_steps << endl; // 输出结果
  return 0;
}
```

#### 智能驾驶

**题目描述**：

有一辆汽车需要从 m \* n 的地图左上角（起点）开往地图的右下角（终点），去往每一个地区都需要消耗一定的油量，加油站可进行加油。

请你计算汽车确保从从起点到达终点时所需的最少初始油量。

说明：

1. 智能汽车可以上下左右四个方向移动
2. 地图上的数字取值是 0 或 -1 或 正整数：
   - -1 ：表示加油站，可以加满油，汽车的油箱容量最大为 100；
   - 0 ：表示这个地区是障碍物，汽车不能通过
   - 正整数：表示汽车走过这个地区的耗油量
3. 如果汽车无论如何都无法到达终点，则返回 -1

**输入描述**：

第一行为两个数字，M，N，表示地图的大小为 M \* N

- 0 < M, N ≤ 200

后面一个 M \* N 的矩阵，其中的值是 0 或 -1 或正整数，加油站的总数不超过 200 个

**输出描述**：

如果汽车无论如何都无法到达终点，则返回 -1

如果汽车可以到达终点，则返回最少的初始油量

**用例 1**：

输入：

```
2,2
10,20
30,40
```

输出：

```
70
```

说明：行走的路线为：右 → 下

**用例 2**：

输入：

```
4,4
10,30,30,20
30,30,-1,10
0,20,20,40
10,-1,30,40
```

输出：

```
70
```

说明：行走的路线为：右 → 右 → 下 → 下 → 下 → 右

**用例 3**：

输入：

```
4,5
10,0,30,-1,10
30,0,20,0,20
10,0,10,0,30
10,-1,30,0,10
```

输出：

```
60
```

说明：行走的路线为：下 → 下 → 下 → 右 → 右 → 上 → 上 → 上 → 右 → 右 → 下 → 下 → 下

**用例 4**：

输入：

```
4,4
10,30,30,20
30,30,20,10
10,20,10,40
10,20,30,40
```

输出：

```
-1
```

说明：无论如何都无法到达终点

难度：困难

算法标签：广度优先搜索、贪心、堆（优先队列）

#### 树状结构查询

**题目描述**：

通常使用多行的节点、父节点表示一棵树，比如

> 西安 陕西
>
> 陕西 中国
>
> 江西 中国
>
> 中国 亚洲
>
> 泰国 亚洲

输入一个节点之后，请打印出来树中他的所有下层节点

**输入描述**：

第一行输入行数，下面是多行数据，每行以空格区分节点和父节点

接着是查询节点

**输出描述**：

输出查询节点的所有下层节点。以字典序排序

树中的节点是唯一的，不会出现两个节点，是同一个名字

**用例 1**：

输入：

```
5
b a
c a
d c
e c
f d
c
```

输出：

```
d
e
f
```

难度：简单

标签：树、深度优先搜索、广度优先搜索、递归

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  // 建立映射关系
  unordered_map<string, vector<string>> tree;
  set<string> nodes;

  // 读取树的节点关系
  for (int i = 0; i < n; i++) {
    string child, parent;
    cin >> child >> parent;

    tree[parent].push_back(child);
    nodes.insert(child);
    nodes.insert(parent);
  }

  // 查询节点
  string query;
  cin >> query;

  // 存储查询结果的集合
  set<string> result;

  // 深度优先搜索查找所有下层节点
  function<void(string)> dfs = [&](string node) {
    // 如果该节点没有子节点，直接返回
    if (tree.count(node) == 0) return;

    // 遍历所有子节点
    for (string child : tree[node]) {
      result.insert(child);
      // 递归查找子节点的下层节点
      dfs(child);
    }
  };

  // 执行深度优先搜索
  dfs(query);

  // 输出结果
  for (string node : result) {
    cout << node << endl;
  }

  return 0;
}
```

#### 周末爬山

**题目描述**：

周末小明准备去爬山锻炼，0 代表平地，山的高度使用 1 到 9 来表示，小明每次爬山或下山高度只能相差 k 及 k 以内，每次只能上下左右一个方向上移动一格，小明从左上角(0,0)位置出发

**输入描述**：

第一行输入 m n k(空格分隔)

- 代表 m\*n 的二维山地图，k 为小明每次爬山或下山高度差的最大值，

然后接下来输入山地图，一共 m 行 n 列，均以空格分隔。取值范围：

- 0 < m ≤ 500
- 0 < n ≤ 500
- 0 < k < 5

**输出描述**：

请问小明能爬到的最高峰多高，到该最高峰的最短步数，输出以空格分隔。

同高度的山峰输出较短步数。

如果没有可以爬的山峰，则高度和步数都返回 0。

所有用例输入均为正确格式，且在取值范围内，考生不需要考虑不合法的输入格式。

**用例 1**：

输入：

```
5 4 1
0 1 2 0
1 0 0 0
1 0 1 2
1 3 1 0
0 0 0 9
```

输出：

```
2 2
```

说明：根据山地图可知，能爬到的最高峰在(0,2)位置，高度为 2，最短路径为(0,0)-(0,1)-(0,2)，最短步数为 2。

**用例 2**：

输入：

```
5 4 3
0 0 0 0
0 0 0 0
0 9 0 0
0 0 0 0
0 0 0 9
```

输出：

```
0 0
```

说明：根据山地图可知，每次爬山距离 3，无法爬到山峰上，步数为 0。

难度：中等

标签：广度优先搜索、图、动态规划、回溯、深度优先搜索

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cstdlib>  // for abs
using namespace std;

int main() {
  int m, n, k;
  cin >> m >> n >> k;

  // 读取地图
  vector<vector<int> > grid(m, vector<int>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> grid[i][j];
    }
  }

  // 定义方向数组：上下左右
  int dx[4] = {-1, 1, 0, 0};
  int dy[4] = {0, 0, -1, 1};

  // 记录访问状态
  vector<vector<bool> > visited(m, vector<bool>(n, false));

  // BFS 队列，存储坐标 (x, y) 和步数 step
  queue<tuple<int, int, int> > q;

  // 初始化
  q.push({0, 0, 0});
  visited[0][0] = true;

  // 记录最高山峰和最小步数
  int max_height = grid[0][0];
  int min_steps = 0;

  while (!q.empty()) {
    // 使用 std::get 获取队列元素
    int x = get<0>(q.front());
    int y = get<1>(q.front());
    int step = get<2>(q.front());
    q.pop();

    // 检查当前位置的高度
    int cur_height = grid[x][y];

    // 更新最高山峰和最小步数
    if (cur_height > max_height) {
      max_height = cur_height;
      min_steps = step; // 更新到更高峰的步数
    } else if (cur_height == max_height) {
      min_steps = min(min_steps, step); // 更新较小步数
    }

    // 四个方向搜索
    for (int i = 0; i < 4; ++i) {
      int new_x = x + dx[i];
      int new_y = y + dy[i];

      // 越界检查
      if (new_x < 0 || new_x >= m || new_y < 0 || new_y >= n)
        continue;
      // 已访问检查
      if (visited[new_x][new_y])
        continue;

      // 高度差检查
      if (abs(grid[new_x][new_y] - cur_height) > k)
        continue;

      // 标记访问并加入队列
      visited[new_x][new_y] = true;
      q.push({new_x, new_y, step + 1});
    }
  }

  // 检查结果输出
  if (max_height == grid[0][0]) {
    // 根据你的描述，如果没有可爬的更高山峰
    cout << "0 0" << endl;
  } else {
    cout << max_height << " " << min_steps << endl;
  }

  return 0;
}
```

#### 计算网络信号

**题目描述**：

网络信号经过传递会逐层衰减，且遇到阻隔物无法直接穿透，在此情况下需要计算某个位置的网络信号值。注意: 网络信号可以绕过阻隔物。

- array\[m\]\[n\] 的二维数组代表网格地图，
- array\[i\]\[j\] = 0 代表 i 行 j 列是空旷位置;
- array\[i\]\[j\] = x(x 为正整数)代表 i 行 j 列是信号源，信号强度是 x;
- array\[i\]\[j\] = -1 代表 i 行 j 列是阻隔物。
- 信号源只有 1 个，阻隔物可能有 0 个或多个
- 网络信号衰减是上下左右相邻的网格衰减 1

现要求输出对应位置的网络信号值。

**输入描述**：

输入为三行，

- 第一行为 m 、n ，代表输入是一个 m × n 的数组。
- 第二行是一串 m × n 个用空格分隔的整数。每连续 n 个数代表一行，再往后 n 个代表下一行，以此类推。对应的值代表对应的网格是空旷位置，还是信号源，还是阻隔物。
- 第三行是 i 、 j，代表需要计算 array [i][j] 的网络信号值。

注意：此处 i 和 j 均从 0 开始，即第一行 i 为 0。

例如

```none
6 5
0 0 0 -1 0 0 0 0 0 0 0 0 -1 4 0 0 0 0 0 0 0 0 0 0 -1 0 0 0 0 0
1 4
```

[Copy](javascript:;)

代表如下地图

![img](https://hydro.ac/d/HWOD2023/p/92/file/tnIRJQWGchx_2_4Fkaf5b.png)

需要输出第 1 行第 4 列的网络信号值，如下图，值为 2。

![img](https://hydro.ac/d/HWOD2023/p/92/file/sOwYJzTK-LxMDbxwnGrF_.png)

**输出描述**：

输出对应位置的网络信号值，如果网络信号未覆盖到，也输出 0。

一个网格如果可以途径不同的传播衰减路径传达，取较大的值作为其信号值。

**用例 1**：

输入：

```
6 5
0 0 0 -1 0 0 0 0 0 0 0 0 -1 4 0 0 0 0 0 0 0 0 0 0 -1 0 0 0 0 0
1 4
```

输出：

```
2
```

**用例 2**：

输入：

```
6 5
0 0 0 -1 0 0 0 0 0 0 0 0 -1 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
2 1
```

输出：

```
0
```

难度：中等

标签：广度优先搜索、图、动态规划

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  int m, n;
  cin >> m >> n;

  vector<vector<int> > array(m, vector<int>(n));

  // 输入网格数组
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> array[i][j];
    }
  }

  // 读取需要计算的 (i, j)
  int target_i, target_j;
  cin >> target_i >> target_j;

  // BFS 初始化
  queue<tuple<int, int, int> > q; // (x, y, 信号强度)
  int signal_strength = 0;        // 信号源的强度

  // 查找信号源并初始化 BFS
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (array[i][j] > 0) {
        // 检查信号源
        q.push({i, j, array[i][j]});   // (行, 列, 信号强度)
        signal_strength = array[i][j]; // 保存信号强度
      }
    }
  }

  // 方向数组：上下左右
  int dx[4] = {-1, 1, 0, 0};
  int dy[4] = {0, 0, -1, 1};

  // 记录信号强度到达的值
  vector<vector<int> > signal_value(m, vector<int>(n, 0));
  signal_value[get<0>(q.front())][get<1>(q.front())] = signal_strength;
  // 信号源的强度初始化

  // BFS 传播信号
  while (!q.empty()) {
    auto [x, y, strength] = q.front();
    q.pop();

    // 逐邻居传播信号
    for (int i = 0; i < 4; ++i) {
      int new_x = x + dx[i];
      int new_y = y + dy[i];

      // 边界检查
      if (new_x < 0 || new_x >= m || new_y < 0 || new_y >= n)
        continue;
      // 不能到达阻碍物
      if (array[new_x][new_y] == -1)
        continue;

      int new_signal_strength = strength - 1; // 信号衰减
      // 只在信号大于现有值时更新
      if (new_signal_strength > signal_value[new_x][new_y]) {
        signal_value[new_x][new_y] = new_signal_strength; // 更新信号值
        q.push({new_x, new_y, new_signal_strength});      // 继续传播
      }
    }
  }

  // 输出目标位置的信号值
  cout << signal_value[target_i][target_j] << endl;

  return 0;
}
```

#### 计算疫情扩散时间

**题目描述**：

在一个地图中(地图由 n\*n 个区域组成），有部分区域被感染病菌。 感染区域每天都会把周围（上下左右）的 4 个区域感染。 请根据给定的地图计算，多少天以后，全部区域都会被感染。 如果初始地图上所有区域全部都被感染，或者没有被感染区域，返回-1

**输入描述**：

一行 N\*N 个数字（只包含 0,1，不会有其他数字）表示一个地图，数字间用, 分割，0 表示未感染区域，1 表示已经感染区域 每 N 个数字表示地图中一行，输入数据共表示 N 行 N 列的区域地图。

例如输入 1,0,1,0,0,0,1,0,1，表示地图

```none
1,0,1
0,0,0
1,0,1
```

**输出描述**：

一个整数，表示经过多少天以后，全部区域都被感染 1 <= N < 200

**用例 1**：

输入：

```
1,0,1,0,0,0,1,0,1
```

输出：

```
2
```

说明：1 天以后，地图中仅剩余中心点未被感染；2 天以后，全部被感染。

**用例 2**：

输入：

```
0,0,0,0
```

输出：

```
-1
```

说明：无感染区域

**用例 3**：

输入：

```
1,1,1,1,1,1,1,1,1
```

输出：

```
-1
```

说明：全部都感染

难度：中等

算法：队列、广度优先搜索、图

#### 宜居星球改造计划

**题目描述**：

2XXX 年，人类通过对火星的大气进行宜居改造分析，使得火星已在理论上具备人类宜居的条件；

由于技术原因，无法一次性将火星大气全部改造，只能通过局部处理形式；

假设将火星待改造的区域为 row \* column 的网格，每个网格有 3 个值，宜居区、可改造区、死亡区，使用 YES、NO、NA 代替，YES 表示该网格已经完成大气改造，NO 表示该网格未进行改造，后期可进行改造，NA 表示死亡区，不作为判断是否改造完的宜居，无法穿过；

初始化下，该区域可能存在多个宜居区，并目每个宜居区能同时在每个大阳日单位向上下左右四个方向的相邻格子进行扩散，自动将 4 个方向相邻的真空区改造成宜居区；

请计算这个待改造区域的网格中，可改造区是否能全部成宜居区，如果可以，则返回改造的大阳日天教，不可以则返回-1

**输入描述**：

输入 row \* column 个网格数据，每个网格值枚举值如下: YES，NO，NA；

样例:

```none
YES YES NO
NO NO NO
NA NO YES
```

**输出描述**：

可改造区是否能全部变成宜居区，如果可以，则返回改造的太阳日天数，不可以则返回-1。

grid\[i\]\[j\]只有 3 种情况，YES、NO、NA

- row == grid.length
- column == grid [i].length
- 1 ≤ row, column ≤ 8

**用例 1**：

输入：

```
YES YES NO
NO NO NO
YES NO NO
```

输出：

```
2
```

说明：经过 2 个太阳日，完成宜居改造

**用例 2**：

输入：

```
YES NO NO NO
NO NO NO NO
NO NO NO NO
NO NO NO NO
```

输出：

```
6
```

说明：经过 6 个太阳日，可完成改造

**用例 3**：

输入：

```
NO NA
```

输出：

```
-1
```

说明：无改造初始条件，无法进行改造

**用例 4**：

输入：

```
YES NO NO YES
NO NO YES NO
NO YES NA NA
YES NO NA NO
```

输出：

```
-1
```

说明：右下角的区域，被周边三个死亡区挡住，无法实现改造

难度：中等

标签：广度优先搜索、图、队列

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

int main() {
  string line;
  vector<vector<string> > grid;
  int rows = 0, cols = 0;

  // 读取输入
  while (getline(cin, line)) {
    stringstream ss(line);
    vector<string> row;
    string cell;
    while (ss >> cell) {
      row.push_back(cell);
    }
    grid.push_back(row);
    cols = row.size(); // 每行的列数
    rows++;
  }

  // BFS 初始化
  queue<pair<int, int> > q; // BFS 队列
  int total_no_count = 0;     // 统计可改造区域数量
  int days = 0;             // 记录所需天数

  // 填充初始队列和统计可改造区域
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (grid[i][j] == "YES") {
        q.push(make_pair(i, j)); // 初始化 BFS
      } else if (grid[i][j] == "NO") {
        total_no_count++; // 统计可改造区域
      }
    }
  }

  // 如果没有可改造区域，检查是否有已改造的区域
  if (total_no_count == 0) {
    cout << (q.empty() ? -1 : 0) << endl;
    return 0;
  }

  // BFS 扩散
  int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 上下左右方向

  while (!q.empty()) {
    int size = q.size();
    bool modified = false; // 标记这一轮是否有区域被改造

    for (int i = 0; i < size; ++i) {
      // 使用传统方式访问队列元素
      int x = q.front().first;
      int y = q.front().second;
      q.pop();

      // 尝试向上下左右扩散
      for (int j = 0; j < 4; ++j) {
        int new_x = x + directions[j][0];
        int new_y = y + directions[j][1];

        // 检查边界条件
        if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && grid[new_x][
              new_y] == "NO") {
          grid[new_x][new_y] = "YES";      // 更新为已改造区域
          q.push(make_pair(new_x, new_y)); // 加入队列
          total_no_count--;                // 可改造区域减少
          modified = true;               // 标记发生改造
        }
      }
    }

    // 如果这一轮有更新，表示天数加一
    if (modified) {
      days++;
    }
  }

  // 如果所有可改造区域都已改造
  cout << (total_no_count == 0 ? days : -1) << endl;

  return 0;
}
```

#### 战场索敌

**题目描述**：

有一个大小是 N\*M 的战场地图，被墙壁 '#' 分隔成大小不同的区域，上下左右四个方向相邻的空地 '.' 属于同一个区域，只有空地上可能存在敌人'E”，请求出地图上总共有多少区域里的敌人数小于 K。

**输入描述**：

第一行输入为 N, M, K；

- N 表示地图的行数，M 表示地图的列数， K 表示目标敌人数量
- N，M <= 100

之后为一个 NxM 大小的字符数组。

**输出描述**：

敌人数小于 K 的区域数量

**用例 1**：

输入：

```
3 5 2
..#EE
E.#E.
###..
```

输出：

```
1
```

说明：地图被墙壁分为两个区域，左边区域有 1 个敌人，右边区域有 3 个敌人，符合条件的区域数量是 1

难度：中等

标签：广度优先搜索，深度优先搜索、图、队列

```cpp
#include <bits/stdc++.h>

using namespace std;

void bfs(int start_x, int start_y, const vector<vector<char> >& grid,
         vector<vector<bool> >& visited, int& enemy_count) {
  int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 四个方向
  queue<pair<int, int> > q;
  q.push(make_pair(start_x, start_y)); // 使用 make_pair 创建 pair
  visited[start_x][start_y] = true;

  while (!q.empty()) {
    pair<int, int> current = q.front();
    q.pop();
    int cur_x = current.first;  // 获取 X 坐标
    int cur_y = current.second; // 获取 Y 坐标

    // 如果当前格子是敌人，增加敌人计数
    if (grid[cur_x][cur_y] == 'E') {
      enemy_count++;
    }

    for (auto& dir : directions) {
      int new_x = cur_x + dir[0];
      int new_y = cur_y + dir[1];

      // 检查边界和访问状态
      if (new_x >= 0 && new_x < grid.size() && new_y >= 0 && new_y < grid[0].
          size() &&
          grid[new_x][new_y] != '#' && !visited[new_x][new_y]) {
        visited[new_x][new_y] = true;
        q.push(make_pair(new_x, new_y)); // 加入队列
      }
    }
  }
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<vector<char> > grid(n, vector<char>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> grid[i][j];
    }
  }

  vector<vector<bool> > visited(n, vector<bool>(m, false));
  int valid_region_count = 0;

  // 遍历每个单元格，开始 BFS
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == '.' && !visited[i][j]) {
        int enemy_count = 0;
        bfs(i, j, grid, visited, enemy_count);
        // 检查敌人数是否小于 K
        if (enemy_count < k) {
          valid_region_count++;
        }
      }
      // 加入单独处理 enemy
      if (grid[i][j] == 'E' && !visited[i][j]) {
        int enemy_count = 0;
        bfs(i, j, grid, visited, enemy_count);
        // 检查敌人数是否小于 K
        if (enemy_count < k) {
          valid_region_count++;
        }
      }

    }
  }

  cout << valid_region_count << endl;

  return 0;
}
```

#### 寻找最大价值的矿堆

**题目描述**：

给你一个由 '0' (空地)、'1' (银矿)、'2'(金矿) 组成的的地图，矿堆只能由上下左右相邻的金矿或银矿连接形成。超出地图范围可以认为是空地。

假设银矿价值 1，金矿价值 2 ，请你找出地图中最大价值的矿堆并输出该矿堆的价值。

**输入描述**：

地图元素信息如：

```none
解释22220
00000
00000
11111
```

- 地图范围最大 300\*300
- 0 ≤ 地图元素 ≤ 2

**输出描述**：

矿堆的最大价值

**用例 1**：

输入：

```
22220
00000
00000
01111
```

输出：

```
8
```

**用例 2**：

输入：

```
22220
00020
00010
01111
```

输出：

```
15
```

**用例 3**：

输入：

```
20000
00020
00000
00111
```

输出：

```
3
```

难度：中等

标签：广度优先搜索、深度优先搜索、图、并查集、矩阵代表是

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n = 0, m = 0;
  string line;
  vector<vector<int> > grid;

  // 读取输入行并构建地图
  while (getline(cin, line)) {
    vector<int> row;
    for (char ch : line) {
      row.push_back(ch - '0'); // 将字符转换为整数
    }
    grid.push_back(row);
  }

  n = grid.size();
  m = grid[0].size();
  vector<vector<bool> > visited(n, vector<bool>(m, false));
  int max_value = 0;

  // 定义四个方向
  int directions[4][2] = {
      {-1, 0}, // 上
      {1, 0},  // 下
      {0, -1}, // 左
      {0, 1}   // 右
  };

  // 遍历每个单元格
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!visited[i][j] && grid[i][j] > 0) {
        // 启动 BFS
        queue<pair<int, int> > q;
        q.emplace(i, j);
        visited[i][j] = true;

        int total_value = 0; // 当前矿堆的总价值

        while (!q.empty()) {
          pair<int, int> current = q.front();
          q.pop();
          int x = current.first;  // 获取 x 坐标
          int y = current.second; // 获取 y 坐标

          // 加上当前矿的价值
          total_value += grid[x][y];

          for (auto& dir : directions) {
            int new_x = x + dir[0], new_y = y + dir[1];

            // 检查边界和访问状态
            if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m &&
                !visited[new_x][new_y] && grid[new_x][new_y] > 0) {
              visited[new_x][new_y] = true;
              q.emplace(new_x, new_y); // 加入队列
            }
          }
        }

        // 更新最大矿堆的价值
        max_value = max(max_value, total_value);
      }
    }
  }

  cout << max_value << endl; // 输出最大矿堆的价值
  return 0;
}
```

#### 数值同化

**题目描述**：

存在一个 m\*n 的二维数组，其成员取值范围为 0，1，2。

其中值为 1 的元素具备同化特性，每经过 1S，将上下左右值为 0 的元素同化为 1。

而值为 2 的元素，免疫同化。

将数组所有成员随机初始化为 0 或 2，再将矩阵的 [0, 0] 元素修改成 1，在经过足够长的时间后求矩阵中有多少个元素是 0 或 2（即 0 和 2 数量之和）。

**输入描述**：

输入的前两个数字是矩阵大小。后面是数字矩阵内容。

**输出描述**：

返回矩阵中非 1 的元素个数。

**用例 1**：

输入：

```
4 4
0 0 0 0
0 2 2 2
0 2 0 0
0 2 0 0
```

输出：

```
9
```

说明：

输入数字前两个数字是矩阵大小。后面的数字是矩阵内容。 起始位置(0,0)被修改为 1 后，最终只能同化矩阵为：

1 1 1 1

1 2 2 2

1 2 0 0

1 2 0 0

所以矩阵中非 1 的元素个数为 9

难度：中等

标签：广度优先搜索、深度优先搜索、图、矩阵

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
  int m, n;
  cin >> m >> n;

  vector<vector<int> > matrix(m, vector<int>(n));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> matrix[i][j];
    }
  }

  // 将 (0, 0) 的值设为 1
  if (matrix[0][0] == 0) {
    matrix[0][0] = 1;
  }

  // 定义方向数组
  vector<pair<int, int> > directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  queue<pair<int, int> > bfs_queue; // BFS队列
  bfs_queue.emplace(0, 0);           // 初始位置

  int count = 0; // 记录值为1的元素个数

  // BFS遍历
  while (!bfs_queue.empty()) {
    pair<int, int> current = bfs_queue.front();
    bfs_queue.pop();

    int x = current.first;
    int y = current.second;

    // 当前元素被值为1记录
    count++;

    // 遍历四个方向
    for (const auto& dir : directions) {
      int new_x = x + dir.first;
      int new_y = y + dir.second;

      // 检查边界和同化条件
      if (new_x >= 0 && new_x < m && new_y >= 0 && new_y < n && matrix[new_x][new_y]
          == 0) {
        matrix[new_x][new_y] = 1;      // 同化
        bfs_queue.emplace(new_x, new_y); // 将新的位置加入队列
      }
    }
  }

  // 最终输出矩阵中值为0或2的元素个数
  int total_elements = m * n;               // 总元素个数
  int non_one_count = total_elements - count; // 非1元素的个数

  cout << non_one_count << endl; // 输出结果
  return 0;
}
```

## 单双指针

### 100 分

#### 最长连续子序列

**题目描述**：

有 N 个正整数组成的一个序列。给定整数 sum，求长度最长的连续子序列，使他们的和等于 sum，返回此子序列的长度，

如果没有满足要求的序列，返回-1。

**输入描述**：

第一行输入是：N 个正整数组成的一个序列

第二行输入是：给定整数 sum

**输出描述**：

最长的连续子序列的长度

- 输入序列仅由数字和英文逗号构成，数字之间采用英文逗号分隔
- 序列长度：1 <= N <= 200
- 输入序列不考虑异常情况

**用例 1**：

输入：

```
1,2,3,4,2
6
```

输出：

```
3
```

说明：1,2,3 和 4,2 两个序列均能满足要求，所以最长的连续序列为 1,2,3，因此结果为 3。

**用例 2**：

输入：

```
1,2,3,4,2
20
```

输出：

```
-1
```

说明：没有满足要求的子序列，返回-1

难度：中等

标签：滑动窗口、前缀和、哈希表、数组

```cpp
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
  // 读取输入
  string input;
  getline(cin, input);
  int sum;
  cin >> sum;

  // 解析输入序列
  vector<int> nums;
  stringstream ss(input);
  string token;

  while (getline(ss, token, ',')) {
    nums.push_back(stoi(token)); // 将字符串转换为整数并添加到向量中
  }

  int n = nums.size();
  int longest_length = -1; // 记录最长子序列的长度

  // 使用双指针法查找最长连续子序列
  for (int start = 0; start < n; start++) {
    int current_sum = 0; // 当前窗口的和
    for (int end = start; end < n; end++) {
      current_sum += nums[end]; // 扩展窗口

      if (current_sum == sum) {
        // 更新最长长度
        longest_length = max(longest_length, end - start + 1);
      }
    }
  }

  cout << longest_length << endl; // 输出结果
  return 0;
}
```

#### 分割数组的最大差值

**题目描述**：

给定一个由若干整数组成的数组 nums ，可以在数组内的任意位置进行分割，将该数组分割成两个非空子数组（即左数组和右数组），分别对子数组求和得到两个值，计算这两个值的差值，请输出所有分割方案中，差值最大的值。

**输入描述**：

第一行输入数组中元素个数 n，1 < n ≤ 100000 第二行输入数字序列，以空格进行分隔，数字取值为 4 字节整数

**输出描述**：

输出差值的最大取值

**用例 1**：

输入：

```
6
1 -2 3 4 -9 7
```

输出：

```
10
```

说明：

将数组 nums 划分为两个非空数组的可行方案有:

左数组 = [1] 且 右数组 = [-2,3,4,-9,7]，和的差值 = | 1 - 3 | = 2

左数组 = [1,-2] 且 右数组 = [3,4,-9,7]，和的差值 = | -1 - 5 | = 6

左数组 = [1,-2,3] 且 右数组 = [4,-9,7]，和的差值 = | 2 - 2 | = 0

左数组 = [1,-2,3,4] 且右数组 = [-9,7]，和的差值 = | 6 - (-2) | = 8，

左数组 = [1,-2,3,4,-9] 且 右数组 = [7]，和的差值 = | -3 - 7| = 10 最大的差值为 10

难度：中等

标签：数学、数组、前缀和

```cpp
#include <iostream>
#include <vector>
#include <cstdlib> // for abs

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<long long> nums(n); // 使用 long long 来避免溢出
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  long long total_sum = 0;
  for (long long num : nums) {
    total_sum += num; // 计算整个数组的和
  }

  long long left_sum = 0;
  long long max_diff = 0;

  // 遍历数组，找到最大差值
  for (int i = 0; i < n - 1; i++) {
    // 注意分割点只到 n-1，保证左右非空
    left_sum += nums[i];
    long long right_sum = total_sum - left_sum; // 右部分的和
    max_diff = max(max_diff, abs(left_sum - right_sum));
  }

  cout << max_diff << endl; // 输出结果
  return 0;
}
```

#### 最大花费金额

**题目描述**：

双十一众多商品进行打折销售，小明想购买自己心仪的一些物品，但由于受购买资金限制，所以他决定从众多心仪商品中购买三件，而且想尽可能的花完资金。

现在请你设计一个程序帮助小明计算尽可能花费的最大资金数额。

**输入描述**：

- 输入第一行为一维整型数组 M，数组长度小于 100，数组元素记录单个商品的价格，单个商品价格小于 1000。
- 输入第二行为购买资金的额度 R，R 小于 100000。
- 输入格式是正确的，无需考虑格式错误的情况。

**输出描述**：

- 输出为满足上述条件的最大花费额度。
- 如果不存在满足上述条件的商品，请返回 -1。

**用例 1**：

输入：

```
23,26,36,27
78
```

输出：

```
76
```

说明：金额 23、26 和 27 相加得到 76，而且最接近且小于输入金额 78。

**用例 2**：

输入：

```
23,30,40
26
```

输出：

```
-1
```

说明：因为输入的商品，无法组合出来满足三件之和小于 26.故返回 -1。

难度：中等

标签：双指针、排序

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input); // 读取价格数组

  // 解析输入的价格数组
  vector<int> prices;
  stringstream ss(input);
  string token;

  while (getline(ss, token, ',')) {
    prices.push_back(stoi(token)); // 将字符串转换为整数
  }

  int budget;
  cin >> budget; // 读取预算

  int n = prices.size();
  sort(prices.begin(), prices.end()); // 对数组进行升序排序

  int max_expense = -1; // 初始化最大花费金额为-1，表示未找到

  // 遍历所有可能的 I 指针
  for (int i = 0; i < n - 2; i++) {
    // I 的上限是 n-2，避免越界
    int l = i + 1; // L 指向 I 后一个元素
    int r = n - 1; // R 指向最后一个元素

    while (l < r) {
      // 当 L < R 时，继续尝试组合
      int sum = prices[i] + prices[l] + prices[r];

      if (sum == budget) {
        // 如果找到了恰好等于预算的组合
        cout << sum << endl;
        return 0;
      }

      if (sum < budget) {
        // 记录当前组合并尝试更大的组合
        max_expense = max(max_expense, sum);
        l++; // 增大当前和
      } else {
        r--; // 减小当前和
      }
    }
  }

  cout << max_expense << endl; // 输出结果
  return 0;
}
```

#### 求最多可以派出多少支团队

**题目描述**：

用数组代表每个人的能力，一个比赛活动要求参赛团队的最低能力值为 N，每个团队可以由 1 人或者 2 人组成，且 1 个人只能参加 1 个团队，计算出最多可以派出多少只符合要求的团队。

**输入描述**：

- 第一行代表总人数，范围 1-500000
- 第二行数组代表每个人的能力
  - 数组大小，范围 1-500000
  - 元素取值，范围 1-500000
- 第三行数值为团队要求的最低能力值，范围 1-500000

**输出描述**：

最多可以派出的团队数量

**用例 1**：

输入：

```
5
3 1 5 7 9
8
```

输出：

```
3
```

说明：说明 3、5 组成一队 1、7 一队 9 自己一队 输出 3

**用例 2**：

输入：

```
7
3 1 5 7 9 2 6
8
```

输出：

```
4
```

说明：3、5 组成一队，1、7 一队，9 自己一队，2、6 一队，输出 4

**用例 3**：

输入：

```
3
1 1 9
8
```

输出：

```
1
```

说明：9 自己一队，输出 1

难度：中等

标签：双指针、排序、贪心、数组

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n;
  cin >> n; // 总人数

  vector<int> abilities(n);
  for (int i = 0; i < n; i++) {
    cin >> abilities[i]; // 读取每个人的能力
  }

  int min_cap;
  cin >> min_cap; // 团队要求的最低能力值

  vector<int> remaining; // 用于存储不符合单人要求的人
  int team_count = 0;    // 记录可以组建的团队数量

  // 筛选出能力值至少为 minCap 的人
  for (int i = 0; i < n; i++) {
    if (abilities[i] >= min_cap) {
      team_count++; // 单独可成队
    } else {
      remaining.push_back(abilities[i]); // 将不符合的能力值放入 remaining
    }
  }

  // 对剩余人员进行排序
  sort(remaining.begin(), remaining.end());

  // 双指针方法对剩余人员进行组队
  int k = remaining.size(); // 剩余人员数量
  int l = 0, r = k - 1;     // 初始化指针

  while (l < r) {
    if (remaining[l] + remaining[r] >= min_cap) {
      team_count++; // 能够组成一个团队
      l++;          // 移动低能力值指针
      r--;          // 移动高能力值指针
    } else {
      // 低能力值无法和高能力值组成团队，移动 L
      l++;
    }
  }

  cout << team_count << endl; // 输出可以派出的团队数量
  return 0;
}
```

#### 最长的顺子

**题目描述**：

斗地主起源于湖北十堰房县，据说是一位叫吴修全的年轻人根据当地流行的扑克玩法“跑得快”改编的，如今已风靡整个中国，并流行于互联网上。

牌型：单顺，又称顺子，最少 5 张牌，最多 12 张牌(3…A)不能有 2，也不能有大小王，不计花色。

例如： 3-4-5-6-7-8，7-8-9-10-J-Q，3-4-5-6-7-8-9-10-J-Q-K-A

可用的牌 3 < 4 < 5 < 6 < 7 < 8 < 9 < 10 < J < Q < K < A < 2 < B(小王)< C(大王)，每种牌除大小王外有四种花色

(共有 13×4+2 张牌)

输入：

- 手上有的牌
- 已经出过的牌(包括对手出的和自己出的牌)

输出：

- 对手可能构成的最长的顺子(如果有相同长度的顺子，输出牌面最大的那一个)，
- 如果无法构成顺子，则输出 NO-CHAIN。

**输入描述**：

输入的第一行为当前手中的牌

输入的第二行为已经出过的牌

**输出描述**：

最长的顺子

**用例 1**：

输入：

```
3-3-3-3-4-4-5-5-6-7-8-9-10-J-Q-K-A
4-5-6-7-8-8-8
```

输出：

```
9-10-J-Q-K-A
```

**用例 2**：

输入：

```
3-3-3-3-8-8-8-8
K-K-K-K
```

输出：

```
NO-CHAIN
```

说明：剩余的牌无法构成顺子

难度：中等

标签：数组、滑动窗口、哈希表、贪心

```cpp
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// 将牌面值映射为对应索引
int ConvertCardToIndex(const string& card) {
  if (card == "J")
    return 11;
  if (card == "Q")
    return 12;
  if (card == "K")
    return 13;
  if (card == "A")
    return 14;
  if (card == "2")
    return 16;
  if (card == "B")
    return 17;
  if (card == "C")
    return 18;
  return stoi(card); // 对于 3 到 10，直接转换为整数
}

// 将索引映射为牌面值字符串
string ConvertIndexToCard(int index) {
  switch (index) {
    case 11:
      return "J";
    case 12:
      return "Q";
    case 13:
      return "K";
    case 14:
      return "A";
    case 16:
      return "2";
    case 17:
      return "B";
    case 18:
      return "C";
    default:
      return to_string(index); // 3 到 10
  }
}

int main() {
  // 初始化牌面数量的数组，大小为 19
  vector<int> card_count(19, 0);

  // 设定初始的牌面分布（示例：4张3,4张4,4张5...）
  card_count = {0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4, 1, 1};

  string hand_input, played_input;
  cin >> hand_input;   // 输入玩家手中的牌
  cin >> played_input; // 输入已出过的牌

  // 处理手中的牌
  stringstream hand_stream(hand_input);
  string current_card;
  while (getline(hand_stream, current_card, '-')) {
    card_count[ConvertCardToIndex(current_card)]--;
  }

  // 处理已出过的牌
  stringstream played_stream(played_input);
  while (getline(played_stream, current_card, '-')) {
    card_count[ConvertCardToIndex(current_card)]--;
  }

  int max_length = 0; // 记录当前找到的最长顺子的长度
  int max_start = -1; // 记录当前找到的最长顺子的起始索引

  // 左右指针的初始位置
  int left = 3;
  int right = 3;

  // 声明查找顺子的边界
  while (right <= 15) {
    if (card_count[right] > 0) {
      // 如果有该牌
      right++; // 继续扩展右边界
    } else {
      // 否则，连续性被打断
      if (right - left >= max_length) {
        // 更新最长顺子的长度和起始索引
        max_length = right - left;
        max_start = left;
      }
      left = right + 1; // 移动左指针到右指针的下一个位置
      right = left;     // 同步右指针
    }
  }

  // 输出结果
  if (max_length < 5) {
    cout << "NO-CHAIN"; // 如果没有找到有效的顺子
  } else {
    cout << ConvertIndexToCard(max_start); // 输出最长顺子的开始牌面
    for (int i = 1; i < max_length; ++i) {
      cout << "-" << ConvertIndexToCard(max_start + i); // 输出后续牌面
    }
  }

  return 0;
}
```

## 滑动窗口

### 100 分

#### 增强的 strstr

**题目描述**：

C 语言有一个库函数： char _strstr(const char _ haystack, const char \*needle) ，实现在字符串 haystack 中查找第一次出现字符串 needle 的位置，如果未找到则返回 null。

现要求实现一个 strstr 的增强函数，可以使用带可选段的字符串来模糊查询，与 strstr 一样返回首次查找到的字符串位置。

可选段使用“[]”标识，表示该位置是可选段中任意一个字符即可满足匹配条件。比如“a [bc]”表示可以匹配“ab”或“ac”。

注意目标字符串中可选段可能出现多次。

**输入描述**：

与 strstr 函数一样，输入参数是两个字符串指针，分别是源字符串和目标字符串。

**输出描述**：

与 strstr 函数不同，返回的是源字符串中，匹配子字符串相对于源字符串地址的偏移（从 0 开始算），如果没有匹配返回-1。

补充说明：源字符串中必定不包含‘[]’；目标字符串中‘[]’必定成对出现，且不会出现嵌套。

输入的字符串长度在 [1,100] 之间。

**用例 1**：

输入：

```
abcd
b[cd]
```

输出：

```
1
```

说明：相当于是在源字符串中查找 bc 或者 bd，bc 子字符串相对于 abcd 的偏移是 1

难度：中等

标签：字符串、滑动窗口、贪心、动态规划

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string haystack, needle;

  // 读取输入的源字符串和目标字符串
  getline(cin, haystack);
  getline(cin, needle);

  vector<vector<char> > layers; // 用于存储目标字符串的层次
  vector<char> current_layer;   // 当前层次的字符集合

  // 解析目标字符串并构建层次
  for (size_t i = 0; i < needle.size(); i++) {
    if (needle[i] == '[') {
      current_layer.clear(); // 新层开始，清空当前层
      i++;                   // 跳过 '['
      while (i < needle.size() && needle[i] != ']') {
        current_layer.push_back(needle[i]); // 将可选字符添加到当前层
        i++;
      }
      layers.push_back(current_layer); // 将当前层添加到层次列表
    } else {
      // 如果是普通字符，单独作为一层
      layers.push_back(vector<char>{needle[i]});
    }
  }

  int layer_count = layers.size(); // 层的数量
  int layers_size = haystack.size();

  // Slidng窗口匹配
  for (int i = 0; i <= layers_size - layer_count; i++) {
    bool match = true; // 默认匹配标记为真

    for (int j = 0; j < layer_count; j++) {
      bool found = false; // 每层是否找到匹配字符
      for (char ch : layers[j]) {
        if (haystack[i + j] == ch) {
          found = true; // 找到匹配字符
          break;
        }
      }
      if (!found) {
        match = false; // 如果一层没有找到匹配，标记为不匹配
        break;
      }
    }

    if (match) {
      cout << i << endl; // 匹配成功，输出起始位置
      return 0;          // 结束程序
    }
  }

  cout << -1 << endl; // 如果没有找到匹配，输出 -1
  return 0;
}
```

#### 高矮个子排队

**题目描述**：

现在有一队小朋友，他们高矮不同，我们以正整数数组表示这一队小朋友的身高，如数组{5,3,1,2,3}。

我们现在希望小朋友排队，以“高”“矮”“高”“矮”顺序排列，每一个“高”位置的小朋友要比相邻的位置高或者相等；每一个“矮”位置的小朋友要比相邻的位置矮或者相等；

要求小朋友们移动的距离和最小，第一个从“高”位开始排，输出最小移动距离即可。

例如，在示范小队{5,3,1,2,3}中，{5, 1, 3, 2, 3}是排序结果。

{5, 2, 3, 1, 3} 虽然也满足“高”“矮”“高”“矮”顺序排列，但小朋友们的移动距离大，所以不是最优结果。

移动距离的定义如下所示：

第二位小朋友移到第三位小朋友后面，移动距离为 1，若移动到第四位小朋友后面，移动距离为 2；

**输入描述**：

排序前的小朋友，以英文空格的正整数：

4 3 5 7 8

注：小朋友 < 100 个

**输出描述**：

排序后的小朋友，以英文空格分割的正整数：4 3 7 5 8

备注：4（高）3（矮）7（高）5（矮）8（高）， 输出结果为最小移动距离，只有 5 和 7 交换了位置，移动距离都是 1。

**用例 1**：

输入：

```
4 1 3 5 2
```

输出：

```
4 1 5 2 3
```

说明：

**用例 2**：

输入：

```
1 1 1 1 1
```

输出：

```
1 1 1 1 1
```

说明：相邻位置可以相等

**用例 3**：

输入：

```
xxx
```

输出：

```
[ ]
```

说明：出现非法参数情况， 返回空数组。

难度：中等

标签：数组、贪心、排序、双指针

```cpp
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
  string input;
  getline(cin, input); // 读取输入

  // 将输入字符串转换为整型数组
  vector<int> heights;
  stringstream ss(input);
  int height;

  while (ss >> height) {
    heights.push_back(height);
  }

  // 检查输入是否合法
  if (heights.empty()) {
    cout << "[ ]" << endl;
    return 0;
  }

  int n = heights.size();

  // 按照高矮排列方法
  for (int i = 0; i < n - 1; i++) {
    // 偶数位置：应该是高位置，满足 arr[i] >= arr[i + 1]
    if (i % 2 == 0) {
      if (heights[i] < heights[i + 1]) {
        // 交换 heights[i] 和 heights[i + 1]
        swap(heights[i], heights[i + 1]);
      }
    }
    // 奇数位置：应该是矮位置，满足 arr[i] <= arr[i + 1]
    else {
      if (heights[i] > heights[i + 1]) {
        // 交换 heights[i] 和 heights[i + 1]
        swap(heights[i], heights[i + 1]);
      }
    }
  }

  // 输出结果
  for (int i = 0; i < heights.size(); i++) {
    cout << heights[i];
    if (i < heights.size() - 1) {
      cout << " "; // 打印空格分隔
    }
  }
  cout << endl;

  return 0;
}
```

#### 补种未成活胡杨

**题目描述**：

近些年来，我国防沙治沙取得显著成果。某沙漠新种植 N 棵胡杨（编号 1-N），排成一排。

一个月后，有 M 棵胡杨未能成活。

现可补种胡杨 K 棵，请问如何补种（只能补种，不能新种），可以得到最多的连续胡杨树？

**输入描述**：

N 总种植数量，1 <= N <= 100000

M 未成活胡杨数量，M 个空格分隔的数，按编号从小到大排列，1 <= M <= N

K 最多可以补种的数量，0 <= K <= M

**输出描述**：

最多的连续胡杨棵树

**用例 1**：

输入：

```
5
2
2 4
1
```

输出：

```
3
```

说明：补种到 2 或 4 结果一样，最多的连续胡杨棵树都是 3。

**用例 2**：

输入：

```
10
3
2 4 7
1
```

输出：

```
6
```

说明：补种第 7 棵树，最多连续胡杨树棵数位 6（5，6，7，8，9，10）

难度：中等

标签：数组、双指针、贪心、前缀和

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n, m; // n: 总棵树, m: 死树棵数
  cin >> n >> m;

  vector<int> dead(m); // 保存未成活的树编号
  for (int i = 0; i < m; i++) {
    cin >> dead[i];
  }

  int k; // 可补种的树棵数
  cin >> k;

  // 如果未成活树的数量等于可补种的树数量，返回总树的数量
  if (m == k) {
    cout << n << endl;
    return 0;
  }

  int max_length = 0; // 存储最大连续树的长度

  // 遍历所有可能的补种起始位置
  for (int i = 0; i <= m - k; i++) {
    // 计算左边界
    int left_boundary = (i == 0) ? 1 : dead[i - 1] + 1; // 第一个补种时左边界是1
    // 计算右边界
    int right_boundary = (i + k < m) ? dead[i + k] - 1 : n; // 右边界考虑补种是否超出范围

    // 计算当前段落的长度
    int current_length = right_boundary - left_boundary + 1;
    max_length = max(max_length, current_length); // 更新最大长度
  }

  // 输出结果
  cout << max_length << endl;

  return 0;
}
```

#### 最左侧冗余覆盖子串

**题目描述**：

给定两个字符串 s1 和 s2 和正整数 k，其中 s1 长度为 n1，s2 长度为 n2。

在 s2 中选一个子串，若满足下面条件，则称 s2 以长度 k 冗余覆盖 s1

- 该子串长度为 n1 + k
- 该子串中包含 s1 中全部字母
- 该子串每个字母出现次数不小于 s1 中对应的字母

给定 s1，s2，k，求最左侧的 s2 以长度 k 冗余覆盖 s1 的子串的首个元素的下标，如果没有返回-1。

举例：

> s1 = "ab"
>
> s2 = "aabcd"
>
> k = 1

则子串 “aab” 和 "abc" 均满足此条件，由于 "aab" 在 "abc" 的左侧，"aab" 的第一个元素下部为 0，因此输出 0

**输入描述**：

输入三行，第一行为 s1，第二行为 s2，第三行为 k

- s1 和 s2 只包含小写字母

**输出描述**：

最左侧的 s2 以长度 k 冗余覆盖 s1 的子串首个元素下标，如果没有返回 -1。

- 0 ≤ len(s1) ≤ 1000000
- 0 ≤ len(s2) ≤ 20000000
- 0 ≤ k ≤ 1000

**用例 1**：

输入：

```
ab
aabcd
1
```

输出：

```
0
```

说明：子串 aab 和 abc 符合要求，由于 aab 在 abc 的左侧，因此输出 aab 的下标：0

**用例 2**：

输入：

```
abc
dfs
10
```

输出：

```
-1
```

说明：s2 无法覆盖 s1，输出 -1

难度：中等

标签：滑动窗口、哈希表、双指针

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string s1, s2;
  int k;

  // 读取输入数据
  cin >> s1 >> s2 >> k;

  int n1 = s1.size(), n2 = s2.size();
  if (n1 + k > n2) return cout << -1 << endl, 0; // 如果 s2 的长度不足

  // 统计 s1 中每个字符的频率
  vector<int> char_count(26, 0);
  for (char c : s1) {
    char_count[c - 'a']++;
  }

  // 所需匹配的字符数量
  int required_chars = n1;
  int left = 0, right = 0;

  // 统计当前窗口的字符频率
  vector<int> window_count(26, 0);

  // 初始化窗口
  while (right < n1 + k && right < n2) {
    char c = s2[right++];
    window_count[c - 'a']++;
    if (char_count[c - 'a'] > 0 && window_count[c - 'a'] <= char_count[c - 'a']) {
      required_chars--;
    }
  }

  // 检查初始窗口是否满足条件
  if (required_chars == 0) {
    cout << 0 << endl; // 返回起始索引0
    return 0;
  }

  // 开始滑动窗口
  while (right < n2) {
    // 移除左侧字符
    char remove_char = s2[left++];
    if (char_count[remove_char - 'a'] > 0) {
      if (window_count[remove_char - 'a'] <= char_count[remove_char - 'a']) {
        required_chars++;
      }
      window_count[remove_char - 'a']--;
    }

    // 添加右侧新字符
    char add_char = s2[right++];
    window_count[add_char - 'a']++;
    if (char_count[add_char - 'a'] > 0 && window_count[add_char - 'a'] <= char_count[add_char - 'a']) {
      required_chars--;
    }

    // 检查当前窗口
    if (required_chars == 0) {
      cout << left << endl; // 返回窗口的起始索引
      return 0;
    }
  }

  cout << -1 << endl; // 如果没有找到合适的子串，返回-1
  return 0;
}
```

#### 恢复数字序列

**题目描述**：

对于一个连续正整数组成的序列，可以将其拼接成一个字符串，再将字符串里的部分字符打乱顺序。如序列 8 9 10 11 12，拼接成的字符串为 89101112，打乱一部分字符后得到 90811211，原来的正整数 10 就被拆成了 0 和 1。

现给定一个按如上规则得到的打乱字符的字符串，请将其还原成连续正整数序列，并输出序列中最小的数字。

**输入描述**：

输入一行，为打乱字符的字符串和正整数序列的长度，两者间用空格分隔，字符串长度不超过 200，正整数不超过 1000，保证输入可以还原成唯一序列。

**输出描述**：

输出一个数字，为序列中最小的数字。

**用例 1**：

输入：

```
19801211 5
```

输出：

```
8
```

难度：中等

标签：字符串、滑动窗口、哈希表、双指针

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string scrambled;
  int sequence_length;

  // 读取打乱字符串和序列长度
  cin >> scrambled >> sequence_length;

  // 统计打乱字符串中的字符频率
  unordered_map<char, int> scrambled_count;
  for (char c : scrambled) {
    scrambled_count[c]++;
  }

  // 遍历可能的连续正整数序列
  for (int start = 1; start <= 100000; start++) {
    // 当前窗口对应的数字序列
    string generated;
    for (int i = 0; i < sequence_length; i++) {
      generated += to_string(start + i);
    }

    // 统计当前生成字符串的字符频率
    unordered_map<char, int> generatedCount;
    for (char c : generated) {
      generatedCount[c]++;
    }

    // 比较当前生成窗口的字符频率是否和打乱字符串的字符频率一致
    if (scrambled_count == generatedCount) {
      cout << start << endl; // 输出最小的起始数字
      return 0;              // 找到后结束程序
    }
  }

  cout << -1 << endl; // 如果没有找到有效序列，输出 -1
  return 0;
}
```

#### 关联子串

**题目描述**：

给定两个字符串 str1 和 str2，如果字符串 str1 中的字符，经过排列组合后的字符串中，只要有一个字符串是 str2 的子串，则认为 str1 是 str2 的关联子串。

若 str1 是 str2 的关联子串，请返回子串在 str2 的起始位置；

若不是关联子串，则返回-1。

**输入描述**：

输入两个字符串，分别为题目中描述的 str1、str2。

**输出描述**：

若 str1 是 str2 的关联子串，请返回子串在 str2 的起始位置；

若不是关联子串，则返回-1。

若 str2 中有多个 str1 的组合子串，请返回最小的起始位置。

输入的字符串只包含小写字母；

两个字符串的长度范围 [1, 100000] 之间；

**用例 1**：

输入：

```
abc efghicbaiii
```

输出：

```
5
```

说明：str2 包含 str1 的一种排列组合（"cab")，此组合在 str2 的字符串起始位置为 5（从 0 开始计数）

**用例 2**：

输入：

```
abc efghiccaiii
```

输出：

```
-1
```

说明：“abc”字符串中三个字母的各种组合（abc、acb、bac、bca、cab、cba），str2 中均不包含，因此返回-1

难度：中等

标签：字符串、滑动窗口、哈希表

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
  string str1, str2;

  // 读取输入的两个字符串
  cin >> str1 >> str2;

  int len1 = str1.size(), len2 = str2.size();

  if (len1 > len2) {
    cout << -1 << endl; // 如果 str1 比 str2 长，直接返回 -1
    return 0;
  }

  // 频率统计
  vector<int> count1(26, 0), count2(26, 0);

  // 统计 str1 字符频率
  for (char c : str1) {
    count1[c - 'a']++;
  }

  // 初始化滑动窗口的字符频率
  for (int i = 0; i < len1; i++) {
    count2[str2[i] - 'a']++;
  }

  // 检查第一个滑动窗口
  if (count1 == count2) {
    cout << 0 << endl; // 如果第一个窗口匹配，返回 0
    return 0;
  }

  // 移动窗口
  for (int i = len1; i < len2; i++) {
    // 新增字符
    count2[str2[i] - 'a']++;
    // 移除旧字符
    count2[str2[i - len1] - 'a']--;

    // 检查窗口数据是否匹配
    if (count1 == count2) {
      cout << i - len1 + 1 << endl; // 返回匹配的起始位置
      return 0;
    }
  }

  cout << -1 << endl; // 如果没有找到匹配，输出 -1
  return 0;
}
```

#### 根据某条件聚类最少交换次数

**题目描述**：

给出数字 K, 请输出所有结果小于 K 的整数组合到一起的最少交换次数。

组合一起是指满足条件的数字相邻，不要求相邻后在数组中的位置。

数据范围：

-100 <= K <= 100

-100 <= 数组中数值 <= 100

**输入描述**：

第一行输入数组：1 3 1 4 0

第二行输入 K 数值：2

**输出描述**：

第一行输出最少交换次数：1

**用例 1**：

输入：

```
1 3 1 4 0
2
```

输出：

```
1
```

说明：小于 2 的表达式是 1 1 0, 共三种可能将所有符合要求数字组合一起，最少交换 1 次。

难度：中等

标签：数组、滑动窗口、双指针

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // 读取数组
  vector<int> nums;
  int num;
  while (cin >> num) {
    nums.push_back(num);
    if (cin.get() == '\n')
      break;
  }

  // 读取 K 值
  int k;
  cin >> k;

  // 统计小于 K 的数字个数
  int small_count = 0;
  for (int x : nums) {
    if (x < k) {
      small_count++;
    }
  }

  // 如果没有小于 K 的数字，返回 0
  if (small_count == 0) {
    cout << 0 << endl;
    return 0;
  }

  // 使用滑动窗口计算最少交换次数
  int window_small_count = 0;
  for (int i = 0; i < small_count; i++) {
    if (nums[i] < k) {
      window_small_count++;
    }
  }

  int max_window_small_count = window_small_count;

  // 滑动窗口
  for (int i = small_count; i < nums.size(); i++) {
    if (nums[i - small_count] < k) {
      window_small_count--;
    }
    if (nums[i] < k) {
      window_small_count++;
    }
    max_window_small_count = max(max_window_small_count, window_small_count);
  }

  // 最少交换次数 = 窗口大小 - 窗口内小于K的数字个数
  int min_swaps = small_count - max_window_small_count;

  cout << min_swaps << endl;

  return 0;
}
```

#### 数组连续和

**题目描述**：

给定一个含有 N 个正整数的数组, 求出有多少个连续区间（包括单个正整数）, 它们的和大于等于 x。

**输入描述**：

第一行两个整数 N x（0 < N <= 100000, 0 <= x <= 10000000)

第二行有 N 个正整数（每个正整数小于等于 100)。

**输出描述**：

输出一个整数，表示所求的个数。

注意：此题对效率有要求，暴力解法通过率不高，请考虑高效的实现方式。

**用例 1**：

输入：

```
3 7
3 4 7
```

输出：

```
4
```

说明：第一行的 3 表示第二行数组输入 3 个数，第一行的 7 是比较数，用于判断连续数组是否大于该数；组合为 3 + 4; 3 + 4 + 7; 4 + 7; 7; 都大于等于指定的 7；所以共四组。

**用例 2**：

输入：

```
10 10000
1 2 3 4 5 6 7 8 9 10
```

输出：

```
0
```

说明：所有元素的和小于 10000，所以返回 0。

难度：中等

标签：前缀和、双指针、滑动窗口、数组

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n, x;
  cin >> n >> x;

  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  long long count = 0;       // 用于记录符合条件的子数组数量
  int start = 0;             // 窗口的起始指针
  long long current_sum = 0; // 当前子数组和

  for (int end = 0; end < n; end++) {
    current_sum += nums[end]; // 增加当前元素到和中

    // 当且仅当 current_sum >= x 时，统计符合条件的子数组
    while (current_sum >= x && start <= end) {
      count += (n - end);         // 所有以 start 开头的有效子数组
      current_sum -= nums[start]; // 移动 start，缩小窗口
      start++;                    // 移动窗口的起始位置
    }
  }

  cout << count << endl; // 输出结果
  return 0;
}
```

#### 计算最接近的数

**题目描述**：

给定一个数组 X 和正整数 K，请找出使表达式：

> X [i] - X [i + 1] - ... - X [i + K - 1]

结果最接近于数组中位数的下标 i ，如果有多个 i 满足条件，请返回最大的 i.

其中，数组中位数：长度为 N 的数组，按照元素的值大小升序排列后，下标为 N/2 元素的值

1. 数组 X 的元素均为正整数
2. X 的长度 n 取值范围：2 ≤ n ≤ 1000
3. K 大于 0 目小于数组的大小
4. i 的取值范围: 0 ≤ i < 1000
5. 题目的排序数组 X [N] 的中位数是 X [N/2]

**用例 1**：

输入：

```
[50,50,2,3],2
```

输出：

```
1
```

说明：中位数为 50：[50,50,2,3] 升序排序后变成 [2,3,50,50]，中位数为下标 4/2 = 2 的元素 50

计算结果为 1：X [50,50,2,3] 根据题目计算 X [i] - ... - X [i + k - 1] 得出三个数 0 (X [0] - X [1] = 50 - 50) 、48 (X [1] - X [2] = 50 - 2) 和 -1 (X [2]-X [3] = 2 - 3) ，其中 48 最接近 50，因此返回下标 1。

难度：中等

标签：数组、排序、数学、贪心

```cpp
#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int solution(const vector<int>& x, int k) {
  // Step 1: Find the median
  vector<int> sorted_x = x; // Make a copy of X to sort
  sort(sorted_x.begin(), sorted_x.end());
  int n = sorted_x.size();

  int median = sorted_x[n / 2]; // Median for even length is at n/2

  // Step 2: Initialize variables to find the closest value
  int closest_index = -1;
  int closest_value = INT_MAX;

  // Step 3: Calculate each start index's value for the expression
  for (int i = 0; i <= n - k; i++) {
    int current_sum = x[i];

    for (int j = 1; j < k; j++) {
      // We start from 1 because we already took X[i]
      current_sum -= x[i + j];
    }

    // Calculate the distance from the median
    int current_distance = abs(current_sum - median);

    // Choose the suitable index as described
    if (current_distance < closest_value ||
        (current_distance == closest_value && i > closest_index)) {
      closest_value = current_distance;
      closest_index = i;
    }
  }

  return closest_index;
}

int main() {
  string s;
  cin >> s;

  // Input processing to read the vector and K
  int index = s.rfind(',');

  stringstream ss(s.substr(1, index - 1));
  string token;

  vector<int> x;
  while (getline(ss, token, ',')) {
    x.emplace_back(stoi(token));
  }

  int k = stoi(s.substr(index + 1));

  cout << solution(x, k);

  return 0;
}
```

#### 获得完美走位

**题目描述**：

在第一人称射击游戏中，玩家通过键盘的 A、S、D、W 四个按键控制游戏人物分别向左、向后、向右、向前进行移动，从而完成走位。

假设玩家每按动一次键盘，游戏任务会向某个方向移动一步，如果玩家在操作一定次数的键盘并且各个方向的步数相同时，此时游戏任务必定会回到原点，则称此次走位为完美走位。

现给定玩家的走位（例如：ASDA），请通过更换其中一段连续走位的方式使得原走位能够变成一个完美走位。其中待更换的连续走位可以是相同长度的任何走位。

请返回待更换的连续走位的最小可能长度。

如果原走位本身是一个完美走位，则返回 0。

**输入描述**：

输入为由键盘字母表示的走位 s，例如：ASDA

走位长度 1 ≤ s.length ≤ 100000

s.length 是 4 的倍数

s 中只含有'A', 'S', 'D', 'W' 四种字符

**输出描述**：

输出为待更换的连续走位的最小可能长度。

**用例 1**：

输入：

```
WASDAASD
```

输出：

```
1
```

说明：将第二个 A 替换为 W，即可得到完美走位

**用例 2**：

输入：

```
AAAA
```

输出：

```
3
```

说明：将其中三个连续的 A 替换为 WSD，即可得到完美走位

难度：中等

标签：字符串、滑动窗口、哈希表、贪心

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
  string s;
  cin >> s; // 读取输入

  unordered_map<char, int> count;
  // 统计每个字符的数量
  for (char c : s) {
    count[c]++;
  }

  // 计算每个字母应有的数量
  int n = s.length() / 4;          // 每种字符的目标数量
  unordered_map<char, int> excess; // 记录多余的字符

  // 计算每种字符有多少个超出目标数量
  for (char c : "WASD") {
    if (count[c] > n) {
      excess[c] = count[c] - n; // 记录超过目标数量的部分
    } else {
      excess[c] = 0; // 如果没有超出，设为0
    }
  }

  // 双指针寻找最小覆盖子串
  int min_length = numeric_limits<int>::max();
  int left = 0;
  int right = 0;
  unordered_map<char, int> current_count; // 当前窗口内的字符

  while (right < s.length()) {
    // 扩大右边界，加入当前字符
    current_count[s[right]]++;

    // 检查当前窗口是否有效
    while ([&]() {
      for (char c : "WASD") {
        if (current_count[c] < excess[c]) {
          return false; // 如果不足以弥补，就无效
        }
      }
      return true; // 当前窗口有效
    }()) {
      // 有效后计算长度并更新最小长度
      min_length = min(min_length, right - left + 1);
      // 收缩左边界，移除当前左边的字符
      current_count[s[left]]--;
      left++;
    }

    right++;
  }

  // 如果没有找到有效的覆盖子串，返回 -1，表示无法平衡
  cout << (min_length == numeric_limits<int>::max() ? -1 : min_length) << endl;
  return 0;
}
```

### 200 分

#### 寻找符合要求的最长子串

**题目描述**：

给定一个字符串 s，找出这样一个子串：

1. 该子串中任意一个字符最多出现 2 次
2. 该子串不包含指定某个字符

请你找出满足该条件的最长子串的长度

**输入描述**：

第一行为：要求不包含的指定字符，为单个字符，取值范围 [0-9a-zA-Z]

第二行为：字符串 s，每个字符范围 [0-9a-zA-Z]，长度范围 [1, 10000]

**输出描述**：

一个整数，满足条件的最长子串的长度；

如果不存在满足条件的子串，则返回 0

**用例 1**：

输入：

```
D
ABC132
```

输出：

```
6
```

**用例 2**：

输入：

```
D
ABACA123D
```

输出：

```
7
```

难度：中等

标签：字符串、滑动窗口、哈希表、双指针

```cpp
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
  char forbidden_char;
  string s;

  // 读取输入
  cin >> forbidden_char;
  cin >> s;

  unordered_map<char, int> char_count;
  int max_length = 0; // 记录满足条件的最长子串长度
  int start = 0;     // 滑动窗口的起始位置

  for (int end = 0; end < s.size(); end++) {
    char current_char = s[end];

    // 跳过限制字符
    if (current_char == forbidden_char) {
      start = end + 1;   // 移动窗口开始位置
      char_count.clear(); // 清空字符计数
      continue;
    }

    // 记录当前字符
    char_count[current_char]++;

    // 如果当前字符次数超过 2，则移动左指针
    while (char_count[current_char] > 2) {
      char_count[s[start]]--;
      start++;
    }

    // 更新最长子串长度
    max_length = max(max_length, end - start + 1);
  }

  cout << max_length << endl; // 输出结果
  return 0;
}

```

#### 最小矩阵宽度

**题目描述**：

给定一个矩阵，包含 N \* M 个整数，和一个包含 K 个整数的数组。

现在要求在这个矩阵中找一个宽度最小的子矩阵，要求子矩阵包含数组中所有的整数。

**输入描述**：

第一行输入两个正整数 N，M，表示矩阵大小。

接下来 N 行 M 列表示矩阵内容。

下一行包含一个正整数 K。

下一行包含 K 个整数，表示所需包含的数组，K 个整数可能存在重复数字。

所有输入数据小于 1000。

**输出描述**：

输出包含一个整数，表示满足要求子矩阵的最小宽度，若找不到，输出-1。

**用例 1**：

输入：

```
2 5
1 2 2 3 1
2 3 2 3 2
3
1 2 3
```

输出：

```
2
```

说明：矩阵第 0、3 列包含了 1，2，3，矩阵第 3，4 列包含了 1，2，3

**用例 2**：

输入：

```
2 5
1 2 2 3 1
1 3 2 3 4
3
1 1 4
```

输出：

```
5
```

说明：矩阵第 1、2、3、4、5 列包含了 1、1、4

难度：困难

标签：滑动窗口、矩阵、哈希表

```cpp

```

## 二分法、三分法

### 100 分

#### 内存资源分配

**题目描述**：

有一个简易内存池，内存按照大小粒度分类，每个粒度有若干个可用内存资源，用户会进行一系列内存申请，需要按需分配内存池中的资源返回申请结果成功失败列表。

分配规则如下：

- 分配的内存要大于等于内存的申请量，存在满足需求的内存就必须分配，优先分配粒度小的，但内存不能拆分使用；
- 需要按申请顺序分配，先申请的先分配。
- 有可用内存分配则申请结果为 true，没有可用则返回 false。

注意：不考虑内存释放

**输入描述**：

输入为两行字符串

第一行为内存池资源列表，包含内存粒度数据信息，粒度数据间用逗号分割

- 一个粒度信息内用冒号分割，冒号前为内存粒度大小，冒号后为数量
- 资源列表不大于 1024
- 每个粒度的数量不大于 4096

第二行为申请列表，申请的内存大小间用逗号分割

- 申请列表不大于 100000

如 64:2,128:1,32:4,1:128 50,36,64,128,127

**输出描述**：

输出为内存池分配结果

如 true, true, true, false, false

**用例 1**：

输入：

```
64:2,128:1,32:4,1:128
50,36,64,128,127
```

输出：

```
true,true,true,false,false
```

说明：

内存池资源包含：64K 共 2 个、128K 共 1 个、32K 共 4 个、1K 共 128 个的内存资源；

针对 50,36,64,128,127 的内存申请序列，分配的内存依次是：64,64,128, NULL, NULL,

第三次申请内存时已经将 128 分配出去，因此输出结果是：

true, true, true, false, false

难度：中等

标签：数组、哈希表、贪心、字符串

```cpp
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

int main() {
  string memory_pool_input, request_input;

  // 读取内存池和申请列表
  getline(cin, memory_pool_input);
  getline(cin, request_input);

  // 存储内存池资源
  map<int, int> memory_pool; // 粒度 -> 数量

  // 解析内存池字符串
  stringstream ss(memory_pool_input);
  string token;
  while (getline(ss, token, ',')) {
    size_t colon_pos = token.find(':');
    // 获取粒度大小和数量
    int size = stoi(token.substr(0, colon_pos));      // 粒度大小
    int quantity = stoi(token.substr(colon_pos + 1)); // 数量
    memory_pool[size] += quantity;                    // 将相同大小的内存合并
  }

  // 解析申请并处理
  vector<string> request_results; // 存储申请结果
  stringstream ss_requests(request_input);

  while (getline(ss_requests, token, ',')) {
    // 确保申请的格式有效，跳过空值
    if (token.empty()) {
      continue; // 忽略空申请
    }

    int request_size = stoi(token); // 当前申请的内存大小
    bool allocated = false;

    // 查找合适的内存资源
    for (auto it = memory_pool.lower_bound(request_size);
         it != memory_pool.end();
         ++it) {
      if (it->second > 0) {
        // 找到满足要求的粒度
        it->second--;     // 执行资源分配
        allocated = true; // 申请成功
        request_results.emplace_back("true");
        break; // 处理完当前申请，跳出循环
      }
    }

    // 如果没有可用资源
    if (!allocated) {
      request_results.emplace_back("false");
    }
  }

  // 输出结果
  for (size_t i = 0; i < request_results.size(); ++i) {
    cout << request_results[i];
    if (i < request_results.size() - 1) {
      cout << ","; // 输出逗号分隔
    }
  }
  cout << endl;

  return 0;
}
```

#### 爱吃蟠桃的孙悟空

**题目描述**：

孙悟空爱吃蟠桃，有一天趁着蟠桃园守卫不在来偷吃。已知蟠桃园有 N 棵桃树，每颗树上都有桃子，守卫将在 H 小时后回来。

孙悟空可以决定他吃蟠桃的速度 K（个/小时），每个小时选一颗桃树，并从树上吃掉 K 个，如果树上的桃子少于 K 个，则全部吃掉，并且这一小时剩余的时间里不再吃桃。

孙悟空喜欢慢慢吃，但又想在守卫回来前吃完桃子。

请返回孙悟空可以在 H 小时内吃掉所有桃子的最小速度 K（K 为整数）。如果以任何速度都吃不完所有桃子，则返回 0。

**输入描述**：

第一行输入为 N 个数字，N 表示桃树的数量，这 N 个数字表示每颗桃树上蟠桃的数量。

第二行输入为一个数字，表示守卫离开的时间 H。

其中数字通过空格分割，N、H 为正整数，每颗树上都有蟠桃，且 0 < N < 10000，0 < H < 10000。

**输出描述**：

吃掉所有蟠桃的最小速度 K，无解或输入异常时输出 0。

**用例 1**：

输入：

```
2 3 4 5
4
```

输出：

```
5
```

**用例 2**：

输入：

```
2 3 4 5
3
```

输出：

```
0
```

**用例 3**：

输入：

```
30 11 23 4 20
6
```

输出：

```
23
```

难度：中等

标签：二分查找、数组、贪心

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
  // 读取桃树数量和每棵树上的桃子数
  vector<int> piles;

  // 处理输入
  string line;
  getline(cin, line);

  // 分割字符串并转换为整数
  size_t pos = 0;
  while ((pos = line.find(' ')) != string::npos) {
    string token = line.substr(0, pos);
    piles.push_back(stoi(token));
    line.erase(0, pos + 1);
  }
  piles.push_back(stoi(line)); // 添加最后一个数

  int h;
  cin >> h;

  // 特殊情况处理：桃树数量大于可用时间
  if (piles.size() > h) {
    cout << 0 << endl;
    return 0;
  }

  // 二分查找的左右边界
  int left = 1;
  int right = *max_element(piles.begin(), piles.end());

  // 特殊情况处理：来不及吃完
  int total_hours = 0;
  for (int pile : piles) {
    total_hours += ceil((double)pile / right);
  }
  if (total_hours > h) {
    cout << 0 << endl;
    return 0;
  }

  // 二分查找最小速度
  int result = 0;
  while (left <= right) {
    int mid = left + (right - left) / 2;

    // 直接在这里实现原来 canEatAll 的逻辑
    int hours = 0;
    for (int pile : piles) {
      // 向上取整，计算吃完这堆桃子需要的时间
      hours += ceil((double)pile / mid);
    }

    // 判断是否在规定时间内吃完
    if (hours <= h) {
      // 如果当前速度可以吃完，尝试更小的速度
      result = mid;
      right = mid - 1;
    } else {
      // 当前速度不够，需要增加速度
      left = mid + 1;
    }
  }

  cout << result << endl;

  return 0;
}
```

### 200 分

#### 矩阵匹配

**题目描述**：

从一个 N \* M（N ≤ M）的矩阵中选出 N 个数，任意两个数字不能在同一行或同一列，求选出来的 N 个数中第 K 大的数字的最小值是多少。

**输入描述**：

输入矩阵要求：1 ≤ K ≤ N ≤ M ≤ 150

输入格式：

N M K

N\*M 矩阵

**输出描述**：

N\*M 的矩阵中可以选出 M! / N! 种组合数组，每个组合数组种第 K 大的数中的最小值。无需考虑重复数字，直接取字典排序结果即可。

注意：结果是第 K 大的数字的最小值

**用例 1**：

输入：

```
3 4 2
1 5 6 6
8 3 4 3
6 8 6 3
```

输出：

```
3
```

说明：

N\*M 的矩阵中可以选出 M！/ N！种组合数组，每个组合数组种第 K 大的数中的最小值；

上述输入中选出数组组合为：

1,3,6;

1,3,3;

1,4,8;

1,4,3;

......

上述输入样例中选出的组合数组有 24 种，最小数组为 1,3,3，则第 2 大的最小值为 3

难度：困难

标签：二分查找、图论、贪心

```cpp
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

// 深度优先搜索函数，用于寻找匹配
bool dfs(int row, int mid, const vector<vector<int> >& matrix,
         vector<int>& match, vector<bool>& visited) {
  for (int col = 0; col < matrix[0].size(); ++col) {
    // 如果该列没有被访问过，并且矩阵中对应元素的值小于等于 mid
    if (!visited[col] && matrix[row][col] <= mid) {
      visited[col] = true; // 标记该列已被访问
      // 如果该列没有匹配，或者可以重新匹配
      if (match[col] == -1 || dfs(match[col], mid, matrix, match, visited)) {
        match[col] = row; // 执行匹配
        return true;      // 匹配成功
      }
    }
  }
  return false; // 匹配失败
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<vector<int> > matrix(n, vector<int>(m));
  int max_val = INT_MIN;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> matrix[i][j];
      max_val = max(max_val, matrix[i][j]);
    }
  }

  int low = 1, high = max_val, result = -1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    vector<int> match(m, -1);       // 初始化匹配数组
    vector<bool> visited(m, false); // 初始化访问数组
    int count = 0;                  // 匹配成功的行数

    for (int i = 0; i < n; ++i) {
      fill(visited.begin(), visited.end(), false); // 清空访问标记
      if (dfs(i, mid, matrix, match, visited))
        count++; // 调用 dfs 进行匹配
    }

    // 根据匹配结果调整搜索范围
    if (count >= n - k + 1) {
      result = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  cout << result << endl;
  return 0;
}
```

#### 编码能力提升计划

**题目描述**：

为了提升软件编码能力，小王制定了刷题计划，他选了题库中的 n 道题，编号从 0 到 n-1，并计划在 m 天内按照题目编号顺序刷完所有的题目（注意，小王不能用多天完成同一题）。

在小王刷题计划中，小王需要用 tme [i] 的时间完成编号 i 的题目。

此外，小王还可以查看答案，可以省去该题的做题时间。为了真正达到刷题效果，小王每天最多直接看一次答案。

我们定义 m 天中做题时间最多的一天耗时为 T（直接看答案的题目不计入做题总时间)。

请你帮小王求出最小的 T 是多少。

**输入描述**：

第一行输入为 time，time [i] 的时间完成编号 i 的题目

第二行输入为 m，m 表示几天内完成所有题目，1 ≤ m ≤ 180

**输出描述**：

最小耗时整数 T

**用例 1**：

输入：

```
999,999,999
4
```

输出：

```
0
```

说明：在前三天中，小王每天都直接看答案，这样他可以在三天内完成所有的题目并不花任何时间

**用例 2**：

输入：

```
1,2,2,3,5,4,6,7,8
5
```

输出：

```
4
```

说明：第一天完成前 3 题，第 3 题看答案; 第二天完成第 4 题和第 5 题，第 5 题看答案； 第三天完成第 6 和第 7 题，第 7 提看答案; 第四天完成第 8 题，直接看答案: 第五天完成第 9 题，直接看答案

难度：困难

标签：二分查找、贪心、模拟、数组

```cpp
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// 检查是否可以在 m 天内完成所有题目
bool Finish(const vector<int>& times, int m, int t) {
  int sum_cost = 0;     // 当前总耗时
  int max_cost = 0;     // 当前耗时最多的题目
  int day = 1;          // 当前天数
  bool can_help = true; // 是否可以申请帮助

  for (int time : times) {
    sum_cost += time;
    max_cost = max(max_cost, time);

    if (sum_cost > t) {
      if (can_help) {
        // 申请帮助，减去当天最耗时的题目
        sum_cost -= max_cost;
        can_help = false; // 将申请帮助机会用完
      } else {
        // 不能申请帮助，进入新的一天
        day++;
        sum_cost = time; // 当前题目作为下一天的开始
        max_cost = time; // 清空并重置最大耗时
        can_help = true; // 重置帮助机会
      }
    }

    // 如果今天的时间超限，并且当前总耗时超过最大限制，进入新的一天
    if (sum_cost > t && !can_help) {
      day++;
      sum_cost = time; // 当前题目作为下一天的开始
      max_cost = time; // 清空并重置最大耗时
      can_help = true; // 重置帮助机会
    }
  }

  return day <= m; // 检查是否在规定天数内完成
}

int main() {
  vector<int> times;
  string input;
  getline(cin, input);

  // 解析输入
  stringstream ss(input);
  string num;
  int sum_time = 0, max_time = 0;

  while (getline(ss, num, ',')) {
    int time = stoi(num);
    times.push_back(time);
    sum_time += time;
    max_time = max(max_time, time);
  }

  int m;
  cin >> m;

  // T 的初始取值范围
  int low = 0;
  int high = sum_time - max_time;

  // 二分查找寻找最小的 T
  while (low < high) {
    int mid = (low + high) / 2;

    if (Finish(times, m, mid)) {
      high = mid; // 尝试更小的 T
    } else {
      low = mid + 1; // 尝试更大的 T
    }
  }

  cout << low << endl; // 输出结果
  return 0;
}
```

#### 最佳植树距离

**题目描述**：

按照环保公司要求，小明需要在沙化严重的地区进行植树防沙工作，初步目标是种植一条直线的树带。由于有些区域目前不适合种植树木，所以只能在一些可以种植的点来种植树木。

在树苗有限的情况下，要达到最佳效果，就要尽量散开种植，不同树苗之间的最小间距要尽量大。给你一个适合种情树木的点坐标和一个树苗的数量，请帮小明选择一个最佳的最小种植间距。

例如，适合种植树木的位置分别为 1,3,5,6,7,10,13 树苗数量是 3，种植位置在 1,7,13，树苗之间的间距都是 6，均匀分开，就达到了散开种植的目的，最佳的最小种植间距是 6

**输入描述**：

第 1 行表示：适合种树的坐标数量

第 2 行表示：适合种树的坐标位置

第 3 行表示：树苗的数量

位置范围为 1~10000000

种植树苗的数量范围 2~10000000

用例确保种桔的树苗数量不会超过有效种桔坐标数量

**输出描述**：

最佳的最小种植间距

**用例 1**：

输入：

```
7
1 5 3 6 10 7 13
3
```

输出：

```
6
```

说明：3 棵树苗分别种植在 1，7，13 位置时，树苗种植的最均匀，最小间距为 6

难度：中等

标签：二分查找、贪心、排序、数组

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 判断在给定的最小间距下，是否能够放置指定数量的树苗
bool CanPlace(const vector<int>& positions, int minDistance, int m) {
  int count = 1;                   // 放置的树苗数量
  int last_position = positions[0]; // 上一个放置树苗的位置

  for (int i = 1; i < positions.size(); i++) {
    // 如果当前坐标与最后放置的树苗的距离大于等于最小间距
    if (positions[i] - last_position >= minDistance) {
      count++;                     // 放置树苗
      last_position = positions[i]; // 更新最后放置的树苗位置
      if (count >= m)
        return true; // 如果满足树苗数量，返回 true
    }
  }
  return count >= m; // 计算最终放置的树苗数量是否满足
}

int main() {
  int n; // 坐标数量
  cin >> n;

  vector<int> positions(n);
  for (int i = 0; i < n; i++) {
    cin >> positions[i];
  }

  int m; // 树苗数量
  cin >> m;

  // 排序坐标位置
  sort(positions.begin(), positions.end());

  // 二分查找的范围
  int left = 0;                                     // 最小间距
  int right = positions.back() - positions.front(); // 最大间距

  // 使用二分查找找出最佳最小种植间距
  int best_min_distance = 0;
  while (left <= right) {
    int mid = (left + right) / 2; // 当前尝试的最小距离
    if (CanPlace(positions, mid, m)) {
      best_min_distance = mid; // 记录当前最小距离
      left = mid + 1;        // 尝试更大的间距
    } else {
      right = mid - 1; // 尝试更小的间距
    }
  }

  cout << best_min_distance << endl; // 输出最佳最小种植间距
  return 0;
}
```

#### 组装最大可靠性设备

**题目描述**：

一个设备由 N 种类型元器件组成（每种类型元器件只需要一个，类型 type 编号从 0~N-1），

每个元器件均有可靠性属性 reliability，可靠性越高的器件其价格 price 越贵。

而设备的可靠性由组成设备的所有器件中可靠性最低的器件决定。

给定预算 S，购买 N 种元器件（每种类型元器件都需要购买一个），在不超过预算的情况下，请给出能够组成的设备的最大可靠性。

**输入描述**：

S N // S 总的预算，N 元器件的种类

total // 元器件的总数，每种型号的元器件可以有多种;

此后有 total 行具体器件的数据

type reliability price // type 整数类型，代表元器件的类型编号从 0 ~ N-1; reliabilty 整数类型 ，代表元器件的可靠性; price 整数类型 ，代表元器件的价格

0 <= S, price <= 10000000
0 <= N <= 100
0 <= type <= N-1
0 <= total <= 100000
0 < reliability <= 100000

**输出描述**：

符合预算的设备的最大可靠性，如果预算无法买齐 N 种器件，则返回 -1

**用例 1**：

输入：

```
500 3
6
0 80 100
0 90 200
1 50 50
1 70 210
2 50 100
2 60 150
```

输出：

```
60
```

说明：

预算 500，设备需要 3 种元件组成，方案

类型 0 的第一个(可靠性 80),

类型 1 的第二个(可靠性 70),

类型 2 的第二个(可靠性 60),

可以使设备的可靠性最大 60

**用例 2**：

输入：

```
100 1
1
0 90 200
```

输出：

```
-1
```

说明：组成设备需要 1 个元件，但是元件价格大于预算，因此无法组成设备，返回-1

难度：困难

标签：二分查找、贪心、动态规划、排序

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Component {
  int reliability;
  int price;
};

bool CanAssemble(int minReliability,
                 const vector<vector<Component> >& components, int budget,
                 int N) {
  int total_price = 0;

  for (int type = 0; type < N; ++type) {
    int min_price = INT_MAX;
    bool found = false;

    // 寻找当前类型中可靠性 >= minReliability 的组件，并记录最小价格
    for (const auto& component : components[type]) {
      if (component.reliability >= minReliability) {
        found = true;
        min_price = min(min_price, component.price);
      }
    }

    if (!found)
      return false; // 如果没找到符合要求的组件

    total_price += min_price; // 统计购买所满足的最小价格

    if (total_price > budget)
      return false; // 超过预算
  }

  return total_price <= budget; // 返回是否在预算之内
}

int main() {
  int s, n; // S为预算，N为元件种类
  cin >> s >> n;

  int total; // 总部件数
  cin >> total;

  // 创建一个二维数组记录不同类型的组件
  vector<vector<Component> > components(n);

  for (int i = 0; i < total; ++i) {
    int type, reliability, price;
    cin >> type >> reliability >> price;
    components[type].push_back({reliability, price});
  }

  // 对每种类型的组件按可靠性从高到低排序
  for (int type = 0; type < n; ++type) {
    sort(components[type].begin(), components[type].end(),
         [](const Component& a, const Component& b) {
           return a.reliability > b.reliability; // 按可靠性降序排序
         });
  }

  // 二分查找可靠性
  int left = 1, right = 100000; // 根据可靠性的题目约束
  int best_reliability = -1;

  // 特殊情况处理: 当 N == 0 时不能构造设备
  if (n == 0) {
    cout << -1 << endl;
    return 0;
  }

  while (left <= right) {
    int mid = (left + right) / 2;

    if (CanAssemble(mid, components, s, n)) {
      best_reliability = mid; // 记录当前可以实现的最佳可靠性
      left = mid + 1;         // 尝试寻找更高的可靠性
    } else {
      right = mid - 1; // 减少可靠性
    }
  }

  // 如果无法满足设备的所有类型，则返回 -1
  if (best_reliability == -1) {
    cout << -1 << endl;
  } else {
    cout << best_reliability << endl; // 输出最大可靠性
  }

  return 0;
}
```

#### 部门人力分配

**题目描述**：

部门在进行需求开发时需要进行人力安排。

当前部门需要完成 N 个需求，需求用 requirements  表述，requirements [i] 表示第 i 个需求的工作量大小，单位：人月。

这部分需求需要在 M 个月内完成开发，进行人力安排后每个月人力时固定的。

目前要求每个月最多有 2 个需求开发，并且每个月需要完成的需求不能超过部门人力。

请帮助部门评估在满足需求开发进度的情况下，每个月需要的最小人力是多少？

**输入描述**：

输入为 M 和 requirements，M 表示需求开发时间要求，requirements 表示每个需求工作量大小，N 为 requirements 长度，

1 ≤ N/2 ≤ M ≤ N ≤ 10000

1 ≤ requirements [i] ≤ 10^9

**输出描述**：

对于每一组测试数据，输出部门需要人力需求，行末无多余的空格

**用例 1**：

输入：

```
3
3 5 3 4
```

输出：

```
6
```

说明：

输入数据两行，

第一行输入数据 3 表示开发时间要求，

第二行输入数据表示需求工作量大小，

输出数据一行，表示部门人力需求。

当选择人力为 6 时，2 个需求量为 3 的工作可以在 1 个月里完成，其他 2 个工作各需要 1 个月完成。可以在 3 个月内完成所有需求。

当选择人力为 5 时，4 个工作各需要 1 个月完成，一共需要 4 个月才能完成所有需求。

因此 6 是部门最小的人力需求。

难度：中等

标签：二分查找、双指针、贪心

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // std::accumulate

using namespace std;

// 检查在给定限重下需要多少辆自行车
bool CanCompleteRequirements(const vector<int>& requirements, int m,
                             long long limit) {
  int need = 0;
  int l = 0;
  int r = requirements.size() - 1;

  while (l <= r) {
    if (l == r) {
      need++;
      break;
    }
    if (requirements[l] + requirements[r] <= limit) {
      l++;
      r--;
    } else {
      r--;
    }
    need++; // 使用了一辆车
  }

  return need <= m; // 如果需要的车数小于等于 M，返回 true
}

int main() {
  int m;
  cin >> m; // 输入开发时间要求

  vector<int> requirements;
  int work;

  // 读取需求工作量
  while (cin >> work) {
    requirements.push_back(work);
  }

  // 排序需求工作量
  sort(requirements.begin(), requirements.end());

  // 二分查找初始化
  long long left = *max_element(requirements.begin(), requirements.end());
  long long right = accumulate(requirements.begin(), requirements.end(), 0LL);

  long long result = right; // 结果集

  // 二分查找
  while (left <= right) {
    long long mid = left + (right - left) / 2;

    if (CanCompleteRequirements(requirements, m, mid)) {
      result = mid;    // 找到可行解
      right = mid - 1; // 尝试更小的限重
    } else {
      left = mid + 1; // 增加限重
    }
  }

  cout << result << endl; // 输出部门人力需求
  return 0;
}
```

## 区间问题

### 100 分

#### 路灯照明问题

**题目描述**：

在一条笔直的公路上安装了 N 个路灯，从位置 0 开始安装，路灯之间间距固定为 100 米。 每个路灯都有自己的照明半径，请计算第一个路灯和最后一个路灯之间，无法照明的区间的长度和。

**输入描述**：

第一行为一个数 N，表示路灯个数，1 <= N <= 100000 第二行为 N 个空格分隔的数，表示路灯的照明半径，1 <= 照明半径 <= 100000\*100

**输出描述**：

第一个路灯和最后一个路灯之间，无法照明的区间的长度和

**用例 1**：

输入：

```
2
50 50
```

输出：

```
0
```

说明：路灯 1 覆盖 0-50，路灯 2 覆盖 50-100，路灯 1 和路灯 2 之间(0 米-100 米)无未覆盖的区间。

**用例 2**：

输入：

```
4
50 70 20 70
```

输出：

```
20
```

说明：

路灯 1 覆盖 0-50

路灯 2 覆盖 30-170

路灯 3 覆盖 180-220

路灯 4 覆盖 230-370

[170,180], [220,230]，两个未覆盖的区间，总里程为 20

难度：中等

标签：贪心、排序、双指针

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n;
  cin >> n; // 输入路灯数量

  vector<int> radius(n);
  for (int i = 0; i < n; ++i) {
    cin >> radius[i]; // 输入每个路灯的照明半径
  }

  // 计算每个路灯的照明范围
  vector<pair<int, int> > ranges;
  for (int i = 0; i < n; ++i) {
    int position = i * 100;
    int start = max(0, position - radius[i]);
    int end = position + radius[i];
    ranges.emplace_back(start, end);
  }

  // 按起点升序排序
  sort(ranges.begin(), ranges.end());

  // 合并重叠的照明范围
  vector<pair<int, int> > merged;
  merged.push_back(ranges[0]);

  for (int i = 1; i < ranges.size(); ++i) {
    pair<int, int> current = ranges[i];
    pair<int, int>& last = merged.back();

    if (current.first <= last.second) {
      // 当前区间与最后一个区间有重叠，合并区间
      last.second = max(last.second, current.second);
    } else {
      // 当前区间与最后一个区间无重叠，直接加入结果
      merged.push_back(current);
    }
  }

  // 计算未覆盖的区间长度和
  int uncovered = 0;
  for (int i = 1; i < merged.size(); ++i) {
    int gap = merged[i].first - merged[i - 1].second;
    if (gap > 0) {
      uncovered += gap;
    }
  }

  cout << uncovered << endl; // 输出未覆盖的区间长度和
  return 0;
}
```

### 200 分

#### 观看文艺汇演问题

**题目描述**：

为了庆祝中国共产党成立 100 周年，某公园将举行多场文艺表演，很多演出都是同时进行。

一个人只能同时观看一场演出，且不能迟到早退。

由于演出分布在不同的演出场地，所以连续观看的演出最少有 15 分钟的时间间隔。

小明是一个狂热的文艺迷，想观看尽可能多的演出。

现给出演出时间表，请帮小明计算他最多能观看几场演出。

**输入描述**：

第一行为一个数 N，表示演出场数

1 ≤ N ≤ 1000

接下来 N 行，每行有被空格分割的整数，第一个整数 T 表示演出的开始时间，第二个整数 L 表示演出的持续时间

T 和 L 的单位为分钟

0 ≤ T ≤ 1440

0 < L ≤ 180

**输出描述**：

输出最多能观看的演出场数。

**用例 1**：

输入：

```
2
720 120
840 120
```

输出：

```
1
```

说明：两场演出间隔时间为 0，不满足最小 15 分钟时间间隔的要求，所以最多只能观看一场演出

**用例 2**：

输入：

```
2
0 60
90 60
```

输出：

```
2
```

说明：两场演出间隔大于 15 分钟，都能观看到

难度：中等

标签：贪心、排序

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 存储演出信息的结构体
struct Performance {
  int start_time; // 演出开始时间
  int duration;   // 演出持续时间
  int end_time;   // 演出结束时间
};

int main() {
  int n;
  cin >> n; // 输入演出场数

  vector<Performance> performances(n);

  for (int i = 0; i < n; ++i) {
    int start, length;
    cin >> start >> length;
    performances[i] = {start, length, start + length};
  }

  // 按照结束时间进行排序，使用 Lambda 函数
  sort(performances.begin(), performances.end(),
       [](const Performance& a, const Performance& b) {
         return a.end_time < b.end_time;
       });

  int count = 0;           // 能观看的演出数量
  int last_end_time = -15; // 初始值设置为 -15，确保第一个演出可以观看

  for (const auto& performance : performances) {
    if (performance.start_time >= last_end_time + 15) {
      count++;                              // 可以观看该演出
      last_end_time = performance.end_time; // 更新上次演出结束时间
    }
  }

  cout << count << endl; // 输出最多能观看的演出场数
  return 0;
}
```

#### 最少数量线段覆盖

**题目描述**：

给定坐标轴上的一组线段，线段的起点和终点均为整数并且长度不小于 1，请你从中找到最少数量的线段，这些线段可以覆盖柱所有线段。

**输入描述**：

第一行输入为所有线段的数量，不超过 10000，后面每行表示一条线段，格式为 "x, y"，x 和 y 分别表示起点和终点，取值范围是 [-10^5，10^5]。

**输出描述**：

最少线段数量，为正整数

**用例 1**：

输入：

```
3
1,4
2,5
3,6
```

输出：

```
2
```

难度：中等

标签：贪心、排序、双指针、栈

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int main() {
  int n;
  cin >> n; // 输入线段数量

  vector<vector<int> > ranges(n, vector<int>(2));
  for (int i = 0; i < n; ++i) {
    char comma;
    cin >> ranges[i][0] >> comma >> ranges[i][1];
  }

  // 按照起点升序排序
  sort(ranges.begin(), ranges.end(),
       [](const vector<int>& a, const vector<int>& b) {
         return a[0] < b[0];
       });

  deque<vector<int> > stack;
  stack.push_back(ranges[0]); // 将第一个区间压入栈

  for (int i = 1; i < ranges.size(); ++i) {
    const vector<int>& current = ranges[i];

    while (true) {
      if (stack.empty()) {
        stack.push_back(current);
        break;
      }

      vector<int> top = stack.back();
      int top_start = top[0];
      int top_end = top[1];

      int current_start = current[0];
      int current_end = current[1];

      if (current_start <= top_start) {
        if (current_end <= top_start) {
          // 当前区间在栈顶区间左侧且无重叠
          break;
        }
        if (current_end < top_end) {
          // 当前区间被栈顶区间完全包含
          break;
        }
        // 当前区间覆盖栈顶区间，弹出栈顶
        stack.pop_back();
      } else if (current_start < top_end) {
        if (current_end <= top_end) {
          // 当前区间与栈顶区间有重叠但被包含
          break;
        }
        // 当前区间与栈顶区间有重叠但不完全包含
        stack.push_back({top_end, current_end});
        break;
      } else {
        // 当前区间与栈顶区间无重叠
        stack.push_back(current);
        break;
      }
    }
  }

  cout << stack.size() << endl; // 输出最少需要的线段数量
  return 0;
}
```

#### 招聘

**题目描述**：

某公司组织一场公开招聘活动，假设由于人数和场地的限制，每人每次面试的时长不等，并已经安排给定，用(S1, E1)、 (S2, E2)、 (Sj, Ej)…(Si < Ei，均为非负整数)表示每场面试的开始和结束时间。

面试采用一对一的方式，即一名面试官同时只能面试一名应试者，一名面试官完成一次面试后可以立即进行下一场面试，且每个面试官的面试人次不超过 m。

为了支撑招聘活动高效顺利进行，请你计算至少需要多少名面试官。

**输入描述**：

输入的第一行为面试官的最多面试人次 m，第二行为当天总的面试场次 n，

接下来的 n 行为每场面试的起始时间和结束时间，起始时间和结束时间用空格分隔。

其中， 1 <= n, m <= 500

**输出描述**：

输出一个整数，表示至少需要的面试官数量。

**用例 1**：

输入：

```
2
5
1 2
2 3
3 4
4 5
5 6
```

输出：

```
3
```

说明：总共有 5 场面试，且面试时间都不重叠，但每个面试官最多只能面试 2 人次，所以需要 3 名面试官。

**用例 2**：

输入：

```
3
3
1 2
2 3
3 4
```

输出：

```
1
```

说明：总共有 3 场面试，面试时间不重叠，每个面试官最多能面试 3 人次，所以只需要一名面试官

**用例 3**：

输入：

```
3
3
8 35
5 10
1 3
```

输出：

```
2
```

说明：总共有 3 场面试，[5,10] 和 [8,35] 有重叠，所以至少需要 2 名面试官

难度：中等

标签：堆（优先队列）、数组、贪心

(20/21)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

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
```

## 栈

### 100 分

#### 斗地主之顺子

**题目描述**：

在斗地主扑克牌游戏中， 扑克牌由小到大的顺序为：3,4,5,6,7,8,9,10, J, Q, K, A,2，玩家可以出的扑克牌阵型有：单张、对子、顺子、飞机、炸弹等。

其中顺子的出牌规则为：由至少 5 张由小到大连续递增的扑克牌组成，且不能包含 2。

例如：{3,4,5,6,7}、{3,4,5,6,7,8,9,10, J, Q, K, A}都是有效的顺子；而{J, Q, K, A,2}、 {2,3,4,5,6}、{3,4,5,6}、{3,4,5,6,8}等都不是顺子。

给定一个包含 13 张牌的数组，如果有满足出牌规则的顺子，请输出顺子。

如果存在多个顺子，请每行输出一个顺子，且需要按顺子的第一张牌的大小（必须从小到大）依次输出。

如果没有满足出牌规则的顺子，请输出 No。

**输入描述**：

13 张任意顺序的扑克牌，每张扑克牌数字用空格隔开，每张扑克牌的数字都是合法的，并且不包括大小王：2 9 J 2 3 4 K A 7 9 A 5 6

不需要考虑输入为异常字符的情况

**输出描述**：

组成的顺子，每张扑克牌数字用空格隔开：3 4 5 6 7

**用例 1**：

输入：

```
2 9 J 2 3 4 K A 7 9 A 5 6
```

输出：

```
3 4 5 6 7
```

说明：13 张牌中，可以组成的顺子只有 1 组：3 4 5 6 7。

**用例 2**：

输入：

```
2 9 J 10 3 4 K A 7 Q A 5 6
```

输出：

```
3 4 5 6 7
9 10 J Q K A
```

说明：13 张牌中，可以组成 2 组顺子，从小到大分别为：3 4 5 6 7 和 9 10 J Q K A

**用例 3**：

输入：

```
2 9 9 9 3 4 K A 10 Q A 5 6
```

输出：

```
No
```

说明：13 张牌中，无法组成顺子。

难度：中等

标签：哈希表、贪心、模拟

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
  // 定义牌的映射
  unordered_map<string, int> card_value = {
      {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7},
      {"8", 8}, {"9", 9}, {"10", 10}, {"J", 11},
      {"Q", 12}, {"K", 13}, {"A", 14}
  };

  // 反向映射
  unordered_map<int, string> value_card = {
      {3, "3"}, {4, "4"}, {5, "5"}, {6, "6"}, {7, "7"},
      {8, "8"}, {9, "9"}, {10, "10"}, {11, "J"},
      {12, "Q"}, {13, "K"}, {14, "A"}
  };

  // 读取输入
  string line;
  getline(cin, line);

  // 解析输入
  vector<string> cards;
  stringstream ss(line);
  string card;
  while (ss >> card) {
    cards.push_back(card);
  }

  // 统计每张牌的数量
  unordered_map<int, int> count;
  for (const string& c : cards) {
    if (c != "2") {
      // 排除2
      count[card_value[c]]++;
    }
  }

  // 存储所有顺子
  vector<vector<int> > straights;

  // 尝试生成顺子
  for (int len = 12; len >= 5; len--) {
    // 从最长的顺子开始
    for (int start = 3; start <= 14 - len + 1; start++) {
      unordered_map<int, int> tempCount = count;
      vector<int> straight;
      bool valid = true;

      // 检查连续len张牌是否存在
      for (int i = start; i < start + len; i++) {
        // 如果某张牌不存在，顺子无效
        if (tempCount.find(i) == tempCount.end() || tempCount[i] == 0) {
          valid = false;
          break;
        }
        straight.push_back(i);
        tempCount[i]--;
      }

      // 如果顺子有效，加入结果并更新原始计数
      if (valid) {
        // 更新原始计数
        for (int card : straight) {
          count[card]--;
        }
        straights.push_back(straight);
      }
    }
  }

  // 按顺子起始牌大小排序
  sort(straights.begin(), straights.end(),
       [](const vector<int>& a, const vector<int>& b) {
         return a[0] < b[0];
       });

  // 输出结果
  if (straights.empty()) {
    cout << "No" << endl;
  } else {
    for (const auto& straight : straights) {
      for (int i = 0; i < straight.size(); i++) {
        cout << value_card[straight[i]];
        if (i < straight.size() - 1)
          cout << " ";
      }
      cout << endl;
    }
  }

  return 0;
}
```

#### 荒岛逃生游戏

**题目描述**：

一个荒岛上有若干人，岛上只有一条路通往岛屿两端的港口，大家需要逃往两端的港口才可逃生。

假定每个人移动的速度一样，且只可选择向左或向右逃生。

若两个人相遇，则进行决斗，战斗力强的能够活下来，并损失掉与对方相同的战斗力；若战斗力相同，则两人同归于尽。

**输入描述**：

给定一行非 0 整数数组，元素个数不超过 30000；

正负表示逃生方向（正表示向右逃生，负表示向左逃生），绝对值表示战斗力，越左边的数字表示里左边港口越近，逃生方向相同的人永远不会发生决斗。

**输出描述**：

能够逃生的人总数，没有人逃生输出 0，输入异常时输出-1。

**用例 1**：

输入：

```
5 10 8 -8 -5
```

输出：

```
2
```

说明：第 3 个人和第 4 个人同归于尽，第 2 个人杀死第 5 个人并剩余 5 战斗力，第 1 个人没有遇到敌人。

难度：中等

标签：栈、数组

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  // 读取输入
  string line;
  getline(cin, line);

  // 特殊输入处理
  if (line.empty()) {
    cout << -1 << endl;
    return 0;
  }

  // 解析输入
  vector<int> people;
  int num;
  stringstream ss(line);

  while (ss >> num) {
    people.push_back(num);
  }

  // 输入有效性检查
  if (people.empty() || people.size() > 30000) {
    cout << -1 << endl;
    return 0;
  }

  for (auto p : people) {
    if (p == 0) {
      cout << -1 << endl;
      return 0;
    }
  }

  // 使用栈来处理逃生逻辑
  stack<int> s;           // 用于存储向右逃生的人（正数）
  int negative_count = 0; // 成功向左逃生的人数

  for (int person : people) {
    if (person > 0) {
      // 正数，向右逃生，入栈
      s.push(person);
    } else {
      // 负数，向左逃生
      int current_fight_power = abs(person);
      while (current_fight_power > 0 && !s.empty()) {
        // 先检查栈是否为空
        // 栈顶元素
        int top_power = s.top();
        if (top_power > current_fight_power) {
          // 正数战斗力大于负数
          s.pop();
          s.push(top_power - current_fight_power); // 正数继续逃生
          current_fight_power = 0;                 // 负数已被打败
        } else if (top_power < current_fight_power) {
          // 负数战斗力大于正数
          s.pop();
          current_fight_power -= top_power; // 负数继续战斗
        } else {
          // 同归于尽
          s.pop();
          current_fight_power = 0; // 两者都死亡
        }
      }
      if (current_fight_power > 0) {
        // 如果栈已空，负数逃生成功
        negative_count++;
      }
    }
  }

  // 存活的人数为栈中的正数加上成功的负数人数
  int positive_count = s.size();
  int total_survivors = positive_count + negative_count;

  cout << total_survivors << endl;

  return 0;
}
```

#### 找最小数

**题目描述**：

给一个正整数 NUM1，计算出新正整数 NUM2，NUM2 为 NUM1 中移除 N 位数字后的结果，需要使得 NUM2 的值最小。

**输入描述**：

输入的第一行为一个字符串，字符串由 0-9 字符组成，记录正整数 NUM1，NUM1 长度小于 32。

输入的第二行为需要移除的数字的个数，小于 NUM1 长度。

**输出描述**：

输出一个数字字符串，记录最小值 NUM2。

**用例 1**：

输入：

```
2615371
4
```

输出：

```
131
```

难度：中等

标签：贪心、单调栈、栈、字符串

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string num; // 输入的正整数
  int k;      // 需要移除的数字个数

  // 读取输入
  cin >> num >> k;

  // 特殊情况处理
  if (k == 0) {
    cout << num << endl; // 如果不移除，直接输出原数字
    return 0;
  }
  if (k >= num.length()) {
    cout << "0" << endl; // 如果要移除的数量大于或等于数字长度，输出0
    return 0;
  }

  stack<char> st;   // 用于存储最小结果的栈
  int to_remove = k; // 记录还需要移除的数字个数

  // 遍历每个数字
  for (char digit : num) {
    while (!st.empty() && to_remove > 0 && st.top() > digit) {
      // 如果当前数字小于栈顶元素，且还可以移除数字
      st.pop();   // 移除栈顶元素
      to_remove--; // 减少移除计数
    }
    st.push(digit); // 当前数字入栈
  }

  // 如果还有多余的数字需要移除，继续从栈中移除
  while (to_remove > 0) {
    st.pop();
    to_remove--;
  }

  // 构建结果字符串
  string result;
  while (!st.empty()) {
    result = st.top() + result; // 逆序入结果字符串
    st.pop();
  }

  // 移除前导零
  int start = 0;
  while (start < result.length() && result[start] == '0') {
    start++;
  }

  // 如果结果为空，返回0；否则返回结果字符串
  cout << (result.substr(start).empty() ? "0" : result.substr(start)) << endl;

  return 0;
}
```

#### 最远足迹

**题目描述**：
某探险队负责对地下洞穴进行探险。探险队成员在进行探险任务时，随身携带的记录器会不定期地记录自身的坐标，但在记录的间隙中也会记录其他数据。探索工作结束后，探险队需要获取到某成员在探险过程中相对于探险队总部的最远的足迹位置。

仪器记录坐标时，坐标的数据格式为(x, y)，如(1,2)、(100,200)，其中 0 < x < 1000，0 < y < 1000。同时存在非法坐标，如(01,1)、(1,01)，(0,100)属于非法坐标。 设定探险队总部的坐标为(0,0)，某位置相对总部的距离为：xx+yy。 若两个座标的相对总部的距离相同，则第一次到达的坐标为最远的足迹。 若记录仪中的坐标都不合法，输出总部坐标（0,0）。 备注：

不需要考虑双层括号嵌套的情况，比如 sfsdfsd((1,2))。

**输入描述**：

字符串，表示记录仪中的数据。

如：ferga13fdsf3(100,200)f2r3rfasf(300,400)

**输出描述**：

字符串，表示最远足迹到达的坐标。

如： (300,400)

**用例 1**：

输入：

```
ferg(3,10)a13fdsf3(3,4)f2r3rfasf(5,10)
```

输出：

```
(5,10)
```

说明：记录仪中的合法坐标有 3 个： (3,10)， (3,4)， (5,10)，其中(5,10)是相距总部最远的坐标， 输出(5,10)。

**用例 2**：

输入：

```
asfefaweawfaw(0,1)fe
```

输出：

```
(0,0)
```

说明：记录仪中的坐标都不合法，输出总部坐标（0,0）。

难度：中等

标签：栈、字符串

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input); // 读取输入字符串

  // 正则表达式匹配 (x,y) 格式的坐标
  regex coordinate_regex(R"(\((\d+),(\d+)\))");
  smatch matches;

  int max_distance = -1;
  string farthest_coordinate = "(0,0)"; // 默认坐标

  // 迭代匹配所有的坐标
  auto it = sregex_iterator(input.begin(), input.end(), coordinate_regex);
  auto end = sregex_iterator();

  for (; it != end; ++it) {
    // 提取坐标
    int x = stoi((*it)[1].str());
    int y = stoi((*it)[2].str());

    // 验证坐标合法性，防止前导零
    string x_str = (*it)[1].str();
    string y_str = (*it)[2].str();

    if ((x_str.size() == 1 || x_str[0] != '0') && (
          y_str.size() == 1 || y_str[0] != '0')) {
      if ((x > 0 && x < 1000) && (y > 0 && y < 1000)) {
        int distance = x * x + y * y; // 计算距离

        // 记录最远的坐标
        if (distance > max_distance) {
          max_distance = distance;
          farthest_coordinate = it->str(); // 更新最远坐标
        }
      }
    }
  }

  cout << farthest_coordinate << endl; // 输出结果
  return 0;
}
```

### 200 分

#### 计算堆栈中的剩余数字

**题目描述**：

向一个空栈中依次存入正整数，假设入栈元素 n(1 <= n <= 2^31-1)按顺序依次为 nx…n4、 n3、n2、 n1, 每当元素入栈时，如果 n1 = n2+…+ny(y 的范围 [2, x]， 1 <= x <= 1000)，则 n1~ny 全部元素出栈，重新入栈新元素 m(m = 2\*n1)。

如：依次向栈存入 6、 1、 2、 3, 当存入 6、 1、 2 时，栈底至栈顶依次为 [6、 1、 2]；当存入 3 时， 3 = 2+1， 3、 2、 1 全部出栈，重新入栈元素 6(6 = 2\*3)，此时栈中有元素 6；

因为 6 = 6，所以两个 6 全部出栈，存入 12，最终栈中只剩一个元素 12。

**输入描述**：

使用单个空格隔开的正整数的字符串，如”5 6 7 8″， 左边的数字先入栈，输入的正整数个数为 x， 1 <= x <= 1000。

**输出描述**：

最终栈中存留的元素值，元素值使用空格隔开，如”8 7 6 5″， 栈顶数字在左边。

**用例 1**：

输入：

```
5 10 20 50 85 1

```

输出：

```
1 170
```

说明：5+10+20+50 = 85， 输入 85 时， 5、 10、 20、 50、 85 全部出栈，入栈 170，最终依次出栈的数字为 1 和 170。

**用例 2**：

输入：

```
6 7 8 13 9
```

输出：

```
9 13 8 7 6
```

**用例 3**：

输入：

```
1 2 5 7 9 1 2 2
```

输出：

```
4 1 9 14 1
```

难度：中等

标签：栈、模拟、数组、动态规划

```cpp
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  // 读取输入
  string line;
  getline(cin, line);

  // 解析输入
  vector<long long> stack;
  stringstream ss(line);
  long long num;

  // 依次处理每个数字
  while (ss >> num) {
    stack.push_back(num);

    // 检查是否满足出栈条件
    while (stack.size() >= 2) {
      bool found = false;

      // 尝试查找从栈顶开始的所有可能子序列
      for (int i = 2; i <= min(static_cast<int>(stack.size()), 1000); i++) {
        // 计算最后 i 个元素的和
        long long sum = 0;
        for (int j = stack.size() - i; j < stack.size() - 1; j++) {
          sum += stack[j];
        }

        // 检查是否满足条件
        if (stack.back() == sum) {
          // 出栈 i 个元素
          long long last = stack.back();
          for (int k = 0; k < i; k++) {
            stack.pop_back();
          }

          // 入栈新元素
          stack.push_back(2 * last);

          found = true;
          break;
        }
      }

      // 如果没有找到满足条件的子序列，退出循环
      if (!found)
        break;
    }
  }

  // 输出结果
  if (stack.empty()) {
    cout << "No" << endl;
  } else {
    // 反向输出栈中元素
    for (int i = stack.size() - 1; i >= 0; i--) {
      cout << stack[i];
      if (i > 0)
        cout << " ";
    }
    cout << endl;
  }

  return 0;
}
```

#### 最长方连续方波信号

**题目描述**：

输入一串方波信号，求取最长的完全连续交替方波信号，并将其输出，如果有相同长度的交替方波信号，输出任一即可，方波信号高位用 1 标识，低位用 0 标识，如图：

![img](https://hydro.ac/d/HWOD2023/p/125/file/qvb0UaCgAVHhadE39qU-m.png)

说明：

1. 一个完整的信号一定以 0 开始然后以 0 结尾，即 010 是一个完整信号，但 101，1010，0101 不是
2. 输入的一串方波信号是由一个或多个完整信号组成
3. 两个相邻信号之间可能有 0 个或多个低位，如 0110010，011000010
4. 同一个信号中可以有连续的高位，如 01110101011110001010，前 14 位是一个具有连续高位的信号
5. 完全连续交替方波是指 10 交替，如 01010 是完全连续交替方波，0110 不是

**输入描述**：

输入信号字符串（长度 >= 3 且 <= 1024）

注：输入总是合法的，不用考虑异常情况

**输出描述**：

输出最长的完全连续交替方波信号串

若不存在完全连续交替方波信号串，输出 -1。

**用例 1**：

输入：

```
00101010101100001010010
```

输出：

```
01010
```

说明：

输入信号串中有三个信号：

0 010101010110(第一个信号段)

00 01010(第二个信号段)

010(第三个信号段)

第一个信号虽然有交替的方波信号段，但出现了 11 部分的连续高位，不算完全连续交替方波，

在剩下的连续方波信号串中 01010 最长

难度：中等

标签：栈、字符串

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  cin >> input; // 读取输入信号字符串

  stack<char> st;              // 用于保存当前信号的字符
  string longest_signal = "-1"; // 初始化最长信号为-1
  int max_length = 0;           // 初始化最长信号的长度

  for (char c : input) {
    if (st.empty()) {
      // 如果栈为空，直接压入字符
      st.push(c);
    } else {
      char top = st.top();
      if (c == '0' && top == '0') {
        // 如果出现两个'0'，表示可能开始新的信号
        string current_signal;
        while (!st.empty()) {
          current_signal = st.top() + current_signal; // 组合形成信号
          st.pop();
        }

        // 使用正则表达式验证是否为完全交替信号
        regex pattern1("^0(10)+$"); // 模式1：0后面是一个或多个10
        regex pattern2("^(01)+0$"); // 模式2：0前面是一个或多个01

        // 如果满足任意一个正则，则找到一个交替信号
        if (regex_match(current_signal, pattern1) || regex_match(
                current_signal, pattern2)) {
          int current_length = current_signal.length();
          if (current_length > max_length) {
            max_length = current_length;
            longest_signal = current_signal; // 更新最长信号
          }
        }

        // 新信号的 '0' 入栈
        st.push(c);
      } else if (c == '0' || c == '1') {
        // 其他情况下直接压入栈
        st.push(c);
      }
    }
  }

  // 处理最后一个可能的信号（如果栈不为空时）
  if (!st.empty()) {
    string current_signal;
    while (!st.empty()) {
      current_signal = st.top() + current_signal; // 组合形成信号
      st.pop();
    }

    // 再次验证当前信号
    regex pattern1("^0(10)+$"); // 模式1：0后面是一个或多个10
    regex pattern2("^(01)+0$"); // 模式2：0前面是一个或多个01

    if (regex_match(current_signal, pattern1) || regex_match(
            current_signal, pattern2)) {
      int current_length = current_signal.length();
      if (current_length > max_length) {
        max_length = current_length;
        longest_signal = current_signal; // 更新最长信号
      }
    }
  }

  // 输出结果
  cout << longest_signal << endl;

  return 0;
}
```

#### 解压报文

**题目描述**：

为了提升数据传输的效率，会对传输的报文进行压缩处理。

输入一个压缩后的报文，请返回它解压后的原始报文。

压缩规则：n [str]，表示方括号内部的 str 正好重复 n 次。

注意 n 为正整数（0 < n <= 100），str 只包含小写英文字母，不考虑异常情况。

**输入描述**：

输入压缩后的报文：

1. 不考虑无效的输入，报文没有额外的空格，方括号总是符合格式要求的；

2. 原始报文不包含数字，所有的数字只表示重复的次数 n ，例如不会出现像 5b 或 3\[8\] 的输入；

**输出描述**：

解压后的原始报文

注：原始报文长度不会超过 1000，不考虑异常的情况

**用例 1**：

输入：

```
3[k]2[mn]
```

输出：

```
kkkmnmn
```

说明：k 重复 3 次，mn 重复 2 次，最终得到 kkkmnmn

**用例 2**：

输入：

```
3[m2[c]]
```

输出：

```
mccmccmcc
```

说明：m2 [c] 解压缩后为 mcc，重复三次为 mccmccmcc

难度：中等

标签：栈、字符串、递归

```cpp
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
  string input;
  cin >> input; // 读取输入的压缩报文

  stack<int> count_stack;     // 用于存储重复次数
  stack<string> result_stack; // 用于存储构建的字符串
  string current_string; // 当前构建的字符串
  int idx = 0;               // 用于遍历的索引

  while (idx < input.size()) {
    if (isdigit(input[idx])) {
      // 如果是数字，解析出完整的数字
      int count = 0;
      while (isdigit(input[idx])) {
        count = count * 10 + (input[idx] - '0'); // 处理多位数
        idx++;
      }
      count_stack.push(count); // 将数字入栈
    } else if (input[idx] == '[') {
      // 遇到左括号，将当前字符串入栈
      result_stack.push(current_string); // 将当前字符串保存到栈中
      current_string = "";              // 重置当前字符串
      idx++;                           // 移动到下一个字符
    } else if (input[idx] == ']') {
      // 遇到右括号，构建字符串
      string temp = current_string;        // 暂存当前字符串
      current_string = result_stack.top();  // 取出栈顶的字符串
      result_stack.pop();                  // 弹出栈顶
      int repeat_count = count_stack.top(); // 取出重复次数
      count_stack.pop();                   // 弹出重复次数

      // 将 temp 字符串重复 repeatCount 次并拼接到 currentString
      for (int i = 0; i < repeat_count; ++i) {
        current_string += temp;
      }
      idx++; // 移动到下一个字符
    } else {
      // 处理字母字符，直接加入当前字符串
      current_string += input[idx];
      idx++;
    }
  }

  // 输出解压后的字符串
  cout << current_string << endl;

  return 0;
}
```

#### 仿 LISP 运算

**题目描述**：

LISP 语言唯一的语法就是括号要配对。

形如 (OP P1 P2 …)，括号内元素由单个空格分割。

其中第一个元素 OP 为操作符，后续元素均为其参数，参数个数取决于操作符类型。

注意：

参数 P1, P2 也有可能是另外一个嵌套的 (OP P1 P2 …) ，当前 OP 类型为 add / sub / mul / div（全小写），分别代表整数的加减乘除法，简单起见，所有 OP 参数个数均为 2 。

举例：

输入：(mul 3 -7)输出：-21

输入：(add 1 2) 输出：3

输入：(sub (mul 2 4) (div 9 3)) 输出 ：5

输入：(div 1 0) 输出：error

题目涉及数字均为整数，可能为负；

不考虑 32 位溢出翻转，计算过程中也不会发生 32 位溢出翻转，

除零错误时，输出 “error”，

除法遇除不尽，向下取整，即 3/2 = 1

**输入描述**：

输入为长度不超过 512 的字符串，用例保证了无语法错误

**输出描述**：

输出计算结果或者“error”

**用例 1**：

输入：

```
(div 12 (sub 45 45))
```

输出：

```
error
```

说明：45 减 45 得 0，12 除以 0 为除零错误，输出 error

**用例 2**：

输入：

```
(add 1 (div -7 3))
```

输出：

```
-2
```

说明：-7 除以 3 向下取整得-3，1 加-3 得-2

难度：困难

标签：栈、递归、数学、模拟、字符串

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input); // 读取整个输入行

  stack<string> stack; // 用于存储操作数和操作符
  string sb;      // 用于收集字符的临时字符串

  for (char c : input) {
    if (c != '(' && c != ')' && c != ' ') {
      // 收集操作符或参数的字符
      sb += c;
    } else if (c == ' ' || c == ')') {
      // 当收集完一个元素时，将其压入栈
      if (!sb.empty()) {
        stack.push(sb);
        sb.clear(); // 清空临时字符串
      }

      // 遇到闭合括号，进行计算
      if (c == ')') {
        // 从栈中取出 p2, p1 和 op
        int p2 = stoi(stack.top());
        stack.pop();
        int p1 = stoi(stack.top());
        stack.pop();
        string op = stack.top();
        stack.pop();

        // 执行计算
        int result = 0;
        if (op == "add")
          result = p1 + p2; // 加法
        else if (op == "sub")
          result = p1 - p2; // 减法
        else if (op == "mul")
          result = p1 * p2; // 乘法
        else if (op == "div") {
          // 处理除法，包括除零错误和向下取整
          if (p2 == 0) {
            cout << "error" << endl; // 输出错误信息
            return 0;                // 终止程序
          }
          // 向下取整操作，考虑负数
          result = p1 / p2;
          if (p1 % p2 != 0 && (p1 < 0) != (p2 < 0)) {
            result--; // 调整结果向下取整
          }
        }

        // 将计算结果重新压入栈
        stack.push(to_string(result));
      }
    }
  }

  // 输出最上面的结果，也就是最终计算结果
  cout << stack.top() << endl;

  return 0;
}
```

#### 分奖金

**题目描述**：

公司老板做了一笔大生意，想要给每位员工分配一些奖金，想通过游戏的方式来决定每个人分多少钱。

按照员工的工号顺序，每个人随机抽取一个数字。按照工号的顺序往后排列，遇到第一个数字比自己数字大的，那么，前面的员工就可以获得“距离 \* 数字差值”的奖金。如果遇不到比自己数字大的，就给自己分配随机数数量的奖金。

例如，按照工号顺序的随机数字是：2,10,3。那么第 2 个员工的数字 10 比第 1 个员工的数字 2 大，所以，第 1 个员工可以获得 1 \*（10-2）= 8 。第 2 个员工后面没有比他数字更大的员工，所以，他获得他分配的随机数数量的奖金，就是 10。第 3 个员工是最后一个员工，后面也没有比他更大数字的员工，所以他得到的奖金是 3。

请帮老板计算一下每位员工最终分到的奖金都是多少钱。

**输入描述**：

第一行 n 表示员工数量（包含最后一个老板）

第二是每位员工分配的随机数字

**输出描述**：

最终每位员工分到的奖金数量

注：随机数字不重复，员工数量（包含老板）范围 1~10000，随机数范围 1~100000

**用例 1**：

输入：

```
3
2 10 3
```

输出：

```
8 10 3
```

难度：中等

标签：栈、数组、单调栈

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n; // 读取员工数量
  vector<int> numbers(n);
  vector<int> bonuses(n); // 保存每位员工的奖金

  // 读取随机数字
  for (int i = 0; i < n; i++) {
    cin >> numbers[i];
  }

  stack<int> s; // 用于保存员工索引

  for (int i = 0; i < n; ++i) {
    while (!s.empty() && numbers[s.top()] < numbers[i]) {
      // 计算奖金
      int index = s.top();                                          // 获取栈顶员工的索引
      bonuses[index] = (i - index) * (numbers[i] - numbers[index]); // 奖金计算
      s.pop();                                                      // 弹出栈顶员工
    }
    s.push(i); // 将当前员工的索引压入栈
  }

  // 所有仍在栈中的员工，奖金为他们自己的随机数
  while (!s.empty()) {
    bonuses[s.top()] = numbers[s.top()];
    s.pop();
  }

  // 输出每位员工的奖金
  for (int i = 0; i < n; i++) {
    cout << bonuses[i] << " ";
  }
  cout << endl;

  return 0;
}
```

## 双端队列

### 100 分

#### 喊 7 的次数重排

**题目描述**：

喊 7 是一个传统的聚会游戏，N 个人围成一圈，按顺时针从 1 到 N 编号。

编号为 1 的人从 1 开始喊数，下一个人喊的数字为上一个人的数字加 1，但是当将要喊出来的数字是 7 的倍数或者数字本身含有 7 的话，不能把这个数字直接喊出来，而是要喊”过”。

假定玩这个游戏的 N 个人都没有失误地在正确的时机喊了”过”，当喊到数字 K 时，可以统计每个人喊”过”的次数。

现给定一个长度为 N 的数组，存储了打乱顺序的每个人喊”过”的次数，请把它还原成正确的顺序，即数组的第 i 个元素存储编号 i 的人喊”过”的次数。

**输入描述**：

输入为一行，为空格分隔的喊“过”的次数，注意 K 并不提供，K 不超过 200，而数字的个数即为 N。

**输出描述**：

输出为一行，为顺序正确的喊”过”的次数，也由空格分隔。

**用例 1**：

输入：

```
0 1 0
```

输出：

```
1 0 0
```

说明：

一共只有一次喊”过”，那只会发生在需要喊 7 时，按顺序，编号为 1 的人会遇到 7，故输出 1 0 0。

注意：结束时的 K 不一定是 7，也可以是 8、9 等，喊过的次数都是 1 0 0。

**用例 2**：

输入：

```
0 0 0 2 1
```

输出：

```
0 2 0 1 0
```

说明：一共有三次喊”过”，发生在 7 14 17，按顺序，编号为 2 的人会遇到 7 17，编号为 4 的人会遇到 14，故输出 0 2 0 1 0。

难度：中等

标签：数组、队列

```cpp
#include <bits/stdc++.h>

using namespace std;

// 判断数字是否是7的倍数或包含7
bool IsSeven(int num) {
  if (num % 7 == 0)
    return true;
  while (num > 0) {
    if (num % 10 == 7)
      return true;
    num /= 10;
  }
  return false;
}

int main() {
  vector<int> counts;
  int num;
  while (cin >> num) {
    counts.push_back(num);
  }

  int n = counts.size();    // 人数
  vector<int> result(n, 0); // 初始化结果数组

  int total_passes = 0;
  for (int count : counts) {
    total_passes += count;
  }

  int current_number = 1;
  int current_player = 0;
  int passes_counted = 0;

  while (passes_counted < total_passes) {
    if (IsSeven(current_number)) {
      result[current_player]++;
      passes_counted++;
    }
    current_number++;
    current_player = (current_player + 1) % n;
  }

  for (int i = 0; i < n; i++) {
    cout << result[i] << " ";
  }
  cout << endl;

  return 0;
}
```

#### 报数游戏

**题目描述**：

100 个人围成一圈，每个人有一个编码，编号从 1 开始到 100。

他们从 1 开始依次报数，报到为 M 的人自动退出圈圈，然后下一个人接着从 1 开始报数，直到剩余的人数小于 M。

请问最后剩余的人在原先的编号为多少？

**输入描述**：

输入一个整数参数 M

**输出描述**：

如果输入参数 M 小于等于 1 或者大于等于 100，输出“ERROR!”；

否则按照原先的编号从小到大的顺序，以英文逗号分割输出编号字符串

**用例 1**：

输入：

```
3
```

输出：

```
58,91
```

说明：输入 M 为 3，最后剩下两个人。

**用例 2**：

输入：

```
4
```

输出：

```
34,45,97
```

说明：输入 M 为 4，最后剩下三个人。

难度：中等

标签：数组、队列

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int m;
  cin >> m;

  // 输入参数不合法处理
  if (m <= 1 || m >= 100) {
    cout << "ERROR!" << endl;
    return 0;
  }

  vector<int> people;
  // 初始化1到100的编号
  for (int i = 1; i <= 100; ++i) {
    people.push_back(i);
  }

  int index = 0; // 起始报数的索引

  // 模拟报数过程
  while (people.size() >= m) {
    index = (index + m - 1) % people.size(); // 计算被移除者的索引（-1因为下标从0开始）
    people.erase(people.begin() + index);    // 移除该人
  }

  // 输出剩余人的编号
  stringstream result;
  for (size_t i = 0; i < people.size(); ++i) {
    if (i > 0)
      result << ","; // 处理前面的逗号
    result << people[i];
  }

  cout << result.str() << endl; // 输出结果
  return 0;
}
```

### 200 分

#### 篮球游戏

**题目描述**：

幼儿园里有一个放倒的圆桶，它是一个线性结构，允许在桶的右边将篮球放入，可以在桶的左边和右边将篮球取出。

每个篮球有单独的编号，老师可以连续放入一个或多个篮球，小朋友可以在桶左边或右边将篮球取出，当桶只有一个篮球的情况下，必须从左边取出。

如老师按顺序放入 1、2、3、4、5 共有 5 个编号的篮球，那么小朋友可以依次取出编号为 1、2、3、4、5 或者 3、1、2、4、5 编号的篮球，无法取出 5、1、3、2、4 编号的篮球。

其中 3、1、2、4、5 的取出场景为：

连续放入 1、2、3 号
从右边取出 3 号

从左边取出 1 号

从左边取出 2 号

放入 4 号

从左边取出 4 号

放入 5 号

从左边取出 5 号

简答起见，我们以 L 表示左，R 表示右，此时取出篮球的依次取出序列为“RLLLL”。

**输入描述**：

每次输入包含一个测试用例：

1. 第一行的数字作为老师依次放入的篮球编号

2. 第二行的数字作为要检查是否能够按照放入的顺序取出给定的篮球的编号，其中篮球的编号用逗号进行分隔。

其中篮球编号用逗号进行分隔。

1 ≤ 篮球编号，篮球个数 ≤ 200

篮球上的数字不重复

输出的结果中 LR 必须为大写

**输出描述**：

对于每个篮球的取出序列，如果确实可以获取，请打印出其按照左右方向的操作取出顺序，如果无法获取则打印“NO”。

**用例 1**：

输入：

```
4,5,6,7,0,1,2
6,4,0,1,2,5,7
```

输出：

```
RLRRRLL
```

说明：篮球的取出顺序依次为“右、左、右、右、右、左、左”

**用例 2**：

输入：

```
4,5,6,7,0,1,2
6,0,5,1,2,4,7
```

输出：

```
NO
```

说明：无法取出对应序列的篮球

**用例 3**：

输入：

```
1,2,3,4
1,2,3,5
```

输出：

```
NO
```

说明：不存在编号为 5 的篮球，所以无法取出对应编号的数据

难度：中等

标签：队列

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  string input;
  getline(cin, input);
  stringstream ss(input);
  vector<int> balls;
  int ball;
  while (ss >> ball) {
    balls.push_back(ball);
    if (ss.peek() == ',')
      ss.ignore();
  }

  getline(cin, input);
  stringstream ss2(input);
  vector<int> sequence;
  while (ss2 >> ball) {
    sequence.push_back(ball);
    if (ss2.peek() == ',')
      ss2.ignore();
  }

  deque<int> bucket;
  string result;
  int idx = 0;

  for (int ball : balls) {
    bucket.push_back(ball);
    while (!bucket.empty() && idx < sequence.size() && (
             bucket.front() == sequence[idx] || bucket.back() == sequence[
               idx])) {
      if (bucket.front() == sequence[idx]) {
        result += 'L';
        bucket.pop_front();
      } else {
        result += 'R';
        bucket.pop_back();
      }
      idx++;
    }
  }

  if (idx == sequence.size()) {
    cout << result << endl;
  } else {
    cout << "NO" << endl;
  }

  return 0;
}
```

## 链表

### 100 分

#### 寻找链表的中间结点

**题目描述**：

给定一个单链表 L，请编写程序输出 L 中间结点保存的数据。

如果有两个中间结点，则输出第二个中间结点保存的数据。例如：

给定 L 为 1→7→5，则输出应该为 7；

给定 L 为 1→2→3→4，则输出应该为 3；

**输入描述**：

每个输入包含 1 个测试用例。

每个测试用例：

第一行给出链表首结点的地址、结点总个数正整数 N （≤ 10^5）。结点的地址是 5 位非负整数，NULL 地址用-1 表示。

接下来有 N 行，每行格式位：

Address Data Next

其中 Address 是结点地址，Data 是该结点保存的整数数据（0 ≤ Data ≤ 10^8），Next 是下一结点的地址。

已确保输入的结点所构成的链表 L 不会成环，但会存在部分输入结点不属于链表 L 情况 。

**输出描述**：

对每个测试用例，在一行中输出 L 中间结点保存的数据。 如果有两个中间结点，则输出第二个中间结点保存的数据。

**用例 1**：

输入：

```
00010 4
00000 3 -1
00010 5 12309
11451 6 00000
12309 7 11451
```

输出：

```
6
```

**用例 2**：

输入：

```
10000 3
76892 7 12309
12309 5 -1
10000 1 76892
```

输出：

```
7
```

难度：中等

标签：链表、双指针

```cpp
#include <bits/stdc++.h>

using namespace std;

struct ListNode {
  int address;
  int data;
  int next;
};

int main() {
  int head_address, n;
  cin >> head_address >> n;

  // 存储节点的映射
  unordered_map<int, ListNode> node_map;
  for (int i = 0; i < n; ++i) {
    int address, data, next;
    cin >> address >> data >> next;
    node_map[address] = {address, data, next}; // 记录节点信息
  }

  // 快慢指针找中间节点
  int slow = head_address;
  int fast = head_address;

  // 当快指针非空并且快指针的next非空
  while (fast != -1 && node_map[fast].next != -1) {
    slow = node_map[slow].next; // 慢指针走一步
    fast = node_map[fast].next; // 快指针走两步
    if (fast != -1) {
      // 确保快指针不为空
      fast = node_map[fast].next; // 快指针再走一步
    }
  }

  // 输出中间节点的值
  cout << node_map[slow].data << endl;

  return 0;
}
```

## 树

### 100 分

#### 计算三叉搜索树的高度

**题目描述**：

定义构造三叉搜索树规则如下：

每个节点都存有一个数，当插入一个新的数时，从根节点向下寻找，直到找到一个合适的空节点插入。查找的规则是：

如果数小于节点的数减去 500，则将数插入节点的左子树

如果数大于节点的数加上 500，则将数插入节点的右子树

否则，将数插入节点的中子树

给你一系列数，请按以上规则，按顺序将数插入树中，构建出一棵三叉搜索树，最后输出树的高度。

**输入描述**：

第一行为一个数 N，表示有 N 个数，1 ≤ N ≤ 10000

第二行为 N 个空格分隔的整数，每个数的范围为 [1,10000]

**输出描述**：

输出树的高度（根节点的高度为 1）

**用例 1**：

输入：

```
5
5000 2000 5000 8000 1800
```

输出：

```
3
```

说明：

最终构造出的树如下，高度为 3：

![image](https://hydro.ac/d/HWOD2023/p/362/file/3T4KuBstqV2w-QHYy4QqT.png)

**用例 2**：

输入：

```
3
5000 4000 3000
```

输出：

```
3
```

说明：

最终构造出的树如下，高度为 3：

![image](https://hydro.ac/d/HWOD2023/p/362/file/rOfOkQJG9oMmItjdQOCdU.png)

**用例 3**：

输入：

```
9
5000 2000 5000 8000 1800 7500 4500 1400 8100
```

输出：

```
4
```

说明：

最终构造出的树如下，高度为 4：

![image](https://hydro.ac/d/HWOD2023/p/362/file/qF7J-eXbPNf4bN4sBfVXM.png)

难度：中等

标签：树、递归、二叉搜索树

```cpp
#include <bits/stdc++.h>

using namespace std;

class TreeNode {
  public:
    int value_;
    TreeNode* left_;
    TreeNode* middle_;
    TreeNode* right_;

    explicit TreeNode(int val) : value_(val), left_(nullptr), middle_(nullptr),
                                 right_(nullptr) {}
};

class TernarySearchTree {
  TreeNode* root_;

  void insert(TreeNode*& node, int val) {
    if (node == nullptr) {
      node = new TreeNode(val);
    } else if (val < node->value_ - 500) {
      insert(node->left_, val);
    } else if (val > node->value_ + 500) {
      insert(node->right_, val);
    } else {
      insert(node->middle_, val);
    }
  }

  int height(const TreeNode* node) {
    if (node == nullptr) {
      return 0;
    }
    int left_height = height(node->left_);
    int middle_height = height(node->middle_);
    int right_height = height(node->right_);
    return 1 + max(left_height, max(middle_height, right_height));
  }

  public:
    TernarySearchTree() : root_(nullptr) {}

    void Insert(int val) {
      insert(root_, val);
    }

    int Height() {
      return height(root_);
    }
};

int main() {
  int n;
  cin >> n;

  TernarySearchTree tree;
  vector<int> numbers(n);

  for (int i = 0; i < n; ++i) {
    cin >> numbers[i];
    tree.Insert(numbers[i]);
  }

  cout << tree.Height() << endl;

  return 0;
}
```

#### 生成哈夫曼树

**题目描述**：

给定长度为 n 的无序的数字数组，每个数字代表二叉树的叶子节点的权值，数字数组的值均大于等于 1。

请完成一个函数，根据输入的数字数组，生成哈夫曼树，并将哈夫曼树按照中序遍历输出。

为了保证输出的二叉树中序遍历结果统一，增加以下限制：

二叉树节点中，左节点权值小于右节点权值，根节点权值为左右节点权值之和。当左右节点权值相同时，左子树高度小于等于右子树高度。

注意：

所有用例保证有效，并能生成哈夫曼树。

提醒：

哈夫曼树又称为最优二叉树，是一种带权路径长度最短的二叉树。

所谓树的带权路径长度，就是树中所有的叶节点的权值乘上其到根节点的路径长度（若根节点为 0 层，叶节点到根节点的路径长度为叶节点的层数）

**输入描述**：

例如：由叶子节点：5 15 40 30 10，生成的最优二叉树如下图所示，该树的最短带权路径长度为：40 _ 1 + 30 _ 2 + 5 _ 4 + 10 _ 4 = 205。

![image](https://hydro.ac/d/HWOD2023/p/440/file/NNtwOyVZbsq7KbsgIvonl.png)

**输出描述**：

输出一个哈夫曼树的中序遍历数组，数值间以空格分隔

**用例 1**：

输入：

```
5
5 15 40 30 10
```

输出：

```
40 100 30 60 15 30 5 15 10
```

说明：根据输入，生成哈夫曼树，按照中序遍历返回。所有节点中，左节点权值小于等于右节点权值之和。当左右节点权值相同时，左子树高度小于右子树。结果如上图所示。

难度：中等

标签：树、堆（优先队列）、贪心

```cpp
#include <bits/stdc++.h>

using namespace std;

class TreeNode {
  public:
    int weight_;
    TreeNode* left_;
    TreeNode* right_;

    explicit TreeNode(int w) : weight_(w), left_(nullptr), right_(nullptr) {}

    // 计算树的高度
    int height() const {
      if (!left_ && !right_)
        return 1;
      const int left_height = left_ ? left_->height() : 0;
      const int right_height = right_ ? right_->height() : 0;
      return 1 + max(left_height, right_height);
    }
};

class Compare {
  public:
    bool operator()(TreeNode* a, TreeNode* b) const {
      if (a->weight_ == b->weight_) {
        // 如果权值相同，则比较高度
        return a->height() > b->height(); // 高度较小的优先
      }
      return a->weight_ > b->weight_; // 小的权值优先
    }
};

// 中序遍历并输出
void inorder(TreeNode* node, vector<int>& result) {
  if (!node)
    return;
  inorder(node->left_, result);
  result.push_back(node->weight_);
  inorder(node->right_, result);
}

int main() {
  int n;
  cin >> n;

  priority_queue<TreeNode*, vector<TreeNode*>, Compare> min_heap;
  vector<int> weights(n);

  // 读取权值
  for (int i = 0; i < n; ++i) {
    cin >> weights[i];
    min_heap.push(new TreeNode(weights[i])); // 将权值放入最小堆
  }

  // 构建哈夫曼树
  while (min_heap.size() > 1) {
    TreeNode* left = min_heap.top();
    min_heap.pop();
    TreeNode* right = min_heap.top();
    min_heap.pop();

    // 创建新节点
    auto* parent = new TreeNode(left->weight_ + right->weight_);
    if (left->weight_ < right->weight_ || (
          left->weight_ == right->weight_ && left->height() <= right->
          height())) {
      parent->left_ = left;
      parent->right_ = right;
    } else {
      parent->left_ = right;
      parent->right_ = left;
    }

    // 将新节点放回最小堆
    min_heap.push(parent);
  }

  // 只剩下一个节点，就是根节点
  TreeNode* root = min_heap.top();

  // 中序遍历
  vector<int> result;
  inorder(root, result);

  // 输出结果
  for (size_t i = 0; i < result.size(); ++i) {
    cout << result[i];
    if (i != result.size() - 1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}
```

#### 传递悄悄话

**题目描述**：

给定一个二叉树，每个节点上站一个人，节点数字表示父节点到该节点传递悄悄话需要花费的时间。

初始时，根节点所在位置的人有一个悄悄话想要传递给其他人，求二叉树所有节点上的人都接收到悄悄话花费的时间。

**输入描述**：

给定二叉树

0 9 20 -1 -1 15 7 -1 -1 -1 -1 3 2

注：-1 表示空节点

![image](https://hydro.ac/d/HWOD2023/p/367/file/N_vlVLDOKBSmt9zLJDiRL.png)

**输出描述**：

返回所有节点都接收到悄悄话花费的时间

38

**用例 1**：

输入：

```
0 9 20 -1 -1 15 7 -1 -1 -1 -1 3 2
```

输出：

```
38
```

难度：中等

标签：树、深度优先搜索、广度优先搜索、递归

```cpp
#include <bits/stdc++.h>

using namespace std;

class TreeNode {
  public:
    int val_;
    TreeNode* left_;
    TreeNode* right_;

    explicit TreeNode(int x) : val_(x), left_(nullptr), right_(nullptr) {}
};

// 构建二叉树
TreeNode* buildTree(const vector<int>& nodes, int index) {
  if (index >= nodes.size() || nodes[index] == -1) {
    return nullptr;
  }
  auto* root = new TreeNode(nodes[index]);
  root->left_ = buildTree(nodes, 2 * index + 1);
  root->right_ = buildTree(nodes, 2 * index + 2);
  return root;
}

// 深度优先搜索，计算最大路径和
int dfs(TreeNode* root, int currentSum) {
  if (!root)
    return 0;
  currentSum += root->val_;
  if (!root->left_ && !root->right_) {
    return currentSum;
  }
  int left_sum = dfs(root->left_, currentSum);
  int right_sum = dfs(root->right_, currentSum);
  return max(left_sum, right_sum);
}

int main() {
  string input;
  getline(cin, input); // 读取一行输入
  stringstream ss(input);
  vector<int> nodes;
  int val;
  while (ss >> val) {
    nodes.push_back(val);
  }

  TreeNode* root = buildTree(nodes, 0);
  int max_time = dfs(root, 0);
  cout << max_time << endl;

  return 0;
}
```

### 200 分

#### 二叉树计算

**题目描述**：

给出一个二叉树如下图所示：

![image](https://hydro.ac/d/HWOD2023/p/375/file/FrvjPlfctXQG7dXxtXCBH.png)

请由该二叉树生成一个新的二叉树，它满足其树中的每个节点将包含原始树中的左子树和右子树的和。

![image](https://hydro.ac/d/HWOD2023/p/375/file/6UChfpH83FqmCCUFS-jIe.png)

左子树表示该节点左侧叶子节点为根节点的一颗新树；右子树表示该节点右侧叶子节点为根节点的一颗新树。

**输入描述**：

2 行整数，第 1 行表示二叉树的中序遍历，第 2 行表示二叉树的前序遍历，以空格分割

例如：

7 -2 6 6 9

6 7 -2 9 6

**输出描述**：

1 行整数，表示求和树的中序遍历，以空格分割

例如：

-2 0 20 0 6

**用例 1**：

输入：

```
-3 12 6 8 9 -10 -7
8 12 -3 6 -10 9 -7
```

输出：

```
0 3 0 7 0 2 0
```

难度：中等

标签：树、深度优先搜索、递归

```cpp
#include <bits/stdc++.h>

using namespace std;

class TreeNode {
  public:
    int val_;
    TreeNode* left_;
    TreeNode* right_;

    explicit TreeNode(int x) : val_(x), left_(nullptr), right_(nullptr) {}
};

// 根据中序遍历和前序遍历构建二叉树
TreeNode* BuildTree(vector<int>& inorder, vector<int>& preorder) {
  if (preorder.empty())
    return nullptr;

  auto* root = new TreeNode(preorder[0]);
  stack<TreeNode*> stk;
  stk.push(root);
  int inorder_index = 0;

  for (int i = 1; i < preorder.size(); ++i) {
    TreeNode* node = stk.top();
    if (node->val_ != inorder[inorder_index]) {
      node->left_ = new TreeNode(preorder[i]);
      stk.push(node->left_);
    } else {
      while (!stk.empty() && stk.top()->val_ == inorder[inorder_index]) {
        node = stk.top();
        stk.pop();
        ++inorder_index;
      }
      node->right_ = new TreeNode(preorder[i]);
      stk.push(node->right_);
    }
  }

  return root;
}

// 生成求和树
int GenerateSumTree(TreeNode* root) {
  if (!root)
    return 0;
  int left_sum = GenerateSumTree(root->left_);
  int right_sum = GenerateSumTree(root->right_);
  int original_val = root->val_;
  root->val_ = left_sum + right_sum;
  return original_val + left_sum + right_sum;
}

// 中序遍历二叉树
void InorderTraversal(TreeNode* root, vector<int>& result) {
  stack<TreeNode*> stk;
  TreeNode* curr = root;

  while (curr || !stk.empty()) {
    while (curr) {
      stk.push(curr);
      curr = curr->left_;
    }
    curr = stk.top();
    stk.pop();
    result.push_back(curr->val_);
    curr = curr->right_;
  }
}

int main() {
  vector<int> inorder, preorder;
  string line;

  getline(cin, line);
  stringstream ss(line);
  int val;
  while (ss >> val) {
    inorder.push_back(val);
  }

  getline(cin, line);
  ss.clear();
  ss.str(line);
  while (ss >> val) {
    preorder.push_back(val);
  }

  TreeNode* root = BuildTree(inorder, preorder);
  GenerateSumTree(root);

  vector<int> result;
  InorderTraversal(root, result);

  for (size_t i = 0; i < result.size(); ++i) {
    cout << result[i];
    if (i != result.size() - 1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}
```

#### 模拟目录管理功能

**题目描述**：

实现一个模拟目录管理功能的软件，输入一个命令序列，输出最后一条命令运行结果。

支持命令：

1. 创建目录命令：mkdir 目录名称，如 mkdir abc 为在当前目录创建 abc 目录，如果已存在同名目录则不执行任何操作。此命令无输出。
2. 进入目录命令：cd 目录名称，如 cd abc 为进入 abc 目录，特别地，cd .. 为返回上级目录，如果目录不存在则不执行任何操作。此命令无输出。
3. 查看当前所在路径命令：pwd，输出当前路径字符串。

约束：

1. 目录名称仅支持小写字母；mkdir 和 cd 命令的参数仅支持单个目录，如：mkdir abc 和 cd abc；不支持嵌套路径和绝对路径，如 mkdir abc/efg，cd abc/efg，mkdir /abc/efg，cd /abc/efg 是不支持的。
2. 目录符号为/，根目录/作为初始目录。
3. 任何不符合上述定义的无效命令不做任何处理并且无输出。

**输入描述**：

输入 N 行字符串，每一行字符串是一条命令。

**输出描述**：

输出最后一条命令运行结果字符串。

命令行数限制 100 行以内，目录名称限制 10 个字符以内。

**用例 1**：

输入：

```
mkdir abc
cd abc
pwd

```

输出：

```
/abc/
```

说明：在根目录创建一个 abc 的目录并进入 abc 目录中查看当前目录路径，输出当前路径/abc/。

难度：中等

标签：树、栈、字符串、哈希表、模拟

```cpp
#include <bits/stdc++.h>

using namespace std;

class DirectoryManager {
  stack<string> path_;
  unordered_map<string, unordered_set<string> > directory_structure_;

  public:
    DirectoryManager() {
      path_.emplace("/");
      directory_structure_["/"] = unordered_set<string>();
    }

    void mkdir(const string& dir_name) {
      string current_path = path_.top();
      if (directory_structure_[current_path].find(dir_name) ==
          directory_structure_[
            current_path].end()) {
        directory_structure_[current_path].insert(dir_name);
        directory_structure_[dir_name] = unordered_set<string>();
        // 初始化子目录
      }
    }

    void cd(const string& dir_name) {
      if (dir_name == "..") {
        if (path_.size() > 1) {
          path_.pop();
        }
      } else {
        string current_path = path_.top();
        if (directory_structure_[current_path].find(dir_name) !=
            directory_structure_[
              current_path].end()) {
          path_.push(dir_name);
        }
      }
    }

    string pwd() {
      string result;
      stack<string> temp = path_;
      vector<string> dirs;
      while (!temp.empty()) {
        dirs.push_back(temp.top());
        temp.pop();
      }
      for (int i = dirs.size() - 1; i >= 0; --i) {
        if (dirs[i] == "/") {
          result += "/";
        } else {
          result += dirs[i] + "/";
        }
      }
      return result.empty() ? "/" : result;
    }
};

int main() {
  DirectoryManager dm;
  string line;
  string last_output = "/"; // 默认初始路径为 "/"

  while (getline(cin, line)) {
    if (line.empty())
      break; // 处理空行

    stringstream ss(line);
    string command;
    ss >> command;

    if (command == "mkdir") {
      string dir_name;
      ss >> dir_name;
      dm.mkdir(dir_name);
    } else if (command == "cd") {
      string dir_name;
      ss >> dir_name;
      dm.cd(dir_name);
    } else if (command == "pwd") {
      last_output = dm.pwd();
    }
  }

  cout << last_output << endl;

  return 0;
}
```

#### 数组二叉树

**题目描述**：

二叉树也可以用数组来存储，给定一个数组，树的根节点的值存储在下标 1，对于存储在下标 N 的节点，它的左子节点和右子节点分别存储在下标 2N 和 2N+1，并且我们用值-1 代表一个节点为空。

给定一个数组存储的二叉树，试求从根节点到最小的叶子节点的路径，路径由节点的值组成。

**输入描述**：

输入一行为数组的内容，数组的每个元素都是正整数，元素间用空格分隔。

注意第一个元素即为根节点的值，即数组的第 N 个元素对应下标 N，下标 0 在树的表示中没有使用，所以我们省略了。

输入的树最多为 7 层。

**输出描述**：

输出从根节点到最小叶子节点的路径上，各个节点的值，由空格分隔，用例保证最小叶子节点只有一个。

**用例 1**：

输入：

```
3 5 7 -1 -1 2 4
```

输出：

```
3 7 2
```

说明：最小叶子节点的路径为 3 7 2。

**用例 2**：

输入：

```
5 9 8 -1 -1 7 -1 -1 -1 -1 -1 6
```

输出：

```
5 8 7 6
```

说明：最小叶子节点的路径为 5 8 7 6，注意数组仅存储至最后一个非空节点，故不包含节点“7”右子节点的-1。

难度：中等

标签：树、深度优先搜索、广度优先搜索、递归、数组

```cpp
#include <bits/stdc++.h>

using namespace std;

void dfs(const vector<int>& tree, int index, vector<int>& path, int& min_leaf,
         vector<int>& min_path) {
  if (index >= tree.size() || tree[index] == -1) {
    return;
  }

  path.push_back(tree[index]);

  int left = 2 * index;
  int right = 2 * index + 1;

  // 检查当前节点是否为叶子
  bool is_leaf = true;
  if (left < tree.size() && tree[left] != -1) {
    is_leaf = false;
    dfs(tree, left, path, min_leaf, min_path);
  }
  if (right < tree.size() && tree[right] != -1) {
    is_leaf = false;
    dfs(tree, right, path, min_leaf, min_path);
  }

  if (is_leaf && tree[index] < min_leaf) {
    min_leaf = tree[index];
    min_path = path;
  }

  path.pop_back(); // 回溯
}

vector<int> FindMinLeafPath(const vector<int>& tree) {
  int min_leaf = INT_MAX;
  vector<int> min_path;
  vector<int> path;
  dfs(tree, 1, path, min_leaf, min_path); // 从根开始（索引 1）
  return min_path;
}

int main() {
  string line;
  getline(cin, line);
  stringstream ss(line);
  vector<int> tree;
  tree.push_back(-1); // 索引 0 未使用

  int val;
  while (ss >> val) {
    tree.push_back(val);
  }

  vector<int> min_path = FindMinLeafPath(tree);

  for (size_t i = 0; i < min_path.size(); ++i) {
    cout << min_path[i];
    if (i != min_path.size() - 1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}
```

#### 目录删除

**题目描述**：

某文件系统中有 N 个目录，每个目录都有一个独一无二的 ID。

每个目录只有一个父目录，但每个父目录下可以有零个或者多个子目录，目录结构呈树状结构。

假设，根目录的 ID 为 0，且根目录没有父目录，其他所有目录的 ID 用唯一的正整数表示，并统一编号。

现给定目录 ID 和其父目录 ID 的对应父子关系表[子目录 ID，父目录 ID]，以及一个待删除的目录 ID，请计算并返回一个 ID 序列，表示因为删除指定目录后剩下的所有目录，返回的 ID 序列以递增序输出。

注意

1. 被删除的目录或文件编号一定在输入的 ID 序列中；

2. 当一个目录删除时，它所有的子目录都会被删除。

**输入描述**：

输入的第一行为父子关系表的长度 m；

接下来的 m 行为 m 个父子关系对；

最后一行为待删除的 ID。

序列中的元素以空格分割，参见样例。

**输出描述**：

输出一个序列，表示因为删除指定目录后，剩余的目录 ID。

**用例 1**：

输入：

```
5
8 6
10 8
6 0
20 8
2 6
8
```

输出：

```
2 6
```

说明：

![image](https://hydro.ac/d/HWOD2023/p/240/file/kUMQOB8nE5Gvb_jhHyV8b.png)

难度：中等

标签：树、深度优先搜索、广度优先搜索、哈希表、递归

```cpp
#include <bits/stdc++.h>

using namespace std;

// 深度优先搜索，标记待删除的目录及其子目录
void dfs(int id, unordered_map<int, vector<int> >& children,
         unordered_set<int>& to_delete) {
  to_delete.insert(id); // 标记当前目录为待删除
  for (int child : children[id]) {
    dfs(child, children, to_delete); // 递归处理子目录
  }
}

int main() {
  int m;
  cin >> m;                             // 读取父子关系表的长度
  vector<pair<int, int> > relations(m); // 存储父子关系对
  for (int i = 0; i < m; ++i) {
    cin >> relations[i].first >> relations[i].second; // 读取每个父子关系对
  }
  int delete_id;
  cin >> delete_id; // 读取待删除的目录 ID

  // 构建目录树
  unordered_map<int, vector<int> > children; // 存储每个目录的子目录
  unordered_set<int> all_ids;                // 存储所有目录的 ID

  for (auto& relation : relations) {
    int child_id = relation.first;
    int parent_id = relation.second;
    children[parent_id].push_back(child_id); // 添加子目录
    all_ids.insert(child_id);                // 记录所有目录 ID
    all_ids.insert(parent_id);
  }

  // 标记待删除的目录及其子目录
  unordered_set<int> to_delete;
  dfs(delete_id, children, to_delete);

  // 收集剩余的目录 ID
  vector<int> remaining;
  for (int id : all_ids) {
    // 如果目录未被标记为删除，并且不是根目录 0，则加入剩余列表
    if (to_delete.find(id) == to_delete.end() && id != 0) {
      remaining.push_back(id);
    }
  }

  // 排序并输出结果
  sort(remaining.begin(), remaining.end());
  for (size_t i = 0; i < remaining.size(); ++i) {
    cout << remaining[i];
    if (i != remaining.size() - 1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;
}
```

## 并查集

### 100 分

#### We Are A Team

**题目描述**：

总共有 n 个人在机房，每个人有一个标号（1<=标号<=n），他们分成了多个团队，需要你根据收到的 m 条消息判定指定的两个人是否在一个团队中，具体的：

消息构成为 a b c，整数 a、b 分别代表两个人的标号，整数 c 代表指令

c == 0 代表 a 和 b 在一个团队内

c == 1 代表需要判定 a 和 b 的关系，如果 a 和 b 是一个团队，输出一行’we are a team’,如果不是，输出一行’we are not a team’

c 为其他值，或当前行 a 或 b 超出 1~n 的范围，输出‘da pian zi’

**输入描述**：

第一行包含两个整数 n，m(1<=n,m<100000),分别表示有 n 个人和 m 条消息

随后的 m 行，每行一条消息，消息格式为：a b c(1<=a,b<=n,0<=c<=1)

**输出描述**：

c ==1,根据 a 和 b 是否在一个团队中输出一行字符串，在一个团队中输出‘we are a team‘,不在一个团队中输出’we are not a team’

c 为其他值，或当前行 a 或 b 的标号小于 1 或者大于 n 时，输出字符串‘da pian zi‘

如果第一行 n 和 m 的值超出约定的范围时，输出字符串”NULL“。

**用例 1**：

输入：

```
5 7
1 2 0
4 5 0
2 3 0
1 2 1
2 3 1
4 5 1
1 5 1
```

输出：

```
we are a team
we are a team
we are a team
we are not a team
```

**用例 2**：

输入：

```
5 6
1 2 0
1 2 1
1 5 0
2 3 1
2 5 1
1 3 2
```

输出：

```
we are a team
we are not a team
we are a team
da pian zi
```

难度：中等

标签：并查集、图、动态规划

```cpp
#include <bits/stdc++.h>

using namespace std;

class UnionFind {
  private:
  vector<int> parent;

  public:
  UnionFind(int n) {
    parent.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
      parent[i] = i;  // 初始化每个节点的父节点为自己
    }
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);  // 路径压缩
    }
    return parent[x];
  }

  void unite(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);
    if (root_x != root_y) {
      parent[root_x] = root_y;  // 合并两个集合
    }
  }

  bool is_connected(int x, int y) {
    return find(x) == find(y);  // 判断是否在同一个集合
  }
};

int main() {
  int n, m;
  cin >> n >> m;

  // 检查 n 和 m 的范围
  if (n < 1 || n >= 100000 || m < 1 || m >= 100000) {
    cout << "NULL" << endl;
    return 0;
  }

  UnionFind uf(n);  // 初始化并查集

  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;

    // 检查 a 和 b 的范围
    if (a < 1 || a > n || b < 1 || b > n) {
      cout << "da pian zi" << endl;
      continue;
    }

    if (c == 0) {
      uf.unite(a, b);  // 合并 a 和 b
    } else if (c == 1) {
      if (uf.is_connected(a, b)) {
        cout << "we are a team" << endl;
      } else {
        cout << "we are not a team" << endl;
      }
    } else {
      cout << "da pian zi" << endl;
    }
  }

  return 0;
}
```

### 200 分

#### 字符串化繁为简

**题目描述**：

给定一个输入字符串，字符串只可能由英文字母（ 'a' ~ 'z'、'A' ~ 'Z' ）和左右小括号（ '('、')' ）组成。

当字符里存在小括号时，小括号是成对的，可以有一个或多个小括号对，小括号对不会嵌套，小括号对内可以包含 1 个或多个英文字母，也可以不包含英文字母。

当小括号对内包含多个英文字母时，这些字母之间是相互等效的关系，而且等效关系可以在不同的小括号对之间传递，即当存在 'a' 和 'b' 等效和存在 'b' 和 'c' 等效时，'a' 和 'c' 也等效，另外，同一个英文字母的大写字母和小写字母也相互等效（即使它们分布在不同的括号对里）

需要对这个输入字符串做简化，输出一个新的字符串，输出字符串里只需保留输入字符串里的没有被小括号对包含的字符（按照输入字符串里的字符顺序），并将每个字符替换为在小括号对里包含的且字典序最小的等效字符。

如果简化后的字符串为空，请输出为"0"。

示例 : 输入字符串为"never(dont)give(run)up(f)()"，初始等效字符集合为('d', 'o', 'n', 't')、('r', 'u', 'n')，由于等效关系可以传递，因此最终等效字符集合为('d', 'o', 'n', 't', 'r', 'u')，将输入字符串里的剩余部分按字典序最小的等效字符替换后得到"devedgivedp"

**输入描述**：

input_string

输入为 1 行，代表输入字符串

输入字符串的长度在 1~100000 之间

**输出描述**：

output_string

输出为 1 行，代表输出字符串

**用例 1**：

输入：

```
()abd
```

输出：

```
abd
```

说明：输入字符串里没有被小括号包含的子字符串为"abd"，其中每个字符没有等效字符，输出为"abd"

**用例 2**：

输入：

```
(abd)demand(fb)()for
```

输出：

```
aemanaaor
```

说明：等效字符集为('a', 'b', 'd', 'f')，输入字符串里没有被小括号包含的子字符串集合为'demandfor"，将其中字符替换为字典序最小的等效字符后输出为："aemanaaor"

**用例 2**：

输入：

```
(abd)demand(fb)()for
```

输出：

```
aemanaaor
```

说明：等效字符集为('a', 'b', 'd', 'f')，输入字符串里没有被小括号包含的子字符串集合为'demandfor"，将其中字符替换为字典序最小的等效字符后输出为："aemanaaor"

**用例 3**：

输入：

```
()happy(xyz)new(wxy)year(t)
```

输出：

```
happwnewwear
```

说明：等效字符集为(‘x’, 'y', 'z', 'w')，输入字符串里没有被小括号包含的子字符串集合为"happynewyear"，将其中字符替换为字典序最小的等效字符后输出为："happwnewwear"

**用例 4**：

输入：

```
()abcdefgAC(a)(Ab)(C)
```

输出：

```
AAcdefgAC
```

说明：等效字符集为('a', 'A', 'b')，输入字符里没有被小括号包含的子字符串集合为"abcdefgAC"，将其中字符替换为字典序最小的等效字符后输出为："AAcdefgAC"

难度：困难

标签：并查集、字符串、贪心、哈希表、图

```cpp
#include <bits/stdc++.h>

using namespace std;

// 并查集实现
class UnionFindSet {
public:
    vector<int> parent;  // 存储每个字符的父节点

    // 构造函数，初始化并查集
    explicit UnionFindSet(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;  // 每个节点的初始父节点为自己
        }
    }

    // 查找父节点，并进行路径压缩
    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);  // 路径压缩
        }
        return parent[x];
    }

    // 合并两个节点
    void merge(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        // 保证字典序较小的字符作为根
        if (root_x < root_y) {
            parent[root_y] = root_x;
        } else {
            parent[root_x] = root_y;
        }
    }
};

int main() {
    string input;  // 输入字符串
    cin >> input;

    vector<char> main_chars;  // 主体字符容器
    vector<char> eq_chars;  // 等效字符容器
    UnionFindSet ufs(128);  // 并查集，支持 ASCII 字符
    set<int> char_set;  // 记录已出现的字符

    bool in_parentheses = false;  // 标志是否在括号内

    // 遍历输入字符串
    for (char c : input) {
        if (c == '(') {
            in_parentheses = true;  // 开始收集等效字符
            eq_chars.clear();  // 清空等效字符容器
        } else if (c == ')') {
            in_parentheses = false;  // 括号结束

            if (!eq_chars.empty()) {
                // 处理括号内字符的合并
                int base = eq_chars[0];  // 括号内第一个字符作为基础
                for (char letter : eq_chars) {
                    ufs.merge(letter, base);  // 合并所有等效字符
                    char_set.insert(letter);  // 将当前字符加入集合
                }

                // 处理字符之间的法则
                for (const char letter : eq_chars) {
                    int lower = tolower(letter);  // 获取小写字符
                    int upper = toupper(letter);  // 获取大写字符

                    // 如果之前出现过小写或大写字符，进行合并
                    if (char_set.count(lower)) {
                        ufs.merge(letter, lower);
                    }
                    if (char_set.count(upper)) {
                        ufs.merge(letter, upper);
                    }
                }
            }
        } else {
            if (in_parentheses) {
                eq_chars.emplace_back(c);  // 收集等效字符
            } else {
                main_chars.emplace_back(c);  // 收集主体字符
            }
        }
    }

    // 替换等效字符
    for (char &c : main_chars) {
        c = static_cast<char>(ufs.find(c));  // 替换为等效的字典序最小的字符
    }

    // 输出结果
    if (main_chars.empty()) {
        cout << "0" << endl;  // 如果结果为空，输出 "0"
    } else {
        string result(main_chars.begin(), main_chars.end());
        cout << result << endl;  // 输出简化后的字符串
    }

    return 0;
}
```

#### 服务器广播

**题目描述**：

服务器连接方式包括直接相连，间接相连。A 和 B 直接连接，B 和 C 直接连接，则 A 和 C 间接连接。直接连接和间接连接都可以发送广播。

给出一个 N \* N 数组，代表 N 个服务器，

matrix[i][j] == 1，则代表 i 和 j 直接连接；不等于 1 时，代表 i 和 j 不直接连接。

matrix[i][i] == 1, 即自己和自己直接连接。

matrix[i][j] == matrix[j][i]。

计算初始需要给几台服务器广播，才可以使每个服务器都收到广播。

**输入描述**：

输入为 N 行，每行有 N 个数字，为 0 或 1，由空格分隔，构成 N\*N 的数组，N 的范围为 1 <= N <= 40

**输出描述**：

输出一个数字，为需要广播的服务器的数量

**用例 1**：

输入：

```
1 0 0
0 1 0
0 0 1
```

输出：

```
3
```

说明：3 台服务器互不连接，所以需要分别广播这 3 台服务器

**用例 2**：

输入：

```
1 1
1 1
```

输出：

```
1
```

说明：2 台服务器互相连接，所以只需要广播其中一台服务器

难度：中等

标签：并查集、图、矩阵

```cpp
#include <bits/stdc++.h>

using namespace std;

// 并查集类
class UnionFindSet {
  private:
    vector<int> parent_; // 父节点数组
    vector<int> rank_;   // 秩（用于优化合并操作）

  public:
    // 构造函数，初始化并查集
    explicit UnionFindSet(int n) {
      parent_.resize(n);
      rank_.resize(n, 0);
      for (int i = 0; i < n; i++) {
        parent_[i] = i; // 初始时每个节点的父节点是自己
      }
    }

    // 查找根节点，使用路径压缩优化
    int find(int x) {
      if (parent_[x] != x) {
        parent_[x] = find(parent_[x]);
      }
      return parent_[x];
    }

    // 合并两个集合
    void merge(int x, int y) {
      int root_x = find(x);
      int root_y = find(y);

      if (root_x == root_y)
        return; // 已经在同一个集合

      // 按秩合并，降低树的高度
      if (rank_[root_x] < rank_[root_y]) {
        parent_[root_x] = root_y;
      } else if (rank_[root_x] > rank_[root_y]) {
        parent_[root_y] = root_x;
      } else {
        parent_[root_y] = root_x;
        rank_[root_x]++;
      }
    }

    // 判断两个节点是否属于同一个集合
    bool is_same_set(int x, int y) {
      return find(x) == find(y);
    }

    // 获取集合数量
    int get_set_count(int n) {
      unordered_set<int> roots;
      for (int i = 0; i < n; i++) {
        roots.insert(find(i));
      }
      return roots.size();
    }
};

int main() {
  vector<vector<int> > matrix;

  // 读取输入
  while (cin) {
    string line;
    getline(cin, line);

    // 如果输入为空，则退出
    if (line.empty())
      break;

    // 解析输入行
    vector<int> row;
    stringstream ss(line);
    int num;
    while (ss >> num) {
      row.push_back(num);
    }

    // 检查是否为方阵
    if (!matrix.empty() && row.size() != matrix[0].size()) {
      break;
    }

    matrix.push_back(row);
  }

  int n = matrix.size(); // 服务器数量

  // 创建并查集
  UnionFindSet ufs(n);

  // 合并直接连接的服务器
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] == 1) {
        ufs.merge(i, j);
      }
    }
  }

  // 计算需要广播的服务器数量（集合的数量）
  int broadcast_count = ufs.get_set_count(n);
  cout << broadcast_count << endl;

  return 0;
}
```

#### 机器人活动区域

**题目描述**：

现有一个机器人，可放置于 M × N 的网格中任意位置，每个网格包含一个非负整数编号，当相邻网格的数字编号差值的绝对值小于等于 1 时，机器人可以在网格间移动。

**问题：** 求机器人可活动的最大范围对应的网格点数目。

**说明：**

1. 网格左上角坐标为 (0,0) ,右下角坐标为(m−1,n−1)
2. 机器人只能在相邻网格间上下左右移动

---

示例 1 输入如下网格

![img](https://hydro.ac/d/HWOD2023/p/25/file/-ssEqOdhswJ82UpxgNcu6.png)

输出：6

说明：图中绿色区域，相邻网格差值绝对值都小于等于 1，且为最大区域，对应网格点数目为 6

---

示例 2 输入如下网格

![img](https://hydro.ac/d/HWOD2023/p/25/file/gXy1IIbeH3Dn8-K4U_EuH.png)

输出：1

说明：任意两个相邻网格的差值绝对值都大于 1，机器人不能在网格间移动，只能在单个网格内活动，对应网格点数目为 1

**输入描述**：

第 1 行输入为 M 和 N

- M 表示网格的行数
- N 表示网格的列数

之后 M 行表示网格数值，每行 N 个数值（数值大小用 k 表示），数值间用单个空格分隔，行首行尾无多余空格。

- M、 N、 k 均为整数
- 1 ≤ M,N ≤ 150
- 0 ≤ k ≤ 50

**输出描述**：

输出 1 行，包含 1 个数字，表示最大活动区域的网格点数目，

行首行尾无**多余空格。**

**用例 1**：

输入：

```
4 4
1 2 5 2
2 4 4 5
3 5 7 1
4 6 2 4
```

输出：

```
6
```

说明：见描述中示例1，最大区域对应网格点数目为6

**用例 2**：

输入：

```
2 3
1 3 5
4 1 3
```

输出：

```
1
```

说明：见描述中示例2，最大区域对应网格点数目为1

难度：中等

标签：深度优先搜索、广度优先搜索、图、矩阵、并查集

```cpp
#include <bits/stdc++.h>
using namespace std;
// 四个方向：上、下、左、右
vector<pair<int, int> > directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// DFS遍历可达区域
int dfs(int x, int y, vector<vector<int> >& grid,
        vector<vector<bool> >& visited) {
  visited[x][y] = true; // 标记当前网格为已访问
  int area = 1;         // 统计当前网格
  // 遍历四个方向
  for (auto dir : directions) {
    int new_x = x + dir.first;
    int new_y = y + dir.second;
    // 检查边界条件和可移动条件
    if (new_x >= 0 && new_x < grid.size() &&
        new_y >= 0 && new_y < grid[0].size() &&
        !visited[new_x][new_y] &&
        abs(grid[new_x][new_y] - grid[x][y]) <= 1) {
      area += dfs(new_x, new_y, grid, visited); // 递归查找
    }
  }
  return area; // 返回当前可活动区域大小
}

int main() {
  int m, n;
  cin >> m >> n;
  vector<vector<int> > grid(m, vector<int>(n));
  // 输入网格
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> grid[i][j];
    }
  }
  vector<vector<bool> > visited(m, vector<bool>(n, false)); // 记录访问状态
  int max_area = 0;                                         // 记录最大活动区域
  // 遍历每个网格
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (!visited[i][j]) {
        // 只处理未访问的网格
        int area = dfs(i, j, grid, visited); // 计算当前网格的区域大小
        max_area = max(max_area, area);      // 更新最大区域
      }
    }
  }
  // 输出最大活动区域的网格点数目
  cout << max_area << endl;
  return 0;
}
```

#### Linux发行版的数量

**题目描述**：

Linux操作系统有多个发行版，distrowatch.com提供了各个发行版的资料。这些发行版互相存在关联，例如Ubuntu基于Debian开发，而Mint又基于Ubuntu开发，那么我们认为Mint同Debian也存在关联。

发行版集是一个或多个相关存在关联的操作系统发行版，集合内不包含没有关联的发行版。

给你一个 n * n 的矩阵 isConnected，其中 isConnected[i][j] = 1 表示第 i 个发行版和第 j 个发行版直接关联，而 isConnected[i][j] = 0 表示二者不直接相连。

返回最大的发行版集中发行版的数量。

**输入描述**：

第一行输入发行版的总数量N，

之后每行表示各发行版间是否直接相关

1 ≤ N ≤ 200

**输出描述**：

输出最大的发行版集中发行版的数量

**用例 1**：

输入：

```
4
1 1 0 0
1 1 1 0
0 1 1 0
0 0 0 1
```

输出：

```
3
```

说明：

Debian(1)和Unbuntu2)相关

Mint(3)和Ubuntu(2)相关，

EeulerOS(4)和另外三个都不相关，

所以存在两个发行版集，发行版集中发行版的数量分别是3和1，所以输出3。

难度：中等

标签：深度优先搜索、广度优先搜索、图、矩阵、并查集

```cpp
#include <bits/stdc++.h>

using namespace std;

void dfs(int node, vector<vector<int> >& is_connected, vector<bool>& visited) {
  visited[node] = true; // 标记当前节点为已访问  
  for (int i = 0; i < is_connected.size(); i++) {
    if (is_connected[node][i] == 1 && !visited[i]) {
      // 如果有连接且未访问  
      dfs(i, is_connected, visited); // 递归访问连接的节点  
    }
  }
}

int main() {
  int n;
  cin >> n;                                            // 输入发行版数量  
  vector<vector<int> > is_connected(n, vector<int>(n)); // 创建邻接矩阵  

  // 输入邻接矩阵  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> is_connected[i][j];
    }
  }

  vector<bool> visited(n, false); // 访问状态数组  
  int max_count = 0;              // 记录最大的连通分量  

  // 遍历所有节点  
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      // 仅当节点未访问时进行 DFS  
      int count = 0; // 当前连通分量的大小  
      dfs(i, is_connected, visited);
      for (int j = 0; j < n; j++) {
        if (visited[j]) {
          count++; // 统计当前连通分量大小  
        }
      }
      max_count = max(max_count, count);           // 更新最大连通分量  
      fill(visited.begin(), visited.end(), false); // 重置访问状态  
    }
  }

  // 输出结果  
  cout << max_count << endl;

  return 0;
}
```

## 优先队列

**题目描述**：

**输入描述**：

**输出描述**：

**用例 1**：

输入：

```

```

输出：

```

```

说明：

**用例 2**：

输入：

```

```

输出：

```

```

说明：
