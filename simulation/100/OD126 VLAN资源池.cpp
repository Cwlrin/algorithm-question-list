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