#pragma once

#include <string>
#include "StaticMWLOffsets.h"

namespace MWLParser
{
	namespace Constants
	{
		namespace Header
		{
			constexpr const char* START_OF_FILE_CHARS = "LM";
			constexpr size_t DATA_POINTER_AMOUNT = 8;
			constexpr size_t DATA_POINTER_TABLE_SIZE = (Offsets::DataPointers::DATA_POINTER_OFFSET_SIZE + 
				Offsets::DataPointers::DATA_POINTER_SIZE_SIZE) * DATA_POINTER_AMOUNT;
		}

		namespace PaletteData
		{
			constexpr size_t HEADER_SIZE = 8;
			constexpr size_t PALETTE_DATA_OFFSET = HEADER_SIZE;
			constexpr size_t MAIN_PALETTE_COLOR_AMOUNT = 256;
			constexpr size_t COLOR_BYTE_SIZE = 2;
			constexpr size_t BACKGROUND_COLOR_OFFSET = PALETTE_DATA_OFFSET + MAIN_PALETTE_COLOR_AMOUNT * COLOR_BYTE_SIZE;
		}
	}
}
