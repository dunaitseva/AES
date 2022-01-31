#include "Rijndael.hpp"

namespace crypto {
std::array<std::byte, RIJNDAEL_BLOCK_SIZE> Rijndael::Encrypt([[maybe_unused]] const std::array<std::byte,
																							   RIJNDAEL_BLOCK_SIZE> &block,
															 [[maybe_unused]] const std::array<std::byte,
																							   RIJNDAEL_KEY_SIZE> &key) {
  return {};
}

std::array<std::byte, RIJNDAEL_BLOCK_SIZE> Rijndael::Decrypt([[maybe_unused]] const std::array<std::byte,
																							   RIJNDAEL_BLOCK_SIZE> &block,
															 [[maybe_unused]] const std::array<std::byte,
																							   RIJNDAEL_KEY_SIZE> &key) {
  return {};
}

[[maybe_unused]] void Rijndael::addRoundKey() {}

[[maybe_unused]] void Rijndael::subBytes([[maybe_unused]] State &state) {}

[[maybe_unused]] void Rijndael::shiftRows([[maybe_unused]] State &state) {}

[[maybe_unused]] void Rijndael::mixColumns([[maybe_unused]] State &state) {}

[[maybe_unused]] void Rijndael::invSubBytes([[maybe_unused]] State &state) {}

[[maybe_unused]] void Rijndael::invShiftRows([[maybe_unused]] State &state) {}

[[maybe_unused]] void Rijndael::invMixColumns([[maybe_unused]] State &state) {}

} // namespace crypto