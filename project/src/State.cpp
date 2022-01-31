#include "State.hpp"

#include <array>

#include "BaseBlockCipher.hpp"

namespace crypto {
State::State([[maybe_unused]] const std::array<Byte, RIJNDAEL_BLOCK_SIZE> &block) : blockTable() {}
} // namespace crypto