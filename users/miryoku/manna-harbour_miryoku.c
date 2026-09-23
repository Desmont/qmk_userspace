// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "manna-harbour_miryoku.h"


// Additional Features double tap guard

enum {
    U_TD_BOOT,
#define MIRYOKU_X(LAYER, STRING) U_TD_U_##LAYER,
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    reset_keyboard();
  }
}

#define MIRYOKU_X(LAYER, STRING) \
void u_td_fn_U_##LAYER(tap_dance_state_t *state, void *user_data) { \
  if (state->count == 2) { \
    default_layer_set((layer_state_t)1 << U_##LAYER); \
  } \
}
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X

tap_dance_action_t tap_dance_actions[] = {
    [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
#define MIRYOKU_X(LAYER, STRING) [U_TD_U_##LAYER] = ACTION_TAP_DANCE_FN(u_td_fn_U_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


// keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#define MIRYOKU_X(LAYER, STRING) [U_##LAYER] = U_MACRO_VA_ARGS(MIRYOKU_LAYERMAPPING_##LAYER, MIRYOKU_LAYER_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


// shift functions

const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);

const key_override_t *key_overrides[] = {
    &capsword_key_override
};


// thumb combos

#if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
const uint16_t PROGMEM thumbcombos_base_right[] = {LT(U_SYM, KC_ENT), LT(U_NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(U_NAV, KC_SPC), LT(U_MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[] = {MS_BTN2, MS_BTN1, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[] = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[] = {KC_0, KC_MINS, COMBO_END};
  #if defined (MIRYOKU_LAYERS_FLIP)
const uint16_t PROGMEM thumbcombos_sym[] = {KC_UNDS, KC_LPRN, COMBO_END};
  #else
const uint16_t PROGMEM thumbcombos_sym[] = {KC_RPRN, KC_UNDS, COMBO_END};
  #endif
const uint16_t PROGMEM thumbcombos_fun[] = {KC_SPC, KC_TAB, COMBO_END};
combo_t key_combos[] = {
  COMBO(thumbcombos_base_right, LT(U_FUN, KC_DEL)),
  COMBO(thumbcombos_base_left, LT(U_MEDIA, KC_ESC)),
  COMBO(thumbcombos_nav, KC_DEL),
  COMBO(thumbcombos_mouse, MS_BTN3),
  COMBO(thumbcombos_media, KC_MUTE),
  COMBO(thumbcombos_num, KC_DOT),
  #if defined (MIRYOKU_LAYERS_FLIP)
  COMBO(thumbcombos_sym, KC_RPRN),
  #else
  COMBO(thumbcombos_sym, KC_LPRN),
  #endif
  COMBO(thumbcombos_fun, KC_APP)
};
#endif

// Customisation - tap-then-hold auto-repeats home row letters.
// Mod-taps only: layer-taps keep 0 so tap-then-hold still reaches the layer.
// e.g. tap-then-hold T repeats "t"; tap-then-hold space still switches to Nav.
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    return IS_QK_MOD_TAP(keycode) ? 150 : QUICK_TAP_TERM;
}

// Customisation - Permissive Hold for the thumb layer-taps and the Shift home row mods.
// e.g. hold N, tap P, release N: "P" instead of "np".
// Button layer-taps are excluded: eager, they turned "szt" into "sT".
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    return (IS_QK_LAYER_TAP(keycode) && QK_LAYER_TAP_GET_LAYER(keycode) != U_BUTTON) ||
           (IS_QK_MOD_TAP(keycode) && QK_MOD_TAP_GET_MODS(keycode) == MOD_LSFT);
}

// Customisation - exempt layer-taps from Chordal Hold, so same-hand thumb chords work.
// e.g. left thumb space + left hand D is paste (Nav), not "space d".
#if defined(CHORDAL_HOLD)
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record,
                      uint16_t other_keycode, keyrecord_t *other_record) {
    if (IS_QK_LAYER_TAP(tap_hold_keycode)) {
        return true;
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
}
#endif

// Customisation - register right alt as hold in uncertain circumstances.
// Matched on the modifier so it holds for whichever key the alphabet puts AltGr on.
// e.g. X and . on Colemak-DH, Q on Dvorak.
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return IS_QK_MOD_TAP(keycode) && QK_MOD_TAP_GET_MODS(keycode) == MOD_RALT;
}

// Customisation - Incrase tapping term for key combos involving Win keys
// e.g. A (GUI) settles after 304ms, T (Shift) after MOD_TAP_TERM, space (Nav) after TAPPING_TERM.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_A):
        case LGUI_T(KC_O):
            return TAPPING_TERM * 1.6;
        default:
            return IS_QK_MOD_TAP(keycode) ? MOD_TAP_TERM : TAPPING_TERM;
    }
}

// Customisation - stop modded keys (C(KC_V), KC_HASH) leaking their base key.
// Any press clears weak mods, leaving V or 3 held. Released in pre-process, which runs right after
// that clear and before tap-hold settles.
// e.g. without this, holding paste and pressing T types "vvvv".
static uint8_t held_modded_basic = KC_NO;

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && held_modded_basic != KC_NO) {
        unregister_code(held_modded_basic);
        held_modded_basic = KC_NO;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_QK_MODS(keycode) && !IS_MODIFIER_KEYCODE(QK_MODS_GET_BASIC_KEYCODE(keycode))) {
        if (record->event.pressed) {
            held_modded_basic = QK_MODS_GET_BASIC_KEYCODE(keycode);
        } else if (held_modded_basic == QK_MODS_GET_BASIC_KEYCODE(keycode)) {
            held_modded_basic = KC_NO;
        }
    }
    return true;
}
