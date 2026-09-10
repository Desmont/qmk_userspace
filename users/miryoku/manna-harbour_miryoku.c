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

// Customisation - allow double-tap-hold auto-repeat on the home row.
// Holding a mod-tap engages its modifier, so the letter can only be repeated by tapping the key and
// then holding it again within this term. Returning 0 (the QUICK_TAP_TERM default set in config.h)
// disables that, which is why it is scoped to mod-taps: the thumb and pinky layer-taps keep 0 so a
// tap followed immediately by a hold still reaches the layer instead of repeating space or tab.
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    return IS_QK_MOD_TAP(keycode) ? 150 : QUICK_TAP_TERM;
}

// Customisation - Flow Tap on the thumb layer-taps only. EXPERIMENT.
// A thumb pressed within the flow term of a letter settles as a tap, so the layer cannot engage and
// the preceding letter stays on the base layer - including when that letter was pressed cold, which
// the mod-tap-side version could not catch (its own previous key was already too old).
// Mod-taps deliberately return 0: CHORDAL_HOLD's opposite-hands rule is what guards the home row,
// and Speculative Hold does not protect anything - it only applies the mod earlier.
// Excludes the U_BUTTON pinkies, matching get_permissive_hold's scoping; those are thumbs' business.
// TRADEOFF: a layer chord started within the flow term of a letter now taps instead - space + d
// straight after typing prints "space d" rather than pasting. Pause first and it chords normally.
uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    if (!IS_QK_LAYER_TAP(keycode) || QK_LAYER_TAP_GET_LAYER(keycode) == U_BUTTON) {
        return 0;
    }
    if (is_flow_tap_key(prev_keycode)) {
        return FLOW_TAP_TERM;
    }
    return 0;
}

// Customisation - extend Flow Tap to every thumb key.
// The core default covers KC_SPC and the alphas, so only the space thumb would be protected. The
// other five thumbs tap to Tab/Enter/Backspace/Delete/Escape, which are just as likely to follow a
// letter in normal typing, so add them. Copied from the weak default in action_tapping.c with those
// five keycodes appended.
bool is_flow_tap_key(uint16_t keycode) {
    if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0) {
        return false; // Disable Flow Tap on hotkeys.
    }
    switch (get_tap_keycode(keycode)) {
        case KC_SPC:
        case KC_A ... KC_Z:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
        case KC_SLSH:
        case KC_TAB:  // thumb -> Mouse
        case KC_ENT:  // thumb -> Sym
        case KC_BSPC: // thumb -> Num
        case KC_DEL:  // thumb -> Fun
        case KC_ESC:  // thumb -> Media
            return true;
    }
    return false;
}

// Customisation - Permissive Hold for the thumb layer-taps.
// Without it, holding a thumb and tapping a key inside the tapping term performs the tap action, so
// space + d emitted "space d" instead of Nav's paste. Scoped by target layer rather than by keycode:
// the six thumbs target U_NAV/U_MOUSE/U_MEDIA/U_SYM/U_NUM/U_FUN, and only the bottom-corner pinky keys
// target U_BUTTON. Those are excluded deliberately - they are held together with same-hand thumb mouse
// buttons, and making them eager is what turned "szt" into "sT" via the Button layer's KC_LSFT.
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    return IS_QK_LAYER_TAP(keycode) && QK_LAYER_TAP_GET_LAYER(keycode) != U_BUTTON;
}

// Customisation - exempt layer-taps from Chordal Hold's opposite-hands rule.
// Thumb layer-taps such as LT(U_NAV,KC_SPC) are meant to be usable with either hand: holding the left
// thumb and pressing a left-hand key is a legitimate chord (space + d is paste on Nav), but the default
// rule treats it as a same-hand roll, settles the thumb as a tap and emits "space d" instead. Keep the
// rule for mod-taps, which is where same-hand rolls actually misfire. Safe because
// get_hold_on_other_key_press() below is false for layer-taps, so they still tap on a quick roll.
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
// Matched on the modifier rather than the tap keycode, so this stays correct whichever key the
// selected alphabet layout puts AltGr on: X and . on Colemak-DH, Q on Dvorak, M on Halmak,
// / on BEAKL15, and ALGR_T(KC_DOT) on the custom Extra layer.
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return IS_QK_MOD_TAP(keycode) && QK_MOD_TAP_GET_MODS(keycode) == MOD_RALT;
}

// Customisation - Incrase tapping term for key combos involving Win keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_A):
        case LGUI_T(KC_O):
            return TAPPING_TERM * 1.6;
        default:
            return TAPPING_TERM;
    }
}
