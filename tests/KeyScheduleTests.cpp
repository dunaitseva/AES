#include "gtest/gtest.h"

#include "KeySchedule.hpp"
#include "RijndaelBaseDefinitions.hpp"

// KeyScheduleTesting class help to testing protected methods
// SubWord and RotWord by their public aliases ...TestingImpl.
class KeyScheduleTesting : public crypto::KeySchedule {
 public:
  KeyScheduleTesting() = default;
  explicit KeyScheduleTesting(const std::array<crypto::Byte, crypto::RIJNDAEL_KEY_SIZE> &key)
	  : crypto::KeySchedule(key) {}

  void SubWordTestingImpl(RoundKey &testKey) {
	SubWord(testKey);
  }

  void RotWordTestingImpl(RoundKey &testKey) {
	RotWord(testKey);
  }

  void KeyExpansionTestingImpl(const std::array<crypto::Byte, crypto::RIJNDAEL_KEY_SIZE> &key) {
	KeyExpansion(key);
  }
};

// Add fixture for testing KeySchedule constructor
class KeyScheduleFixture : public ::testing::Test {
 protected:
  KeyScheduleTesting ks;
  std::array<crypto::Byte, crypto::RIJNDAEL_KEY_SIZE> testKey;
  std::array<crypto::KeySchedule::RoundKey, crypto::NUMBER_OF_KEY> firstTestKeys;

  KeyScheduleFixture() : ks(), testKey(), firstTestKeys() {
	for (crypto::Byte i = 0; i < crypto::RIJNDAEL_KEY_SIZE; ++i) {
	  testKey[i] = i;
	}

	for (size_t i = 0; i < crypto::NUMBER_OF_KEY; ++i) {
	  firstTestKeys[i] = crypto::KeySchedule::RoundKey({testKey[crypto::NUMBER_OF_COLUMNS * i],
														testKey[crypto::NUMBER_OF_COLUMNS * i + 1],
														testKey[crypto::NUMBER_OF_COLUMNS * i + 2],
														testKey[crypto::NUMBER_OF_COLUMNS * i + 3]});
	}

	ks = KeyScheduleTesting(testKey);
  }
};

TEST_F(KeyScheduleFixture, ScheduleSizes) {
  ASSERT_EQ(ks.RoundKeys.size(), crypto::AMOUNT_OF_ROUND_KEYS);
  ASSERT_EQ(ks.RoundKeys[0].size(), crypto::NUMBER_OF_COLUMNS);
}

TEST_F(KeyScheduleFixture, ScheduleFirstRoundKeys) {
  for (size_t i = 0; i < firstTestKeys.size(); ++i) {
	ASSERT_TRUE(firstTestKeys[i] == ks.RoundKeys[i]);
  }
}

TEST_F(KeyScheduleFixture, SubWordTest) {
  crypto::KeySchedule::RoundKey expectedWord({0x63, 0x7c, 0x77, 0x7b});
  ks.SubWordTestingImpl(firstTestKeys[0]);
  ASSERT_TRUE(expectedWord == firstTestKeys[0]);
}

TEST_F(KeyScheduleFixture, RotWordTest) {
  crypto::KeySchedule::RoundKey startWord({0, 1, 2, 3});
  crypto::KeySchedule::RoundKey expectedWord({1, 2, 3, 0});
  ks.RotWordTestingImpl(startWord);
  ASSERT_TRUE(startWord == expectedWord);
}

TEST(KeyScheduleTesting, KeyExpansionTotalResult) {
  // It is very important and very big test =(
  // 0x60, 0x3d, 0xeb, 0x10,
  // 0x15, 0xca, 0x71, 0xbe,
  // 0x2b, 0x73, 0xae, 0xf0,
  // 0x85, 0x7d, 0x77, 0x81,
  // 0x1f, 0x35, 0x2c, 0x07,
  // 0x3b, 0x61, 0x08, 0xd7,
  // 0x2d, 0x98, 0x10, 0xa3,
  // 0x09, 0x14, 0xdf, 0xf4
  constexpr std::array<crypto::Byte, crypto::RIJNDAEL_KEY_SIZE> testKey =
	  {
		  0x60, 0x3d, 0xeb, 0x10, // 0
		  0x15, 0xca, 0x71, 0xbe, // 1
		  0x2b, 0x73, 0xae, 0xf0, // 2
		  0x85, 0x7d, 0x77, 0x81, // 3
		  0x1f, 0x35, 0x2c, 0x07, // 4
		  0x3b, 0x61, 0x08, 0xd7, // 5
		  0x2d, 0x98, 0x10, 0xa3, // 6
		  0x09, 0x14, 0xdf, 0xf4  // 7
	  };
  KeyScheduleTesting helpStructure;
  helpStructure.RoundKeys = {
	  {
		  {0x60, 0x3d, 0xeb, 0x10}, // 0
		  {0x15, 0xca, 0x71, 0xbe}, // 1
		  {0x2b, 0x73, 0xae, 0xf0}, // 2
		  {0x85, 0x7d, 0x77, 0x81}, // 3
		  {0x1f, 0x35, 0x2c, 0x07}, // 4
		  {0x3b, 0x61, 0x08, 0xd7}, // 5
		  {0x2d, 0x98, 0x10, 0xa3}, // 6
		  {0x09, 0x14, 0xdf, 0xf4}, // 7
		  {0x9b, 0xa3, 0x54, 0x11}, // 8
		  {0x8e, 0x69, 0x25, 0xaf}, // 9
		  {0xa5, 0x1a, 0x8b, 0x5f}, // 10
		  {0x20, 0x67, 0xfc, 0xde}, // 11
		  {0xa8, 0xb0, 0x9c, 0x1a}, // 12
		  {0x93, 0xd1, 0x94, 0xcd}, // 13
		  {0xbe, 0x49, 0x84, 0x6e}, // 14
		  {0xb7, 0x5d, 0x5b, 0x9a}, // 15
		  {0xd5, 0x9a, 0xec, 0xb8}, // 16
		  {0x5b, 0xf3, 0xc9, 0x17}, // 17
		  {0xfe, 0xe9, 0x42, 0x48}, // 18
		  {0xde, 0x8e, 0xbe, 0x96}, // 19
		  {0xb5, 0xa9, 0x32, 0x8a}, // 20
		  {0x26, 0x78, 0xa6, 0x47}, // 21
		  {0x98, 0x31, 0x22, 0x29}, // 22
		  {0x2f, 0x6c, 0x79, 0xb3}, // 23
		  {0x81, 0x2c, 0x81, 0xad}, // 24
		  {0xda, 0xdf, 0x48, 0xba}, // 25
		  {0x24, 0x36, 0x0a, 0xf2}, // 26
		  {0xfa, 0xb8, 0xb4, 0x64}, // 27
		  {0x98, 0xc5, 0xbf, 0xc9}, // 28
		  {0xbe, 0xbd, 0x19, 0x8e}, // 29
		  {0x26, 0x8c, 0x3b, 0xa7}, // 30
		  {0x09, 0xe0, 0x42, 0x14}, // 31
		  {0x68, 0x00, 0x7b, 0xac}, // 32
		  {0xb2, 0xdf, 0x33, 0x16}, // 33
		  {0x96, 0xe9, 0x39, 0xe4}, // 34
		  {0x6c, 0x51, 0x8d, 0x80}, // 35
		  {0xc8, 0x14, 0xe2, 0x04}, // 36
		  {0x76, 0xa9, 0xfb, 0x8a}, // 37
		  {0x50, 0x25, 0xc0, 0x2d}, // 38
		  {0x59, 0xc5, 0x82, 0x39}, // 39
		  {0xde, 0x13, 0x69, 0x67}, // 40
		  {0x6c, 0xcc, 0x5a, 0x71}, // 41
		  {0xfa, 0x25, 0x63, 0x95}, // 42
		  {0x96, 0x74, 0xee, 0x15}, // 43
		  {0x58, 0x86, 0xca, 0x5d}, // 44
		  {0x2e, 0x2f, 0x31, 0xd7}, // 45
		  {0x7e, 0x0a, 0xf1, 0xfa}, // 46
		  {0x27, 0xcf, 0x73, 0xc3}, // 47
		  {0x74, 0x9c, 0x47, 0xab}, // 48
		  {0x18, 0x50, 0x1d ,0xda}, // 49
		  {0xe2, 0x75, 0x7e, 0x4f}, // 50
		  {0x74, 0x01, 0x90, 0x5a}, // 51
		  {0xca, 0xfa, 0xaa, 0xe3}, // 52
		  {0xe4, 0xd5, 0x9b, 0x34}, // 53
		  {0x9a, 0xdf, 0x6a, 0xce}, // 54
		  {0xbd, 0x10, 0x19, 0x0d}, // 55
		  {0xfe, 0x48, 0x90, 0xd1}, // 56
		  {0xe6, 0x18, 0x8d, 0x0b}, // 57
		  {0x04, 0x6d, 0xf3, 0x44}, // 58
		  {0x70, 0x6c, 0x63, 0x1e}, // 59
	  }
  };

  crypto::KeySchedule ks(testKey);
  for (size_t i = 0; i < ks.RoundKeys.size(); ++i) {
	EXPECT_EQ(helpStructure.RoundKeys[i], ks.RoundKeys[i]);
//	std::cout << i << ") ";
//
//	for (size_t j = 0; j < helpStructure.RoundKeys[i].size(); ++j) {
//	  std::cout << static_cast<uint32_t>(helpStructure.RoundKeys[i][j]);
//	}
//	std::cout << ' ';
//	for (size_t j = 0; j < ks.RoundKeys[i].size(); ++j) {
//	  std::cout << static_cast<uint32_t>(ks.RoundKeys[i][j]);
//	}
//
//	std::cout << (helpStructure.RoundKeys[i] == ks.RoundKeys[i] ? " TRUE" : " FALSE") << '\n';
  }
}
