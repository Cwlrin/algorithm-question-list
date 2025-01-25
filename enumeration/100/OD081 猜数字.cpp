#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<pair<string, string> > guesses(n);
  for (int i = 0; i < n; i++) {
    cin >> guesses[i].first >> guesses[i].second;
  }

  vector<string> possible_answers;

  // 枚举所有可能的四位数  
  for (int num = 0; num <= 9999; num++) {
    string secret = to_string(num);
    while (secret.length() < 4) {
      secret = "0" + secret;
    }

    bool is_valid = true;
    for (const auto& guess : guesses) {
      int A = 0, B = 0;
      vector<int> secret_count(10, 0), guess_count(10, 0);

      for (int i = 0; i < 4; i++) {
        if (secret[i] == guess.first[i]) {
          A++;
        } else {
          secret_count[secret[i] - '0']++;
          guess_count[guess.first[i] - '0']++;
        }
      }

      for (int i = 0; i < 10; i++) {
        B += min(secret_count[i], guess_count[i]);
      }

      string expected_hint = to_string(A) + "A" + to_string(B) + "B";
      if (expected_hint != guess.second) {
        is_valid = false;
        break;
      }
    }

    if (is_valid) {
      possible_answers.push_back(secret);
    }
  }

  if (possible_answers.size() == 1) {
    cout << possible_answers[0] << endl;
  } else {
    cout << "NA" << endl;
  }

  return 0;
}