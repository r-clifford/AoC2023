#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
const std::unordered_map<char, int> valueMap = {
    std::pair<char, int>('2', 0),  std::pair<char, int>('3', 1),
    std::pair<char, int>('4', 2),  std::pair<char, int>('5', 3),
    std::pair<char, int>('6', 4),  std::pair<char, int>('7', 5),
    std::pair<char, int>('8', 6),  std::pair<char, int>('9', 7),
    std::pair<char, int>('T', 8),  std::pair<char, int>('J', 9),
    std::pair<char, int>('Q', 10), std::pair<char, int>('K', 11),
    std::pair<char, int>('A', 12),
};
class Hand {
 public:
  enum Type {
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    FullHouse,
    FourOfAKind,
    FiveOfAKind,
  };
  uint64_t bid_;
  std::string cards_;
  Type type_;
  std::unordered_map<char, int> cardCounts_;
  std::multimap<int, char> reverseMap_;
  static Type getType(std::multimap<int, char> reverseMap) {
    if (reverseMap.count(5) > 0) {
      return Type::FiveOfAKind;
    }
    if (reverseMap.count(4) > 0) {
      return Type::FourOfAKind;
    }
    if (reverseMap.count(3) == 1) {
      if (reverseMap.count(2) == 1) {
        return Type::FullHouse;
      } else {
        return Type::ThreeOfAKind;
      }
    }
    if (reverseMap.count(2) == 2) {
      return Type::TwoPair;
    }
    if (reverseMap.count(2) == 1) {
      return Type::OnePair;
    }
    return Type::HighCard;
  }
  Hand(std::string cards, uint64_t bid) : cards_(cards), bid_(bid) {
    for (auto c : cards_) {
      cardCounts_[c]++;
    }
    for (auto p : cardCounts_) {
      reverseMap_.insert(std::pair<int, char>(p.second, p.first));
    }
    type_ = getType(reverseMap_);
  }
  uint64_t strength() const {
    switch (type_) {
      case Type::HighCard:
        return 0;
      case Type::OnePair:
        return 100;
      case Type::TwoPair:
        return 200;
      case Type::ThreeOfAKind:
        return 300;
      case Type::FullHouse:
        return 400;
      case Type::FourOfAKind:
        return 500;
      case Type::FiveOfAKind:
        return 600;
    }
  }
  bool operator==(Hand rhs) const { return strength() == rhs.strength(); }
  bool operator<(Hand rhs) const {
    if (*this == rhs) {
      for (size_t i = 0; i < cards_.size(); i++) {
        char a = cards_[i];
        char b = rhs.cards_[i];
        if (valueMap.at(a) == valueMap.at(b)) {
          continue;
        }
        return valueMap.at(a) < valueMap.at(b);
      }
    } else {
      return strength() < rhs.strength();
    }
  }
  operator std::string() const {
    std::stringstream s;
    s << cards_ << " " << strength();
    return s.str();
  }
};
int main() {
  std::vector<Hand> hands;

  std::fstream input("7.txt");
  std::string line;
  while (std::getline(input, line)) {
    std::stringstream s(line);
    std::string cards;
    uint64_t bid;
    s >> cards;
    s >> bid;
    hands.push_back(Hand(cards, bid));
  }
  std::sort(hands.begin(), hands.end());
  uint64_t i = 0;
  uint64_t total = 0;
  for (auto h : hands) {
    i++;
    uint64_t reward = h.bid_ * i;
    total += reward;
    std::cout << (std::string)h << " | " << reward << std::endl;
  }
  std::cout << total << std::endl;  // 245794640
}