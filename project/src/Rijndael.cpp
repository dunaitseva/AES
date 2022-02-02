#include "Rijndael.hpp"

#include <algorithm>
#include <iostream>


#include "BaseBlockCipher.hpp"

namespace crypto {
std::array<Byte, RIJNDAEL_BLOCK_SIZE> Rijndael::Encrypt([[maybe_unused]] const std::array<Byte,
																						  RIJNDAEL_BLOCK_SIZE> &block,
														[[maybe_unused]] const std::array<Byte,
																						  RIJNDAEL_KEY_SIZE> &key) const {
  return {};
}

std::array<Byte, RIJNDAEL_BLOCK_SIZE> Rijndael::Decrypt([[maybe_unused]] const std::array<Byte,
																						  RIJNDAEL_BLOCK_SIZE> &block,
														[[maybe_unused]] const std::array<Byte,
																						  RIJNDAEL_KEY_SIZE> &key) const {
  return {};
}

[[maybe_unused]] void Rijndael::addRoundKey() {}

void Rijndael::subBytes(State &state) const {
  for (auto &row : state.blockTable) {
	std::transform(row.begin(), row.end(), row.begin(), [](Byte &b) -> Byte { return SBox[b]; });
  }
}


void Rijndael::shiftRows(State &state) const {
  size_t counter = 0;
  for (auto &row: state.blockTable) {
	std::rotate(row.begin(), row.begin() + counter, row.end());
	++counter;
  }
}

[[maybe_unused]] void Rijndael::mixColumns([[maybe_unused]] State &state) {}

void Rijndael::invSubBytes(State &state) const {
  for (auto &row : state.blockTable) {
	std::transform(row.begin(), row.end(), row.begin(), [](Byte &b) -> Byte { return InvSBox[b]; });
  }
}

void Rijndael::invShiftRows(State &state) const {
  int counter = 0;
  for (auto &row: state.blockTable) {
	std::rotate(row.rbegin(), row.rbegin() + counter, row.rend());
	++counter;
  }
}

[[maybe_unused]] void Rijndael::invMixColumns([[maybe_unused]] State &state) {}

} // namespace crypto