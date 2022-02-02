#pragma once

#include <cstddef>
#include <algorithm>
#include <array>

#include "BaseBlockCipher.hpp"

namespace crypto {
/*
 * XOR_WORDS implements XOR (^) operation for
 * two arrays size of SIZE_OF_WORD for every Byte in word
 */
template<size_t SIZE_OF_WORD>
std::array<Byte, SIZE_OF_WORD> XOR_WORDS(const std::array<Byte, SIZE_OF_WORD> &lhs,
										 const std::array<Byte, SIZE_OF_WORD> &rhs) {
  std::array<Byte, SIZE_OF_WORD> result;
  std::transform(rhs.begin(),
				 rhs.end(),
				 lhs.begin(),
				 result.begin(),
				 [](const Byte &rhs_byte, const Byte &lhs_byte) -> Byte { return rhs_byte ^ lhs_byte; });
  return result;
}

/*
 * GaluaMul multiply numbers in the characteristic 2 finite field of order 2 ^ 8
 */
Byte GaluaMul(Byte lhs, Byte rhs);
} // namespace crypto