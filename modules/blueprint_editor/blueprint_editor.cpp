#include "blueprint_editor.h"

#include "editor/editor_interface.h"
#include "scene/gui/box_container.h"
#include "scene/gui/label.h"

BlueprintEditor::BlueprintEditor() {
	main_panel = memnew(PanelContainer);



	EditorInterface::get_singleton()->get_editor_main_screen()->add_child(main_panel);
}

String BlueprintEditor::get_plugin_name() const {
	return "Blueprint Editor";
}

bool BlueprintEditor::has_main_screen() const {
	return true;
}
