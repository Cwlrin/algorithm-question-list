#include <bits/stdc++.h>

using namespace std;

// 并查集实现
class UnionFindSet {
public:
    vector<int> parent;  // 存储每个字符的父节点

    // 构造函数，初始化并查集
    explicit UnionFindSet(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;  // 每个节点的初始父节点为自己
        }
    }

    // 查找父节点，并进行路径压缩
    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);  // 路径压缩
        }
        return parent[x];
    }

    // 合并两个节点
    void merge(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        // 保证字典序较小的字符作为根
        if (root_x < root_y) {
            parent[root_y] = root_x;
        } else {
            parent[root_x] = root_y;
        }
    }
};

int main() {
    string input;  // 输入字符串
    cin >> input;

    vector<char> main_chars;  // 主体字符容器
    vector<char> eq_chars;  // 等效字符容器
    UnionFindSet ufs(128);  // 并查集，支持 ASCII 字符
    set<int> char_set;  // 记录已出现的字符

    bool in_parentheses = false;  // 标志是否在括号内

    // 遍历输入字符串
    for (char c : input) {
        if (c == '(') {
            in_parentheses = true;  // 开始收集等效字符
            eq_chars.clear();  // 清空等效字符容器
        } else if (c == ')') {
            in_parentheses = false;  // 括号结束

            if (!eq_chars.empty()) {
                // 处理括号内字符的合并
                int base = eq_chars[0];  // 括号内第一个字符作为基础
                for (char letter : eq_chars) {
                    ufs.merge(letter, base);  // 合并所有等效字符
                    char_set.insert(letter);  // 将当前字符加入集合
                }

                // 处理字符之间的法则
                for (const char letter : eq_chars) {
                    int lower = tolower(letter);  // 获取小写字符
                    int upper = toupper(letter);  // 获取大写字符

                    // 如果之前出现过小写或大写字符，进行合并
                    if (char_set.count(lower)) {
                        ufs.merge(letter, lower);
                    }
                    if (char_set.count(upper)) {
                        ufs.merge(letter, upper);
                    }
                }
            }
        } else {
            if (in_parentheses) {
                eq_chars.emplace_back(c);  // 收集等效字符
            } else {
                main_chars.emplace_back(c);  // 收集主体字符
            }
        }
    }

    // 替换等效字符
    for (char &c : main_chars) {
        c = static_cast<char>(ufs.find(c));  // 替换为等效的字典序最小的字符
    }

    // 输出结果
    if (main_chars.empty()) {
        cout << "0" << endl;  // 如果结果为空，输出 "0"
    } else {
        string result(main_chars.begin(), main_chars.end());
        cout << result << endl;  // 输出简化后的字符串
    }

    return 0;
}