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

		namespace BypassInfo
		{
			enum class ExGFXSlot
			{
				AN2,
				LT3,
				BG3,
				BG2,
				FG3,
				BG1,
				FG2,
				FG1,
				SP4,
				SP3,
				SP2,
				SP1,
				LG4,
				LG3,
				LG2,
				LG1
			};

			enum class Layer3ActAsSetting
			{
				Water,
				Lava,
				MarioLava,
				CaveLava,
				Solid,
				Tile0x200,
				Tile0x201,
				Tile0x202,
				Tile0x203,
				Tile0x204,
				Tile0x205,
				Tile0x206,
				Tile0x207,
				Tile0x208,
				Tile0x209,
				Tile0x20A
			};

			enum class Layer3HorizontalScrollSetting
			{
				None,
				Constant,
				Variable,
				Variable2,
				Slow,
				Fast,
				Auto_ScrollLeftSlow,
				Auto_ScrollLeftNormal,
				Auto_ScrollLeftFast,
				Auto_ScrollLeftFast2,
				Auto_ScrollRightSlow,
				Auto_ScrollRightNormal,
				Auto_ScrollRightFast,
				Auto_ScrollRightFast2,
				NotUsed1,
				NotUsed2
			};

			enum class Layer3VerticalScrollSetting
			{
				None,
				Constant,
				Variable,
				Variable2,
				Slow,
				Fast,
				Auto_ScrollUpSlow,
				Auto_ScrollUpNormal,
				Auto_ScrollUpFast,
				Auto_ScrollUpFast2,
				Auto_ScrollDownSlow,
				Auto_ScrollDownNormal,
				Auto_ScrollDownFast,
				Auto_ScrollDownFast2,
				NotUsed1,
				NotUsed2
			};

			enum class Layer3InitialXPosition
			{
				_00,
				_04,
				_08,
				_10
			};

			enum class Layer3FileDestinationSetting
			{
				UnderStatusBar,
				StartOfLayer3,
				LastLineOfStatusBar,
				BottomHalfOfLayer3
			};

			enum class Layer3FileSizeSetting
			{
				_0x2000Bytes512x512,
				_0x1000Bytes512x256,
				_0x800Bytes256x256,
				DoNotUse
			};

			constexpr size_t EXGFX_NUMBER_SIZE = 2;
			constexpr size_t EXGFX_SLOT_AMOUNT = 16;
		}
	}
}
