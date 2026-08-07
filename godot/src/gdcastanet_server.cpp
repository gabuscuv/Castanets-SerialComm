
#include "gdcastanet_server.h"
#include <godot_cpp/core/class_db.hpp>
#include "lib.h"
#include "shared/dataStruct.h"

namespace godot 
{
    GDCastanetsServer* GDCastanetsServer::singleton = nullptr;

    void GDCastanetsServer::_bind_methods()
    {
        // Binding methods can be done here if needed
        ADD_SIGNAL(MethodInfo(READ_NFC_CALLBACK));
    }

    void GDCastanetsServer::lib_callback_function(InputFrame inputFrame)
    {
        GDCastanetsServer::get_singleton()->
            emit_signal(READ_NFC_CALLBACK);
    }

    GDCastanetsServer::GDCastanetsServer() 
    {
        singleton = this;
        castanetscomm_init(&GDCastanetsServer::lib_callback_function);
    }

    GDCastanetsServer::~GDCastanetsServer() 
    {
        castanetscomm_exit();
        singleton = nullptr;
    }

    GDCastanetsServer* GDCastanetsServer::get_singleton() 
    {
        return singleton;
    }
}