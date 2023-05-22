/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE,  // default layer
    SYMB,  // symbols
    NUMB,  // numbers
};

enum custom_keycodes {
    VRSN = SAFE_RANGE,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_moonlander(
        QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
        KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_HOME,
        
        KC_NO, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_NO,
        KC_NO, KC_J, KC_L, KC_U, KC_Y, KC_SEMICOLON, KC_PAGE_UP,
        
        QK_CAPS_WORD_TOGGLE, KC_A, KC_R, KC_S, KC_T, KC_G, KC_NO,
        KC_NO, KC_M, KC_N, KC_E, KC_I, KC_O, KC_PAGE_DOWN,
        
        KC_NO, LALT_T(KC_X), LGUI_T(KC_C), LSFT_T(KC_D), LCTL_T(KC_V), KC_Z,
        KC_K, RCTL_T(KC_H), RSFT_T(KC_COMMA), RGUI_T(KC_DOT), RALT_T(KC_SLASH), KC_END,
        
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_KB_VOLUME_DOWN,
        KC_KB_VOLUME_UP, KC_NO, KC_UP, KC_DOWN, KC_LEFT, KC_RIGHT,
        
        KC_SPACE, KC_ESCAPE, KC_TAB, KC_DELETE, KC_ENTER, KC_BACKSPACE
        ),

    [SYMB] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        
        KC_NO, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_MINUS, KC_UNDERSCORE, KC_TILDE, KC_NO,
        KC_NO, KC_NO, KC_EXCLAIM, KC_AT, KC_HASH, KC_NO, KC_NO,
        
        KC_NO, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_QUOTE, KC_DOUBLE_QUOTE, KC_TILDE, KC_NO,
        KC_NO, KC_NO, KC_DOLLAR, KC_PERCENT, KC_CIRCUMFLEX, KC_PIPE, KC_NO,
        
        KC_NO, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_GRAVE, KC_EQUAL, KC_NO,
        KC_NO, KC_AMPERSAND, KC_BACKSLASH, KC_SLASH, KC_NO, KC_NO,
        
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        
        _______, _______, _______, _______, _______, _______
        ),

    [NUMB] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_1, KC_2, KC_3, KC_NO, KC_NO,

        KC_NO, KC_SLASH, KC_ASTERISK, KC_EQUAL, KC_PLUS, KC_MINUS, KC_NO,
        KC_NO, KC_NO, KC_4, KC_5, KC_6, KC_DOT, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_7, KC_8, KC_9, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_0, KC_0, KC_0, KC_NO, KC_NO,
        
        _______, _______, _______, _______, _______, _______
        ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case VRSN:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        }
    }
    return true;
}
