#pragma once

#include <string_view>
#include <array>
#include <cinttypes>

#include "RijndaelBaseDefinitions.hpp"

namespace crypto {
class KeySchedule {
 public:
  using RoundKey = std::array<uint8_t, NUMBER_OF_STATE_ROWS>;

  KeySchedule() = default;
  [[maybe_unused]] explicit KeySchedule(const std::string_view &key);

  std::array<RoundKey, NUMBER_OF_COLUMNS * (NUMBER_OF_ROUNDS + 1)> RoundKeys;
 private:
  [[maybe_unused]] void KeyExpansion(const std::string_view &key);
  [[maybe_unused]] void SubWord(RoundKey &key);
  [[maybe_unused]] void RotWord(RoundKey &key);
};
} // namespace crypto