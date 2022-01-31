#include "KeySchedule.hpp"

namespace crypto {
KeySchedule::KeySchedule([[maybe_unused]] const std::string_view &key) : RoundKeys() {}

[[maybe_unused]] void KeySchedule::KeyExpansion([[maybe_unused]] const std::string_view &key) {}

[[maybe_unused]] void KeySchedule::SubWord([[maybe_unused]] RoundKey &key) {}

[[maybe_unused]] void KeySchedule::RotWord([[maybe_unused]] RoundKey &key) {}
} // namespace crypto