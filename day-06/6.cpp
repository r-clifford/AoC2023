#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Race {
 public:
  int time_, distance_;
  Race(int time, int distance_) : time_(time), distance_(distance_) {}
  int maximize() {
    int hold_time = std::floor(time_ / 2);
    return traveled(hold_time);
  }
  int traveled(int hold_time) {
    int travel_time = time_ - hold_time;
    return travel_time * hold_time;
  }
  int brute_force() {
    int count = 0;
    for (int i = 0; i < time_; i++) {
      if (traveled(i) > distance_) {
        count++;
      }
    }
    return count;
  }
};
void parseLine(std::string line, std::vector<int>& result) {
  std::stringstream s(line);
  std::string name;
  s >> name;
  int n;
  while (!s.eof()) {
    s >> n;
    result.push_back(n);
  }
}
int main() {
  std::ifstream input("6.txt");
  std::string line;
  std::getline(input, line);
  std::vector<int> time;
  parseLine(line, time);

  std::getline(input, line);
  std::vector<int> distance;
  parseLine(line, distance);
  std::vector<Race> races;
  for (size_t i = 0; i < time.size(); i++) {
    races.push_back(Race(time[i], distance[i]));
  }
  int answer = 1;
  for (auto race : races) {
    int total = race.brute_force();
    std::cout << "Max: " << race.maximize() << " Total: " << total << std::endl;
    answer *= total;
  }
  std::cout << "Answer: " << answer << std::endl; // 741000

  return 0;
}