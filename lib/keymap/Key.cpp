#include <Key.h>
#include "Keyboard.h"

Key::Key(int code)
{
    keyCode = code;
    isLayer = false;
}

LayerKey::LayerKey(int layer)
{
    keyCode = layer;
    isLayer = true;
}

SpecialKey::SpecialKey(int code)
{
    keyCode = code;
    isLayer = false;
    isSpecial = true;
}