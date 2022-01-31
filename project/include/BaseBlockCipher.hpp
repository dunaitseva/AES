#pragma once

#include <cstddef>
#include <array>

namespace crypto {
template<size_t BLOCK_SIZE, size_t KEY_SIZE>
class BaseBlockCipher {
 public:
  virtual std::array<std::byte, BLOCK_SIZE> Encrypt(const std::array<std::byte, BLOCK_SIZE> &block,
													const std::array<std::byte, KEY_SIZE> &key) = 0;
  virtual std::array<std::byte, BLOCK_SIZE> Decrypt(const std::array<std::byte, BLOCK_SIZE> &block,
													const std::array<std::byte, KEY_SIZE> &key) = 0;
};
} // namespace crypto
