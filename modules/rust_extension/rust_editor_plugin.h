#pragma once
#include "editor/editor_node.h"
#include "editor/plugins/editor_plugin.h"
#include "scene/gui/button.h"

class RustEditorPlugin: public EditorPlugin{
	GDCLASS(RustEditorPlugin, EditorPlugin)
public:
	RustEditorPlugin();
	~RustEditorPlugin();

	PopupMenu* submenu;
	Button* build_button;
	void _build_button_callback();

private:
	void _submenu_callback(int p_id);

protected:
	static void _bind_methods();
};

class BuildButton: public Button{
	GDCLASS(BuildButton, Button)
	
protected:
	void _notification(int p_what);

public:
	BuildButton();
	~BuildButton();

};