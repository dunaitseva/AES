#include "gtest/gtest.h"

#include "Rijndael.hpp"

#include "State.hpp"

constexpr std::array<crypto::Byte, crypto::RIJNDAEL_BLOCK_SIZE> originalBlock = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
};

constexpr std::array<crypto::Byte, crypto::RIJNDAEL_BLOCK_SIZE> SBoxTransformedOrigBlock = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76
};

constexpr std::array<crypto::Byte, crypto::RIJNDAEL_BLOCK_SIZE> shiftedOrigBlock = {
	0x00, 0x05, 0x0a, 0x0f, 0x04, 0x09, 0x0e, 0x03, 0x08, 0x0d, 0x02, 0x07, 0x0c, 0x01, 0x06, 0x0b
};

//constexpr std::array<std::array<crypto::Byte, crypto::NUMBER_OF_COLUMNS>, crypto::NUMBER_OF_STATE_ROWS> originalTable = {
//	{
//		{0x00, 0x04, 0x08, 0x0c},
//		{0x01, 0x05, 0x09, 0x0d},
//		{0x02, 0x06, 0x0a, 0x0e},
//		{0x03, 0x07, 0x0b, 0x0f}
//	}
//};
//
//constexpr std::array<std::array<crypto::Byte, crypto::NUMBER_OF_COLUMNS>, crypto::NUMBER_OF_STATE_ROWS> shiftedTable = {
//	{
//		{0x00, 0x04, 0x08, 0x0c},
//		{0x05, 0x09, 0x0d, 0x01},
//		{0x0a, 0x0e, 0x02, 0x06},
//		{0x0f, 0x03, 0x07, 0x0b}
//	}
//};

class RijndaelTestingImpl : crypto::Rijndael {
 public:
  void SubBytesImpl(crypto::State &state) {
	subBytes(state);
  }

  void InvSubBytesImpl(crypto::State &state) {
	invSubBytes(state);
  }

  void ShiftRowsImpl(crypto::State &state) {
	shiftRows(state);
  }

  void InvShiftRowsImpl(crypto::State &state) {
	invShiftRows(state);
  }
};

TEST(RijndaelTestsSubBytes, SubBytesTesting) {
  crypto::State testingState(originalBlock);
  std::array<crypto::Byte, crypto::RIJNDAEL_BLOCK_SIZE> expectedValues = SBoxTransformedOrigBlock;
  RijndaelTestingImpl cipherBlock;
  cipherBlock.SubBytesImpl(testingState);
  ASSERT_EQ(testingState.GetBlock(), expectedValues);
}

TEST(RijndaelTestsSubBytes, InvSubBytesTesting) {
  std::array<crypto::Byte, crypto::RIJNDAEL_BLOCK_SIZE> expectedValues = originalBlock;
  crypto::State testingState(SBoxTransformedOrigBlock);
  RijndaelTestingImpl cipherBlock;
  cipherBlock.InvSubBytesImpl(testingState);
  ASSERT_EQ(testingState.GetBlock(), expectedValues);
}

TEST(RijndaelTestsSubBytes, ReversibilitySubBytes) {
  std::array<crypto::Byte, crypto::RIJNDAEL_BLOCK_SIZE> block = originalBlock;
  RijndaelTestingImpl cipherBlock;
  crypto::State testState(block);
  cipherBlock.SubBytesImpl(testState);
  cipherBlock.InvSubBytesImpl(testState);
  std::array<crypto::Byte, crypto::RIJNDAEL_BLOCK_SIZE> resultBlock = testState.GetBlock();

  // While subByte and invSubByte not implemented, test possibly will pass
  ASSERT_EQ(block, resultBlock);
}

TEST(RijndaelTestsShiftRows, ShiftRowsTesting) {
  crypto::State testState(originalBlock);
  RijndaelTestingImpl cipherBlock;
  cipherBlock.ShiftRowsImpl(testState);
  ASSERT_EQ(testState.GetBlock(), shiftedOrigBlock);
}

TEST(RijndaelTestsShiftRows, InvShiftRowsTesting) {
  crypto::State testState(shiftedOrigBlock);
  RijndaelTestingImpl cipherBlock;
  cipherBlock.InvShiftRowsImpl(testState);
  ASSERT_EQ(testState.GetBlock(), originalBlock);
}

TEST(RijndaelTestsShiftRows, ReversibilityShiftRowsTesting) {
  crypto::State testState(originalBlock);
  RijndaelTestingImpl cipherBlock;
  cipherBlock.ShiftRowsImpl(testState);
  cipherBlock.InvShiftRowsImpl(testState);
  ASSERT_EQ(testState.GetBlock(), originalBlock);
}
