#pragma once
#include "editor/plugins/editor_plugin.h"
#include "scene/gui/panel_container.h"

class BlueprintEditor : public EditorPlugin{
	GDCLASS(BlueprintEditor, EditorPlugin)
public:
	explicit BlueprintEditor();

	String get_plugin_name() const override;
	bool has_main_screen() const override;

private:
	PanelContainer* main_panel;
};
