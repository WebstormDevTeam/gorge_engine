#include "register_types.h"

#include "blueprint_editor.h"
#include "core/object/class_db.h"

void initialize_blueprint_editor_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	// ClassDB::register_class<BlueprintEditor>();
}

void uninitialize_blueprint_editor_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
