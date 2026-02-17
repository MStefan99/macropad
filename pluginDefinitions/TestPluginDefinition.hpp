#ifndef TEST_PLUGIN_HPP
#define TEST_PLUGIN_HPP

#include "Keyboard.h"
#include "../QuickPlugin.hpp"


QuickPluginDefinition testPluginDefinition {
    "test",
    "Test plugin",
    {
        {
            "Undo",
            {KEY_LEFT_CTRL, 'z'}
        },
        {
            "Redo",
            {KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'z'}
        }
    }
};

#endif
