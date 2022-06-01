#include "pch.h"

#include "ByteUtility.h"

size_t MWLParser::joinBytes(const std::vector<uint8_t>::const_iterator first_byte, size_t byte_amount)
{
	std::vector<uint8_t>::const_iterator it = first_byte;

	size_t res = 0;
	
	for (size_t i = 0; i != byte_amount; ++i)
	{
		res += *it++ << i * 8;
	}

	return res;
}

size_t MWLParser::joinBytes(const std::vector<uint8_t>::const_iterator start, const std::vector<uint8_t>::const_iterator end)
{
	size_t res = 0;
	size_t i = 0;
	for (std::vector<uint8_t>::const_iterator it = start; it != end; ++it)
	{
		res += *it << i++ * 8;
	}

	return res;
}

uint32_t MWLParser::join4Bytes(const std::vector<uint8_t>::const_iterator first_byte)
{
	return static_cast<uint32_t>(MWLParser::joinBytes(first_byte, 4));
}

std::vector<uint8_t> MWLParser::strToBytes(const std::string& s)
{
	return std::vector<uint8_t>(s.begin(), s.end());
}

std::vector<uint8_t> MWLParser::splitInto4Bytes(uint32_t four_bytes)
{
	std::vector<uint8_t> bytes{};

	for (size_t i = 0; i != 4; ++i)
	{
		bytes.push_back((four_bytes >> (i * 8)) & 0xFF);
	}

	return bytes;
}
