#pragma once

#include "shared/dataStruct.h"
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/object.hpp>

#define READ_NFC_CALLBACK "read_nfc_card_callback"

struct InputFrame;

namespace godot 
{
    class GDCastanetsServer : public Object
    {
    GDCLASS(GDCastanetsServer, Object);
    static GDCastanetsServer* singleton;

    protected:
    	static void _bind_methods();
        static void lib_callback_function(InputFrame inputFrame);

    public:
	    GDCastanetsServer();
	    ~GDCastanetsServer();
        static GDCastanetsServer* get_singleton();
    };
}