#include "gtest/gtest.h"

#include "BaseCryptoUtils.hpp"
#include "BaseBlockCipher.hpp"
#include "RijndaelBaseDefinitions.hpp"

#include <array>

static constexpr crypto::Byte b1 = 0b00000001;
static constexpr crypto::Byte b2 = 0b00000010;
static constexpr crypto::Byte b3 = 0b00000100;
static constexpr crypto::Byte b4 = 0b00001000;

TEST(BaseCryptoUtilsXOR, WordSize2XOR) {
  constexpr size_t SIZE_OF_WORD = 2;
  std::array<crypto::Byte, SIZE_OF_WORD> first = {b1, b1};
  std::array<crypto::Byte, SIZE_OF_WORD> second = {b1, b2};
  std::array<crypto::Byte, SIZE_OF_WORD> expect = {b1 ^ b1, b1 ^ b2};
  std::array<crypto::Byte, SIZE_OF_WORD> result = crypto::XOR_WORDS(first, second);
  ASSERT_EQ(expect, result);
}

TEST(BaseCryptoUtilsXOR, WordSize4XOR) {
  constexpr size_t SIZE_OF_WORD = crypto::NUMBER_OF_COLUMNS;
  std::array<crypto::Byte, SIZE_OF_WORD> first = {b1, b2, b3, b4};
  std::array<crypto::Byte, SIZE_OF_WORD> second = {b4, b3, b2, b1};
  std::array<crypto::Byte, SIZE_OF_WORD> expect = {b1 ^ b4, b2 ^ b3, b3 ^ b2, b4 ^ b1};
  std::array<crypto::Byte, SIZE_OF_WORD> result = crypto::XOR_WORDS(first, second);
  ASSERT_EQ(expect, result);
}