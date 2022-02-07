#include "BaseCryptoUtils.hpp"

namespace crypto {
Byte GaluaMul(Byte lhs, Byte rhs) {
  constexpr Byte moduloLimits = 0x80; // GF modulo: if a >= 128, then it will overflow when shifted left, so reduce
  Byte result = 0;
  while (lhs && rhs) {
	if (rhs & 1) {
	  result ^= lhs;
	}

	if (lhs & moduloLimits) {
	  lhs = (lhs << 1) ^ 0x11b; // XOR with the primitive polynomial x^8 + x^4 + x^3 + x + 1
	} else {
	  lhs <<= 1;
	}
	rhs >>= 1;
  }
  return result;
}
} // namespace crypto