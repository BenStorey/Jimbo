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
    const KeyModifier KeyModifier::ShiftDown      = KeyModifier(MOD::SHIFT);
    const KeyModifier KeyModifier::ControlDown    = KeyModifier(MOD::CONTROL);
    const KeyModifier KeyModifier::AltDown        = KeyModifier(MOD::ALT);
    const KeyModifier KeyModifier::SuperDown      = KeyModifier(MOD::SUPER);
    const KeyModifier KeyModifier::NoModifier     = KeyModifier(0);
}