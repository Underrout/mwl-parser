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
	}
}
