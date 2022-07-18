#include "pch.h"

#include "ByteUtility.h"
#include <iterator>


size_t MWLParser::joinBytes(const std::vector<uint8_t> vec, size_t start_idx, size_t byte_amount)
{
	auto start = vec.begin() + start_idx;
	return joinBytes(start, byte_amount);
}

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

std::vector<uint8_t> MWLParser::splitIntoBytes(size_t number, size_t byte_amount)
{
	std::vector<uint8_t> bytes{};

	for (size_t i = 0; i != byte_amount; ++i)
	{
		bytes.push_back((number >> (i * 8)) & 0xFF);
	}

	return bytes;
}

std::vector<uint8_t> MWLParser::subVec(const std::vector<uint8_t>& vec, size_t start)
{
	return subVec(vec, start, vec.size());
}

std::vector<uint8_t> MWLParser::subVec(const std::vector<uint8_t>& vec, size_t start, size_t end)
{
	std::vector<uint8_t> new_vec{};
	std::copy(vec.begin() + start, vec.begin() + end, std::back_inserter(new_vec));
	return new_vec;
}

std::vector<uint8_t> MWLParser::subVec(const std::vector<uint8_t>::const_iterator start, const std::vector<uint8_t>::const_iterator end)
{
	std::vector<uint8_t> new_vec{};
	std::copy(start, end, std::back_inserter(new_vec));
	return new_vec;
}

std::vector<uint8_t> MWLParser::subVec(const std::pair<std::vector<uint8_t>::const_iterator, std::vector<uint8_t>::const_iterator> start_end_pair)
{
	return subVec(start_end_pair.first, start_end_pair.second);
}
