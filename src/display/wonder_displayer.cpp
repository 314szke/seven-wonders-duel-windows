#include "wonder_displayer.h"

#include <iostream>

#include "../display/card_displayer.h"
#include "../enums/player_id.h"


void WonderDisplayer::Show(std::shared_ptr<const Wonder> wonder)
{
	std::cout << "Wonder " << wonder->ID << std::endl;
	
	std::cout << "    cost      [";
	CardDisplayer::PrintMaterials(wonder->material_cost);
	std::cout << "]" << std::endl;

	std::cout << "    gain      $:" << wonder->money << "/-" << wonder->enemy_money << " ";
	std::cout << "M:" << wonder->military_point << " ";
	std::cout << "V:" << wonder->victory_point << std::endl;
	
	std::cout << "    materials [";
	if (! wonder->hybrid_materials.isEmpty()) {
		CardDisplayer::PrintHybridProduction(wonder->hybrid_materials);
	}
	std::cout << "] " << std::endl;

	std::cout << "    action    [";
	if (wonder->action != NO_WONDER_ACTION) {
		switch (wonder->action) {
			case BROWN_DISCARD: std::cout << "BROWN_DISCARD"; break;
			case GREY_DISCARD: std::cout << "GREY_DISCARD"; break;
			case CARD_PICK: std::cout << "CARD_PICK"; break;
			case NEW_TURN: std::cout << "NEW_TURN"; break;
			case PROGRESS_COIN: std::cout << "PROGRESS_COIN"; break;
		}
	}
	std::cout << "]" << std::endl;
}

void WonderDisplayer::ShowID(std::shared_ptr<const Wonder> wonder)
{
	std::cout << "w" << wonder->ID  << "|(";
	if (wonder->isBuilt()) {
		std::cout << wonder->build_card_id;
	}
	std::cout << ")";
}

void WonderDisplayer::Show(std::vector<std::shared_ptr<const Wonder>> wonders)
{
	for (std::shared_ptr<const Wonder> wonder : wonders) {
		Show(wonder);
	}
}

void WonderDisplayer::ShowIDsOnly(std::vector<std::shared_ptr<const Wonder>> wonders)
{
	std::cout << "    ";
	for (std::shared_ptr<const Wonder> wonder : wonders) {
		ShowID(wonder);
		std::cout << "    ";
	}
	std::cout << std::endl;
}

void WonderDisplayer::ShowUnowned(std::vector<std::shared_ptr<const Wonder>> wonders)
{
	for (std::shared_ptr<const Wonder> wonder : wonders) {
		if (wonder->player_id == NO_PLAYER) {
			Show(wonder);
		}
	}
}
