#pragma once

#include <cstddef>
#include <algorithm>
#include <array>

#include "BaseBlockCipher.hpp"

namespace crypto {
template<size_t SIZE_OF_WORD>
std::array<Byte, SIZE_OF_WORD> XOR_WORDS(const std::array<Byte, SIZE_OF_WORD> &rhs,
										 const std::array<Byte, SIZE_OF_WORD> &lhs) {
  std::array<Byte, SIZE_OF_WORD> result;
  std::transform(rhs.begin(),
				 rhs.end(),
				 lhs.begin(),
				 result.begin(),
				 [](const Byte &rhs_byte, const Byte &lhs_byte) -> Byte { return rhs_byte ^ lhs_byte; });
  return result;
}
} // namespace crypto