#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
int check_adj(const std::vector<std::vector<int>>& values, size_t i, size_t j) {
  int result = 0;
  std::unordered_set<int> set;
  for (size_t a = i - 1; a <= i + 1; a++) {
    for (size_t b = j - 1; b <= j + 1; b++) {
      try {
        int tmp = values[a][b];
        if (tmp && set.find(tmp) == set.end()) {
          result += tmp;
          set.insert(tmp);
        }
      } catch (const std::out_of_range& _) {
        continue;
      }
    }
  }
  return result;
}
int parse_matrix(const std::vector<std::string>& matrix) {
  std::vector<std::vector<int>> value_matrix;
  for (size_t i = 0; i < matrix.size(); ++i) {
    value_matrix.push_back(std::vector<int>());
    bool parsing = false;
    size_t start;
    std::string n_str;
    for (size_t j = 0; j < matrix[0].size(); j++) {
      value_matrix[i].push_back(0);
      if (std::isdigit(matrix[i][j])) {
        if (!parsing) {
          start = j;
          parsing = true;
        }
        n_str += matrix[i][j];
      } else {
        if (parsing) {
          parsing = false;
          int num;
          try {
            num = std::stoi(n_str);
          } catch (const std::out_of_range& _) {
            std::cout << n_str << std::endl;
          }
          n_str.clear();
          for (size_t k = start; k < j; k++) {
            value_matrix[i][k] = num;
          }
        }
      }
    }
  }
  int sum = 0;
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[0].size(); j++) {
      char tmp = matrix[i][j];
      if (tmp != '.' && std::ispunct(tmp)) {
        int part = check_adj(value_matrix, i, j);
        sum += part;
      }
    }
  }

  return sum;
}
int main() {
  std::ifstream input("3.txt");
  std::vector<std::string> matrix;
  while (input) {
    std::string tmp;
    input >> tmp;
    tmp += ".";  // ensure correct end of line parsing
    matrix.push_back(tmp);
  }

  std::cout << parse_matrix(matrix) << std::endl;  // 497027 low
}