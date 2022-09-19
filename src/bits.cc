#include "bits.hh"
#include "util.hh"

std::vector <uint8_t> Bits::Split16(uint16_t integer) {
	return {
		(uint8_t) ((integer & 0xFF00) >> 010),
		(uint8_t) (integer & 0x00FF)
	};
}

uint16_t Bits::Join16(std::vector <uint8_t> bytes) {
	if (bytes.size() != 2) {
		Util::Error(
			"Bytes::Join16, invalid amount of bytes (given %lli)",
			(long long int) bytes.size()
		);
	}
	return ((uint16_t) bytes[0] << 010) | ((uint16_t) bytes[1]);
}

std::vector <uint8_t> Bits::Split32(uint32_t integer) {
	return {
		(uint8_t) ((integer & 0xFF000000) >> 030),
		(uint8_t) ((integer & 0x00FF0000) >> 020),
		(uint8_t) ((integer & 0x0000FF00) >> 010),
		(uint8_t) ((integer & 0x000000FF))
	};
}

uint32_t Bits::Join32(std::vector <uint8_t> bytes) {
	if (bytes.size() != 4) {
		Util::Error(
			"Bytes::Join32, invalid amount of bytes (given %lli)",
			(long long int) bytes.size()
		);
	}
	return (
		((uint32_t) bytes[0] << 030) |
		((uint32_t) bytes[1] << 020) |
		((uint32_t) bytes[2] << 010) |
		((uint32_t) bytes[3])
	);
}
