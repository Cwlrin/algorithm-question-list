#include <bits/stdc++.h>

using namespace std;  

int main() {  
  string input;  
  cin >> input; // 读取输入  
  uint64_t number = stoull(input); // 将输入转换为无符号64位整数  

  vector<uint8_t> encoded_bytes;  

  // 编码过程
  do {  
    uint8_t byte = number & 0x7F; // 取低7位  
    number >>= 7; // 右移7位  
    // 如果还有更多的字节，设置最高位为1  
    if (number != 0) {  
      byte |= 0x80; // 设置最高位为1  
    }  
    encoded_bytes.push_back(byte);  
  } while (number != 0);  
    
  // 使用小端序，把字节反转  
  stringstream result;  
  for (unsigned char encoded_byte : encoded_bytes) {
    // 输出为16进制格式，确保每个字节占2位，不足补0，转为大写  
    result << uppercase << setfill('0') << setw(2) << hex << static_cast<int>(encoded_byte);
  }  
    
  cout << result.str() << endl; // 输出编码结果  

  return 0;  
}