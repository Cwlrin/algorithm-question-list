#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  // 定义数据结构  
  unordered_map<int, int> income;      // 代理商号 -> 收入  
  unordered_map<int, set<int> > fa_ch; // 父级代理商 -> 子级代理商集合  
  unordered_map<int, int> ch_fa;       // 子级代理商 -> 父级代理商  
  set<int> agents;                     // 所有代理商  

  // 读取输入  
  for (int i = 0; i < n; ++i) {
    int id, p, inc;
    cin >> id >> p >> inc;
    income[id] = inc;
    ch_fa[id] = p;
    fa_ch[p].insert(id);
    agents.insert(id);
    agents.insert(p);
  }

  // 找到顶级代理商（root）  
  int root = -1;
  for (int agent : agents) {
    if (ch_fa.find(agent) == ch_fa.end()) {
      root = agent;
      break;
    }
  }

  // 拓扑排序计算收入  
  unordered_map<int, int> total_income = income; // 初始化总收入  
  queue<int> q;
  for (int agent : agents) {
    if (fa_ch.find(agent) == fa_ch.end()) {
      // 叶子节点  
      q.push(agent);
    }
  }

  while (!q.empty()) {
    int agent = q.front();
    q.pop();
    if (ch_fa.find(agent) != ch_fa.end()) {
      int parent = ch_fa[agent];
      total_income[parent] += (total_income[agent] / 100) * 15; // 每100元抽15元  
      fa_ch[parent].erase(agent);                             // 移除已处理的子级  
      if (fa_ch[parent].empty()) {
        // 如果父级没有其他子级，加入队列  
        q.push(parent);
      }
    }
  }

  // 输出结果  
  cout << root << " " << total_income[root] << endl;

  return 0;
}