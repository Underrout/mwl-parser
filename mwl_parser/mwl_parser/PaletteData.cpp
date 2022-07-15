#include "pch.h"
#include "PaletteData.h"

using MWLParser::PaletteData;
using MWLParser::Convertible;

PaletteData::PaletteData(const std::vector<uint8_t>& mwl_bytes)
{
	auto current_color_start = mwl_bytes.begin() + Constants::PaletteData::PALETTE_DATA_OFFSET;
	auto current_color_end = current_color_start + Constants::PaletteData::COLOR_BYTE_SIZE;

	main_palette = std::vector<size_t>();

	for (size_t i = 0; i != Constants::PaletteData::MAIN_PALETTE_COLOR_AMOUNT; ++i)
	{
		main_palette.push_back(joinBytes(current_color_start, current_color_end));

		current_color_start += Constants::PaletteData::COLOR_BYTE_SIZE;
		current_color_end += Constants::PaletteData::COLOR_BYTE_SIZE;
	}

	const auto background_color_start = mwl_bytes.begin() + Constants::PaletteData::BACKGROUND_COLOR_OFFSET;
	background_color = joinBytes(background_color_start, Constants::PaletteData::COLOR_BYTE_SIZE);
}

PaletteData::PaletteData(const std::vector<size_t>& palette, size_t background_color)
{
	this->main_palette = palette;
	this->background_color = background_color;
}

std::shared_ptr<Convertible> PaletteData::fromBytes(const std::vector<uint8_t>& bytes)
{
	return std::make_shared<PaletteData>(bytes);
}

std::vector<uint8_t> PaletteData::toBytes() const
{
	// zeroing out the header since it's unused, at least for our purposes
	std::vector<uint8_t> bytes = std::vector<uint8_t>(Constants::PaletteData::HEADER_SIZE, 0);

	for (size_t color : main_palette)
	{
		for (const auto& byte : splitIntoBytes(color, Constants::PaletteData::COLOR_BYTE_SIZE))
		{
			bytes.push_back(byte);
		}
	}

	for (const auto& byte : splitIntoBytes(background_color, Constants::PaletteData::COLOR_BYTE_SIZE))
	{
		bytes.push_back(byte);
	}

	return bytes;
}
