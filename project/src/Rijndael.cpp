#include "Rijndael.hpp"

#include <algorithm>

#include "BaseBlockCipher.hpp"
#include "BaseCryptoUtils.hpp"

namespace crypto {
std::array<Byte, RIJNDAEL_BLOCK_SIZE> Rijndael::Encrypt(const std::array<Byte, RIJNDAEL_BLOCK_SIZE> &block,
														const std::array<Byte, RIJNDAEL_KEY_SIZE> &key) const {
  State blockState(block);
  KeySchedule ks(key);

  addRoundKey(blockState, {ks.RoundKeys[0], ks.RoundKeys[1], ks.RoundKeys[2], ks.RoundKeys[3]});

  for (size_t i = 1; i < NUMBER_OF_ROUNDS; ++i) {
	subBytes(blockState);
	shiftRows(blockState);
	mixColumns(blockState);
	size_t rkShift = i * NUMBER_OF_COLUMNS; // round keys shift in key schedule table
	addRoundKey(blockState,
				{ks.RoundKeys[rkShift],
				 ks.RoundKeys[rkShift + 1],
				 ks.RoundKeys[rkShift + 2],
				 ks.RoundKeys[rkShift + 3]});
  }

  subBytes(blockState);
  shiftRows(blockState);
  size_t shift = NUMBER_OF_COLUMNS * NUMBER_OF_ROUNDS;
  addRoundKey(blockState,
			  {ks.RoundKeys[shift],
			   ks.RoundKeys[shift + 1],
			   ks.RoundKeys[shift + 2],
			   ks.RoundKeys[shift + 3]});

  return blockState.GetBlock();
}

std::array<Byte, RIJNDAEL_BLOCK_SIZE> Rijndael::Decrypt(const std::array<Byte, RIJNDAEL_BLOCK_SIZE> &block,
														const std::array<Byte, RIJNDAEL_KEY_SIZE> &key) const {
  State blockState(block);
  KeySchedule ks(key);

  size_t shift = NUMBER_OF_ROUNDS * NUMBER_OF_COLUMNS;
  addRoundKey(blockState,
			  {ks.RoundKeys[shift],
			   ks.RoundKeys[shift + 1],
			   ks.RoundKeys[shift + 2],
			   ks.RoundKeys[shift + 3]});

  for (size_t i = NUMBER_OF_ROUNDS - 1; i >= 1; --i) {
	invShiftRows(blockState);
	invSubBytes(blockState);
	size_t ksShift = i * NUMBER_OF_COLUMNS;
	addRoundKey(blockState,
				{ks.RoundKeys[ksShift],
				 ks.RoundKeys[ksShift + 1],
				 ks.RoundKeys[ksShift + 2],
				 ks.RoundKeys[ksShift + 3]});
	invMixColumns(blockState);
  }

  invShiftRows(blockState);
  invSubBytes(blockState);
  addRoundKey(blockState, {ks.RoundKeys[0], ks.RoundKeys[1], ks.RoundKeys[2], ks.RoundKeys[3]});

  return blockState.GetBlock();
}

void Rijndael::addRoundKey(State &state, const std::array<KeySchedule::RoundKey, NUMBER_OF_COLUMNS> &roundKeys) const {
  for (size_t i = 0; i < NUMBER_OF_COLUMNS; ++i) {
	for (size_t j = 0; j < NUMBER_OF_STATE_ROWS; ++j) {
	  state.blockTable[j][i] ^= roundKeys[i][j];
	}
  }
}

void Rijndael::subBytes(State &state) const {
  for (auto &row : state.blockTable) {
	std::transform(row.begin(), row.end(), row.begin(), [](Byte &b) -> Byte { return SBox[b]; });
  }
}

void Rijndael::shiftRows(State &state) const {
  size_t counter = 0;
  for (auto &row : state.blockTable) {
	std::rotate(row.begin(), row.begin() + counter, row.end());
	++counter;
  }
}

void Rijndael::mixColumns(State &state) const {
  constexpr Byte polyMatrixMul[NUMBER_OF_STATE_ROWS][NUMBER_OF_COLUMNS] = {
	  {0x02, 0x03, 0x01, 0x01},
	  {0x01, 0x02, 0x03, 0x01},
	  {0x01, 0x01, 0x02, 0x03},
	  {0x03, 0x01, 0x01, 0x02}
  };

  for (size_t i = 0; i < NUMBER_OF_COLUMNS; ++i) {
	std::array<Byte, NUMBER_OF_STATE_ROWS> mixedColumn{};
	for (size_t j = 0; j < NUMBER_OF_STATE_ROWS; ++j) {
	  mixedColumn[j] = GaluaMul(polyMatrixMul[j][0], state.blockTable[0][i]);
	  for (size_t k = 1; k < NUMBER_OF_COLUMNS; ++k) {
		mixedColumn[j] ^= GaluaMul(polyMatrixMul[j][k], state.blockTable[k][i]);
	  }
	}

	for (size_t j = 0; j < NUMBER_OF_STATE_ROWS; ++j) {
	  state.blockTable[j][i] = mixedColumn[j];
	}
  }
}

void Rijndael::invSubBytes(State &state) const {
  for (auto &row : state.blockTable) {
	std::transform(row.begin(), row.end(), row.begin(), [](Byte &b) -> Byte { return InvSBox[b]; });
  }
}

void Rijndael::invShiftRows(State &state) const {
  int counter = 0;
  for (auto &row : state.blockTable) {
	std::rotate(row.rbegin(), row.rbegin() + counter, row.rend());
	++counter;
  }
}

void Rijndael::invMixColumns(State &state) const {
  constexpr Byte polyMatrixMul[NUMBER_OF_STATE_ROWS][NUMBER_OF_COLUMNS] = {
	  {0x0e, 0x0b, 0x0d, 0x09},
	  {0x09, 0x0e, 0x0b, 0x0d},
	  {0x0d, 0x09, 0x0e, 0x0b},
	  {0x0b, 0x0d, 0x09, 0x0e}
  };

  for (size_t i = 0; i < NUMBER_OF_COLUMNS; ++i) {
	std::array<Byte, NUMBER_OF_STATE_ROWS> mixedColumn{};
	for (size_t j = 0; j < NUMBER_OF_STATE_ROWS; ++j) {
	  mixedColumn[j] = GaluaMul(polyMatrixMul[j][0], state.blockTable[0][i]);
	  for (size_t k = 1; k < NUMBER_OF_COLUMNS; ++k) {
		mixedColumn[j] ^= GaluaMul(polyMatrixMul[j][k], state.blockTable[k][i]);
	  }
	}

	for (size_t j = 0; j < NUMBER_OF_STATE_ROWS; ++j) {
	  state.blockTable[j][i] = mixedColumn[j];
	}
  }
}

} // namespace crypto