#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// 定义灯的结构体
struct Light {
  int id;             // 编号
  int x1, y1;         // 左上角坐标
  int x2, y2;         // 右下角坐标
  int centerX;        // 中心x坐标
  int centerY;        // 中心y坐标
  int height;         // 灯的高度
  bool used = false;  // 是否已经被使用
};

int main() {
  int N;
  cin >> N;

  vector<Light> lights(N);

  // 读取输入
  for (int i = 0; i < N; i++) {
    cin >> lights[i].id >> lights[i].x1 >> lights[i].y1 >> lights[i].x2 >>
        lights[i].y2;

    // 计算中心坐标
    lights[i].centerX = (lights[i].x1 + lights[i].x2) / 2;
    lights[i].centerY = (lights[i].y1 + lights[i].y2) / 2;

    // 计算高度
    lights[i].height = lights[i].y2 - lights[i].y1;
  }

  // 存储最终排序结果
  vector<int> result;

  while (result.size() < N) {
    // 找出未使用的最高的灯（y坐标最小的）
    int highest_index = -1;
    for (int i = 0; i < N; i++) {
      if (!lights[i].used) {
        if (highest_index == -1 ||
            lights[i].centerY < lights[highest_index].centerY) {
          highest_index = i;
        }
      }
    }

    // 找出同一行的灯
    vector<Light*> current_row;
    current_row.push_back(&lights[highest_index]);
    lights[highest_index].used = true;

    // 找出和最高灯坐标相差小于等于灯半径的灯
    for (int i = 0; i < N; i++) {
      if (!lights[i].used) {
        bool same_row = true;
        for (auto* row_light : current_row) {
          if (abs(lights[i].centerY - row_light->centerY) >
              row_light->height / 2) {
            same_row = false;
            break;
          }
        }

        if (same_row) {
          current_row.push_back(&lights[i]);
          lights[i].used = true;
        }
      }
    }

    // 对同一行的灯按x坐标排序
    sort(
        current_row.begin(), current_row.end(),
        [](const Light* a, const Light* b) { return a->centerX < b->centerX; });

    // 将同一行的灯id加入结果
    for (auto* light : current_row) {
      result.push_back(light->id);
    }
  }

  // 输出排序后的编号
  for (int i = 0; i < N; i++) {
    cout << result[i];
    if (i < N - 1)
      cout << " ";
  }
  cout << endl;

  return 0;
}