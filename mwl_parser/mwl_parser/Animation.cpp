#include "pch.h"
#include "Animation.h"

using namespace MWLParser::Constants::ExAnimation;

using MWLParser::Animation;
using MWLParser::FrameAnimation;
using MWLParser::PaletteRotateAnimation;
using MWLParser::ColorAnimation;
using MWLParser::TileAnimation;

std::shared_ptr<Animation> Animation::getAnimation(const std::vector<uint8_t>& mwl_bytes)
{
	const auto animation_type = getAnimationType(mwl_bytes);

	if (std::find(PALETTE_ROTATE_TYPES.begin(), PALETTE_ROTATE_TYPES.end(),
		animation_type) != PALETTE_ROTATE_TYPES.end())
	{
		return std::make_shared<PaletteRotateAnimation>(mwl_bytes);
	}
	else if (animation_type >= FIRST_PALETTE_ANIMATION_TYPE)
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
	trigger = static_cast<Trigger>(
		joinBytes(mwl_bytes,
			INDIVIDUAL_ANIMATION_TRIGGER_OFFSET,
			INDIVIDUAL_ANIMATION_TRIGGER_SIZE
	));

	animation_type = getAnimationType(mwl_bytes);

	vram_destination = joinBytes(mwl_bytes,
		INDIVIDUAL_ANIMATION_TILE_DESTINATION_OFFSET,
		INDIVIDUAL_ANIMATION_TILE_DESTINATION_SIZE
	);
}

PaletteRotateAnimation::PaletteRotateAnimation(const std::vector<uint8_t>& mwl_bytes) : Animation(mwl_bytes)
{
	delay = joinBytes(mwl_bytes,
		INDIVIDUAL_ANIMATION_FRAME_AMOUNT_OFFSET,
		INDIVIDUAL_ANIMATION_FRAME_AMOUNT_SIZE
	);

	color_amount = ((vram_destination & 0xFF00) >> 8) + 1;

	palette_destination = vram_destination & 0xFF;
}

std::vector<uint8_t> PaletteRotateAnimation::toBytes() const
{
	std::vector<uint8_t> bytes = commonToBytes();

	extendVec(bytes, splitIntoBytes(delay, INDIVIDUAL_ANIMATION_FRAME_AMOUNT_SIZE));

	extendVecAt(bytes, splitIntoBytes(palette_destination,
		INDIVIDUAL_ANIMATION_PALETTE_DESTINATION_SIZE),
		INDIVIDUAL_ANIMATION_PALETTE_DESTINATION_OFFSET);

	extendVecAt(bytes, splitIntoBytes(color_amount - 1,
		INDIVIDUAL_ANIMATION_AMOUNT_OF_COLORS_SIZE),
		INDIVIDUAL_ANIMATION_AMOUNT_OF_COLORS_OFFSET);

	return bytes;
}

FrameAnimation::FrameAnimation(const std::vector<uint8_t>& mwl_bytes) : Animation(mwl_bytes)
{
	trigger = static_cast<Trigger>(
		joinBytes(mwl_bytes,
			INDIVIDUAL_ANIMATION_TRIGGER_OFFSET,
			INDIVIDUAL_ANIMATION_TRIGGER_SIZE
		)
	);

	size_t amount_of_frames = joinBytes(mwl_bytes,
		INDIVIDUAL_ANIMATION_FRAME_AMOUNT_OFFSET,
		INDIVIDUAL_ANIMATION_FRAME_AMOUNT_SIZE
	) + 1;

	if (std::find(DOUBLE_FRAME_TRIGGERS.begin(), DOUBLE_FRAME_TRIGGERS.end(),
		trigger) != DOUBLE_FRAME_TRIGGERS.end())
	{
		amount_of_frames *= 2;
	}

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

std::vector<uint8_t> Animation::commonToBytes() const
{
	std::vector<uint8_t> bytes{};

	extendVec(bytes, splitIntoBytes(static_cast<size_t>(animation_type), INDIVIDUAL_ANIMATION_TYPE_SIZE));
	extendVec(bytes, splitIntoBytes(static_cast<size_t>(trigger), INDIVIDUAL_ANIMATION_TRIGGER_SIZE));

	return bytes;
}

std::vector<uint8_t> FrameAnimation::commonToBytes() const
{
	std::vector<uint8_t> bytes = Animation::commonToBytes();

	size_t amount_of_frames = frames.size();
	if (std::find(DOUBLE_FRAME_TRIGGERS.begin(), DOUBLE_FRAME_TRIGGERS.end(),
		trigger) != DOUBLE_FRAME_TRIGGERS.end())
	{
		amount_of_frames /= 2;
	}

	extendVec(bytes, splitIntoBytes(amount_of_frames - 1, INDIVIDUAL_ANIMATION_FRAME_AMOUNT_SIZE));

	for (size_t frame : frames)
	{
		extendVec(bytes, splitIntoBytes(frame, INDIVIDUAL_ANIMATION_FRAME_SIZE));
	}

	return bytes;
}

TileAnimation::TileAnimation(const std::vector<uint8_t>& mwl_bytes) : Animation(mwl_bytes), FrameAnimation(mwl_bytes)
{
	uses_alt_gfx = vram_destination & 0x8000;

	tile_destination = vram_destination;
}

std::vector<uint8_t> TileAnimation::toBytes() const
{
	auto bytes = commonToBytes();

	size_t destination = tile_destination | 
		(static_cast<size_t>(uses_alt_gfx) << (8 * INDIVIDUAL_ANIMATION_TILE_DESTINATION_SIZE - 1));

	extendVecAt(bytes, splitIntoBytes(destination,
		INDIVIDUAL_ANIMATION_TILE_DESTINATION_SIZE), 
		INDIVIDUAL_ANIMATION_TILE_DESTINATION_OFFSET);

	return bytes;
}

ColorAnimation::ColorAnimation(const std::vector<uint8_t>& mwl_bytes) : Animation(mwl_bytes), FrameAnimation(mwl_bytes)
{
	color_amount = ((vram_destination & 0xFF00) >> 8) + 1;

	palette_destination = vram_destination & 0xFF;
}

std::vector<uint8_t> ColorAnimation::toBytes() const
{
	auto bytes = commonToBytes();

	extendVecAt(bytes, splitIntoBytes(palette_destination,
		INDIVIDUAL_ANIMATION_PALETTE_DESTINATION_SIZE),
		INDIVIDUAL_ANIMATION_PALETTE_DESTINATION_OFFSET);

	extendVecAt(bytes, splitIntoBytes(color_amount - 1,
		INDIVIDUAL_ANIMATION_AMOUNT_OF_COLORS_SIZE),
		INDIVIDUAL_ANIMATION_AMOUNT_OF_COLORS_OFFSET);

	return bytes;
}
