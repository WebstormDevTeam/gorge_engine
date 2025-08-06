#pragma once
#include "core/object/ref_counted.h"

class InitRustExtension: public RefCounted {
	GDCLASS(InitRustExtension,RefCounted)
public:
	InitRustExtension();

	static String get_extension_file(const String& project_name);

	enum ExtensionTypes {
		NONE,
		RUST,
		CSHARP
	};


};
