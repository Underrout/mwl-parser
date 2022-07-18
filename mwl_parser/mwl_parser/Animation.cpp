#include "pch.h"
#include "Animation.h"

using namespace MWLParser::Constants::ExAnimation;

using MWLParser::Animation;
using MWLParser::ColorAnimation;
using MWLParser::TileAnimation;

std::shared_ptr<Animation> Animation::getAnimation(const std::vector<uint8_t>& mwl_bytes)
{
	const auto animation_type = getAnimationType(mwl_bytes);

	if (animation_type >= FIRST_PALETTE_ANIMATION_TYPE)
	{
		return std::make_shared<ColorAnimation>(mwl_bytes);
	}
	else
	{
		return std::make_shared<TileAnimation>(mwl_bytes);
	}
}

AnimationType Animation::getAnimationType(const std::vector<uint8_t>& mwl_bytes)
{
	return static_cast<AnimationType>(joinBytes(mwl_bytes,
		INDIVIDUAL_ANIMATION_TYPE_OFFSET,
		INDIVIDUAL_ANIMATION_TYPE_SIZE
	));
}

Animation::Animation(const std::vector<uint8_t>& mwl_bytes)
{
	animation_type = getAnimationType(mwl_bytes);

	trigger = static_cast<Trigger>(
		joinBytes(mwl_bytes,
			INDIVIDUAL_ANIMATION_TRIGGER_OFFSET,
			INDIVIDUAL_ANIMATION_TRIGGER_SIZE
		)
	);

	amount_of_frames = joinBytes(mwl_bytes,
		INDIVIDUAL_ANIMATION_FRAME_AMOUNT_OFFSET,
		INDIVIDUAL_ANIMATION_FRAME_AMOUNT_SIZE
	) + 1;

    vram_destination = joinBytes(mwl_bytes,
		INDIVIDUAL_ANIMATION_TILE_DESTINATION_OFFSET,
		INDIVIDUAL_ANIMATION_TILE_DESTINATION_SIZE
	);

	uses_alt_gfx = vram_destination & 0x8000;

	vram_destination = vram_destination & 0x7FFF;

	for (size_t i = 0; i != amount_of_frames; ++i)
	{
		size_t frame = joinBytes(mwl_bytes,
			INDIVIDUAL_ANIMATION_FRAME_ARRAY_OFFSET +
			i * INDIVIDUAL_ANIMATION_FRAME_SIZE,
			INDIVIDUAL_ANIMATION_FRAME_SIZE
		);

		frames.push_back(frame);
	}
}

TileAnimation::TileAnimation(const std::vector<uint8_t>& mwl_bytes) : Animation(mwl_bytes)
{
	tile_destination = vram_destination;
}

std::vector<uint8_t> TileAnimation::toBytes() const
{
	return std::vector<uint8_t>();
}

ColorAnimation::ColorAnimation(const std::vector<uint8_t>& mwl_bytes) : Animation(mwl_bytes)
{
	color_amount = joinBytes(mwl_bytes,
		INDIVIDUAL_ANIMATION_AMOUNT_OF_COLORS_OFFSET,
		INDIVIDUAL_ANIMATION_AMOUNT_OF_COLORS_SIZE
	) + 1;

	palette_destination = joinBytes(mwl_bytes,
		INDIVIDUAL_ANIMATION_PALETTE_DESTINATION_OFFSET,
		INDIVIDUAL_ANIMATION_PALETTE_DESTINATION_SIZE
	);
}

std::vector<uint8_t> ColorAnimation::toBytes() const
{
	return std::vector<uint8_t>();
}
