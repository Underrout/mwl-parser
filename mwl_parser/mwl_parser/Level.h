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
		std::shared_ptr<Header> header;
		std::shared_ptr<DataPointers> data_pointers;
		std::shared_ptr<PaletteData> palette_data;
		std::shared_ptr<BypassInformation> bypass_information;
		std::shared_ptr<BaseExAnimationData> exanimation_data;

		Level() = default;
		Level(const std::vector<uint8_t>& mwl_bytes);

		std::vector<uint8_t> toBytes() const;
	};
}
