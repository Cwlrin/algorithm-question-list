#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

int main() {
  string memory_pool_input, request_input;

  // 读取内存池和申请列表
  getline(cin, memory_pool_input);
  getline(cin, request_input);

  // 存储内存池资源
  map<int, int> memory_pool; // 粒度 -> 数量

  // 解析内存池字符串
  stringstream ss(memory_pool_input);
  string token;
  while (getline(ss, token, ',')) {
    size_t colon_pos = token.find(':');
    // 获取粒度大小和数量
    int size = stoi(token.substr(0, colon_pos));      // 粒度大小
    int quantity = stoi(token.substr(colon_pos + 1)); // 数量
    memory_pool[size] += quantity;                    // 将相同大小的内存合并
  }

  // 解析申请并处理
  vector<string> request_results; // 存储申请结果
  stringstream ss_requests(request_input);

  while (getline(ss_requests, token, ',')) {
    // 确保申请的格式有效，跳过空值
    if (token.empty()) {
      continue; // 忽略空申请
    }

    int request_size = stoi(token); // 当前申请的内存大小
    bool allocated = false;

    // 查找合适的内存资源
    for (auto it = memory_pool.lower_bound(request_size);
         it != memory_pool.end();
         ++it) {
      if (it->second > 0) {
        // 找到满足要求的粒度
        it->second--;     // 执行资源分配
        allocated = true; // 申请成功
        request_results.emplace_back("true");
        break; // 处理完当前申请，跳出循环
      }
    }

    // 如果没有可用资源
    if (!allocated) {
      request_results.emplace_back("false");
    }
  }

  // 输出结果
  for (size_t i = 0; i < request_results.size(); ++i) {
    cout << request_results[i];
    if (i < request_results.size() - 1) {
      cout << ","; // 输出逗号分隔
    }
  }
  cout << endl;

  return 0;
}