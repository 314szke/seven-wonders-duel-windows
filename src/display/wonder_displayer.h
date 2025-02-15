# pragma once

#include <memory>
#include <vector>

#include "../deck/wonder.h"


class WonderDisplayer {
public:
	static void Show(std::shared_ptr<const Wonder> wonder);
	static void ShowID(std::shared_ptr<const Wonder> wonder);

	static void Show(std::vector<std::shared_ptr<const Wonder>> wonders);
	static void ShowIDsOnly(std::vector<std::shared_ptr<const Wonder>> wonders);
	static void ShowUnowned(std::vector<std::shared_ptr<const Wonder>> wonders);
};
