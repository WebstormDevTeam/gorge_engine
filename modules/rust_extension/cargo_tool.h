#pragma once
#include "core/object/ref_counted.h"

class CargoTool: public RefCounted{
	GDCLASS(CargoTool, RefCounted)

public:
	static CargoTool* Cargo();
	CargoTool* set_work_dir(const String& _work_dir);
	CargoTool* init();
	CargoTool* build();
	CargoTool* add(const String& crate_name);
	Error done() const;

private:
	List<String> cargo_args;
	String work_dir;
};
