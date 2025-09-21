#include "rust_editor_plugin.h"

#include "cargo_tool.h"
#include "core/config/project_settings.h"
#include "editor/editor_node.h"
#include "editor/editor_string_names.h"
#include "editor/gui/editor_title_bar.h"
#include "modules/mono/utils/path_utils.h"
#include "scene/gui/button.h"
#include "scene/gui/file_dialog.h"
#include "scene/gui/label.h"
#include "scene/gui/line_edit.h"
#include "scene/gui/popup_menu.h"

RustEditorPlugin::RustEditorPlugin() {
	submenu = memnew(PopupMenu);
	submenu->add_item(TTR("Initial Rust Project"), INIT);
	submenu->add_item(TTR("Cargo Build"), BUILD);
	submenu->add_item(TTR("Cargo Add Godot"), ADD_DEPS);
	submenu->add_item(TTR("Create New Rust Object"), NEW_OBJECT);
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
		case INIT:
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
		case BUILD:
			print_line("cargo build");
			build_err = CargoTool::Cargo()->set_work_dir(work_dir)->build()->done();
			if (build_err != OK) {
				ERR_PRINT("Cargo build Failed");
			}
			break;
		case ADD_DEPS:
			add_deps_err = CargoTool::Cargo()->set_work_dir(work_dir)->add("godot")->done();
			if (add_deps_err != OK) {
				ERR_PRINT("Cargo add godot Failed");
			}
			break;
		case NEW_OBJECT:
			_create_new_rust_object();
			break;
		default:
			ERR_PRINT("Cargo Failed");
	}
}

void RustEditorPlugin::_create_new_rust_object() {
	print_line("Create new rust object");
	//TODO:修复UI形态的问题
	create_windows = memnew(Window);
	create_windows->set_title(TTR("New Rust Object"));
	create_windows->set_position((DisplayServer::get_singleton()->screen_get_size() / 2));
	create_windows->set_size(Size2i(500, 300));

	VBoxContainer* vbox = memnew(VBoxContainer);
	vbox->set_h_size_flags(Control::SIZE_FILL);
	vbox->set_alignment(BoxContainer::ALIGNMENT_CENTER);

	// 类名输入部分
	Label* name_label = memnew(Label);
	name_label->set_text(TTR("Class Name:"));

	HBoxContainer* name_hbox = memnew(HBoxContainer);
	name_hbox->set_h_size_flags(Control::SIZE_FILL);
	vbox->add_child(name_hbox);

	name_hbox->add_child(name_label);

	LineEdit* name_input = memnew(LineEdit);
	name_input->set_placeholder(TTR("Enter Class Name By snake_case"));
	name_input->set_h_size_flags(Control::SIZE_FILL);
	name_input->set_horizontal_alignment(HORIZONTAL_ALIGNMENT_CENTER);
	name_hbox->add_child(name_input);

	// 路径选择部分
	Label* path_label = memnew(Label);
	path_label->set_text(TTR("Path:"));

	HBoxContainer* path_hbox = memnew(HBoxContainer);
	path_hbox->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	vbox->add_child(path_hbox);

	path_hbox->add_child(path_label);

	LineEdit* path_input = memnew(LineEdit);
	path_input->set_placeholder(TTR("Select Path:"));
	path_input->set_editable(false);
	path_input->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	path_input->set_horizontal_alignment(HORIZONTAL_ALIGNMENT_CENTER);
	path_hbox->add_child(path_input);

	Button* browse_button = memnew(Button);
	browse_button->set_text(TTR("Browse"));
	path_hbox->add_child(browse_button);

	FileDialog* file_dialog = memnew(FileDialog);
	file_dialog->set_access(FileDialog::ACCESS_RESOURCES);
	file_dialog->set_file_mode(FileDialog::FILE_MODE_SAVE_FILE);
	file_dialog->set_show_hidden_files(false);
	create_windows->add_child(file_dialog);

	// 按钮区域
	HBoxContainer* button_hbox = memnew(HBoxContainer);
	button_hbox->set_alignment(BoxContainer::ALIGNMENT_CENTER);
	vbox->add_child(button_hbox);

	Button* ok_button = memnew(Button);
	ok_button->set_text(TTR("OK"));
	ok_button->set_custom_minimum_size(Size2(100, 0));
	button_hbox->add_child(ok_button);

	Button* cancel_button = memnew(Button);
	cancel_button->set_text(TTR("Cancel"));
	cancel_button->set_custom_minimum_size(Size2(100, 0));
	button_hbox->add_child(cancel_button);

	create_windows->add_child(vbox);

	// 连接信号
	browse_button->connect("pressed", callable_mp(file_dialog, &FileDialog::FileDialog::popup_file_dialog));
	file_dialog->connect("dir_selected", callable_mp(path_input, &LineEdit::set_text));
	cancel_button->connect("pressed", callable_mp(this, &RustEditorPlugin::_free_windows_object));

	create_windows->connect("close_requested", callable_mp(this, &RustEditorPlugin::_free_windows_object));
	EditorNode::get_singleton()->add_child(create_windows);
}

void RustEditorPlugin::_free_windows_object() {
	create_windows->queue_free();
}

//TODO:添加快捷键绑定
void RustEditorPlugin::_build_button_callback() {
	print_line("Run Cargo Building...");
	const String work_dir = ProjectSettings::get_singleton()->get_resource_path();
	const Error build_err = CargoTool::Cargo()->set_work_dir(work_dir)->build()->done();
	print_line("Cargo build done");
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
		default:
			break;
	}
}

BuildButton::BuildButton() {
	set_flat(true);
	set_tooltip_text(TTR("Cargo Build"));
	// 图标将在 NOTIFICATION_THEME_CHANGED 中设置
}

BuildButton::~BuildButton() {
}
