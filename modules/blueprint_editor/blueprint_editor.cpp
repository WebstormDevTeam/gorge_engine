#define SAFETY

#include "blueprint_editor.h"

#include "safety.h"
#include "editor/editor_interface.h"
#include "editor/inspector/editor_inspector.h"
#include "scene/gui/box_container.h"
#include "scene/gui/label.h"



BlueprintEditor::BlueprintEditor() {
	main_panel = memnew(PanelContainer);

	let left_panel = memnew(PanelContainer);
	left_panel->set_size(Vector2(200,main_panel->get_size().y));
	let left_panel_title = memnew(Label);
	left_panel_title->set_text("Blueprint Component");

	let editor_panel = memnew(PanelContainer);
	let editor_panel_title = memnew(Label);
	editor_panel_title->set_text("Blueprint Editor");

	editor_panel->add_child(editor_panel_title);

	left_panel->add_child(left_panel_title);

	main_panel->add_child(left_panel);
	main_panel->add_child(editor_panel);
	EditorInterface::get_singleton()->get_editor_main_screen()->add_child(main_panel);
}

String BlueprintEditor::get_plugin_name() const {
	return "Blueprint Editor";
}

bool BlueprintEditor::has_main_screen() const {
	return true;
}
