#include "cargo_tool.h"

#include "core/core_bind.h"

CargoTool* CargoTool::Cargo() {
	return memnew(CargoTool);
}

CargoTool * CargoTool::set_work_dir(const String &_work_dir) {
	this->work_dir = _work_dir;
	return this;
}

CargoTool * CargoTool::init() {
	this->cargo_args.push_back("init");
	this->cargo_args.push_back("--lib");
	return this;
}

CargoTool * CargoTool::build() {
	this->cargo_args.push_back("build");
	return this;
}

CargoTool * CargoTool::add(const String &crate_name) {
	this->cargo_args.push_back("add");
	this->cargo_args.push_back(crate_name);
	return this;
}

Error CargoTool::done() const {
	String output;
	int exit_code;
	OS *os = OS::get_singleton();
	if (this->work_dir.is_empty()) {
		ERR_PRINT("CargoTool: Not set work_dir");
		return FAILED;
	}
	// String main_command = "cd "+ this->work_dir + " && cargo";
	os->set_cwd(this->work_dir);
	int result = os->execute("cargo", this->cargo_args, &output, &exit_code, true);
	if (result != 0 || exit_code != 0) {
		ERR_PRINT("CargoTool: cargo failed to execute");
		ERR_PRINT(output);
		return FAILED;
	}
	// delete this;
	return OK;
}
