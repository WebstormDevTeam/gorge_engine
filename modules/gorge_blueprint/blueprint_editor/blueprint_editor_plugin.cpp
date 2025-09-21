#include "blueprint_editor_plugin.h"

#include "editor/editor_interface.h"
#include "scene/gui/box_container.h"
#include "scene/gui/label.h"

BlueprintEditorPlugin::BlueprintEditorPlugin() {
	auto test = memnew(Label);
	test->set_text("hello");
	print_line("test");
	EditorInterface *editor_interface = EditorInterface::get_singleton();
	editor_interface->get_editor_main_screen()->add_child(test);
}

BlueprintEditorPlugin::~BlueprintEditorPlugin() {
}

String BlueprintEditorPlugin::get_plugin_name()const {
	return TTR("BluePrint Editor");
}
