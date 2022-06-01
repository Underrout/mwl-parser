#pragma once

#include <string>
#include <vector>

#include "StaticMWLOffsets.h"
#include "ByteUtility.h"

namespace MWLParser 
{
	class Header
	{
	private:
		const std::string lunar_magic_version;
		const std::string comment_field;

		const std::string getString(
			const std::vector<uint8_t>::const_iterator string_start, 
			const std::vector<uint8_t>::const_iterator string_end
		);

	public:
		Header(const std::vector<uint8_t>& mwl_bytes);

		const std::string& getLunarMagicVersion();
		const std::string& getCommentField();
	};
}
