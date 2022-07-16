#pragma once
#include "Convertible.h"
#include "MWLConstants.h"
#include "ByteUtility.h"

namespace MWLParser
{
	struct PaletteData : public virtual Convertible
	{
		std::vector<size_t> main_palette{};
		size_t background_color;

		PaletteData() = default;
		PaletteData(const std::vector<uint8_t>& mwl_bytes);
		PaletteData(const std::vector<size_t>& palette, size_t background_color);

		std::shared_ptr<Convertible> fromBytes(const std::vector<uint8_t>& bytes);
		std::vector<uint8_t> toBytes() const;
	};
}
