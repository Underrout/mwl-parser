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
