#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int solution(const vector<int>& x, int k) {
  // Step 1: Find the median
  vector<int> sorted_x = x; // Make a copy of X to sort
  sort(sorted_x.begin(), sorted_x.end());
  int n = sorted_x.size();

  int median = sorted_x[n / 2]; // Median for even length is at n/2

  // Step 2: Initialize variables to find the closest value
  int closest_index = -1;
  int closest_value = INT_MAX;

  // Step 3: Calculate each start index's value for the expression
  for (int i = 0; i <= n - k; i++) {
    int current_sum = x[i];

    for (int j = 1; j < k; j++) {
      // We start from 1 because we already took X[i]
      current_sum -= x[i + j];
    }

    // Calculate the distance from the median
    int current_distance = abs(current_sum - median);

    // Choose the suitable index as described
    if (current_distance < closest_value ||
        (current_distance == closest_value && i > closest_index)) {
      closest_value = current_distance;
      closest_index = i;
    }
  }

  return closest_index;
}

int main() {
  string s;
  cin >> s;

  // Input processing to read the vector and K
  int index = s.rfind(',');

  stringstream ss(s.substr(1, index - 1));
  string token;

  vector<int> x;
  while (getline(ss, token, ',')) {
    x.emplace_back(stoi(token));
  }

  int k = stoi(s.substr(index + 1));

  cout << solution(x, k);

  return 0;
}