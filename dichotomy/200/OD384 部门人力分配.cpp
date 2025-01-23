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