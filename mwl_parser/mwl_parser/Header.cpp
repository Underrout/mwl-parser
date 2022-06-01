#include "pch.h"
#include "Header.h"

using MWLParser::Header;

Header::Header(const std::vector<uint8_t>& mwl_bytes) :
	lunar_magic_version(getString(
		mwl_bytes.begin() + Offsets::Header::LUNAR_MAGIC_VERSION_START,
		mwl_bytes.begin() + Offsets::Header::LUNAR_MAGIC_VERSION_END
	)),
	comment_field(getString(
		mwl_bytes.begin() + Offsets::Header::COMMENT_FIELD_START,
		mwl_bytes.begin() + joinBytes(
			mwl_bytes.begin() + Offsets::Header::DATA_POINTER_TABLE_OFFSET_START,
			mwl_bytes.begin() + Offsets::Header::DATA_POINTER_TABLE_OFFSET_END
		)
	))
{

}

const std::string Header::getString(
	const std::vector<uint8_t>::const_iterator string_start,
	const std::vector<uint8_t>::const_iterator string_end
)
{
	const std::string result = std::string(string_start, string_end);
	return result;
}

const std::string& Header::getLunarMagicVersion()
{
	return lunar_magic_version;
}

const std::string& Header::getCommentField()
{
	return comment_field;
}
