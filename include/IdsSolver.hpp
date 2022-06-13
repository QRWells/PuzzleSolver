#ifndef _IDS_SOLVER_HPP_
#define _IDS_SOLVER_HPP_

#include "Solver.hpp"

template <unsigned int Num>
class IdsSolver : public Solver<Num> {
 public:
  IdsSolver(int const &max, Puzzle<Num> const &goal)
      : Solver<Num>(goal), max_(max) {}

  auto Solve(Puzzle<Num> &puzzle)
      -> std::vector<NodePtr<Puzzle<Num>>> override {
    auto init = std::make_shared<Node<Puzzle<Num>>>(puzzle, 0);

    for (int i = 0; i <= max_; i++) {
      if (Dfs(0, i, init)) break;
    }

    if (final_ == nullptr) return {};

    std::vector<NodePtr<Puzzle<Num>>> solution;
    auto s = final_;
    do {
      solution.emplace_back(s);
      s = s->GetParent();
    } while (s != nullptr);
    std::reverse(solution.begin(), solution.end());
    return solution;
  }

  auto Dfs(int depth, int limit, NodePtr<Puzzle<Num>> const &current) -> bool {
    if (current->GetState() == this->goal) {
      final_ = current;
      return true;
    }
    if (depth == limit) return false;
    auto zero = current->GetState().FindEmptyTileIndex();
    auto neighbours = this->graph.GetNeighbours(zero);
    for (int next : neighbours) {
      Puzzle<Num> state(current->GetState());
      state.SwapWithEmpty(zero, next);
      auto node = std::make_shared<Node<Puzzle<Num>>>(state, current, depth, 0);
      if (Dfs(depth + 1, limit, node)) {
        return true;
      }
    }
    return false;
  }

 private:
  NodePtr<Puzzle<Num>> final_ = nullptr;
  int max_;
};

#endif