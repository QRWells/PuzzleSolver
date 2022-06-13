#ifndef _SOLVER_HPP_
#define _SOLVER_HPP_

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <set>

#include "Node.hpp"
#include "Puzzle.hpp"

template <unsigned int Num>
auto const COMP =
    [](NodePtr<Puzzle<Num>> const &a, NodePtr<Puzzle<Num>> const &b) {
      return a->GetCost() < b->GetCost();
    };

template <unsigned int Num>
class Solver {
 public:
  using NodeList = std::vector<NodePtr<Puzzle<Num>>>;
  explicit Solver(Puzzle<Num> const &goal) : goal(goal) {}

  virtual auto Solve(Puzzle<Num> &puzzle)
      -> std::vector<NodePtr<Puzzle<Num>>> = 0;

  auto static Contains(NodeList const &list, Puzzle<Num> const &node) -> bool {
    for (auto const &n : list) {
      if (n->GetState() == node) return true;
    }
    return false;
  }

 protected:
  NeighborMap<Num> graph;
  const Puzzle<Num> &goal;
};

#endif