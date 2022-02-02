#pragma once

#include "BaseBlockCipher.hpp"
#include "State.hpp"
#include "KeySchedule.hpp"

#include <array>
#include <cstddef>

namespace crypto {
class Rijndael : public BaseBlockCipher<RIJNDAEL_BLOCK_SIZE, RIJNDAEL_KEY_SIZE> {
 public:
  [[nodiscard]] std::array<Byte, RIJNDAEL_BLOCK_SIZE> Encrypt(const std::array<Byte, RIJNDAEL_BLOCK_SIZE> &block,
												const std::array<Byte, RIJNDAEL_KEY_SIZE> &key) const override;
  [[nodiscard]] std::array<Byte, RIJNDAEL_BLOCK_SIZE> Decrypt(const std::array<Byte, RIJNDAEL_BLOCK_SIZE> &block,
												const std::array<Byte, RIJNDAEL_KEY_SIZE> &key) const override;

 protected:
  void addRoundKey(State &state, const std::array<KeySchedule::RoundKey, NUMBER_OF_COLUMNS> &roundKeys) const;

  void subBytes(State &state) const;
  void shiftRows(State &state) const;
  void mixColumns(State &state) const;

  void invSubBytes(State &state) const;
  void invShiftRows(State &state) const;
  void invMixColumns(State &state) const;
};
} // namespace crypto