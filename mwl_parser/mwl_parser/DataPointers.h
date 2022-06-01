#pragma once

#include <vector>
#include <utility>

#include "ByteUtility.h"
#include "StaticMWLOffsets.h"

namespace MWLParser {
	using DataIteratorPair = std::pair<std::vector<uint8_t>::const_iterator, std::vector<uint8_t>::const_iterator>;

	class DataPointers
	{
		using ConstDataIteratorPair = const std::pair<const std::vector<uint8_t>::const_iterator, const std::vector<uint8_t>::const_iterator>;

	private:
		const std::vector<uint8_t>::const_iterator mwl_start;

		const std::vector<uint8_t>::const_iterator data_pointers_start;

		ConstDataIteratorPair level_information, layer_1_data, layer_2_data, sprite_data, palette_data,
			secondary_entrances, exanimation, bypass_information;


		const std::vector<uint8_t>::const_iterator getDataPointersStart(const std::vector<uint8_t>& mwl_bytes);

		ConstDataIteratorPair getDataAreaIterators(
			size_t data_pointer_offset_start, size_t data_pointer_offset_end,
			size_t data_pointer_size_start, size_t data_pointer_size_end
		);

		DataIteratorPair getMutableIterators(ConstDataIteratorPair const_iterator_pair);

	public:
		DataPointers(const std::vector<uint8_t>& mwl_bytes);

		DataIteratorPair getLevelInformationIterators();
		DataIteratorPair getLayer1DataIterators();
		DataIteratorPair getLayer2DataIterators();
		DataIteratorPair getSpriteDataIterators();
		DataIteratorPair getPaletteDataIterators();
		DataIteratorPair getSecondaryEntrancesIterators();
		DataIteratorPair getExAnimationIterators();
		DataIteratorPair getBypassInformationIterators();
	};
}
