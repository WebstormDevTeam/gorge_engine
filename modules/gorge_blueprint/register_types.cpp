#include "register_types.h"

#include "blueprint_editor/blueprint_editor_plugin.h"
#include "core/object/class_db.h"

void initialize_gorge_blueprint_module(ModuleInitializationLevel p_level) {
	if (p_level!=MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	ClassDB::register_class<BlueprintEditorPlugin>();
}

void uninitialize_gorge_blueprint_module(ModuleInitializationLevel p_level) {
	if (p_level!=MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
