/**
 * USB HID Keyboard scan codes as per USB spec 1.11
 * plus some additional codes
 * 
 * Created by MightyPork, 2016
 * Public domain
 * 
 * Adapted from:
 * https://source.android.com/devices/input/keyboard-devices.html
 */

#ifndef KEYCODES_H
#define KEYCODES_H

#define KEY_CTRL  0x0080
#define KEY_SHIFT 0x0081
#define KEY_ALT   0x0082
#define KEY_META  0x0083

#define KEY_NONE 0x0000 // No key pressed
#define KEY_ERR_OVF 0x0001 //  Keyboard Error Roll Over - used for all slots if too many keys are pressed ("Phantom key")

#define KEY_A 0x0004 // Keyboard a and A
#define KEY_B 0x0005 // Keyboard b and B
#define KEY_C 0x0006 // Keyboard c and C
#define KEY_D 0x0007 // Keyboard d and D
#define KEY_E 0x0008 // Keyboard e and E
#define KEY_F 0x0009 // Keyboard f and F
#define KEY_G 0x000a // Keyboard g and G
#define KEY_H 0x000b // Keyboard h and H
#define KEY_I 0x000c // Keyboard i and I
#define KEY_J 0x000d // Keyboard j and J
#define KEY_K 0x000e // Keyboard k and K
#define KEY_L 0x000f // Keyboard l and L
#define KEY_M 0x0010 // Keyboard m and M
#define KEY_N 0x0011 // Keyboard n and N
#define KEY_O 0x0012 // Keyboard o and O
#define KEY_P 0x0013 // Keyboard p and P
#define KEY_Q 0x0014 // Keyboard q and Q
#define KEY_R 0x0015 // Keyboard r and R
#define KEY_S 0x0016 // Keyboard s and S
#define KEY_T 0x0017 // Keyboard t and T
#define KEY_U 0x0018 // Keyboard u and U
#define KEY_V 0x0019 // Keyboard v and V
#define KEY_W 0x001a // Keyboard w and W
#define KEY_X 0x001b // Keyboard x and X
#define KEY_Y 0x001c // Keyboard y and Y
#define KEY_Z 0x001d // Keyboard z and Z

#define KEY_1 0x001e // Keyboard 1 and !
#define KEY_2 0x001f // Keyboard 2 and @
#define KEY_3 0x0020 // Keyboard 3 and #
#define KEY_4 0x0021 // Keyboard 4 and $
#define KEY_5 0x0022 // Keyboard 5 and %
#define KEY_6 0x0023 // Keyboard 6 and ^
#define KEY_7 0x0024 // Keyboard 7 and &
#define KEY_8 0x0025 // Keyboard 8 and *
#define KEY_9 0x0026 // Keyboard 9 and (
#define KEY_0 0x0027 // Keyboard 0 and )

#define KEY_ENTER 0x0028 // Keyboard Return (ENTER)
#define KEY_ESC 0x0029 // Keyboard ESCAPE
#define KEY_BACKSPACE 0x002a // Keyboard DELETE (Backspace)
#define KEY_TAB 0x002b // Keyboard Tab
#define KEY_SPACE 0x002c // Keyboard Spacebar
#define KEY_MINUS 0x002d // Keyboard - and _
#define KEY_EQUAL 0x002e // Keyboard = and +
#define KEY_LEFTBRACE 0x002f // Keyboard [ and {
#define KEY_RIGHTBRACE 0x0030 // Keyboard ] and }
#define KEY_BACKSLASH 0x0031 // Keyboard \ and |
#define KEY_HASHTILDE 0x0032 // Keyboard Non-US # and ~
#define KEY_SEMICOLON 0x0033 // Keyboard ; and :
#define KEY_APOSTROPHE 0x0034 // Keyboard ' and "
#define KEY_GRAVE 0x0035 // Keyboard ` and ~
#define KEY_COMMA 0x0036 // Keyboard , and <
#define KEY_DOT 0x0037 // Keyboard . and >
#define KEY_SLASH 0x0038 // Keyboard / and ?
#define KEY_CAPSLOCK 0x0039 // Keyboard Caps Lock

#define KEY_F1 0x003a // Keyboard F1
#define KEY_F2 0x003b // Keyboard F2
#define KEY_F3 0x003c // Keyboard F3
#define KEY_F4 0x003d // Keyboard F4
#define KEY_F5 0x003e // Keyboard F5
#define KEY_F6 0x003f // Keyboard F6
#define KEY_F7 0x0040 // Keyboard F7
#define KEY_F8 0x0041 // Keyboard F8
#define KEY_F9 0x0042 // Keyboard F9
#define KEY_F10 0x0043 // Keyboard F10
#define KEY_F11 0x0044 // Keyboard F11
#define KEY_F12 0x0045 // Keyboard F12

#define KEY_PRINT_SCREEN 0x0046 // Keyboard Print Screen
#define KEY_SCROLLLOCK 0x0047 // Keyboard Scroll Lock
#define KEY_PAUSE 0x0048 // Keyboard Pause
#define KEY_INSERT 0x0049 // Keyboard Insert
#define KEY_HOME 0x004a // Keyboard Home
#define KEY_PAGEUP 0x004b // Keyboard Page Up
#define KEY_DELETE 0x004c // Keyboard Delete Forward
#define KEY_END 0x004d // Keyboard End
#define KEY_PAGEDOWN 0x004e // Keyboard Page Down
#define KEY_RIGHT 0x004f // Keyboard Right Arrow
#define KEY_LEFT 0x0050 // Keyboard Left Arrow
#define KEY_DOWN 0x0051 // Keyboard Down Arrow
#define KEY_UP 0x0052 // Keyboard Up Arrow

#define KEY_NUMLOCK 0x0053 // Keyboard Num Lock and Clear
#define KEY_KPSLASH 0x0054 // Keypad /
#define KEY_KPASTERISK 0x0055 // Keypad *
#define KEY_KPMINUS 0x0056 // Keypad -
#define KEY_KPPLUS 0x0057 // Keypad +
#define KEY_KPENTER 0x0058 // Keypad ENTER
#define KEY_KP1 0x0059 // Keypad 1 and End
#define KEY_KP2 0x005a // Keypad 2 and Down Arrow
#define KEY_KP3 0x005b // Keypad 3 and PageDn
#define KEY_KP4 0x005c // Keypad 4 and Left Arrow
#define KEY_KP5 0x005d // Keypad 5
#define KEY_KP6 0x005e // Keypad 6 and Right Arrow
#define KEY_KP7 0x005f // Keypad 7 and Home
#define KEY_KP8 0x0060 // Keypad 8 and Up Arrow
#define KEY_KP9 0x0061 // Keypad 9 and Page Up
#define KEY_KP0 0x0062 // Keypad 0 and Insert
#define KEY_KPDOT 0x0063 // Keypad . and Delete

#define KEY_F13 0x0068 // Keyboard F13
#define KEY_F14 0x0069 // Keyboard F14
#define KEY_F15 0x006a // Keyboard F15
#define KEY_F16 0x006b // Keyboard F16
#define KEY_F17 0x006c // Keyboard F17
#define KEY_F18 0x006d // Keyboard F18
#define KEY_F19 0x006e // Keyboard F19
#define KEY_F20 0x006f // Keyboard F20
#define KEY_F21 0x0070 // Keyboard F21
#define KEY_F22 0x0071 // Keyboard F22
#define KEY_F23 0x0072 // Keyboard F23
#define KEY_F24 0x0073 // Keyboard F24

//LAYERS
#define HOLD_LAYER_0 0x00f0
#define HOLD_LAYER_1 0x00f1
#define HOLD_LAYER_2 0x00f2
#define HOLD_LAYER_3 0x00f3
#define HOLD_LAYER_4 0x00f4
#define HOLD_LAYER_5 0x00f5
#define HOLD_LAYER_6 0x00f6

#define TOGGLE_LAYER_0 0x00f7
#define TOGGLE_LAYER_1 0x00f8
#define TOGGLE_LAYER_2 0x00f9
#define TOGGLE_LAYER_3 0x00fa
#define TOGGLE_LAYER_4 0x00fb
#define TOGGLE_LAYER_5 0x00fc
#define TOGGLE_LAYER_6 0x00fd


//SHIFTED KEYS
#define KEY_EXCLAMATION 0x0f1e // Keyboard !
#define KEY_AT 0x0f1f // Keyboard @
#define KEY_HASH 0x0f20 // Keyboard #
#define KEY_DOLLAR 0x0f21 // Keyboard $
#define KEY_MODULO 0x0f22 // Keyboard %
#define KEY_CARET 0x0f23 // Keyboard ^
#define KEY_AMPERSAND 0x0f24 // Keyboard &
#define KEY_ASTERISK 0x0f25 // Keyboard *
#define KEY_LEFT_BRACKET 0x0f26 // Keyboard (
#define KEY_RIGHT_BRACKET 0x0f27 // Keyboard )

#define KEY_UNDERSCORE 0x0f2d // Keyboard _
#define KEY_PLUS 0x0f2e // Keyboard +
#define KEY_LEFT_CURLY 0x0f2f // Keyboard {
#define KEY_RIGHT_CURLY 0x0f30 // Keyboard }
#define KEY_PIPE 0x0f31 // Keyboard |
#define KEY_COLON 0x0f33 // Keyboard :
#define KEY_QUOTE 0x0f34 // Keyboard ' and "
#define KEY_TILDE 0x0f35 // Keyboard ` and ~
#define KEY_LESS 0x0f36 // Keyboard <
#define KEY_GREATER 0x0f37 // Keyboard >
#define KEY_QUESTION 0x0f38 // Keyboard ?

//MEDIA KEYS
#define BEGIN_MEDIA 0x0088
#define END_MEDIA 0x00ef

#define MEDIA_VOL_MUTE 0x00E2
#define MEDIA_VOL_UP 0x00E9
#define MEDIA_VOL_DOWN 0x00EA

#define MEDIA_NEXT 0xB5
#define MEDIA_PREV 0xB6
#define MEDIA_PLAY_PAUSE 0xCD

//MOUSE KEYS

#endif
