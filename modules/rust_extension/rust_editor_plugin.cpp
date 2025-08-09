#include "rust_editor_plugin.h"

#include "cargo_tool.h"
#include "core/config/project_settings.h"
#include "editor/editor_node.h"
#include "editor/editor_string_names.h"
#include "editor/gui/editor_title_bar.h"
#include "modules/mono/utils/path_utils.h"
#include "scene/gui/button.h"
#include "scene/gui/popup_menu.h"

RustEditorPlugin::RustEditorPlugin() {
	submenu = memnew(PopupMenu);
	submenu->add_item(TTR("Initial Rust Project"), 0);
	submenu->add_item(TTR("Cargo Build"), 1);
	submenu->add_item(TTR("Cargo Add Godot"), 2);
	submenu->connect("id_pressed", callable_mp(this, &RustEditorPlugin::_submenu_callback));
	submenu->add_separator();
	add_tool_submenu_item(TTR("Rust Extension"), submenu);

	build_button = memnew(BuildButton);
	build_button->connect("pressed", callable_mp(this,&RustEditorPlugin::_build_button_callback));
	add_control_to_container(CONTAINER_TOOLBAR, build_button);
	EditorNode::get_title_bar()->move_child(build_button,4);
}

RustEditorPlugin::~RustEditorPlugin() {
	remove_tool_menu_item(TTR("Rust Extension"));
	// if (build_button) {
	// 	remove_control_from_container(CONTAINER_TOOLBAR, build_button);
	// }
}

void RustEditorPlugin::_submenu_callback(int p_id) {
	const String work_dir = ProjectSettings::get_singleton()->get_resource_path();
	print_line(work_dir);
	Error build_err;
	Error add_deps_err;
	Error init_err;
	switch (p_id) {
		case 0:
			init_err = CargoTool::Cargo()->set_work_dir(work_dir)->init()->done();
			if (init_err != OK) {
				ERR_PRINT("Cargo init Failed");
			}
			add_deps_err = CargoTool::Cargo()->set_work_dir(work_dir)->add("godot")->done();
			if (add_deps_err != OK) {
				ERR_PRINT("Cargo add godot Failed");
			}
			build_err = CargoTool::Cargo()->set_work_dir(work_dir)->build()->done();
			if (build_err != OK) {
				ERR_PRINT("Cargo build Failed");
			}
			break;
		case 1:
			print_line("cargo build");
			build_err = CargoTool::Cargo()->set_work_dir(work_dir)->build()->done();
			if (build_err != OK) {
				ERR_PRINT("Cargo build Failed");
			}
			break;
		case 2:
			add_deps_err = CargoTool::Cargo()->set_work_dir(work_dir)->add("godot")->done();
			if (add_deps_err != OK) {
				ERR_PRINT("Cargo add godot Failed");
			}
			break;
		default:
			ERR_PRINT("Cargo Failed");
	}
}

void RustEditorPlugin::_build_button_callback() {
	print_line("Run Cargo Building...");
	const String work_dir = ProjectSettings::get_singleton()->get_resource_path();
	const Error build_err = CargoTool::Cargo()->set_work_dir(work_dir)->build()->done();
	if (build_err != OK) {
		ERR_PRINT("Cargo build Failed");
	}
}


void RustEditorPlugin::_bind_methods() {
}

void BuildButton::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_THEME_CHANGED: {
			Ref<Texture> icon = get_theme_icon(SNAME("Script"), EditorStringName(EditorIcons));
			set_button_icon(icon);
			break;
		}
	}
}

BuildButton::BuildButton() {
	set_flat(true);
	set_tooltip_text(TTR("Cargo Build"));
	// 图标将在 NOTIFICATION_THEME_CHANGED 中设置
}

BuildButton::~BuildButton() {
}
