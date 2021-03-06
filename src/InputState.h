/*
Copyright © 2011-2012 Clint Bellanger
Copyright © 2012-2015 Justin Jacobs

This file is part of FLARE.

FLARE is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

FLARE is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
FLARE.  If not, see http://www.gnu.org/licenses/
*/

#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include "CommonIncludes.h"
#include "Utils.h"

#define JOY_POS_CENTER	0
#define JOY_POS_LEFT	-1
#define JOY_POS_RIGHT	1
#define JOY_POS_UP	-1
#define JOY_POS_DOWN	1

enum INPUT_BINDINGS {
	INPUT_BINDING_DEFAULT = 0,
	INPUT_BINDING_ALT = 1,
	INPUT_BINDING_JOYSTICK = 2
};

// Input commands enum
const int CANCEL = 0;
const int ACCEPT = 1;
const int UP = 2;
const int DOWN = 3;
const int LEFT = 4;
const int RIGHT = 5;
const int BAR_1 = 6;
const int BAR_2 = 7;
const int BAR_3 = 8;
const int BAR_4 = 9;
const int BAR_5 = 10;
const int BAR_6 = 11;
const int BAR_7 = 12;
const int BAR_8 = 13;
const int BAR_9 = 14;
const int BAR_0 = 15;
const int CHARACTER = 16;
const int INVENTORY = 17;
const int POWERS = 18;
const int LOG = 19;
const int MAIN1 = 20;
const int MAIN2 = 21;
const int CTRL = 22;
const int SHIFT = 23;
const int ALT = 24;
const int DEL = 25;
const int ACTIONBAR = 26;
const int ACTIONBAR_BACK = 27;
const int ACTIONBAR_FORWARD = 28;
const int ACTIONBAR_USE = 29;
const int DEVELOPER_MENU = 30;

// we store mouse bindings and keyboard bindings together
// keyboard keycodes are all positive integers, so we use negative integers for mouse buttons
// -1 is reserved for unbound keys, so we start mouse bindings at -2
// adding MOUSE_BIND_OFFSET to a mouse bind gives us the appropriate mouse button (mouse buttons start at 1)
const int MOUSE_BIND_OFFSET = 2;
const int JOY_AXIS_OFFSET = 2;

// some mouse buttons are named (e.g. "Left Mouse")
const int MOUSE_BUTTON_NAME_COUNT = 7;

/**
 * class InputState
 *
 * Handles keyboard and mouse states
 */

class InputState {
public:
	static const int key_count = 31;
	int binding[key_count];
	int binding_alt[key_count];
	int binding_joy[key_count];

	std::string binding_name[31];
	std::string mouse_button[MOUSE_BUTTON_NAME_COUNT];

	InputState(void);
	virtual ~InputState() {};

	virtual void initJoystick() = 0;
	void defaultJoystickBindings();
	void loadKeyBindings();
	void saveKeyBindings();
	void resetScroll();
	void lockActionBar();
	void unlockActionBar();
	void setKeybindNames();

	virtual void handle();
	virtual void defaultQwertyKeyBindings() = 0;
	virtual void hideCursor() = 0;
	virtual void showCursor() = 0;
	virtual std::string getJoystickName(int index) = 0;
	virtual std::string getKeyName(int key) = 0;
	virtual std::string getMouseButtonName(int button) = 0;
	virtual std::string getJoystickButtonName(int button) = 0;
	virtual std::string getBindingString(int key, int bindings_list = INPUT_BINDING_DEFAULT) = 0;
	virtual std::string getMovementString() = 0;
	virtual std::string getAttackString() = 0;
	virtual std::string getContinueString() = 0;
	virtual int getNumJoysticks() = 0;
	virtual bool usingMouse() = 0;
	virtual void startTextInput() = 0;
	virtual void stopTextInput() = 0;
	virtual void setKeybind(int key, int binding_button, int bindings_list, std::string& keybind_msg) = 0;

	void enableEventLog();

	bool pressing[key_count];
	bool lock[key_count];

	// handle repeating keys, such as when holding Backspace to delete text in WidgetInput
	bool slow_repeat[key_count];
	int repeat_ticks[key_count];
	int max_repeat_ticks[key_count];

	bool done;
	Point mouse;
	std::string inkeys;
	int last_key;
	int last_button;
	int last_joybutton;
	int last_joyaxis;
	bool last_is_joystick;
	bool scroll_up;
	bool scroll_down;
	bool lock_scroll;
	bool touch_locked;
	bool lock_all;
	bool window_minimized;
	bool window_restored;
	bool window_resized;
	bool pressing_up;
	bool pressing_down;
	bool joysticks_changed;

protected:
	Point scaleMouse(unsigned int x, unsigned int y);

	bool un_press[key_count];
	Point current_touch;
	bool dump_event;
};

#endif
