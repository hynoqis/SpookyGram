#include "spookygram/core/spookygram_facade.h"

namespace SpookyGram {

void Facade::Initialize() {
	Config().load();
	Bookmarks().load();
}

void Facade::Deinitialize() {
	Config().save();
	Bookmarks().save();
}

} // namespace SpookyGram
