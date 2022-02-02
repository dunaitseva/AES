#include "State.hpp"

#include <array>

#include "BaseBlockCipher.hpp"

namespace crypto {
State::State(const std::array<Byte, RIJNDAEL_BLOCK_SIZE> &block) : blockTable() {
  for (size_t i = 0; i < NUMBER_OF_STATE_ROWS; ++i) {
	for (size_t j = 0; j < NUMBER_OF_COLUMNS; ++j) {
	  blockTable[i][j] = block[i + 4 * j];
	}
  }
}

std::array<Byte, RIJNDAEL_BLOCK_SIZE> State::GetBlock() const {
  std::array<Byte, RIJNDAEL_BLOCK_SIZE> block{};
  for (size_t i = 0; i < NUMBER_OF_STATE_ROWS; ++i) {
	for (size_t j = 0; j < NUMBER_OF_COLUMNS; ++j) {
	  block[i + 4 * j] = blockTable[i][j];
	}
  }

  return block;
}
} // namespace crypto