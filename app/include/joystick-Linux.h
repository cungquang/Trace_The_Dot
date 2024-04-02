#ifndef _JOYSTICK_LINUX_H_
#define _JOYSTICK_LINUX_H_

//Initiate joystick
void joystick_init(void);
void joystick_cleanup(void);

// Get from joystick down
bool joystickDown_isPressed(void);
int joystickDown_pressCount(void);

// Get from joystick right
bool joystickRight_isPressed(void);
int joystickRight_pressCount(void);

#endif