#pragma once

#include <string>
#include <vector>
#include <memory>

#include "StaticMWLOffsets.h"
#include "ByteUtility.h"
#include "Convertible.h"
#include "MWLConstants.h"

namespace MWLParser 
{
	struct Header : public virtual Convertible
	{
		std::string lunar_magic_version;
		std::string comment_field;
		bool exported_from_sma2;

		Header() = default;
		Header(const std::vector<uint8_t>& mwl_bytes);
		Header(const std::string& lunar_magic_version, const std::string& comment_field, bool exported_from_sma2);

		std::shared_ptr<Convertible> fromBytes(const std::vector<uint8_t>& bytes);
		std::vector<uint8_t> toBytes() const;
	};
}
