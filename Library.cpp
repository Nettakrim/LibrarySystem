#include "Library.h"

Library* Library::INSTANCE;

Library::Library() {
	Library::INSTANCE = this;

	load();
}

Library::~Library()
{
	save();
}