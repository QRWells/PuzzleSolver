#ifndef _PUZZLE_HPP_
#define _PUZZLE_HPP_

#include <algorithm>
#include <array>
#include <cmath>
#include <random>
#include <sstream>
#include <string_view>

template <unsigned int Num>
class Puzzle {
 private:
  std::array<int, Num * Num> data_;

 public:
  Puzzle() {
    if constexpr (Num == 3) {
      data_[0] = 1;
      data_[1] = 2;
      data_[2] = 3;
      data_[3] = 8;
      data_[4] = 0;
      data_[5] = 4;
      data_[6] = 7;
      data_[7] = 6;
      data_[8] = 5;
    } else if constexpr (Num != 3) {
      for (auto i = 1; i < Num * Num; i++) {
        data_[i - 1] = i;
      }
      data_[Num * Num - 1] = 0;
    }
  }

  explicit Puzzle(const std::array<int, Num * Num>& arr) { data_ = arr; }

  Puzzle(const Puzzle<Num>& other) { data_ = other.data_; }

  ~Puzzle() = default;

  auto operator=(const Puzzle<Num>& other) -> Puzzle& {
    if (this != &other) data_ = other.data_;
    return *this;
  }

  template <unsigned int T>
  auto operator==(const Puzzle<T>& b) const -> bool {
    if (T == Num) return (this->data_ == b.data_);
    return false;
  }

  template <unsigned int T>
  auto operator!=(const Puzzle<T>& b) const -> bool {
    if (T == Num) return (this->data_ != b.data_);
    return true;
  }

  inline void Shuffle() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::shuffle(data_.begin(), data_.end(), rng);
  }

  [[nodiscard]] inline auto FindEmptyTileIndex() const -> int {
    for (auto i = 0; i < data_.size(); ++i)
      if (data_[i] == 0) return i;
    return data_.size();
  }

  inline void SwapWithEmpty(int i0, int i1) {
    int tmp = data_[i1];
    data_[i1] = data_[i0];
    data_[i0] = tmp;
  }

  inline auto GetData() const -> std::array<int, Num * Num> const& {
    return data_;
  }

  inline auto GetManhattanCost(Puzzle<Num> const& other) const -> int {
    int cost = 0;
    int p = 0;
    static std::vector<int> expected_index(Num * Num);
    for (auto i = 0; i < data_.size(); ++i) {
      int v = data_[i];
      if (v == 0) continue;
      // auto p = _expectedIndex[v];
      int gx = p % Num;
      int gy = p / Num;
      int x = i % Num;
      int y = i / Num;
      int mancost = std::abs(x - gx) + std::abs(y - gy);
      cost += mancost;
    }
    return cost;
  }

  inline auto GetHammingCost(Puzzle<Num> const& other) const -> int {
    int cost = 0;
    for (unsigned int i = 0; i < data_.size(); ++i) {
      if (data_[i] == 0) continue;
      if (data_[i] != other.data_[i]) cost += 1;
    }
    return cost;
  }

  inline auto Solvable() -> bool {
    // todo: implement
    return true;
  }

  [[nodiscard]] auto ToString() const -> std::string {
    std::stringstream ss;
    for (auto i = 0; i < data_.size(); ++i) {
      ss << data_[i] << " ";
      if (i % Num == Num - 1) ss << "\n";
    }
    return ss.str();
  }
};

template <unsigned int Num>
class NeighborMap {
  using IndexNeighbourMap = std::unordered_map<int, std::vector<int>>;

 public:
  NeighborMap() {
    for (auto i = 0; i < Num * Num; i++) {
      auto x = i % Num;
      auto y = i / Num;
      std::vector<int> neighbours;
      if (x > 0) neighbours.push_back(i - 1);
      if (x < Num - 1) neighbours.push_back(i + 1);
      if (y > 0) neighbours.push_back(i - Num);
      if (y < Num - 1) neighbours.push_back(i + Num);
      edges_[i] = neighbours;
    }
  }

  auto GetNeighbours(int idx) const -> std::vector<int> const& {
    auto itr(edges_.find(idx));
    if (itr != edges_.end()) return itr->second;
    static std::vector<int> empty;
    return empty;
  }

 private:
  IndexNeighbourMap edges_;
};

#endif