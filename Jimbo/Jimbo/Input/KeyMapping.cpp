/////////////////////////////////////////////////////////
// KeyMapping.cpp
//
// Ben Storey
//
// Some static defines to make the interface even nicer 
//
/////////////////////////////////////////////////////////

#include "KeyMapping.h"

namespace Jimbo
{
    KeyModifier KeyModifier::ShiftDown      = KeyModifier(MOD::SHIFT);
    KeyModifier KeyModifier::ControlDown    = KeyModifier(MOD::CONTROL);
    KeyModifier KeyModifier::AltDown        = KeyModifier(MOD::ALT);
    KeyModifier KeyModifier::SuperDown      = KeyModifier(MOD::SUPER);
    KeyModifier KeyModifier::NoModifier     = KeyModifier(0);
}