#pragma once

#include <vector>

#include "Convertible.h"
#include "Header.h"
#include "DataPointers.h"
#include "PaletteData.h"
#include "BypassInformation.h"
#include "ExAnimationData.h"

namespace MWLParser
{
	class Level : public virtual Convertible
	{
	public:
		Header header;
		DataPointers data_pointers;
		PaletteData palette_data;
		BypassInformation bypass_information;
		ExAnimationData exanimation_data;

		Level() = default;
		Level(const std::vector<uint8_t>& mwl_bytes);

		std::vector<uint8_t> toBytes() const;
	};
}
