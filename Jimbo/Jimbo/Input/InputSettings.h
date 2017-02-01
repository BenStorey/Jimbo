#pragma once

/////////////////////////////////////////////////////////
// InputSettings.h
//
// Ben Storey
//
// We want to map our keys (or joystick or whatever) to game actions. Game actions are merely
// represented by an int (which will be a regular enum in code) so that the appropriate parameter
// can be passed back to Scene callbacks. 
//
/////////////////////////////////////////////////////////

#include <unordered_map>
#include <boost/optional/optional.hpp>
#include "input/keymapping.h"

namespace jimbo
{
    class InputSettings
    {

    private:
        // Private structs for storing the mapping data
        struct Key;
        struct KeyHasher;
        
    public:

        using Action = unsigned int;

        void addKeyMapping(KeyMapping key, Action action)
        {
            keyMappings_[Key(key, KeyModifier::NoModifier)] = action;
        }
        
        void addKeyMapping(KeyMapping key, KeyModifier mod, Action action)
        {
            keyMappings_[Key(key, mod)] = action;
        }

        // Returns the action associated with a keypress
        boost::optional<Action> getAction(KeyMapping key, KeyModifier mod)
        {
            auto k = Key(key, mod);
            if (keyMappings_.find(k) == keyMappings_.end()) return boost::optional<Action>();
            return keyMappings_[k];
        }

        void setRepeatInterval(Action action, std::chrono::milliseconds millis)
        {
            repeatIntervals_[action] = millis;
        }

        boost::optional<std::chrono::milliseconds> getRepeatInterval(Action action)
        {
            if (repeatIntervals_.find(action) == repeatIntervals_.end()) return boost::optional<std::chrono::milliseconds>();
            return repeatIntervals_[action];
        }

        void reset()
        {
            keyMappings_.clear();
            repeatIntervals_.clear();
        }

    private:

        // Need to implement comparison operator since we are using Key+Modifier together as our key
        struct Key
        {
            Key(KeyMapping key, KeyModifier mod) : key_(key), mod_(mod) {}

            KeyMapping key_;
            KeyModifier mod_;

            bool Key::operator==(const Key& other) const { return (key_ == other.key_) && (mod_ == other.mod_); }
            bool Key::operator!=(const Key& other) const { return !(*this == other); }
        };

        // We can compare keys, but we need to define a hash function for them. Fortunately this is pretty simple,
        // since we know that our int values are small enough that we can have them take 16 bits each
        struct KeyHasher
        {
            std::size_t operator()(const Key& k) const
            {
                return k.mod_.mod_ << 16 | static_cast<unsigned int>(k.key_);
            }
        };

        // Finally our maps. 
        std::unordered_map<Key, Action, KeyHasher> keyMappings_;
        std::unordered_map<Action, std::chrono::milliseconds> repeatIntervals_;
    };
}