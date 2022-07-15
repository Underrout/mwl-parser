#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace MWLParser 
{
	size_t joinBytes(const std::vector<uint8_t>::const_iterator first_byte, size_t byte_amount);
	size_t joinBytes(const std::vector<uint8_t>::const_iterator start, const std::vector<uint8_t>::const_iterator end);
	uint32_t join4Bytes(const std::vector<uint8_t>::const_iterator first_byte);
	std::vector<uint8_t> splitIntoBytes(size_t number, size_t byte_amount);
	std::vector<uint8_t> strToBytes(const std::string& s);
}
