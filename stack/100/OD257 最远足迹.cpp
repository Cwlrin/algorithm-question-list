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