#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Race {
 public:
  uint64_t time_, distance_;
  Race(uint64_t time, uint64_t distance_) : time_(time), distance_(distance_) {}
  uint64_t maximize() {
    uint64_t hold_time = std::floor(time_ / 2);
    return traveled(hold_time);
  }
  uint64_t traveled(uint64_t hold_time) {
    uint64_t travel_time = time_ - hold_time;
    return travel_time * hold_time;
  }
  uint64_t brute_force() {
    uint64_t count = 0;
    for (uint64_t i = 0; i < time_; i++) {
      if (traveled(i) >= distance_) {
        count++;
      }
    }
    return count;
  }
};
uint64_t parseLine(std::string line) {
  std::stringstream s(line);
  std::string name;
  s >> name;
  uint64_t n;
  std::vector<int> result;
  while (!s.eof()) {
    s >> n;
    result.push_back(n);
  }
  std::string num_str;
  for (auto i : result) {
    num_str += std::to_string(i);
  }
  return std::stoll(num_str);
}
int main() {
  std::ifstream input("6.txt");
  std::string line;
  std::getline(input, line);
  uint64_t time = parseLine(line);

  std::getline(input, line);
  uint64_t distance = parseLine(line);
  Race race(time, distance);
  uint64_t total = race.brute_force();
  std::cout << "Max: " << race.maximize() << " Total: " << total << std::endl;
  std::cout << "Answer: " << total << std::endl;  // 38220708

  return 0;
}