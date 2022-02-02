#include "BaseCryptoUtils.hpp"

//uint8_t gmul(uint8_t a, uint8_t b) {
//  uint8_t p = 0; /* the product of the multiplication */
//  while (a && b) {
//	if (b & 1) /* if b is odd, then add the corresponding a to p (final product = sum of all a's corresponding to odd b's) */
//	  p ^= a; /* since we're in GF(2^m), addition is an XOR */
//
//	if (a & 0x80) /* GF modulo: if a >= 128, then it will overflow when shifted left, so reduce */
//	  a = (a << 1) ^ 0x11b; /* XOR with the primitive polynomial x^8 + x^4 + x^3 + x + 1 (0b1_0001_1011) – you can change it but it must be irreducible */
//	else
//	  a <<= 1; /* equivalent to a*2 */
//	b >>= 1; /* equivalent to b // 2 */
//  }
//  return p;
//}

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