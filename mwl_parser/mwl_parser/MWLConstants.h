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

			// from -0x400 to 0x3FF
			constexpr size_t LAYER_3_Y_POSITION_RANGE = 0x800;
		}

		namespace ExAnimation
		{
			enum class CustomTriggerInitState
			{
				NotInitialized,
				On,
				Off
			};

			enum class AltGfx
			{
				_060,
				_061,
				_062,
				_063
			};

			constexpr size_t ANIMATION_HEADER_OFFSET = 0;
			constexpr size_t ANIMATION_HEADER_SIZE = 8;

			constexpr size_t ANIMATION_SETTINGS_OFFSET = ANIMATION_HEADER_OFFSET;
			constexpr size_t ANIMATION_SETTINGS_SIZE = 1;

			constexpr size_t GENERAL_ANIMATION_START_OFFSET = ANIMATION_HEADER_OFFSET +
				ANIMATION_HEADER_SIZE;
			
			constexpr size_t GENERAL_ANIMATION_HIGHEST_USED_SLOT_OFFSET =
				GENERAL_ANIMATION_START_OFFSET;
			constexpr size_t GENERAL_ANIMATION_HIGHEST_USED_SLOT_SIZE = 1;

			constexpr size_t GENERAL_ANIMATION_ALTERNATE_GFX_FILE_OFFSET =
				GENERAL_ANIMATION_HIGHEST_USED_SLOT_OFFSET +
				GENERAL_ANIMATION_HIGHEST_USED_SLOT_SIZE;
			constexpr size_t GENERAL_ANIMATION_ALTERNATE_GFX_FILE_SIZE = 1;

			constexpr size_t GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_OFFSET =
				GENERAL_ANIMATION_ALTERNATE_GFX_FILE_OFFSET +
				GENERAL_ANIMATION_ALTERNATE_GFX_FILE_SIZE;
			constexpr size_t GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_SIZE = 2;

			constexpr size_t GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_STATES_OFFSET =
				GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_OFFSET +
				GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_SIZE;
			constexpr size_t GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_STATES_SIZE = 2;

			constexpr size_t GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_OFFSET =
				GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_STATES_OFFSET +
				GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_STATES_SIZE;
			constexpr size_t GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_SIZE = 2;

			constexpr size_t GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_STATES_OFFSET =
				GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_OFFSET +
				GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_SIZE;
			constexpr size_t GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_STATES_SIZE = 1;

			constexpr size_t GENERAL_ANIMATION_INDICE_LIST_ENTRY_SIZE = 2;

			constexpr size_t GENERAL_ANIMATION_UNUSED_SLOT_INDICE_VALUE = 0;

			enum class AnimationType
			{
				NotUsed,
				_1_8x8,
				_2_8x8s_line,
				_3_8x8s_line,
				_4_8x8s_line,
				_5_8x8s_line,
				_6_8x8s_line,
				_7_8x8s_line,
				_8_8x8s_line,
				_0x0C_8x8s_line,
				_0x10_8x8s_line,
				_0x14_8x8s_line,
				_0x18_8x8s_line,
				_0x1C_8x8s_line,
				_0x20_8x8s_line,
				_1_8x8_2bpp,
				_2_8x8s_stacked,
				_4_8x8s_16x16,
				_8_8x8s_32_16,
				Palette,
				Palette_Working,
				Palette_Working_StopOnFade,
				PaletteBackAreaColor,
				PaletteBackAreaColor_StopOnFade,
				PaletteRotateRight,
				PaletteRotateRight_RevOnTrigger,
				PaletteRotateLeft,
				PaletteRotateLeft_RevOnTrigger
			};

			constexpr AnimationType FIRST_PALETTE_ANIMATION_TYPE = AnimationType::Palette;

			enum class Trigger
			{
				None,
				POW,
				SilverPOW,
				ON_OFF,
				HaveStar,
				Timer_100,
				Timer_100_OneShot,
				_5_YoshiCoins,
				_5_YoshiCoins_OneShot,
				DoNotUse0,
				DoNotUse1,
				DoNotUse2,
				DoNotUse3,
				DoNotUse4,
				DoNotUse5,
				PrecisionTimerPaletteRotate,
				Manual0,
				Manual1,
				Manual2,
				Manual3,
				Manual4,
				Manual5,
				Manual6,
				Manual7,
				Manual8,
				Manual9,
				ManualA,
				ManualB,
				ManualC,
				ManualD,
				ManualE,
				ManualF,
				Custom0,
				Custom1,
				Custom2,
				Custom3,
				Custom4,
				Custom5,
				Custom6,
				Custom7,
				Custom8,
				Custom9,
				CustomA,
				CustomB,
				CustomC,
				CustomD,
				CustomE,
				CustomF,
				OneShot00,
				OneShot01,
				OneShot02,
				OneShot03,
				OneShot04,
				OneShot05,
				OneShot06,
				OneShot07,
				OneShot08,
				OneShot09,
				OneShot0A,
				OneShot0B,
				OneShot0C,
				OneShot0D,
				OneShot0E,
				OneShot0F,
				OneShot10,
				OneShot11,
				OneShot12,
				OneShot13,
				OneShot14,
				OneShot15,
				OneShot16,
				OneShot17,
				OneShot18,
				OneShot19,
				OneShot1A,
				OneShot1B,
				OneShot1C,
				OneShot1D,
				OneShot1E,
				OneShot1F
			};

			constexpr size_t INDIVIDUAL_ANIMATION_START_OFFSET = 0;

			constexpr size_t INDIVIDUAL_ANIMATION_TYPE_OFFSET = 
				INDIVIDUAL_ANIMATION_START_OFFSET;
			constexpr size_t INDIVIDUAL_ANIMATION_TYPE_SIZE = 1;

			constexpr size_t INDIVIDUAL_ANIMATION_TRIGGER_OFFSET = 
				INDIVIDUAL_ANIMATION_TYPE_OFFSET + INDIVIDUAL_ANIMATION_TYPE_SIZE;
			constexpr size_t INDIVIDUAL_ANIMATION_TRIGGER_SIZE = 1;

			constexpr size_t INDIVIDUAL_ANIMATION_FRAME_AMOUNT_OFFSET =
				INDIVIDUAL_ANIMATION_TRIGGER_OFFSET + INDIVIDUAL_ANIMATION_TRIGGER_SIZE;
			constexpr size_t INDIVIDUAL_ANIMATION_FRAME_AMOUNT_SIZE = 1;

			constexpr size_t INDIVIDUAL_ANIMATION_TILE_DESTINATION_OFFSET =
				INDIVIDUAL_ANIMATION_FRAME_AMOUNT_OFFSET + INDIVIDUAL_ANIMATION_FRAME_AMOUNT_SIZE;
			constexpr size_t INDIVIDUAL_ANIMATION_TILE_DESTINATION_SIZE = 2;

			constexpr size_t INDIVIDUAL_ANIMATION_AMOUNT_OF_COLORS_OFFSET =
				INDIVIDUAL_ANIMATION_TILE_DESTINATION_OFFSET + INDIVIDUAL_ANIMATION_TILE_DESTINATION_SIZE;
			constexpr size_t INDIVIDUAL_ANIMATION_AMOUNT_OF_COLORS_SIZE = 1;

			constexpr size_t INDIVIDUAL_ANIMATION_PALETTE_DESTINATION_OFFSET =
				INDIVIDUAL_ANIMATION_AMOUNT_OF_COLORS_OFFSET + INDIVIDUAL_ANIMATION_AMOUNT_OF_COLORS_SIZE;
			constexpr size_t INDIVIDUAL_ANIMATION_PALETTE_DESTINATION_SIZE = 1;

			constexpr size_t INDIVIDUAL_ANIMATION_FRAME_ARRAY_OFFSET =
				INDIVIDUAL_ANIMATION_TILE_DESTINATION_OFFSET + INDIVIDUAL_ANIMATION_TILE_DESTINATION_SIZE;
			constexpr size_t INDIVIDUAL_ANIMATION_FRAME_SIZE = 2;
		}
	}
}
