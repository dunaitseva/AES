#pragma once

#include <array>

#include "RijndaelBaseDefinitions.hpp"

namespace crypto {
struct State {
  State() = default;
  [[maybe_unused]] explicit State(const std::string_view &block);
  std::array<std::array<uint8_t, NUMBER_OF_COLUMNS>, NUMBER_OF_STATE_ROWS> stateTable;
};
} // namespace crypto