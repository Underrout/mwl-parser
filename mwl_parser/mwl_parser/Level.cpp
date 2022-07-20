#include "pch.h"
#include "Level.h"

using MWLParser::Level;

Level::Level(const std::vector<uint8_t>& mwl_bytes) : 
	header(std::make_shared<Header>(mwl_bytes)), data_pointers(std::make_shared<DataPointers>(mwl_bytes))
{
	palette_data = std::make_shared<PaletteData>(subVec(data_pointers->getPaletteDataIterators()));
	bypass_information = std::make_shared<BypassInformation>(subVec(data_pointers->getBypassInformationIterators()));
	exanimation_data = BaseExAnimationData::getExAnimationData(subVec(data_pointers->getExAnimationIterators()));
}

std::vector<uint8_t> Level::toBytes() const
{
	return std::vector<uint8_t>();
}
