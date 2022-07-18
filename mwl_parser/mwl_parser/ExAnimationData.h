#pragma once

#include <vector>
#include <optional>
#include <map>

#include "Convertible.h"
#include "ByteUtility.h"
#include "MWLConstants.h"
#include "Animation.h"

namespace MWLParser
{
	using namespace MWLParser::Constants::ExAnimation;

	struct ExAnimationData : public virtual Convertible
	{
		bool enable_original_games_global_tile_animations;
		bool enable_original_games_palette_animations;
		bool enable_lunar_magics_global_animations;
		bool enable_lunar_magics_level_animations;

		AltGfx alternate_gfx_file;

		std::vector<CustomTriggerInitState> custom_trigger_initialization_settings{};
		std::vector<std::optional<size_t>> manual_trigger_initialization_settings{};

		std::map<size_t, std::shared_ptr<Animation>> animation_slots{};

		ExAnimationData() = default;
		ExAnimationData(const std::vector<uint8_t>& mwl_bytes);

		std::vector<uint8_t> toBytes() const;
	};
}
