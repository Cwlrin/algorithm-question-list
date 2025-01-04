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
    // if (countMap.find(arr[i]) == countMap.end())
    if (!count_map.contains(arr[i])) {
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
  ranges::sort(sorted_arr, [](const auto& a, const auto& b) {
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

**输入描述 **：

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
  ranges::sort(sorted_chars, [](const auto& a, const auto& b) {
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

**题目描述 **：

现有两门选修课，每门选修课都有一部分学生选修，每个学生都有选修课的成绩，需要你找出同时选修了两门选修课的学生，先按照班级进行划分，班级编号小的先输出，每个班级按照两门选修课成绩和的降序排序，成绩相同时按照学生的学号升序排序。

**输入描述 **：

第一行为第一门选修课学生的成绩，

第二行为第二门选修课学生的成绩，

每行数据中学生之间以英文分号分隔，每个学生的学号和成绩以英文逗号分隔，

学生学号的格式为 8 位数字

> 2 位院系编号 + 入学年份后 2 位 + 院系内部 1 位专业编号 + 所在班级 3 位学号

学生成绩的取值范围为 [0,100] 之间的整数，

两门选修课选修学生数的取值范围为 [1-2000] 之间的整数。

**输出描述 **：

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
    if (scores2.contains(id)) {
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
```



#### 热点网站统计

**题目描述 **：

企业路由器的统计页面，有一个功能需要动态统计公司访问最多的网页 URL top N。

请设计一个算法，可以高效动态统计 Top N 的页面。

**输入描述 **：

每一行都是一个 URL 或一个数字，如果是 URL，代表一段时间内的网页访问； 如果是一个数字 N，代表本次需要输出的 Top N 个 URL。

输入约束：

1. 总访问网页数量小于 5000 个，单网页访问次数小于 65535 次；
2. 网页 URL 仅由字母，数字和点分隔符组成，且长度小于等于 127 字节；
3. 数字是正整数，小于等于 10 且小于当前总访问网页数；

**输出描述 **：

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
      ranges::sort(url_list, [](const auto& a, const auto& b) {
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

**题目描述 **：

磁盘的容量单位常用的有 M，G，T 这三个等级，

它们之间的换算关系为 1T = 1024G，1G = 1024M，

现在给定 n 块磁盘的容量，请对它们按从小到大的顺序进行稳定排序，

例如给定 5 块盘的容量，1T，20M，3G，10G6T，3M12G9M

排序后的结果为 20M，3G，3M12G9M，1T，10G6T。

注意单位可以重复出现，上述 3M12G9M 表示的容量即为 3M+12G+9M，和 12M12G 相等。

**输入描述 **：

输入第一行包含一个整数 n(2 <= n <= 100)，表示磁盘的个数，

接下的 n 行，每行一个字符串 (长度大于 2，小于 30)，

表示磁盘的容量，由一个或多个格式为 mv 的子串组成，

其中 m 表示容量大小，v 表示容量单位，例如 20M，1T，30G，10G6T，3M12G9M。

磁盘容量 m 的范围为 1 到 1024 的正整数，

容量单位 v 的范围只包含题目中提到的 M，G，T 三种，换算关系如题目描述。

**输出描述 **：

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
  for (size_t i = 0; i < s.size(); i++) {
    if (isdigit(s[i])) {
      num = num * 10 + (s[i] - '0'); // 累计数字
    } else {
      // 根据单位累加总容量
      if (s[i] == 'M') {
        total += num;
      } else if (s[i] == 'G') {
        total += num * 1024LL;
      } else if (s[i] == 'T') {
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
  ranges::stable_sort(disks, [](const auto& a, const auto& b) {
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

**题目描述 **：

公司某部门软件教导团正在组织新员工每日打卡学习活动，他们开展这项学习活动已经一个月了，所以想统计下这个月优秀的打卡员工。每个员工会对应一个 id，每天的打卡记录记录当天打卡员工的 id 集合，一共 30 天。

请你实现代码帮助统计出打卡次数 top5 的员工。加入打卡次数相同，将较早参与打卡的员工排在前面，如果开始参与打卡的时间还是一样，将 id 较小的员工排在前面。

注：不考虑并列的情况，按规则返回前 5 名员工的 id 即可，如果当月打卡的员工少于 5 个，按规则排序返回所有有打卡记录的员工 id。

**输入描述 **：

第一行输入为新员工数量 N，表示新员工编号 id 为 0 到 N-1，N 的范围为 [1,100]

第二行输入为 30 个整数，表示每天打卡的员工数量，每天至少有 1 名员工打卡。

之后 30 行为每天打卡的员工 id 集合，id 不会重复。

**输出描述 **：

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
      if (!stats.contains(id)) {
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

  ranges::sort(employees, [](const auto& a, const auto& b) {
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

**题目描述 **：

给定一个整型数组，请从该数组中选择 3 个元素组成最小数字并输出

（如果数组长度小于 3，则选择数组中所有元素来组成最小数字）。

**输入描述 **：

一行用半角逗号分割的字符串记录的整型数组，0 < 数组长度 <= 100，0 < 整数的取值范围 <= 10000。

**输出描述 **：

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

  ranges::sort(numbers, [](const auto& a, const auto& b) {
    return stoi(a) < stoi(b);
  });

  if (numbers.size() > 3) {
    numbers.resize(3);
  }

  ranges::sort(numbers, [](const auto& a, const auto& b) {
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

**输出描述 **：

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

  ranges::stable_sort(logs, [](const auto& a, const auto& b) {
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

**输入描述 **：

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

**输出描述 **：

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

矩阵代表是 4*5，每个数字是选手的编号，每一行代表一个评委对选手的打分排序，

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
  set unique_chars2(input2.begin(), input2.end());
  int target_count = unique_chars2.size();

  // 使用正则表达式分割字符串，提取仅含有字母的有效子串
  const regex non_letter_pattern("[0-9a-f]+");
  sregex_token_iterator it(input1.begin(), input1.end(), non_letter_pattern,
                           -1);
  sregex_token_iterator end;

  vector<string> vaild_substrings;
  for (; it != end; ++it) {
    // 移除空串
    if (string substring = it->str(); !substring.empty()) {
      vaild_substrings.push_back(substring);
    }
  }

  string best_substring = "Not Found";
  int best_count = -1;

  // 遍历有效子串
  for (const string& substring : vaild_substrings) {
    // 计算当前子串中不同字母的数量
    set unique_chars(substring.begin(), substring.end());
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

  ranges::sort(nums, [](const string& a, const string& b) {
    return a + b > b + a;
  });

  string result;
  for (const string& n : nums) {
    result += n;
  }

  // 处理边界情况
  if (result[0] == '0') {
    cout << "0" << endl;  // 如果最高位是 0，则结果是 0
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

难度：中等

标签：数组

#### 敏感字段加密

**题目描述**：

给定一个由多个命令字组成的命令字符串：

1. 字符串长度小于等于 127 字节，只包含大小写字母，数字，下划线和偶数个双引号；
2. 命令字之间以一个或多个下划线_进行分割；
3. 可以通过两个双引号 "" 来标识包含下划线_的命令字或空命令字（仅包含两个双引号的命令字），双引号不会在命令字内部出现；

请对指定索引的敏感字段进行加密，替换为 \*\*\*\*\*\*（6 个 \*），并删除命令字前后多余的下划线 _。 如果无法找到指定索引的命令字，输出字符串 ERROR。

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

4. 一个 App 可以在一天内注册多个时段 ![image](https://hydro.ac/d/HWOD2023/p/413/file/0uizC1CHqpz3kBQECPU21.png)

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

#### 英文输入法

**题目描述**：

主管期望你来实现英文输入法单词联想功能。

需求如下：

- 依据用户输入的单词前缀，从已输入的英文语句中联想出用户想输入的单词，按字典序输出联想到的单词序列，
- 如果联想不到，请输出用户输入的单词前缀。

注意：

1. 英文单词联想时，区分大小写
2. 缩略形式如”don’t”，判定为两个单词，”don”和”t "
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

从用户已输入英文语句”I love you”中提炼出“I”、“love”、“you”三个单词，接下来用户输入“He”，

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

根据考勤数据字符串，如果能得到考勤奖，输出”true”；否则输出”false”。

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

0 < k <= array1.size() * array2.size()

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



此样例有多种组合满足两回合跳到最后，譬如：[-1,9]，[2,6]，其中 [-1,9] 的索引和为 0+3 = 3，[2,6] 的索和为 1+4 = 5，所以索引和最小的步数组合 [-1,9]



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



#### 判断一组不等式是否满足约束并输出最大差



**题目描述**：

给定一组不等式，判断是否成立并输出不等式的最大差(输出浮点数的整数部分)

要求:

1. 不等式系数为 double 类型，是一个二维数组
2. 不等式的变量为 int 类型，是一维数组;
3. 不等式的目标值为 double 类型，是一维数组
4. 不等式约束为字符串数组，只能是:“>”,“>=”,“<”,“<=”,“=”，

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





#### 一种字符串压缩表示的解压

**题目描述**：

有一种简易压缩算法：针对全部由小写英文字母组成的字符串，将其中连续超过两个相同字母的部分压缩为连续个数加该字母，其他部分保持原样不变。

例如：字符串“aaabbccccd”经过压缩成为字符串“3abb4cd”。

请您编写解压函数，根据输入的字符串，判断其是否为合法压缩过的字符串，

若输入合法则输出解压缩后的字符串，否则输出字符串“! error”来报告错误。

**输入描述**：

输入一行，为一个 ASCII 字符串，长度不会超过 100 字符，用例保证输出的字符串长度也不会超过 100 字符。

**输出描述**：

若判断输入为合法的经过压缩后的字符串，则输出压缩前的字符串；

若输入不合法，则输出字符串 “**! error**”。

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

1 ≤ n ≤ 3 * 10^5。

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



#### 猜字谜

**题目描述**：

小王设计了一个简单的猜字谜游戏，游戏的谜面是一个错误的单词，比如 nesw，玩家需要猜出谜底库中正确的单词。猜中的要求如下： 对于某个谜面和谜底单词，满足下面任一条件都表示猜中：

1. 变换顺序以后一样的，比如通过变换 w 和 e 的顺序，“nwes”跟“news”是可以完全对应的；
2. 字母去重以后是一样的，比如“woood”和“wood”是一样的，它们去重后都是“wod”

请你写一个程序帮忙在谜底库中找到正确的谜底。谜面是多个单词，都需要找到对应的谜底，如果找不到的话，返回”not found”

**输入描述**：

1. 谜面单词列表，以“,”分隔
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

| CNY  | JPY  | HKD  | EUR  | GBP  |
| :--- | :--- | :--- | :--- | :--- |
| 100  | 1825 | 123  | 14   | 12   |

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

#### 螺旋数字矩阵

**题目描述**：

疫情期间，小明隔离在家，百无聊赖，在纸上写数字玩。他发明了一种写法：

给出数字个数 n （0 < n ≤ 999）和行数 m（0 < m ≤ 999），从左上角的 1 开始，按照顺时针螺旋向内写方式，依次写出 2,3,...., n，最终形成一个 m 行矩阵。

小明对这个矩阵有些要求：

1. 每行数字的个数一样多
2. 列的数量尽可能少
3. 填充数字时优先填充外部
4. 数字不够时，使用单个 * 号占位

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



说明：3 个数字写 5 行，只有一列，数字不够用*号填充

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

#### 学生方阵



**题目描述**：

学校组织活动，将学生排成一个矩形方阵。

请在矩形方阵中找到最大的位置相连的男生数量。

这个相连位置在一个直线上，方向可以是水平的，垂直的，成对角线的或者呈反对角线的。

注：学生个数不会超过 10000

**输入描述**：

输入的第一行为矩阵的行数和列数，接下来的 n 行为矩阵元素，元素间用”,”分隔。

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

输出元素列表，元素数量 = 窗口数量 * 窗口大小，元素之间以空格分隔，多个窗口合并为一个列表输出，参考样例：

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

#### 最优资源分配



**题目描述**：

某块业务芯片最小容量单位为 1.25G，总容量为 M*1.25G，对该芯片资源编号为 1，2，...，M。该芯片支持 3 种不同的配置，分别为 A、B、C。

- 配置 A：占用容量为 1.25 * 1 = 1.25G
- 配置 B：占用容量为 1.25 * 2 = 2.5G
- 配置 C：占用容量为 1.25 * 8 = 10G 某块板卡上集成了 N 块上述芯片，对芯片编号为 1，2，...，N，各个芯片之间彼此独立，不能跨芯片占用资源。

给定板卡上芯片数量 N、每块芯片容量 M、用户按次序配置后，请输出芯片资源占用情况，保证消耗的芯片数量最少。

资源分配规则：按照芯片编号从小到大分配所需资源，芯片上资源如果被占用标记为 1，没有被占用标记为 0.

用户配置序列：用户配置是按次序依次配置到芯片中，如果用户配置序列种某个配置超过了芯片总容量，丢弃该配置，继续遍历用户后续配置。

**输入描述**：

M：每块芯片容量为 M * 1.25G，取值范围为：1~256

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



## 数学

**题目描述**：



**输入描述**：



**输出描述**：



**用例 1**：

输入：

```
10 9
```

输出： 

```
910
```



说明：



**用例 2**：

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





