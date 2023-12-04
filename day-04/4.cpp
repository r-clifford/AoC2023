#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int parseLine1(std::string line) {
  std::string::iterator it = line.begin();
  while (*it != ':') {
    it++;
  }
  it += 2;
  std::unordered_set<int> winningSet;
  std::string numStr;
  while (*it != '|') {
    if (*it == ' ') {
      int tmp;
      try {
        tmp = std::stoi(numStr);
      } catch (std::invalid_argument _) {
        it++;
        continue;
      }
      winningSet.insert(tmp);
      numStr.clear();
    }
    if (std::isdigit(*it)) numStr += *(it);
    it++;
  }
  it += 2;
  numStr.clear();
  std::unordered_set<int> numbers;
  while (it != line.end()) {
    if (*it == ' ') {
      int tmp;
      try {
        tmp = std::stoi(numStr);
      } catch (std::invalid_argument _) {
        it++;
        continue;
      }
      numbers.insert(tmp);
      numStr.clear();
    }
    if (std::isdigit(*it)) numStr += *(it);
    if (it == line.end()) {
      break;
    } else {
      it++;
    }
  }
  int result = 0;
  for (auto item : numbers) {
    if (winningSet.find(item) != winningSet.end()) {
      result = result == 0 ? 1 : result * 2;
    }
  }
  return result;
}
int parseLine2(std::string line) {
  std::string::iterator it = line.begin();
  while (*it != ':') {
    it++;
  }
  it += 2;
  std::unordered_set<int> winningSet;
  std::string numStr;
  while (*it != '|') {
    if (*it == ' ') {
      int tmp;
      try {
        tmp = std::stoi(numStr);
      } catch (std::invalid_argument _) {
        it++;
        continue;
      }
      winningSet.insert(tmp);
      numStr.clear();
    }
    if (std::isdigit(*it)) numStr += *(it);
    it++;
  }
  it += 2;
  numStr.clear();
  std::unordered_set<int> numbers;
  while (it != line.end()) {
    if (*it == ' ') {
      int tmp;
      try {
        tmp = std::stoi(numStr);
      } catch (std::invalid_argument _) {
        it++;
        continue;
      }
      numbers.insert(tmp);
      numStr.clear();
    }
    if (std::isdigit(*it)) numStr += *(it);
    if (it == line.end()) {
      break;
    } else {
      it++;
    }
  }
  int matches = 0;
  for (auto &p : numbers) {
    if (winningSet.find(p) != winningSet.end()) {
      matches++;
    }
  }
  return matches;
}
int main() {
  std::ifstream input("4.txt");
  std::vector<std::string> lines;
  std::string tmp;
  std::vector<int> counts = {};
  while (std::getline(input, tmp)) {
    tmp += ' ';

    lines.push_back(tmp);
    tmp.clear();
    counts.push_back(1);
  }
  int total = 0;
  size_t i = 0;
  for (auto line : lines) {
    int reward;
    if (counts[i] > 0) {
      reward = parseLine2(line);
    }
    while (counts[i]-- > 0) {
      for (size_t j = i + 1; j <= i + reward; j++) {
        counts[j]++;
      }

      total++;
    }
    i++;
  }
  std::cout << total << std::endl;
}