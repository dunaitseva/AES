#include "Rijndael.hpp"

namespace crypto {
std::string_view Rijndael::Encrypt([[maybe_unused]] const std::string_view &block, [[maybe_unused]] const std::string_view &key) {
  return {};
}

std::string_view Rijndael::Decrypt([[maybe_unused]] const std::string_view &block, [[maybe_unused]] const std::string_view &key) {
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