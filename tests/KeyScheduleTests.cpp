#include "gtest/gtest.h"

#include "KeySchedule.hpp"
#include "RijndaelBaseDefinitions.hpp"

// KeyScheduleTesting class help to testing protected methods
// SubWord and RotWord by their public aliases ...TestingImpl.
class KeyScheduleTesting : public crypto::KeySchedule {
 public:
  KeyScheduleTesting() = default;
  explicit KeyScheduleTesting(const std::array<crypto::Byte, crypto::RIJNDAEL_KEY_SIZE> &key) : crypto::KeySchedule(key) {}

  void SubWordTestingImpl(RoundKey &testKey) {
	SubWord(testKey);
  }

  void RotWordTestingImpl(RoundKey &testKey) {
	RotWord(testKey);
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

