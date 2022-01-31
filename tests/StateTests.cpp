#include "gtest/gtest.h"

#include "BaseBlockCipher.hpp"
#include "State.hpp"
#include "RijndaelBaseDefinitions.hpp"

#include <array>

TEST(StateConstructor, BlockToStateAngles) {
  std::array<crypto::Byte, crypto::RIJNDAEL_BLOCK_SIZE>
	  testBlock = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
  crypto::State currentState(testBlock);
  EXPECT_EQ(currentState.blockTable[0][0], testBlock[0]);
  EXPECT_EQ(currentState.blockTable[0][3], testBlock[12]);
  EXPECT_EQ(currentState.blockTable[3][0], testBlock[3]);
  ASSERT_EQ(currentState.blockTable[3][3], testBlock[15]);
}

TEST(StateConstructor, BlockToStateCenter) {
  std::array<crypto::Byte, crypto::RIJNDAEL_BLOCK_SIZE>
	  testBlock = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
  crypto::State currentState(testBlock);
  ASSERT_EQ(currentState.blockTable[1][1], testBlock[5]);
}