#include "pch.h"
#include "Level.h"

using MWLParser::Level;

Level::Level(const std::vector<uint8_t>& mwl_bytes) : 
	header(Header(mwl_bytes)), data_pointers(DataPointers(mwl_bytes))
{
	palette_data = PaletteData(subVec(data_pointers.getPaletteDataIterators()));
	bypass_information = BypassInformation(subVec(data_pointers.getBypassInformationIterators()));
	exanimation_data = ExAnimationData(subVec(data_pointers.getExAnimationIterators()));
}

std::vector<uint8_t> Level::toBytes() const
{
	return std::vector<uint8_t>();
}
