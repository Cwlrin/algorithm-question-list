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

    if (constraints[i] == "<=")
      satisfied = left_side <= target_values[i];
    else if (constraints[i] == "<")
      satisfied = left_side < target_values[i];
    else if (constraints[i] == ">=")
      satisfied = left_side >= target_values[i];
    else if (constraints[i] == ">")
      satisfied = left_side > target_values[i];
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