#pragma once
#include "core/object/ref_counted.h"

class InitRustExtension: public RefCounted {
	GDCLASS(InitRustExtension,RefCounted)
public:
	InitRustExtension();

	static String get_extension_file(const String& project_name);
	static String get_enter_file();

	enum ExtensionTypes {
		NONE,
		RUST,
		CSHARP
	};


};
