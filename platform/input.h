#ifndef INPUT_H
#define INPUT_H

#include "core/defines.h"

#if LF_PLATFORM_LINUX

#include "keys.h"
#include "math/math_types.h"

// Initialize input
void input_init();

/* KEYBOARD */
// Return if key is/was pressed
b8 is_key_down(Keys key);
b8 was_key_down(Keys key);

// Return if key is/was released
b8 is_key_up(Keys key);
b8 was_key_up(Keys key);

/* MOUSE */
// Return if button is/was pressed
b8 is_button_down(Buttons button);
b8 was_button_down(Buttons button);

// Return if button is/was released
b8 is_button_up(Buttons button);
b8 was_button_up(Buttons button);

// Return mouse position
sshort16 get_mouse_x();
sshort16 get_mouse_y();
// Vec2 get_mouse_position();

// Handle mouse input
void input_process_button(Buttons button, b8 pressed);
void input_update_mouse_position(f32 x, f32 y);

// Handle keyboard input
void input_process_key(Keys key, b8 pressed);

// Update input from previous cicle
void input_update();

// Translate keycode from XCB to custom keycode
Keys translate_keycode(uint32 x_keycode);

#endif // LF_PLATFORM_LINUX

#endif // INPUT_H