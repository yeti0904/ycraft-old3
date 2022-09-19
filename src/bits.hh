#ifndef YCRAFT_BITS_HH
#define YCRAFT_BITS_HH

#include "_components.hh"

namespace Bits {
	std::vector <uint8_t> Split16(uint16_t integer);
	uint16_t              Join16(std::vector <uint8_t> bytes);
	std::vector <uint8_t> Split32(uint32_t integer);
	uint32_t              Join32(std::vector <uint8_t> bytes);
}

#endif
