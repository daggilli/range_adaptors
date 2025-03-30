#ifndef __RANGE_ADAPTORS_H__
#define __RANGE_ADAPTORS_H__
#include <ranges>

struct drop_last_n_t : std::ranges::range_adaptor_closure<drop_last_n_t> {
  std::size_t len;

  constexpr drop_last_n_t(std::size_t len) : len(len){};

  template <std::ranges::viewable_range R>
  auto operator()(R&& r) const {
    if constexpr (std::ranges::sized_range<R>) {
      auto n = std::ranges::size(r);
      return std::views::take(std::forward<R>(r), n > len ? n - len : 0);
    } else {
      auto head = std::ranges::begin(r);
      auto tail = std::ranges::end(r);
      auto n = std::ranges::distance(head, tail);
      auto ntail = std::ranges::next(head, n > len ? n - len : 0, tail);
      return std::ranges::subrange(std::move(head), std::move(ntail));
    }
  }
};
constexpr inline auto drop_last_n(std::size_t len = 1) { return drop_last_n_t{len}; };

struct drop_two_sided_t : std::ranges::range_adaptor_closure<drop_two_sided_t> {
  std::size_t front, back;

  constexpr drop_two_sided_t(std::size_t front, std::size_t back) : front(front), back(back) {}

  template <std::ranges::viewable_range R>
  constexpr auto operator()(R&& r) const {
    if constexpr (std::ranges::sized_range<R>) {
      auto n = std::ranges::size(r);
      return (front + back >= n) ? std::views::drop(std::forward<R>(r), 0) | std::views::take(0)
                                 : std::views::drop(std::forward<R>(r), front) | std::views::take(n - front - back);
    } else {
      auto first = std::ranges::begin(r);
      auto last = std::ranges::end(r);

      first = std::ranges::next(first, front, last);
      auto newLast = std::ranges::next(first, std::ranges::distance(first, last) - back, last);
      return std::ranges::subrange(std::move(first), std::move(newLast));
    }
  }
};
constexpr inline auto drop_two_sided(std::size_t front, std::size_t back) { return drop_two_sided_t{front, back}; }

struct substr_t : std::ranges::range_adaptor_closure<substr_t> {
  std::size_t start, len;

  constexpr substr_t(std::size_t start, std::size_t len) : start(start), len(len) {}

  template <std::ranges::viewable_range R>
  constexpr auto operator()(R&& r) const {
    if constexpr (std::ranges::sized_range<R>) {
      auto n = std::ranges::size(r);
      return (start >= n) ? std::views::drop(std::forward<R>(r), 0) | std::views::take(0)
                          : std::views::drop(std::forward<R>(r), start) | std::views::take(len);
    } else {
      auto head = std::ranges::begin(r);
      auto tail = std::ranges::end(r);
      head = std::ranges::next(head, start, tail);
      auto newTail = std::ranges::next(head, len, tail);
      return std::ranges::subrange(std::move(head), std::move(newTail));
    }
  };
};
constexpr inline auto substr(std::size_t start, std::size_t len) { return substr_t{start, len}; }

#endif
