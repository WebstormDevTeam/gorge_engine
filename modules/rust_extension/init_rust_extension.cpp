#include "init_rust_extension.h"

InitRustExtension::InitRustExtension() {

}

String InitRustExtension::get_extension_file(const String& project_name) {

	const String profile = R"(
		[configuration]
		entry_symbol = "gdext_rust_init"
		compatibility_minimum = 4.1
		reloadable = true

		[libraries]
		linux.debug.x86_64 =     "res://target/debug/lib{YourCrate}.so"
		linux.release.x86_64 =   "res://target/release/lib{YourCrate}.so"
		windows.debug.x86_64 =   "res://target/debug/{YourCrate}.dll"
		windows.release.x86_64 = "res://target/release/{YourCrate}.dll"
		macos.debug =            "res://target/debug/lib{YourCrate}.dylib"
		macos.release =          "res://target/release/lib{YourCrate}.dylib"
		macos.debug.arm64 =      "res://target/debug/lib{YourCrate}.dylib"
		macos.release.arm64 =    "res://target/release/lib{YourCrate}.dylib"
	)";
	//替换所有的{YourCrate}为项目名
	return profile.replace("{YourCrate}", project_name);
}
