#pragma once

#include <array>
#include <cstddef>

#include "BaseBlockCipher.hpp"
#include "RijndaelBaseDefinitions.hpp"

namespace crypto {
struct State {
  State() = default;
  explicit State(const std::array<Byte, RIJNDAEL_BLOCK_SIZE> &block);
  std::array<Byte, RIJNDAEL_BLOCK_SIZE> GetBlock() const;
  std::array<std::array<Byte, NUMBER_OF_COLUMNS>, NUMBER_OF_STATE_ROWS> blockTable;
};
} // namespace crypto