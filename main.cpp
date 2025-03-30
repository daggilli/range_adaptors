#include <iostream>

using namespace std::string_literals;

#include "range_adaptors.h"

int main() {
  auto s{"0123456789"s};

  auto dl = s | drop_last_n(6) | std::ranges::to<std::string>();
  std::cout << "|" << dl << "|\n";

  auto sn{"0123456789"s};

  auto sndts = sn | drop_two_sided(2, 3) | std::ranges::to<std::string>();
  std::cout << "|" << sndts << "|\n";
  sndts = sn | drop_two_sided(12, 3) | std::ranges::to<std::string>();
  std::cout << "|" << sndts << "|\n";

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