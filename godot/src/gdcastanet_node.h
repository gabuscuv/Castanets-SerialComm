#pragma once

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node.hpp>

namespace godot 
{
    class GDCastanetsNode : public Node
    {
    GDCLASS(GDCastanetsNode, Node);

    protected:
    	static void _bind_methods();

    public:
        void on_nfc_card_read();
	    GDCastanetsNode();
        ~GDCastanetsNode();
    };
}