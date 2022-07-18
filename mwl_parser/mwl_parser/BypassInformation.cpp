#include "pch.h"
#include "BypassInformation.h"

using MWLParser::BypassInformation;
using MWLParser::Convertible;

BypassInformation::BypassInformation(const std::vector<uint8_t>& mwl_bytes)
{
	auto curr_number_start = mwl_bytes.begin();

	signed long long temp_initial_y = 0;

	for (auto exgfx_slot : order)
	{
		auto number = joinBytes(curr_number_start, EXGFX_NUMBER_SIZE);
		exgfx_files.insert(std::make_pair(exgfx_slot, number & ((1 << (4 + (EXGFX_NUMBER_SIZE - 1) * 8)) - 1)));
		curr_number_start += EXGFX_NUMBER_SIZE;

		uint8_t high_byte = number >> (8 * (EXGFX_NUMBER_SIZE - 1));
		switch (exgfx_slot)
		{
			case ExGFXSlot::AN2:
				enable_super_gfx_bypass = high_byte & 0b10000000;
				enable_layer_3_bypass = high_byte & 0b01000000;
				enable_layer_3_tilemap_bypass = high_byte & 0b00100000;
				break;

			case ExGFXSlot::LT3:
				layer_3_destination_for_file_setting = static_cast<Layer3FileDestinationSetting>((high_byte & 0b11000000) >> 6);
				layer_3_file_size_setting = static_cast<Layer3FileSizeSetting>((high_byte & 0b00110000) >> 4);
				break;

			case ExGFXSlot::BG3:
				layer_3_act_as_setting = static_cast<Layer3ActAsSetting>((high_byte & 0b11110000) >> 4);
				break;

			case ExGFXSlot::SP3:
				temp_initial_y += (high_byte & 0b11110000) << 1;
				break;

			case ExGFXSlot::SP2:
				temp_initial_y += (high_byte & 0b11110000) << 5;
				break;

			case ExGFXSlot::SP1:
				move_layer_3_to_subscreen = high_byte & 0b10000000;
				enable_cgadsub_for_layer_3 = high_byte & 0b01000000;
				layer_3_initial_x_position = static_cast<Layer3InitialXPosition>((high_byte & 0b00110000) >> 4);
				break;

			case ExGFXSlot::LG4:
				temp_initial_y += (high_byte & 0b10000000) >> 7;
				sprite_air_water_flag = high_byte & 0b01000000;
				fix_layer_3_scroll_sync_issue = high_byte & 0b00100000;
				enabled_advanced_bypass_of_layer_3 = high_byte & 0b00010000;
				break;

			case ExGFXSlot::LG3:
				temp_initial_y += (high_byte & 0b11110000) >> 3;
				break;

			case ExGFXSlot::LG2:
				layer_3_horizontal_scroll_setting = static_cast<Layer3HorizontalScrollSetting>((high_byte & 0b11110000) >> 4);
				break;

			case ExGFXSlot::LG1:
				layer_3_vertical_scroll_setting = static_cast<Layer3VerticalScrollSetting>((high_byte & 0b11110000) >> 4);
				break;
		}
	}

	layer_3_initial_y_position = temp_initial_y < LAYER_3_Y_POSITION_RANGE / 2 ? temp_initial_y : -((temp_initial_y ^ (static_cast<signed long long>(LAYER_3_Y_POSITION_RANGE) - 1)) + 1);
}

std::vector<uint8_t> BypassInformation::toBytes() const
{
	std::vector<uint8_t> bytes{};

	auto reconverted_y_pos = layer_3_initial_y_position >= 0 ? layer_3_initial_y_position : -(((layer_3_initial_y_position - 1) ^ (static_cast<signed long long>(LAYER_3_Y_POSITION_RANGE) - 1)));

	for (auto exgfx_slot : order)
	{
		auto exgfx_number = exgfx_files.at(exgfx_slot);

		size_t high_byte = 0;

		switch (exgfx_slot)
		{
		case ExGFXSlot::AN2:
			high_byte |= (enable_super_gfx_bypass << 7) | (enable_layer_3_bypass << 6) | (enable_layer_3_tilemap_bypass << 5);
			break;

		case ExGFXSlot::LT3:
			high_byte |= (static_cast<size_t>(layer_3_destination_for_file_setting) << 6) | (static_cast<size_t>(layer_3_file_size_setting) << 4);
			break;

		case ExGFXSlot::BG3:
			high_byte |= static_cast<size_t>(layer_3_act_as_setting) << 4;
			break;

		case ExGFXSlot::SP3:
			high_byte |= (reconverted_y_pos & 0b111100000) >> 1;
			break;

		case ExGFXSlot::SP2:
			high_byte |= (reconverted_y_pos & 0b1111000000000) >> 5;
			break;

		case ExGFXSlot::SP1:
			high_byte |= (move_layer_3_to_subscreen << 7) | (enable_cgadsub_for_layer_3 << 6) | 
				(static_cast<size_t>(layer_3_initial_x_position) << 4);
			break;

		case ExGFXSlot::LG4:
			high_byte |= (reconverted_y_pos << 7) | (sprite_air_water_flag << 6) |
				(fix_layer_3_scroll_sync_issue << 5) | (enabled_advanced_bypass_of_layer_3 << 4);
			break;

		case ExGFXSlot::LG3:
			high_byte |= (reconverted_y_pos & 0b11110) << 3;
			break;

		case ExGFXSlot::LG2:
			high_byte |= static_cast<size_t>(layer_3_horizontal_scroll_setting) << 4;
			break;

		case ExGFXSlot::LG1:
			high_byte |= static_cast<size_t>(layer_3_vertical_scroll_setting) << 4;
			break;
		}

		auto mask = high_byte << (8 * (EXGFX_NUMBER_SIZE - 1));
		exgfx_number |= mask;

		for (const auto byte : splitIntoBytes(exgfx_number, EXGFX_NUMBER_SIZE))
		{
			bytes.push_back(byte);
		}
	}

	return bytes;
}
