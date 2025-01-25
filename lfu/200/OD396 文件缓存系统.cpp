#include <iostream>
#include <unordered_map>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct FileInfo {
  int size;         // 文件大小
  int access_count; // 访问次数
  int last_access;  // 最近访问时间
};

int main() {
  int m, n;
  cin >> m >> n;

  unordered_map<string, FileInfo> file_map; // 文件名 -> 文件信息

  // 优先队列的比较逻辑
  auto compare = [](const pair<string, FileInfo>& a,
                    const pair<string, FileInfo>& b) {
    if (a.second.access_count == b.second.access_count) {
      return a.second.last_access > b.second.last_access; // 时间早的优先
    }
    return a.second.access_count > b.second.access_count; // 访问次数少的优先
  };

  priority_queue<pair<string, FileInfo>, vector<pair<string, FileInfo> >,
                 decltype(compare)> pq(compare); // 删除顺序

  int current_size = 0; // 当前缓存大小
  int time = 0;         // 时间戳

  for (int i = 0; i < n; ++i) {
    string op, file_name;
    cin >> op >> file_name;

    if (op == "put") {
      int file_size;
      cin >> file_size;

      // 如果文件已存在，直接跳过
      if (file_map.find(file_name) != file_map.end()) {
        continue; // 不改变当前缓存状态
      }

      // 如果缓存空间不足，则删除文件
      while (current_size + file_size > m && !pq.empty()) {
        auto top = pq.top();
        pq.pop();
        if (file_map.find(top.first) != file_map.end() &&
            file_map[top.first].access_count == top.second.access_count &&
            file_map[top.first].last_access == top.second.last_access) {
          current_size -= top.second.size;
          file_map.erase(top.first);
        }
      }

      // 如果缓存空间足够，则插入文件
      if (current_size + file_size <= m) {
        FileInfo info = {file_size, 0, time++};
        file_map[file_name] = info;
        pq.push({file_name, info});
        current_size += file_size;
      }
    } else if (op == "get") {
      if (file_map.find(file_name) != file_map.end()) {
        // 更新访问次数和最近访问时间
        file_map[file_name].access_count++;
        file_map[file_name].last_access = time++;
        // 重新插入文件以更新优先队列
        pq.push({file_name, file_map[file_name]});
      }
    }
  }

  // 输出缓存中的文件名
  if (file_map.empty()) {
    cout << "NONE" << endl;
  } else {
    set<string> sorted_files;
    for (const auto& entry : file_map) {
      sorted_files.insert(entry.first);
    }
    bool first = true;
    for (const auto& file : sorted_files) {
      if (!first) {
        cout << ",";
      }
      cout << file;
      first = false;
    }
    cout << endl;
  }

  return 0;
}