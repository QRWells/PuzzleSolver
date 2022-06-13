#include <algorithm>
#include <array>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <ratio>
#include <string_view>
#include <vector>

#include "TestCase.hpp"

using namespace std;

template <unsigned int Num>
auto DoTest(Puzzle<Num> const &testcase) {
  auto static h0 = [](Puzzle<Num> const &puzzle, Puzzle<Num> const &goal) {
    return 0;
  };
  auto static h1 = [](Puzzle<Num> const &puzzle, Puzzle<Num> const &goal) {
    return puzzle.GetManhattanCost(goal);
  };
  auto static h2 = [](Puzzle<Num> const &puzzle, Puzzle<Num> const &goal) {
    return puzzle.GetHammingCost(goal);
  };

  cout << Num << ","
       << chrono::duration_cast<chrono::microseconds>(
              TestCaseAStar<Num>(testcase, h0))
              .count()
       << ","
       << chrono::duration_cast<chrono::microseconds>(
              TestCaseAStar<Num>(testcase, h1))
              .count()
       << ","
       << chrono::duration_cast<chrono::microseconds>(
              TestCaseAStar<Num>(testcase, h2))
              .count()
       << ","
       << chrono::duration_cast<chrono::microseconds>(
              TestCaseIds<Num, 16>(testcase))
              .count()
       << endl;
}

template <unsigned int Num>
auto GenerateTestCase() -> Puzzle<Num> {
  static std::random_device rd;
  static std::mt19937 rng(rd());
  static NeighborMap<Num> graph;

  auto current = Puzzle<Num>();
  for (auto i = 0; i < 32; ++i) {
    auto zero = current.FindEmptyTileIndex();
    auto neighbours = graph.GetNeighbours(zero);
    current.SwapWithEmpty(zero, neighbours[rng() % neighbours.size()]);
  }

  return current;
}

auto main(int argc, char *const argv[]) -> int {
  int size = 3;
  int count = 10;
  if (argc > 1) {
    size = atoi(argv[1]);
    count = atoi(argv[2]);
  }

  // cout << "size,A*(h0),A*(h1),A*(h2),IDS" << endl;
  if (size < 4)
    for (auto i = 0; i < count; ++i) {
      auto testcase = GenerateTestCase<3>();
      DoTest<3>(testcase);
    }
  else
    for (auto i = 0; i < count; ++i) {
      auto testcase = GenerateTestCase<4>();
      DoTest<4>(testcase);
    }

  return 0;
}