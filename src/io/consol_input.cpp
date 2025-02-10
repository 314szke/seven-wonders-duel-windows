#include "consol_input.h"

#include <iostream>
#include <regex>

#include "../enums/exception_types.h"


static const std::regex PLAYER_TYPE_REGEX("[0-9]");
static const std::regex PLAYER_NAME_REGEX("[A-Za-z]+");
static const std::regex PLAYER_ACTION_REGEX("(t|d|b|i|(?:take)|(?:discard)|(?:build)|(?:info))\\s+([0-9][0-9]?)");


PlayerType ConsolInput::ReadPlayerOption(const PlayerID player_id)
{
	std::string line;
	std::smatch regex_match;
	int player_option = -1;

	while (player_option == -1) {
		std::cout << "Player #" << (player_id+1) << ":" << std::endl;
		for (const std::string& option_string : PLAYER_TYPE_STRINGS) {
			std::cout << "   " << option_string << std::endl;
		}
		std::cout << ">> ";

		std::getline(std::cin, line);
		if (std::regex_match(line, regex_match, PLAYER_TYPE_REGEX)) {
			player_option = stoi(regex_match[0].str());
		} else {
			std::cout << "WARNING: your input must only contain the DIGIT identifying the player type!" << std::endl << std::endl;
			continue;
		}

		switch (player_option) {
			case CONSOL_PLAYER: return CONSOL_PLAYER;
			case ROBOT_PLAYER: return ROBOT_PLAYER;
			default: {
				std::cout << "WARNING: invalid option " << player_option << " !" << std::endl << std::endl;
				player_option = -1;
			}
		}
	}

	throw CONSOL_NO_PLAYER_TYPE;
}

std::string ConsolInput::ReadPlayerName(const PlayerID player_id)
{
	std::string line;
	std::smatch regex_match;

	while (line.empty()) {
		std::cout << "Name Player #" << (player_id + 1) << " >> ";

		std::getline(std::cin, line);
		if (std::regex_match(line, regex_match, PLAYER_NAME_REGEX)) {
			return line;
		}
		else {
			std::cout << "WARNING: the name must only contain alphabetical characters!" << std::endl << std::endl;
			line.resize(0);
		}
	}	

	throw CONSOL_NO_PLAYER_NAME;
}

PlayerAction ConsolInput::ReadPlayerAction()
{
	PlayerAction player_action;
	std::string line;
	std::smatch regex_match;

	while (true) {
		std::cout << ">> ";
		std::getline(std::cin, line);

		if (std::regex_match(line, regex_match, PLAYER_ACTION_REGEX)) {
			if (regex_match[1].str() == "t" || regex_match[1].str() == "take") {
				player_action.action_type = TAKE;
			} else if (regex_match[1].str() == "d" || regex_match[1].str() == "discard") {
				player_action.action_type = DISCARD;
			} else if (regex_match[1].str() == "b" || regex_match[1].str() == "build") {
				player_action.action_type = BUILD;
			} else if (regex_match[1].str() == "i" || regex_match[1].str() == "info") {
				player_action.action_type = INFO;
			}
			player_action.card_id = stoi(regex_match[2].str());
			return player_action;
		}
		else {
			std::cout << "WARNING: invalid input! Valid inputs: <action_type> <card_id>." << std::endl;
			std::cout << "Action types: t or take, d or discard, b or build, i or info." << std::endl << std::endl;
		}
	}
}
