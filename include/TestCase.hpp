#ifndef _TESTCASE_HPP_
#define _TESTCASE_HPP_

#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>

#include "AStarSolver.hpp"
#include "IdsSolver.hpp"
#include "Puzzle.hpp"

template <unsigned int Num>
auto TestCaseAStar(
    Puzzle<Num> const &puzzle,
    std::function<int(Puzzle<Num> const &, Puzzle<Num> const &)> hueristic) {
  auto static goal = Puzzle<Num>();
  auto init = Puzzle<Num>(puzzle);

  auto s = AStarSolver<Num>(goal, hueristic);

  using namespace std::chrono;

  auto start = high_resolution_clock::now();
  auto solution = s.Solve(init);
  auto end = high_resolution_clock::now();

  return end - start;
}

template <unsigned int Num, int max>
auto TestCaseIds(Puzzle<Num> const &puzzle) {
  auto static goal = Puzzle<Num>();
  auto init = Puzzle<Num>(puzzle);

  auto static s = IdsSolver<Num>(max, goal);

  using namespace std::chrono;

  auto start = high_resolution_clock::now();
  auto solution = s.Solve(init);
  auto end = high_resolution_clock::now();

  if (solution.empty()) {
    return decltype(end - start)::zero();
  }
  return end - start;
}

#endif