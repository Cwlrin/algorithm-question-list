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