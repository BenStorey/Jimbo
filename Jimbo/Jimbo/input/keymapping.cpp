/////////////////////////////////////////////////////////
// KeyMapping.cpp
//
// Ben Storey
//
// Some static defines to make the interface even nicer 
//
/////////////////////////////////////////////////////////

#include "input/keymapping.hpp"

namespace jimbo
{
    KeyModifier KeyModifier::ShiftDown      = KeyModifier(MOD::SHIFT);
    KeyModifier KeyModifier::ControlDown    = KeyModifier(MOD::CONTROL);
    KeyModifier KeyModifier::AltDown        = KeyModifier(MOD::ALT);
    KeyModifier KeyModifier::SuperDown      = KeyModifier(MOD::SUPER);
    KeyModifier KeyModifier::NoModifier     = KeyModifier(0);
}