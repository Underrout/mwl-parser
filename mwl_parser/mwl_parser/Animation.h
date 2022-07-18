#pragma once

#include "Convertible.h"
#include "MWLConstants.h"
#include "ByteUtility.h"


namespace MWLParser
{
	using namespace MWLParser::Constants::ExAnimation;

	struct Animation : public virtual Convertible
	{
	protected:
		size_t amount_of_frames;
		size_t vram_destination;
		bool uses_alt_gfx;

	public:
		AnimationType animation_type;
		Trigger trigger;
		std::vector<size_t> frames{};

		Animation(const std::vector<uint8_t>& mwl_bytes);

		static std::shared_ptr<Animation> getAnimation(const std::vector<uint8_t>& mwl_bytes);
		static AnimationType getAnimationType(const std::vector<uint8_t>& mwl_bytes);
	};

	struct TileAnimation : public virtual Animation
	{
		size_t tile_destination;
		std::vector<size_t> tile_frames{};

		TileAnimation(const std::vector<uint8_t>& mwl_bytes);

	private:
		static size_t frameToTileNumber(size_t frame_value);
		static size_t tileNumberToFrame(size_t tile_number);

	public:
		std::vector<uint8_t> toBytes() const;
	};

	struct ColorAnimation : public virtual Animation
	{
		size_t color_amount;
		size_t palette_destination;
		std::vector<size_t> color_frames{};

		ColorAnimation(const std::vector<uint8_t>& mwl_bytes);

		std::vector<uint8_t> toBytes() const;
	};
}