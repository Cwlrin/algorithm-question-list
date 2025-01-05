#include <bits/stdc++.h>

using namespace std;

int main() {
  string target_tag, tlv_stream, token;
  vector<unsigned char> bytes;
  // 读取目标 tag
  getline(cin, target_tag);
  // 读取 TLV 码流并转换为字节数组
  getline(cin, tlv_stream);
  stringstream ss(tlv_stream);
  // 将 16 进制字符串转换为字节数组
  while (ss >> token) {
    bytes.push_back(stoi(token, nullptr, 16));
  }
  // 将目标 tag 转换为数值
  unsigned char tag = stoi(target_tag, nullptr, 16);

  // 遍历码流
  for (size_t i = 0; i < bytes.size();) {
    // 当前信元的 tag
    unsigned char current_tag = bytes[i];
    // 检查是否匹配目标 tag
    if (current_tag == tag) {
      // 小端序读取长度（两个字节）
      unsigned short length = bytes[i + 2] * 256 + bytes[i + 1];
      // 输出对应的 value
      for (size_t j = i + 3; j < i + 3 + length; ++j) {
        cout << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(
          bytes[j]);
        // 最后一个字节不加空格
        if (j < i + 2 + length) {
          cout << " ";
        }
      }
      cout << endl;
      // 成功找到并输出后直接退出
      return 0;
    }
    // 小端序读取长度
    unsigned short length = bytes[i + 2] * 256 + bytes[i + 1];
    // 移动到下一个信元
    i += 3 + length;
  }
  return 0;
}