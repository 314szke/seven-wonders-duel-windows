#include "card_info.h"

#include "../enums/card_age_types.h"
#include "../enums/card_colors.h"
#include "../enums/exception_types.h"


CardInfo::CardInfo(const uint32_t card_id, const uint32_t card_age, const uint32_t card_color) :
	ID(card_id)
{
    switch (card_age) {
        case FIRST_AGE: age = FIRST_AGE; break;
        case SECOND_AGE: age = SECOND_AGE; break;
        case THIRD_AGE: age = THIRD_AGE; break;
        default: throw CARD_UNKNOWN_AGE;
    }

    switch (card_color) {
        case BROWN: color = BROWN; break;
        case GREY: color = GREY; break;
        case YELLOW: color = YELLOW; break;
        case RED: color = RED; break;
        case GREEN: color = GREEN; break;
        case BLUE: color = BLUE; break;
        case PURPLE: color = PURPLE; break;
        default: throw CARD_UNKNOWN_COLOR;
    }
}
