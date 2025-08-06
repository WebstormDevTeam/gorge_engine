#include "register_types.h"

#include "cargo_tool.h"
#include "init_rust_extension.h"
#include "rust_extension.h"
#include "core/object/class_db.h"

void initialize_rust_extension_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	ClassDB::register_class<RustExtension>();
	ClassDB::register_class<InitRustExtension>();
	ClassDB::register_class<CargoTool>();
}

void uninitialize_rust_extension_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

