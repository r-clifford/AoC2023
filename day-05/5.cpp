#include <stdlib.h>

#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

class Range {
 public:
  size_t src, dst, len;
  Range(size_t src, size_t dst, size_t len) : src(src), dst(dst), len(len) {}
  size_t operator()(size_t value) {
    if ((value >= src) && (value < src + len)) {
      return (value - src) + dst;
    }
    return value;
  }
};
void parseSeeds(std::string line, std::vector<int>& seeds) {
  line += " ";
  std::string s;
  for (auto c : line) {
    if (std::isdigit(c)) {
      s += c;
    } else {
      try {
        int i = std::stoi(s);
        seeds.push_back(i);
      } catch (std::exception& _) {
      }
      s.clear();
    }
  }
}
Range parseLine(std::string line) {
  int src, dst, len;
  sscanf(line.c_str(), "%d %d %d", &dst, &src, &len);
  return Range(src, dst, len);
}
int main() {
  std::ifstream input("5.txt");
  std::string line;
  std::vector<int> seeds;
  std::getline(input, line);
  parseSeeds(line, seeds);
  std::getline(input, line);
  std::vector<std::vector<Range>> mappings;
  for (size_t i = 0; i < 7; i++) {
    mappings.push_back(std::vector<Range>());
    std::getline(input, line);
    std::getline(input, line);
    while (!line.empty()) {
      mappings[i].push_back(parseLine(line));
      std::getline(input, line);
    }
  }
  std::vector<int> minimum;
  for (auto seed : seeds) {
    size_t value = seed;
    for (auto mapping : mappings) {
      for (auto range : mapping) {
        int tmp = range(value);
        if (value != tmp) {
          value = tmp;
          break;
        }
      }
    }
    if (minimum.empty()) {
      minimum.push_back(value);
    }
    if (value < minimum[0]) {
      minimum[0] = value;
    }
  }
  std::cout << minimum[0] << std::endl;  // p1: 178159714
}