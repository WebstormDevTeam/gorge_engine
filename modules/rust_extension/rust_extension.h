#pragma once
#include "core/object/ref_counted.h"

class RustExtension : public RefCounted{
	GDCLASS(RustExtension, RefCounted)

public:
	RustExtension();


protected:
	static void _bind_methods();
};
