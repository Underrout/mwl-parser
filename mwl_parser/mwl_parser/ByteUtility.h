#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace MWLParser 
{
	size_t joinBytes(const std::vector<uint8_t>::const_iterator first_byte, size_t byte_amount);
	size_t joinBytes(const std::vector<uint8_t>::const_iterator start, const std::vector<uint8_t>::const_iterator end);
	size_t joinBytes(const std::vector<uint8_t> vec, size_t start_idx, size_t byte_amount);
	uint32_t join4Bytes(const std::vector<uint8_t>::const_iterator first_byte);
	std::vector<uint8_t> splitIntoBytes(size_t number, size_t byte_amount);
	std::vector<uint8_t> strToBytes(const std::string& s);

	std::vector<uint8_t> subVec(const std::vector<uint8_t>& vec, size_t start);
	std::vector<uint8_t> subVec(const std::vector<uint8_t>& vec, size_t start, size_t end);

	std::vector<uint8_t> subVec(const std::vector<uint8_t>::const_iterator start, const std::vector<uint8_t>::const_iterator end);

	std::vector<uint8_t> subVec(const std::pair<std::vector<uint8_t>::const_iterator, std::vector<uint8_t>::const_iterator> start_end_pair);
}
