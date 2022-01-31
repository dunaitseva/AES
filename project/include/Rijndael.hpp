#pragma once

#include "BaseBlockCipher.hpp"
#include "State.hpp"

namespace crypto {
class Rijndael : public BaseBlockCipher {
 public:
  std::string_view Encrypt(const std::string_view &block, const std::string_view &key) override;
  std::string_view Decrypt(const std::string_view &block, const std::string_view &key) override;

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