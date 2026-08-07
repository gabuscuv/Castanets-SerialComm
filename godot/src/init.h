#pragma once

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

extern "C" GDExtensionBool GDE_EXPORT GDExtensionInit(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization);

void initialize_gdcastanet_module(ModuleInitializationLevel p_level);
void uninitialize_gdcastanet_module(ModuleInitializationLevel p_level);