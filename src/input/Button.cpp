#include "Button.h"

#include <SFML/Graphics.hpp>

void Button::update(const bool isPressed)
{
    if      (isIdle()   &&  isPressed)  state = ButtonState::Tapped;
    else if (isTapped() &&  isPressed)  state = ButtonState::Held;
    else if (isTapped() && !isPressed)  state = ButtonState::Released;
    else if (isHeld()   && !isPressed)  state = ButtonState::Released;
    else if (isReleased()            )  state = ButtonState::Idle;
}