#pragma once

#include <stdint.h>

#include "../enums/card_age_types.h"
#include "../enums/card_colors.h"


class CardInfo {
public:
	CardInfo(const uint32_t card_id, const uint32_t card_age, const uint32_t card_color);

	uint32_t ID;
	CardAgeType age;
	CardColor color;
};

