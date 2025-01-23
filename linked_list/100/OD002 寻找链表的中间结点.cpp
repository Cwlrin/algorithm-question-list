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