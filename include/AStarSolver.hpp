#include "Solver.hpp"

template <unsigned int Num>
class AStarSolver : public Solver<Num> {
 public:
  explicit AStarSolver(
      Puzzle<Num> const &goal,
      std::function<int(Puzzle<Num> const &, Puzzle<Num> const &)> hueristic)
      : Solver<Num>(goal), hueristic_(hueristic) {}

  auto Solve(Puzzle<Num> &puzzle)
      -> std::vector<NodePtr<Puzzle<Num>>> override {
    this->open_list_.clear();
    this->close_list_.clear();

    auto cost = hueristic_(puzzle, this->goal);
    this->open_list_.emplace_back(
        std::make_shared<Node<Puzzle<Num>>>(puzzle, cost));

    NodePtr<Puzzle<Num>> current;

    while (this->open_list_.size() > 0) {
      current = this->GetNextNode();
      if (current == nullptr) {
        return {};
      }
      if (current->GetState() == this->goal) {
        break;
      }

      this->ExpandNode(current);
    }

    std::vector<NodePtr<Puzzle<Num>>> solution;
    auto s = current;
    do {
      solution.emplace_back(s);
      s = s->GetParent();
    } while (s != nullptr);
    std::reverse(solution.begin(), solution.end());
    return solution;
  }

  auto GetNextNode() -> NodePtr<Puzzle<Num>> {
    if (this->open_list_.empty()) return nullptr;
    auto itr = std::min_element(this->open_list_.begin(),
                                this->open_list_.end(), COMP<Num>);
    auto current = *itr;
    this->open_list_.erase(itr);
    this->close_list_.emplace_back(current);
    return current;
  }

  void ExpandNode(NodePtr<Puzzle<Num>> current) {
    auto zero = current->GetState().FindEmptyTileIndex();
    auto neighbours = this->graph.GetNeighbours(zero);

    for (int next : neighbours) {
      Puzzle<Num> state(current->GetState());
      state.SwapWithEmpty(zero, next);

      if (Solver<Num>::Contains(this->close_list_, state)) continue;

      auto tentative_is_better = false;
      auto cost = hueristic_(state, this->goal) + current->GetDepth() + 1;
      if (!Solver<Num>::Contains(this->open_list_, state))
        tentative_is_better = true;

      if (tentative_is_better) {
        auto node = std::make_shared<Node<Puzzle<Num>>>(
            state, current, current->GetDepth() + 1, cost);
        this->open_list_.emplace_back(node);
      }
    }
  }

 private:
  using NodeList = std::vector<NodePtr<Puzzle<Num>>>;
  std::function<int(Puzzle<Num> const &, Puzzle<Num> const &)> hueristic_;

  NodeList open_list_{};
  NodeList close_list_{};
};