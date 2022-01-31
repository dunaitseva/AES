#pragma once

#include "BaseBlockCipher.hpp"
#include "State.hpp"

#include <array>
#include <cstddef>

namespace crypto {
class Rijndael : public BaseBlockCipher<RIJNDAEL_BLOCK_SIZE, RIJNDAEL_KEY_SIZE> {
 public:
  std::array<Byte, RIJNDAEL_BLOCK_SIZE> Encrypt(const std::array<Byte, RIJNDAEL_BLOCK_SIZE> &block,
											const std::array<Byte, RIJNDAEL_KEY_SIZE> &key) override;
  std::array<Byte, RIJNDAEL_BLOCK_SIZE> Decrypt(const std::array<Byte, RIJNDAEL_BLOCK_SIZE> &block,
													 const std::array<Byte, RIJNDAEL_KEY_SIZE> &key) override;

 private:
  [[maybe_unused]] void addRoundKey();
  [[maybe_unused]] void subBytes(State &state);
  [[maybe_unused]] void shiftRows(State &state);
  [[maybe_unused]] void mixColumns(State &state);
  [[maybe_unused]] void invSubBytes(State &state);
  [[maybe_unused]] void invShiftRows(State &state);
  [[maybe_unused]] void invMixColumns(State &state);
};
} // namespace crypto