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
    MOVE,
    TOHO,
};

enum custom_keycodes {
    PARENS = SAFE_RANGE,
    CURLY,
    SQUARE,
    DQUOTE,
    FIRE_TOGGLE,
};

enum combo_events {
    SV_ESC,
    COMMAD_CAPS_LOCK,
    VOLDOWNVOLUP_MUTE,
    COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM esc_combo[] = {KC_S, LCTL_T(KC_V), COMBO_END};
const uint16_t PROGMEM capslock_combo[] = {RSFT_T(KC_COMMA), LSFT_T(KC_D), COMBO_END};
const uint16_t PROGMEM mute_combo[] = {KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, COMBO_END};

combo_t key_combos[] = {
    [SV_ESC] = COMBO_ACTION(esc_combo),
    [COMMAD_CAPS_LOCK] = COMBO_ACTION(capslock_combo),
    [VOLDOWNVOLUP_MUTE] = COMBO_ACTION(mute_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    static bool commad_caps_lock_on = false;
    if(pressed) {
        switch(combo_index) {
        case SV_ESC:
            tap_code16(KC_ESC);
            break;
        case COMMAD_CAPS_LOCK:
            tap_code16(KC_CAPS_LOCK);
            if(commad_caps_lock_on) {
                rgb_matrix_set_color(18, 0, 0, 0);
                rgb_matrix_set_color(54, 0, 0, 0);
                commad_caps_lock_on = false;
            } else {
                rgb_matrix_set_color(18, 255, 255, 255);
                rgb_matrix_set_color(54, 255, 255, 255);
                commad_caps_lock_on = true;
            }
            break;
        case VOLDOWNVOLUP_MUTE:
            tap_code16(KC_KB_MUTE);
            break;
        }
    }
}

bool get_combo_must_press_in_order(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
        default:
            return true;
    }
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        case SV_ESC:
            return 75;
    case COMMAD_CAPS_LOCK:
    case VOLDOWNVOLUP_MUTE:
        return 100;
    }
    return COMBO_TERM;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_moonlander(
        QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
        KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_HOME,
        
        KC_NO, KC_Q, KC_W, KC_F, KC_P, KC_B, TG(TOHO),
        KC_NO, KC_J, KC_L, KC_U, KC_Y, KC_SEMICOLON, KC_PAGE_UP,
        
        QK_CAPS_WORD_TOGGLE, KC_A, KC_R, KC_S, LT(MOVE, KC_T), KC_G, KC_NO,
        KC_NO, KC_M, KC_N, KC_E, KC_I, KC_O, KC_PAGE_DOWN,
        
        KC_NO, LALT_T(KC_X), LGUI_T(KC_C), LSFT_T(KC_D), LCTL_T(KC_V), KC_Z,
        KC_K, RCTL_T(KC_H), RSFT_T(KC_COMMA), RGUI_T(KC_DOT), LALT_T(KC_SLASH), KC_END,
        
        RGB_TOG, KC_NO, KC_NO, KC_NO, KC_LEFT_GUI, KC_KB_VOLUME_DOWN,
        KC_KB_VOLUME_UP, TT(SYMB), KC_UP, KC_DOWN, KC_LEFT, KC_RIGHT,
        
        LT(NUMB, KC_SPACE), KC_TAB, KC_ESCAPE, KC_DELETE, KC_ENTER, LT(SYMB, KC_BACKSPACE)
        ),

    [SYMB] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        
        KC_NO, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_MINUS, KC_UNDERSCORE, KC_TILDE, KC_NO,
        KC_NO, KC_NO, KC_EXCLAIM, KC_AT, KC_HASH, KC_NO, KC_NO,
        
        KC_NO, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_QUOTE, DQUOTE, KC_TILDE, KC_NO,
        KC_NO, KC_NO, KC_DOLLAR, KC_PERCENT, KC_CIRCUMFLEX, KC_PIPE, KC_NO,
        
        KC_NO, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_GRAVE, KC_EQUAL, KC_NO,
        KC_NO, KC_AMPERSAND, KC_BACKSLASH, KC_SLASH, KC_NO, KC_NO,
        
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        
        PARENS, SQUARE, CURLY, _______, _______, _______
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

    [MOVE] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, LCTL(KC_LEFT), KC_UP, LCTL(KC_RIGHT), KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_F12, _______, _______, _______, _______, LCTL(KC_BACKSPACE)
        ),

    [TOHO] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TG(TOHO),
        KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_C, KC_LEFT_SHIFT, KC_Z, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        FIRE_TOGGLE, _______, _______, _______, _______, KC_X
        ),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LT(MOVE, KC_T):
        return 165;
    case LT(NUMB, KC_SPACE):
    case LT(SYMB, KC_BACKSPACE):
    case LALT_T(KC_X):
    case LGUI_T(KC_C):
    case LSFT_T(KC_D):
    case LCTL_T(KC_V):
    case RCTL_T(KC_H):
    case RSFT_T(KC_COMMA):
    case RGUI_T(KC_DOT):
    case RALT_T(KC_SLASH):
        return 175;
    default:
        return TAPPING_TERM;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool fire_on = false;
    if (record->event.pressed) {
        switch (keycode) {
        case PARENS:
            SEND_STRING(SS_LSFT("90") SS_TAP(X_LEFT));
            return false;
        case CURLY:
            SEND_STRING(SS_LSFT("[]") SS_TAP(X_LEFT));
            return false;
        case SQUARE:
            SEND_STRING("[]" SS_TAP(X_LEFT));
            return false;
        case DQUOTE:
            SEND_STRING(SS_LSFT("''") SS_TAP(X_LEFT));
            return false;
        case FIRE_TOGGLE:
            if(fire_on) {
                unregister_code16(KC_Z);
                fire_on = false;
            } else {
                register_code16(KC_Z);
                fire_on = true;
            }
            return false;
        }
    }
    return true;
}
