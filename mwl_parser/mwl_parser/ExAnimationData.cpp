#include "pch.h"
#include "ExAnimationData.h"

using namespace MWLParser::Constants::ExAnimation;

using MWLParser::ExAnimationData;
using MWLParser::BaseExAnimationData;
using MWLParser::Convertible;

BaseExAnimationData::BaseExAnimationData(const std::vector<uint8_t>& mwl_bytes)
{
	size_t animation_settings = joinBytes(mwl_bytes,
		ANIMATION_SETTINGS_OFFSET,
		ANIMATION_SETTINGS_SIZE
	);

	enable_original_games_global_tile_animations = !(animation_settings & 0b01000000);
	enable_original_games_palette_animations = !(animation_settings & 0b10000000);
	enable_lunar_magics_global_animations = !(animation_settings & 0b00100000);
	enable_lunar_magics_level_animations = !(animation_settings & 0b00010000);
}

ExAnimationData::ExAnimationData(const std::vector<uint8_t>& mwl_bytes) : BaseExAnimationData(mwl_bytes)
{
	size_t slot_amount = joinBytes(mwl_bytes,
		GENERAL_ANIMATION_HIGHEST_USED_SLOT_OFFSET,
		GENERAL_ANIMATION_HIGHEST_USED_SLOT_SIZE
	);

	alternate_gfx_file = static_cast<AltGfx>(joinBytes(mwl_bytes,
		GENERAL_ANIMATION_ALTERNATE_GFX_FILE_OFFSET,
		GENERAL_ANIMATION_ALTERNATE_GFX_FILE_SIZE
	));

	size_t custom_init_bits = joinBytes(mwl_bytes,
		GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_OFFSET,
		GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_SIZE
	);

	size_t custom_init_states = joinBytes(mwl_bytes,
		GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_STATES_OFFSET,
		GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_STATES_SIZE
	);

	for (size_t i = 0; i != GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_SIZE * 8; ++i)
	{
		bool is_initialized = (custom_init_bits & (1 << i)) == 0;

		if (!is_initialized)
		{
			custom_trigger_initialization_settings
				.push_back(CustomTriggerInitState::NotInitialized);
		}
		else
		{
			bool is_on = (custom_init_bits & (1 << i)) == 0;
			CustomTriggerInitState state =
				is_on ? CustomTriggerInitState::On : CustomTriggerInitState::Off;
			custom_trigger_initialization_settings.push_back(state);
		}
	}

	size_t manual_init_bits = joinBytes(mwl_bytes,
		GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_OFFSET,
		GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_SIZE
	);

	size_t initialized_slots = 0;
	for (size_t i = 0; i != GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_SIZE * 8; ++i)
	{
		bool is_initialized = (manual_init_bits & (1 << i)) == 1;

		if (!is_initialized)
		{
			manual_trigger_initialization_settings.push_back(std::nullopt);
		}
		else
		{
			size_t frame_number = joinBytes(mwl_bytes,
				GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_STATES_OFFSET +
				initialized_slots * GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_STATES_SIZE,
				GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_STATES_SIZE
			);

			manual_trigger_initialization_settings
				.push_back(std::make_optional(frame_number));

			++initialized_slots;
		}
	}

	size_t start_of_individual_animation_data =
		GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_STATES_OFFSET +
		GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_STATES_SIZE * initialized_slots;

	for (size_t i = 0; i != slot_amount; ++i)
	{
		size_t relative_animation_data_index = joinBytes(mwl_bytes,
			start_of_individual_animation_data +
			GENERAL_ANIMATION_INDICE_LIST_ENTRY_SIZE * i,
			GENERAL_ANIMATION_INDICE_LIST_ENTRY_SIZE
		);

		if (relative_animation_data_index != GENERAL_ANIMATION_UNUSED_SLOT_INDICE_VALUE)
		{
			size_t animation_data_index = relative_animation_data_index +
				start_of_individual_animation_data;

			auto sub_vec = subVec(mwl_bytes, animation_data_index);

			animation_slots.insert(std::make_pair(
				i, Animation::getAnimation(sub_vec)
			));
		}
	}
}

std::vector<uint8_t> BaseExAnimationData::toBytes() const
{
	uint8_t first_header_byte = (!enable_original_games_global_tile_animations << 6) |
		(!enable_original_games_palette_animations << 7) |
		(!enable_lunar_magics_global_animations << 5) |
		(!enable_lunar_magics_level_animations << 4);

	std::vector<uint8_t> bytes{ first_header_byte };

	// zero out rest of the header, which is supposedly unused
	bytes.insert(bytes.end(),
		ANIMATION_HEADER_SIZE - ANIMATION_SETTINGS_SIZE, 0);

	return bytes;
}

std::shared_ptr<BaseExAnimationData> BaseExAnimationData::getExAnimationData(const std::vector<uint8_t>& mwl_bytes)
{
	if (mwl_bytes.size() <= ANIMATION_HEADER_SIZE)
	{
		return std::make_shared<BaseExAnimationData>(mwl_bytes);
	}
	else
	{
		return std::make_shared<ExAnimationData>(mwl_bytes);
	}
}

std::vector<uint8_t> ExAnimationData::toBytes() const
{
	auto bytes = BaseExAnimationData::toBytes();

	const auto max_slot_plus_one = 
		animation_slots.empty() ? 0 : animation_slots.rbegin()->first + 1;

	extendVec(bytes, splitIntoBytes(max_slot_plus_one,
		GENERAL_ANIMATION_HIGHEST_USED_SLOT_SIZE));

	extendVec(bytes, splitIntoBytes(static_cast<size_t>(alternate_gfx_file),
		GENERAL_ANIMATION_ALTERNATE_GFX_FILE_SIZE));

	size_t uninitialized_custom_triggers = 0;
	size_t initial_custom_trigger_states = 0;
	size_t i = 0;
	for (const auto setting : custom_trigger_initialization_settings)
	{
		if (setting == CustomTriggerInitState::NotInitialized)
		{
			uninitialized_custom_triggers |= 1 << i;
		}
		else
		{
			if (setting == CustomTriggerInitState::Off)
			{
				initial_custom_trigger_states |= 1 << i;
			}
		}
		++i;
	}

	extendVec(bytes, splitIntoBytes(uninitialized_custom_triggers,
		GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_SIZE));

	extendVec(bytes, splitIntoBytes(initial_custom_trigger_states,
		GENERAL_ANIMATION_CUSTOM_TRIGGER_INIT_STATES_SIZE));

	size_t initialized_manual_triggers = 0;
	i = 0;
	for (const auto setting : manual_trigger_initialization_settings)
	{
		if (setting.has_value())
		{
			initialized_manual_triggers |= 1 << i;
			extendVec(bytes, splitIntoBytes(setting.value(),
				GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_STATES_SIZE));
		}
		++i;
	}

	extendVecAt(bytes, splitIntoBytes(initialized_manual_triggers,
		GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_SIZE),
		GENERAL_ANIMATION_MANUAL_TRIGGER_INIT_OFFSET);

	size_t indice_list_offset = bytes.size();
	size_t individual_animation_data_offset = indice_list_offset +
		max_slot_plus_one * GENERAL_ANIMATION_INDICE_LIST_ENTRY_SIZE;

	for (size_t i = 0; i != max_slot_plus_one; ++i)
	{
		const auto slot = animation_slots.find(i);

		if (slot != animation_slots.end())
		{
			const auto size_of_previous_slots = bytes.size() - 
				indice_list_offset - i * GENERAL_ANIMATION_INDICE_LIST_ENTRY_SIZE;
			const auto idx = individual_animation_data_offset - indice_list_offset + size_of_previous_slots;
			extendVec(bytes, slot->second->toBytes());
			extendVecAt(bytes, splitIntoBytes(idx,
				GENERAL_ANIMATION_INDICE_LIST_ENTRY_SIZE),
				indice_list_offset + i * GENERAL_ANIMATION_INDICE_LIST_ENTRY_SIZE);
		}
		else
		{
			extendVecAt(bytes, splitIntoBytes(0,
				GENERAL_ANIMATION_INDICE_LIST_ENTRY_SIZE),
				indice_list_offset + i * GENERAL_ANIMATION_INDICE_LIST_ENTRY_SIZE);
		}
	}

	return bytes;
}
