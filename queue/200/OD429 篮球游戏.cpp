#include <bits/stdc++.h>
using namespace std;

int main() {
  string input;
  getline(cin, input);
  stringstream ss(input);
  vector<int> balls;
  int ball;
  while (ss >> ball) {
    balls.push_back(ball);
    if (ss.peek() == ',')
      ss.ignore();
  }

  getline(cin, input);
  stringstream ss2(input);
  vector<int> sequence;
  while (ss2 >> ball) {
    sequence.push_back(ball);
    if (ss2.peek() == ',')
      ss2.ignore();
  }

  deque<int> bucket;
  string result;
  int idx = 0;

  for (int ball : balls) {
    bucket.push_back(ball);
    while (!bucket.empty() && idx < sequence.size() && (
             bucket.front() == sequence[idx] || bucket.back() == sequence[
               idx])) {
      if (bucket.front() == sequence[idx]) {
        result += 'L';
        bucket.pop_front();
      } else {
        result += 'R';
        bucket.pop_back();
      }
      idx++;
    }
  }

  if (idx == sequence.size()) {
    cout << result << endl;
  } else {
    cout << "NO" << endl;
  }

  return 0;
}