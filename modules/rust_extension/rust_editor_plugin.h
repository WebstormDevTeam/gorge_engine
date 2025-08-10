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
	Window* create_windows;
	void _build_button_callback();

	enum RustMenuID {
		INIT,
		BUILD,
		ADD_DEPS,
		NEW_OBJECT
	};

private:
	void _submenu_callback(int p_id);
	void _create_new_rust_object();
	void _free_windows_object();

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
