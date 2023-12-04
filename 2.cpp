#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>

const std::unordered_map<std::string, int> availableCubes = {
    std::pair<std::string, int>("red", 12),
    std::pair<std::string, int>("green", 13),
    std::pair<std::string, int>("blue", 14),
};
int getId(std::string line, size_t& pos) {
  std::string id_str;
  while (line[pos] != ':') {
    id_str.push_back(line[pos++]);
  }
  return std::stoi(id_str);
}
int testLine1(std::string line) {
  size_t pos = 5;  // start at first character of id
  int id = getId(line, pos);
  std::string::iterator iter = line.begin() + pos;
  std::unordered_map<std::string, int> totals = {
      std::pair<std::string, int>("red", 0),
      std::pair<std::string, int>("green", 0),
      std::pair<std::string, int>("blue", 0),
  };
  std::string color;
  std::string value;
  while (iter != line.end()) {
    while (std::isdigit(*iter)) {
      value.push_back(*(iter++));
    }
    while (std::isalpha(*iter)) {
      color.push_back(*(iter++));
    }
    if (!color.empty() && !value.empty()) {
      totals[color] += std::stoi(value);
      color.clear();
      value.clear();
    }

    if (*iter == ';' || iter == line.end()) {
      for (auto& p : availableCubes) {
        if (totals[p.first] > p.second) {
          return 0;
        }
        totals[p.first] = 0;
      }
      if (iter == line.end()) {
        break;
      }
    }
    iter++;
  }
  return id;
}
int testLine2(std::string line) {
  size_t pos = 5;
  getId(line, pos);
  std::string::iterator it = line.begin() + pos;
  std::unordered_map<std::string, int> result_map = {
      std::pair<std::string, int>("red", 0),
      std::pair<std::string, int>("green", 0),
      std::pair<std::string, int>("blue", 0),
  };
  std::unordered_map<std::string, int> current_map = {
      std::pair<std::string, int>("red", 0),
      std::pair<std::string, int>("green", 0),
      std::pair<std::string, int>("blue", 0),
  };
  std::string color, value;
  while (it != line.end()) {
    while (std::isdigit(*it)) {
      value.push_back(*(it++));
    }
    while (std::isalpha(*it)) {
      color.push_back(*(it++));
    }
    if (!color.empty() && !value.empty()) {
      current_map[color] += std::stoi(value);
      color.clear();
      value.clear();
    }
    if (*it == ';' || it == line.end()) {
      for (auto& p : current_map) {
        if (p.second > result_map[p.first]) {
          result_map[p.first] = p.second;
        }
        p.second = 0;
      }
    }
    if (it == line.end()) {
      break;
    }
    it++;
  }
  int result = 1;
  for (auto& p : result_map) {
    result *= p.second;
  }
  return result;
}
int main(int argc, char* argv[]) {
  std::ifstream inputStream("2.txt", std::ios::in);
  std::string line;
  int total = 0;
  while (std::getline(inputStream, line)) {
    int res = testLine2(line);
    total += res;
  }
  std::cout << total << std::endl;  // 190 low, 2864 high
}