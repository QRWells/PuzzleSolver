#ifndef _NODE_HPP_
#define _NODE_HPP_

#include <memory>

template <typename T>
class Node {
 public:
  Node(const T& state, int cost) : state_(state), cost_(cost) {}
  Node(const T& state, std::shared_ptr<Node> parent, int depth, int cost)
      : state_(state), parent_(std::move(parent)), depth_(depth), cost_(cost) {}
  auto GetParent() const -> std::shared_ptr<Node> { return parent_; }

  [[nodiscard]] auto GetState() const -> const T& { return state_; }
  [[nodiscard]] auto GetDepth() const -> int { return depth_; }
  [[nodiscard]] auto GetCost() const -> int { return cost_; }
  void SetCost(int cost) { cost_ = cost; }

  [[nodiscard]] auto Solvable() const -> bool { return state_.Solvable(); }

 private:
  T state_;
  std::shared_ptr<Node> parent_{nullptr};
  int depth_{0};
  int cost_{0};
};

template <typename T>
using NodePtr = std::shared_ptr<Node<T>>;

#endif