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

constexpr std::array<crypto::Byte, crypto::RIJNDAEL_BLOCK_SIZE> plainText =
	{
		0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
	};

constexpr std::array<crypto::Byte, crypto::RIJNDAEL_BLOCK_SIZE> cipherText =
	{
		0x8e, 0xa2, 0xb7, 0xca, 0x51, 0x67, 0x45, 0xbf, 0xea, 0xfc, 0x49, 0x90, 0x4b, 0x49, 0x60, 0x89
	};

constexpr std::array<crypto::Byte, crypto::RIJNDAEL_KEY_SIZE> testKey = {
	0x00, 0x01, 0x02, 0x03,
	0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b,
	0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13,
	0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1a, 0x1b,
	0x1c, 0x1d, 0x1e, 0x1f
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
  void SubBytesImpl(crypto::State &state) const {
	subBytes(state);
  }

  void InvSubBytesImpl(crypto::State &state) const {
	invSubBytes(state);
  }

  void ShiftRowsImpl(crypto::State &state) const {
	shiftRows(state);
  }

  void InvShiftRowsImpl(crypto::State &state) const {
	invShiftRows(state);
  }

  void MixColumnsImpl(crypto::State &state) const {
	mixColumns(state);
  }

  void InvMixColumnsImpl(crypto::State &state) const {
	invMixColumns(state);
  }

  void AddRoundKeyImpl(crypto::State &state,
					   const std::array<crypto::KeySchedule::RoundKey, crypto::NUMBER_OF_COLUMNS> &roundKeys) const {
	addRoundKey(state, roundKeys);
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

  // While subByte and invSubByte not implemented, test possibly will pass
  ASSERT_EQ(testState.GetBlock(), originalBlock);
}

TEST(RijndaelTestsMixColumns, ReversibilityMixColumnsTesting) {
  crypto::State testState(originalBlock);
  RijndaelTestingImpl cipherBlock;
  cipherBlock.MixColumnsImpl(testState);
  cipherBlock.InvMixColumnsImpl(testState);

  // While subByte and invSubByte not implemented, test possibly will pass
  ASSERT_EQ(testState.GetBlock(), originalBlock);
}

TEST(RijndaelTestsAddRoundKey, AddRoundKeyTesting) {
  constexpr std::array<crypto::Byte, crypto::RIJNDAEL_BLOCK_SIZE> expectedResult =
	  {
		  0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0
	  };

  crypto::KeySchedule ks(testKey);
  crypto::State state(plainText);
  RijndaelTestingImpl cipherBlock;
  cipherBlock.AddRoundKeyImpl(state, {ks.RoundKeys[0], ks.RoundKeys[1], ks.RoundKeys[2], ks.RoundKeys[3]});
  ASSERT_EQ(state.GetBlock(), expectedResult);
}

TEST(RijndaelTestsEncrypt, EncryptMethodTesting) {
  crypto::Rijndael rijndael;
  std::array<crypto::Byte, crypto::RIJNDAEL_BLOCK_SIZE> outputResult = rijndael.Encrypt(plainText, testKey);
  ASSERT_EQ(outputResult, cipherText);
}

TEST(RijndaelTestsDecrypt, DecryptMethodTesting) {
  crypto::Rijndael rijndael;
  std::array<crypto::Byte, crypto::RIJNDAEL_BLOCK_SIZE> outputResult = rijndael.Decrypt(cipherText, testKey);
  ASSERT_EQ(outputResult, plainText);
}
