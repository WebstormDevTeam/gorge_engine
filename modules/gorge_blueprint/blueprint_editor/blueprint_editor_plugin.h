#pragma once
#include "editor/plugins/editor_plugin.h"

class BlueprintEditorPlugin : public EditorPlugin{
	GDCLASS(BlueprintEditorPlugin, EditorPlugin)
public:
	BlueprintEditorPlugin();
	~BlueprintEditorPlugin();

	String get_plugin_name() const override;
};
