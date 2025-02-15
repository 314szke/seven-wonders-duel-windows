#pragma once

#include <memory>

#include "parser.h"
#include "../deck/wonder.h"


class WonderLoader : private Parser {
public:
	WonderLoader();
	
	std::shared_ptr<const Wonder> getWonder(const uint32_t wonder_id) const;
	std::shared_ptr<Wonder> getWonder(const uint32_t wonder_id);

private:
	void parseWonder(const uint32_t wonder_id, const std::smatch& match);

	std::vector<std::shared_ptr<Wonder>> wonders;
};
