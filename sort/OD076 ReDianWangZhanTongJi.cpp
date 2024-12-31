// OD076. 热点网站统计
// 题目描述：
// 企业路由器的统计页面，有一个功能需要动态统计公司访问最多的网页 URL top N。
// 请设计一个算法，可以高效动态统计 Top N 的页面。
// 输入描述：
// 每一行都是一个 URL 或一个数字，如果是 URL，代表一段时间内的网页访问； 如果是一个数字 N，代表本次需要输出的 Top N 个 URL。
// 输入约束：
// 1. 总访问网页数量小于 5000 个，单网页访问次数小于 65535 次；
// 2. 网页 URL 仅由字母，数字和点分隔符组成，且长度小于等于 127 字节；
// 3. 数字是正整数，小于等于 10 且小于当前总访问网页数；
// 输出描述：
// 每行输入要对应一行输出，输出按访问次数排序的前 N 个 URL，用逗号分隔。
// 输出要求：
// 1. 每次输出要统计之前所有输入，不仅是本次输入；
// 2. 如果有访问次数相等的 URL，按 URL 的字符串字典序升序排列，输出排序靠前的 URL；
// 用例 1：
// 输入：
// news.qq.com
// news.sina.com.cn
// news.qq.com
// news.qq.com
// game.163.com
// game.163.com
// www.huawei.com
// www.cctv.com
// 3
// www.huawei.com
// www.cctv.com
// www.huawei.com
// www.cctv.com
// www.huawei.com
// www.cctv.com
// www.huawei.com
// www.cctv.com
// www.huawei.com
// 3
// 输出：
// news.qq.com,game.163.com,news.sina.com.cn
// www.huawei.com,www.cctv.com,news.qq.com
// 用例 2：
// 输入：
// news.qq.com
// www.cctv.com
// 1
// www.huawei.com
// www.huawei.com
// 输出：
// news.qq.com
// www.huawei.com,news.qq.com
// www.huawei.com,news.qq.com,www.cctv.com
// 难度：中等
// 标签：哈希、排序、堆

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