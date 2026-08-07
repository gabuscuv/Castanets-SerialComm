#include "gdcastanet_node.h"

#include "gdcastanet_server.h"
#include <godot_cpp/variant/utility_functions.hpp>

#define EXPORT_NFC_READ_SIGNAL "on_nfc_card_read"

void godot::GDCastanetsNode::_bind_methods()
{
    ClassDB::bind_method(D_METHOD(EXPORT_NFC_READ_SIGNAL), &GDCastanetsNode::on_nfc_card_read);
}

godot::GDCastanetsNode::GDCastanetsNode()
{
    GDCastanetsServer::get_singleton()->
    connect(READ_NFC_CALLBACK, 
        Callable(this, EXPORT_NFC_READ_SIGNAL)
    );
}

void godot::GDCastanetsNode::on_nfc_card_read()
{
    godot::UtilityFunctions::print("NFC Card Read!");
}

godot::GDCastanetsNode::~GDCastanetsNode()
{
}