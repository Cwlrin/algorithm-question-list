#include <bits/stdc++.h>

using namespace std;

class DirectoryManager {
  stack<string> path_;
  unordered_map<string, unordered_set<string> > directory_structure_;

  public:
    DirectoryManager() {
      path_.emplace("/");
      directory_structure_["/"] = unordered_set<string>();
    }

    void mkdir(const string& dir_name) {
      string current_path = path_.top();
      if (directory_structure_[current_path].find(dir_name) ==
          directory_structure_[
            current_path].end()) {
        directory_structure_[current_path].insert(dir_name);
        directory_structure_[dir_name] = unordered_set<string>();
        // 初始化子目录
      }
    }

    void cd(const string& dir_name) {
      if (dir_name == "..") {
        if (path_.size() > 1) {
          path_.pop();
        }
      } else {
        string current_path = path_.top();
        if (directory_structure_[current_path].find(dir_name) !=
            directory_structure_[
              current_path].end()) {
          path_.push(dir_name);
        }
      }
    }

    string pwd() {
      string result;
      stack<string> temp = path_;
      vector<string> dirs;
      while (!temp.empty()) {
        dirs.push_back(temp.top());
        temp.pop();
      }
      for (int i = dirs.size() - 1; i >= 0; --i) {
        if (dirs[i] == "/") {
          result += "/";
        } else {
          result += dirs[i] + "/";
        }
      }
      return result.empty() ? "/" : result;
    }
};

int main() {
  DirectoryManager dm;
  string line;
  string last_output = "/"; // 默认初始路径为 "/"

  while (getline(cin, line)) {
    if (line.empty())
      break; // 处理空行

    stringstream ss(line);
    string command;
    ss >> command;

    if (command == "mkdir") {
      string dir_name;
      ss >> dir_name;
      dm.mkdir(dir_name);
    } else if (command == "cd") {
      string dir_name;
      ss >> dir_name;
      dm.cd(dir_name);
    } else if (command == "pwd") {
      last_output = dm.pwd();
    }
  }

  cout << last_output << endl;

  return 0;
}