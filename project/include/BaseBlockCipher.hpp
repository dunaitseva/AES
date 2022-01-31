#pragma once

#include <string_view>

namespace crypto {
class BaseBlockCipher {
 public:
  virtual std::string_view Encrypt(const std::string_view &block, const std::string_view &key) = 0;
  virtual std::string_view Decrypt(const std::string_view &block, const std::string_view &key) = 0;
 private:
};
} // namespace crypto
