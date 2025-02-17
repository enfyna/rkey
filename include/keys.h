#include <raylib.h>

#define KEY_COUNT (61)

int keys[KEY_COUNT] = {

    [0] = KEY_ESCAPE,

    [1] = KEY_ONE,
    [2] = KEY_TWO,
    [3] = KEY_THREE,
    [4] = KEY_FOUR,
    [5] = KEY_FIVE,
    [6] = KEY_SIX,
    [7] = KEY_SEVEN,
    [8] = KEY_EIGHT,
    [9] = KEY_NINE,
    [10] = KEY_ZERO,

    [11] = KEY_MINUS,
    [12] = KEY_EQUAL,
    [13] = KEY_BACKSPACE,

    [14] = KEY_TAB,

    [15] = KEY_Q,
    [16] = KEY_W,
    [17] = KEY_E,
    [18] = KEY_R,
    [19] = KEY_T,
    [20] = KEY_Y,
    [21] = KEY_U,
    [22] = KEY_I,
    [23] = KEY_O,
    [24] = KEY_P,

    [25] = KEY_LEFT_BRACKET,
    [26] = KEY_RIGHT_BRACKET,

    [27] = KEY_ENTER,
    [28] = KEY_CAPS_LOCK,

    [29] = KEY_A,
    [30] = KEY_S,
    [31] = KEY_D,
    [32] = KEY_F,
    [33] = KEY_G,
    [34] = KEY_H,
    [35] = KEY_J,
    [36] = KEY_K,
    [37] = KEY_L,
    [38] = KEY_SEMICOLON,

    [39] = KEY_APOSTROPHE,
    [40] = KEY_BACKSLASH,

    [41] = KEY_ENTER,
    [42] = KEY_LEFT_SHIFT,

    [43] = KEY_Z,
    [44] = KEY_X,
    [45] = KEY_C,
    [46] = KEY_V,
    [47] = KEY_B,
    [48] = KEY_N,
    [49] = KEY_M,

    [50] = KEY_COMMA,
    [51] = KEY_PERIOD,
    [52] = KEY_SLASH,

    [53] = KEY_RIGHT_SHIFT,

    [54] = KEY_LEFT_CONTROL,
    [55] = KEY_LEFT_SUPER,
    [56] = KEY_LEFT_ALT,
    [57] = KEY_SPACE,
    [58] = KEY_RIGHT_ALT,
    [59] = KEY_KB_MENU,
    [60] = KEY_RIGHT_CONTROL,

};

#define KP_COUNT 8

int keys_pos[KP_COUNT] = {
    KEY_F,
    KEY_D,
    KEY_S,
    KEY_A,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_SEMICOLON,
};

int pos_keys[84][10] = {

    [KEY_F] = {
        KEY_G,
        KEY_FOUR,
        KEY_FIVE,
        KEY_R,
        KEY_T,
        KEY_F,
        KEY_V,
        KEY_B,
    },

    [KEY_D] = {
        KEY_E,
        KEY_THREE,
        KEY_D,
        KEY_C,
    },

    [KEY_S] = {
        KEY_W,
        KEY_TWO,
        KEY_S,
        KEY_X,
    },

    [KEY_A] = {
        KEY_Q,
        KEY_ONE,
        KEY_A,
        KEY_Z,
    },

    [KEY_J] = {
        KEY_J,
        KEY_SIX,
        KEY_SEVEN,
        KEY_Y,
        KEY_U,
        KEY_H,
        KEY_N,
        KEY_M,
    },

    [KEY_K] = {
        KEY_I,
        KEY_EIGHT,
        KEY_K,
        KEY_COMMA,
    },

    [KEY_L] = {
        KEY_O,
        KEY_NINE,
        KEY_L,
        KEY_PERIOD,
    },

    [KEY_SEMICOLON] = {
        KEY_ZERO,
        KEY_P,
        KEY_SEMICOLON,
        KEY_SLASH,
        KEY_MINUS,
        KEY_EQUAL,
        KEY_LEFT_BRACKET,
        KEY_RIGHT_BRACKET,
        KEY_APOSTROPHE,
        KEY_BACKSLASH,
    },

};
