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
		std::vector<uint8_t> commonToBytes() const;
	public:
		AnimationType animation_type;
		Trigger trigger;
		size_t vram_destination;

		Animation(const std::vector<uint8_t>& mwl_bytes);

		static std::shared_ptr<Animation> getAnimation(const std::vector<uint8_t>& mwl_bytes);
		static AnimationType getAnimationType(const std::vector<uint8_t>& mwl_bytes);
	};

	struct FrameAnimation : public virtual Animation
	{
	protected:
		std::vector<uint8_t> commonToBytes() const;

	public:
		std::vector<size_t> frames{};

		FrameAnimation(const std::vector<uint8_t>& mwl_bytes);
	};

	struct PaletteRotateAnimation : public virtual Animation
	{
		size_t delay;
		size_t color_amount;
		size_t palette_destination;

		PaletteRotateAnimation(const std::vector<uint8_t>& mwl_bytes);

		std::vector<uint8_t> toBytes() const;
	};

	struct TileAnimation : public virtual FrameAnimation
	{
		bool uses_alt_gfx;
		size_t tile_destination;
		std::vector<size_t> tile_frames{};

		TileAnimation(const std::vector<uint8_t>& mwl_bytes);

	public:
		std::vector<uint8_t> toBytes() const;
	};

	struct ColorAnimation : public virtual FrameAnimation
	{
		size_t color_amount;
		size_t palette_destination;
		std::vector<size_t> color_frames{};

		ColorAnimation(const std::vector<uint8_t>& mwl_bytes);

		std::vector<uint8_t> toBytes() const;
	};
}