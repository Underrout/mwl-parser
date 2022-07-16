#pragma once

#include <map>
#include <vector>
#include <array>

#include "Convertible.h"
#include "MWLConstants.h"
#include "ByteUtility.h"

namespace MWLParser
{
	using namespace MWLParser::Constants::BypassInfo;

	struct BypassInformation : public virtual Convertible
	{
		std::array<ExGFXSlot, EXGFX_SLOT_AMOUNT> order{ { ExGFXSlot::AN2, ExGFXSlot::LT3, ExGFXSlot::BG3,
			ExGFXSlot::BG2, ExGFXSlot::FG3, ExGFXSlot::BG1, ExGFXSlot::FG2, ExGFXSlot::FG1,
			ExGFXSlot::SP4, ExGFXSlot::SP3, ExGFXSlot::SP2, ExGFXSlot::SP1, ExGFXSlot::LG4,
			ExGFXSlot::LG3, ExGFXSlot::LG2, ExGFXSlot::LG1 } };

		std::map<ExGFXSlot, size_t> exgfx_files{};

		bool enable_super_gfx_bypass;
		bool enable_layer_3_bypass;
		bool enable_layer_3_tilemap_bypass;
		bool enable_cgadsub_for_layer_3;
		bool enabled_advanced_bypass_of_layer_3;
		bool sprite_air_water_flag;
		bool fix_layer_3_scroll_sync_issue;
		bool move_layer_3_to_subscreen;

		Layer3FileDestinationSetting layer_3_destination_for_file_setting;
		Layer3FileSizeSetting layer_3_file_size_setting;
		Layer3ActAsSetting layer_3_act_as_setting;
		Layer3InitialXPosition layer_3_initial_x_position;
		size_t layer_3_initial_y_position;
		Layer3HorizontalScrollSetting layer_3_horizontal_scroll_setting;
		Layer3VerticalScrollSetting layer_3_vertical_scroll_setting;

		BypassInformation() = default;
		BypassInformation(const std::vector<uint8_t>& mwl_bytes);

		std::shared_ptr<Convertible> fromBytes(const std::vector<uint8_t>& bytes);
		std::vector<uint8_t> toBytes() const;
	};
}
