# range_adaptors

## C++20/23 utilities for manipulating ranges

This is a small collection of functors (callable structs) for manipulating ranges. I wanted an adaptor to drop the last character in a range, so I wrote one. Then I wrote one to drop the last _n_ characters, and so on. Usage is pretty self-explanatory from the test harness in `main.cpp`. The adaptors work on sized and non-sized ranges, although in the latter case they (unavoidably) have linear complexity.
