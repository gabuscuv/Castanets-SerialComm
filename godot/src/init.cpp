#include "init.h"
#include "gdcastanet_server.h"
#include "gdcastanet_node.h"

godot::ModuleInitializationLevel module_init_level = godot::MODULE_INITIALIZATION_LEVEL_SCENE;

// Initialization.
GDExtensionBool GDE_EXPORT GDExtensionInit(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_gdcastanet_module);
	init_obj.register_terminator(uninitialize_gdcastanet_module);
	init_obj.set_minimum_library_initialization_level(module_init_level);

	return init_obj.init();
}

void initialize_gdcastanet_module(ModuleInitializationLevel p_level) {
    if (p_level != module_init_level) {
        return;
    }

    ClassDB::register_class<godot::GDCastanetsServer>();
    memnew(godot::GDCastanetsServer);
    ClassDB::register_class<godot::GDCastanetsNode>();
}
void uninitialize_gdcastanet_module(ModuleInitializationLevel p_level) {
    if (p_level != module_init_level) {
        return;
    }

    memdelete(godot::GDCastanetsServer::get_singleton());
}