#pragma once

#include <cstddef>
#include <array>

namespace crypto {
using Byte = unsigned char;

template<size_t BLOCK_SIZE, size_t KEY_SIZE>
class BaseBlockCipher {
 public:
  virtual std::array<Byte, BLOCK_SIZE> Encrypt(const std::array<Byte, BLOCK_SIZE> &block,
													const std::array<Byte, KEY_SIZE> &key) = 0;
  virtual std::array<Byte, BLOCK_SIZE> Decrypt(const std::array<Byte, BLOCK_SIZE> &block,
													const std::array<Byte, KEY_SIZE> &key) = 0;
};
} // namespace crypto
