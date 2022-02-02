#include "KeySchedule.hpp"

#include <algorithm>

#include <RijndaelBaseDefinitions.hpp>
#include <BaseCryptoUtils.hpp>

namespace crypto {
KeySchedule::KeySchedule(const std::array<Byte, RIJNDAEL_KEY_SIZE> &key) : RoundKeys() { KeyExpansion(key); }

void KeySchedule::KeyExpansion(const std::array<Byte, RIJNDAEL_KEY_SIZE> &key) {
  for (size_t i = 0; i < NUMBER_OF_KEY; ++i) {
	RoundKeys[i] = RoundKey({key[NUMBER_OF_COLUMNS * i],
							 key[NUMBER_OF_COLUMNS * i + 1],
							 key[NUMBER_OF_COLUMNS * i + 2],
							 key[NUMBER_OF_COLUMNS * i + 3]});
  }

  for (size_t i = NUMBER_OF_KEY; i < AMOUNT_OF_ROUND_KEYS; ++i) {
	RoundKey tmp = RoundKeys[i - 1];
	if (i % NUMBER_OF_KEY == 0) {
	  RotWord(tmp);
	  SubWord(tmp);
	  tmp = XOR_WORDS(tmp, Rcon.at(i / NUMBER_OF_KEY));
	}

	if (i % NUMBER_OF_KEY == NUMBER_OF_COLUMNS) {
	  SubWord(tmp);
	}

	RoundKeys[i] = XOR_WORDS(RoundKeys[i - NUMBER_OF_KEY], tmp);
  }
}

void KeySchedule::SubWord(RoundKey &key) {
  /*
   * SubWord is a function, that takes a byte from current input and
   * perform substitution from SBox on this byte position in array
   */
  std::transform(key.begin(), key.end(), key.begin(),
				 [](const Byte &byte) -> Byte { return SBox[byte]; });
}

void KeySchedule::RotWord(RoundKey &key) {
  /*
   * RotWord is a function, that rotate current input so that
   * the first byte puts in the tail of array and other bytes
   * shift in left for one position for each byte
   */
  std::rotate(key.begin(), key.begin() + 1, key.end());
}
} // namespace crypto