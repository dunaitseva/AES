#pragma once

#include "BaseBlockCipher.hpp"
#include "State.hpp"

#include <array>
#include <cstddef>

namespace crypto {
class Rijndael : public BaseBlockCipher<RIJNDAEL_BLOCK_SIZE, RIJNDAEL_KEY_SIZE> {
 public:
  std::array<Byte, RIJNDAEL_BLOCK_SIZE> Encrypt(const std::array<Byte, RIJNDAEL_BLOCK_SIZE> &block,
											const std::array<Byte, RIJNDAEL_KEY_SIZE> &key) const override;
  std::array<Byte, RIJNDAEL_BLOCK_SIZE> Decrypt(const std::array<Byte, RIJNDAEL_BLOCK_SIZE> &block,
													 const std::array<Byte, RIJNDAEL_KEY_SIZE> &key) const override;

 protected:
  [[maybe_unused]] void addRoundKey();

  void subBytes(State &state) const;
  void shiftRows(State &state) const;
  [[maybe_unused]] void mixColumns(State &state);

  void invSubBytes(State &state) const;
  void invShiftRows(State &state) const;
  [[maybe_unused]] void invMixColumns(State &state);
};
} // namespace crypto