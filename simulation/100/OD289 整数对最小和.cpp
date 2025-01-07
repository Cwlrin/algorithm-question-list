#include <bits/stdc++.h>

using namespace std;

int main() {
  int size1, size2;
  cin >> size1;
  vector<int> array1(size1);
  for (int i = 0; i < size1; ++i) {
    cin >> array1[i];
  }
  cin >> size2;
  vector<int> array2(size2);
  for (int i = 0; i < size2; ++i) {
    cin >> array2[i];
  }
  int k;
  cin >> k;
  // 最小堆来存储元素对及其对应的和
  priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >
                 , greater<pair<int, pair<int, int> > > > min_heap;
  // 将所有可能的初始对放入堆中
  for (int i = 0; i < size1; ++i) {
    // 先将每个 array1 的元素与 array2 的第一个元素配对
    min_heap.push({array1[i] + array2[0], {i, 0}});
  }
  int min_sum = 0;
  // 取出 k 对
  for (int count = 0; count < k; ++count) {
    auto current_pair = min_heap.top();
    min_heap.pop();
    min_sum += current_pair.first; // 加上当前最小和
    int index1 = current_pair.second.first;
    int index2 = current_pair.second.second;
    // 如果当前对的第二个元素还有更多可能的配对，进行入堆
    if (index2 + 1 < size2) {
      min_heap.push({array1[index1] + array2[index2 + 1],
                     {index1, index2 + 1}});
    }
  }
  cout << min_sum << endl;
  return 0;
}