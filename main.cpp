// g++ -std=c++23 main.cpp -o range_adaptors
#include <iostream>
#include <ranges>
#include <vector>

#include "range_adaptors.h"

using namespace std::string_literals;
using namespace RangeAdaptor;

void dropit(const std::vector<int> &v, const struct drop_last_t &d) {
  auto dv = v | d | std::ranges::to<std::vector<int>>();
  for (auto &e : v) {
    std::cout << e << " ";
  }
  std::cout << "\n";
}

int main() {
  auto s{"0123456789"s};

  // fully qualified with namespace
  auto dln = s | RangeAdaptor::drop_last_n(6) | std::ranges::to<std::string>();
  std::cout << "|" << dln << "|\n";
  auto dl = s | drop_last | std::ranges::to<std::string>();
  std::cout << "|" << dl << "|\n";
  auto dd = drop_last_t();
  auto dldd = s | dd | std::ranges::to<std::string>();
  std::cout << "|" << dldd << "|\n";

  auto sn{"0123456789"s};

  auto sndts = sn | drop_two_sided(2, 3) | std::ranges::to<std::string>();
  std::cout << "|" << sndts << "|\n";
  sndts = sn | drop_two_sided(12, 3) | std::ranges::to<std::string>();
  std::cout << "|" << sndts << "|\n";

  auto vi = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  dropit(vi, drop_last);

  auto irng = std::views::iota(0) | std::views::take(20);
  for (int i : irng) {
    std::cout << i << " ";
  }
  std::cout << "\n";

  auto irngdts = irng | drop_two_sided(2, 3);

  std::cout << "|";
  auto sep{""s};

  for (int i : irngdts) {
    std::cout << sep << i;
    sep = " "s;
  }
  std::cout << "|\n";

  irngdts = irng | drop_two_sided(22, 3);

  std::cout << "|";
  sep = "";

  for (int i : irngdts) {
    std::cout << sep << i;
    sep = " "s;
  }
  std::cout << "|\n";

  irngdts = irng | substr(3, 7);

  std::cout << "|";
  sep = "";

  for (int i : irngdts) {
    std::cout << sep << i;
    sep = " "s;
  }
  std::cout << "|\n";

  irngdts = irng | substr(23, 7);

  std::cout << "|";
  sep = "";

  for (int i : irngdts) {
    std::cout << sep << i;
    sep = " "s;
  }
  std::cout << "|\n";

  auto irngdln = irng | drop_last_n(3);
  std::cout << "|";
  sep = "";

  for (int i : irngdln) {
    std::cout << sep << i;
    sep = " "s;
  }
  std::cout << "|\n";

  irngdln = irng | drop_last_n(23);
  std::cout << "|";
  sep = "";

  for (int i : irngdln) {
    std::cout << sep << i;
    sep = " "s;
  }
  std::cout << "|\n";

  auto szr = std::views::counted(irng.begin(), std::ranges::distance(irng));

  std::cout << szr.size() << "\n";
  return 0;
}