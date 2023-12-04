#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int parseLine(std::string line) {
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
int main() {
  std::ifstream input("4.txt");
  std::vector<std::string> lines;
  std::string tmp;
  while (std::getline(input, tmp)) {
    tmp += ' ';

    lines.push_back(tmp);
    std::cout << tmp << std::endl;
    tmp.clear();
  }
  int total = 0;
  for (auto line : lines) {
    total += parseLine(line);
  }
  std::cout << total << std::endl;
}