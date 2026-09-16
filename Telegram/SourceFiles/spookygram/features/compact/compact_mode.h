#pragma once

#include "rpl/producer.h"

namespace SpookyGram {

class CompactMode final {
public:
	static bool IsEnabled();
	static void Toggle();
	static void SetEnabled(bool enabled);
	static rpl::producer<bool> Changes();

	static int DialogRowHeight(int defaultHeight);
	static int ChatPadding(int defaultPadding);
};

} // namespace SpookyGram
