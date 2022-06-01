#include "pch.h"
#include "Header.h"

using MWLParser::Header;
using MWLParser::Convertible;

Header::Header(const std::vector<uint8_t>& mwl_bytes)
{
	const auto mwl_start = mwl_bytes.begin();

	this->lunar_magic_version = std::string(
		mwl_start + Offsets::Header::LUNAR_MAGIC_VERSION_START,
		mwl_start + Offsets::Header::LUNAR_MAGIC_VERSION_END
	);

	this->exported_from_sma2 = *(mwl_start + Offsets::Header::SPECIAL_INFORMATION_START) & 1;

	size_t comment_field_end = joinBytes(
		mwl_start + Offsets::Header::DATA_POINTER_TABLE_OFFSET_START,
		mwl_start + Offsets::Header::DATA_POINTER_TABLE_OFFSET_END
	);

	this->comment_field = std::string(
		mwl_start + Offsets::Header::COMMENT_FIELD_START,
		mwl_start + comment_field_end
	);
}

Header::Header(const std::string& lunar_magic_version, const std::string& comment_field, bool exported_from_sma2)
{
	this->lunar_magic_version = lunar_magic_version;
	this->comment_field = comment_field;
	this->exported_from_sma2 = exported_from_sma2;
}

std::shared_ptr<Convertible> Header::fromBytes(const std::vector<uint8_t>& bytes)
{
	return std::make_shared<Header>(bytes);
}

std::vector<uint8_t> Header::toBytes() const
{
	std::vector<uint8_t> bytes{};

	// constant characters at start of file

	for (size_t i = 0; i != strlen(Constants::Header::START_OF_FILE_CHARS); ++i)
	{
		bytes.push_back(Constants::Header::START_OF_FILE_CHARS[i]);
	}

	// lunar magic version number

	const auto version = strToBytes(lunar_magic_version);
	bytes.insert(bytes.end(), version.begin(), version.end());

	// data pointer table offset + size

	const auto offset = splitInto4Bytes(
		Offsets::Header::COMMENT_FIELD_START + comment_field.size());
	bytes.insert(bytes.end(), offset.begin(), offset.end());

	const auto size = splitInto4Bytes(
		Constants::Header::DATA_POINTER_TABLE_SIZE);
	bytes.insert(bytes.end(), size.begin(), size.end());

	// special flags

	bytes.insert(bytes.end(), { exported_from_sma2, 0, 0, 0 });

	// comment field

	const auto comment = strToBytes(comment_field);
	bytes.insert(bytes.end(), comment.begin(), comment.end());

	return bytes;
}
