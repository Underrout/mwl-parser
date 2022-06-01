#include "pch.h"
#include "DataPointers.h"

using MWLParser::DataPointers;
using MWLParser::DataIteratorPair;

DataPointers::DataPointers(const std::vector<uint8_t>& mwl_bytes) :
	mwl_start(mwl_bytes.begin()),
	data_pointers_start(getDataPointersStart(mwl_bytes)),
	level_information(
		getDataAreaIterators(
			Offsets::DataPointers::LEVEL_INFORMATION_OFFSET_START,
			Offsets::DataPointers::LEVEL_INFORMATION_OFFSET_END,
			Offsets::DataPointers::LEVEL_INFORMATION_SIZE_START,
			Offsets::DataPointers::LEVEL_INFORMATION_SIZE_END
		)
	),
	layer_1_data(
		getDataAreaIterators(
			Offsets::DataPointers::LAYER_1_DATA_OFFSET_START,
			Offsets::DataPointers::LAYER_1_DATA_OFFSET_END,
			Offsets::DataPointers::LAYER_1_DATA_SIZE_START,
			Offsets::DataPointers::LAYER_1_DATA_SIZE_END
		)
	),
	layer_2_data(
		getDataAreaIterators(
			Offsets::DataPointers::LAYER_2_DATA_OFFSET_START,
			Offsets::DataPointers::LAYER_2_DATA_OFFSET_END,
			Offsets::DataPointers::LAYER_2_DATA_SIZE_START,
			Offsets::DataPointers::LAYER_2_DATA_SIZE_END
		)
	),
	sprite_data(
		getDataAreaIterators(
			Offsets::DataPointers::SPRITE_DATA_OFFSET_START,
			Offsets::DataPointers::SPRITE_DATA_OFFSET_END,
			Offsets::DataPointers::SPRITE_DATA_SIZE_START,
			Offsets::DataPointers::SPRITE_DATA_SIZE_END
		)
	),
	palette_data(
		getDataAreaIterators(
			Offsets::DataPointers::PALETTE_DATA_OFFSET_START,
			Offsets::DataPointers::PALETTE_DATA_OFFSET_END,
			Offsets::DataPointers::PALETTE_DATA_SIZE_START,
			Offsets::DataPointers::PALETTE_DATA_SIZE_END
		)
	),
	secondary_entrances(
		getDataAreaIterators(
			Offsets::DataPointers::SECONDARY_ENTRANCES_OFFSET_START,
			Offsets::DataPointers::SECONDARY_ENTRANCES_OFFSET_END,
			Offsets::DataPointers::SECONDARY_ENTRANCES_SIZE_START,
			Offsets::DataPointers::SECONDARY_ENTRANCES_SIZE_END
		)
	),
	exanimation(
		getDataAreaIterators(
			Offsets::DataPointers::EXANIMATION_OFFSET_START,
			Offsets::DataPointers::EXANIMATION_OFFSET_END,
			Offsets::DataPointers::EXANIMATION_SIZE_START,
			Offsets::DataPointers::EXANIMATION_SIZE_END
		)
	),
	bypass_information(
		getDataAreaIterators(
			Offsets::DataPointers::BYPASS_INFORMATION_OFFSET_START,
			Offsets::DataPointers::BYPASS_INFORMATION_OFFSET_END,
			Offsets::DataPointers::BYPASS_INFORMATION_SIZE_START,
			Offsets::DataPointers::BYPASS_INFORMATION_SIZE_END
		)
	)
{

};

const std::vector<uint8_t>::const_iterator DataPointers::getDataPointersStart(const std::vector<uint8_t>& mwl_bytes)
{
	size_t data_pointer_offset = join4Bytes(mwl_start + Offsets::Header::DATA_POINTER_TABLE_OFFSET_START);

	return mwl_start + data_pointer_offset;
}

DataPointers::ConstDataIteratorPair DataPointers::getDataAreaIterators(
	size_t data_pointer_offset_start, size_t data_pointer_offset_end,
	size_t data_pointer_size_start, size_t data_pointer_size_end
)
{
	const auto offset = joinBytes(
		data_pointers_start + data_pointer_offset_start,
		data_pointers_start + data_pointer_offset_end
	);
	const auto size = joinBytes(
		data_pointers_start + data_pointer_size_start,
		data_pointers_start + data_pointer_size_end
	);

	return std::make_pair(mwl_start + offset, mwl_start + offset + size);
}

DataIteratorPair DataPointers::getMutableIterators(ConstDataIteratorPair const_iterator_pair)
{
	std::vector<uint8_t>::const_iterator start = const_iterator_pair.first;
	std::vector<uint8_t>::const_iterator end = const_iterator_pair.second;

	return std::make_pair(start, end);
}

DataIteratorPair DataPointers::getLevelInformationIterators()
{
	return getMutableIterators(level_information);
}

DataIteratorPair DataPointers::getLayer1DataIterators() 
{
	return getMutableIterators(layer_1_data);
}

DataIteratorPair DataPointers::getLayer2DataIterators() 
{
	return getMutableIterators(layer_2_data);
}

DataIteratorPair DataPointers::getSpriteDataIterators() 
{
	return getMutableIterators(sprite_data);
}

DataIteratorPair DataPointers::getPaletteDataIterators() 
{
	return getMutableIterators(palette_data);
}

DataIteratorPair DataPointers::getSecondaryEntrancesIterators() 
{
	return getMutableIterators(secondary_entrances);
}

DataIteratorPair DataPointers::getExAnimationIterators() 
{
	return getMutableIterators(exanimation);
}

DataIteratorPair DataPointers::getBypassInformationIterators() 
{
	return getMutableIterators(bypass_information);
}
