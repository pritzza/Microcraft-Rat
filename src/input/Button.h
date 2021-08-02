#pragma once

enum class ButtonState
{
	Tapped,
	Held,
	Released,
	Idle
};

class Button
{
private:
	ButtonState state{ ButtonState::Idle };

public:
	void update(const bool isPressed);

	inline const bool isTapped() const		{ return state == ButtonState::Tapped;	 }
	inline const bool isHeld() const		{ return state == ButtonState::Held;	 }
	inline const bool isReleased() const	{ return state == ButtonState::Released; }
	inline const bool isIdle() const		{ return state == ButtonState::Idle;	 }
	inline const bool isDown() const		{ return isTapped() || isHeld();		 }
};