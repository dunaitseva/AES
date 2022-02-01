#pragma once

#include <string_view>
#include <array>
#include <cinttypes>

#include "BaseBlockCipher.hpp"
#include "RijndaelBaseDefinitions.hpp"

namespace crypto {
class KeySchedule {
 public:
  using RoundKey = std::array<Byte, NUMBER_OF_STATE_ROWS>;

  KeySchedule() = default;
  explicit KeySchedule(const std::array<Byte, RIJNDAEL_KEY_SIZE> &key);

  std::array<RoundKey, AMOUNT_OF_ROUND_KEYS> RoundKeys;
 protected:
  void KeyExpansion(const std::array<Byte, RIJNDAEL_KEY_SIZE> &key);
  void SubWord(RoundKey &key);
  void RotWord(RoundKey &key);
};
} // namespace crypto