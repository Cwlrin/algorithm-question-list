#include <bits/stdc++.h>
using namespace std;

int main() {
  // 读取依赖关系列表
  string dependencies;
  getline(cin, dependencies);

  // 读取故障服务列表
  string faults;
  getline(cin, faults);

  // 解析故障服务列表
  unordered_set<string> fault_set;
  stringstream fault_stream(faults);
  string fault;
  while (getline(fault_stream, fault, ',')) {
    fault_set.insert(fault);
  }

  // 解析依赖关系列表并构建图
  unordered_map<string, vector<string> > graph;
  unordered_set<string> services; // 所有服务
  stringstream dep_stream(dependencies);
  string dep;
  while (getline(dep_stream, dep, ',')) {
    size_t split_pos = dep.find('-');
    string service1 = dep.substr(0, split_pos);
    string service2 = dep.substr(split_pos + 1);
    graph[service2].push_back(service1); // service1 依赖 service2
    services.insert(service1);
    services.insert(service2);
  }

  // BFS 遍历所有不可用服务
  unordered_set<string> unavailable_set;
  queue<string> q;
  for (const string& fault : fault_set) {
    q.push(fault);
    unavailable_set.insert(fault);
  }

  while (!q.empty()) {
    string current = q.front();
    q.pop();
    for (const string& dependent : graph[current]) {
      if (unavailable_set.find(dependent) == unavailable_set.end()) {
        unavailable_set.insert(dependent);
        q.push(dependent);
      }
    }
  }

  // 收集可用服务
  vector<string> available_services;
  for (const string& service : services) {
    if (unavailable_set.find(service) == unavailable_set.end()) {
      available_services.push_back(service);
    }
  }

  // 按依赖关系列表中的顺序排序
  unordered_map<string, int> service_order;
  stringstream dep_stream2(dependencies);
  int order = 0;
  while (getline(dep_stream2, dep, ',')) {
    string service1 = dep.substr(0, dep.find('-'));
    string service2 = dep.substr(dep.find('-') + 1);
    if (service_order.find(service1) == service_order.end()) {
      service_order[service1] = order++;
    }
    if (service_order.find(service2) == service_order.end()) {
      service_order[service2] = order++;
    }
  }
  sort(available_services.begin(), available_services.end(),
       [&service_order](const string& a, const string& b) {
         return service_order[a] < service_order[b];
       });

  // 输出结果
  if (available_services.empty()) {
    cout << "," << endl;
  } else {
    for (size_t i = 0; i < available_services.size(); ++i) {
      if (i > 0) {
        cout << ",";
      }
      cout << available_services[i];
    }
    cout << endl;
  }

  return 0;
}