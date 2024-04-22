// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// Implemented in manna-harbour_miryoku.c
#define TAPPING_TERM_PER_KEY
#define TAPPING_TERM_ACCENT 150

#define MIRYOKU_LAYER_EXTRA \
KC_TAB,            KC_Q,              KC_W,              KC_E,              KC_R,             KC_Y,              KC_U,              KC_UP,             KC_O,              KC_P,              \
KC_LSFT,           KC_A,              KC_S,              KC_D,              KC_F,             KC_H,              KC_LEFT,           KC_DOWN,           KC_RGHT,           LGUI_T(KC_QUOT),   \
KC_LCTL,           KC_Z,              KC_X,              KC_C,              KC_V,             KC_N,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    LT(U_BUTTON,KC_SLSH),\
U_NP,              U_NP,              KC_ESC,            KC_SPC,            KC_LALT,          LT(U_SYM,KC_ENT),  LT(U_NUM,KC_BSPC), LT(U_FUN,KC_DEL),  U_NP,              U_NP

#define MIRYOKU_LAYER_NAV \
TD(U_TD_BOOT),     U_NA,              LCTL(KC_F),        U_NA,              KC_BSPC,           U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,             \
KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           KC_ENT,            CW_TOGG,           KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,           \
U_UND,             U_CUT,             U_CPY,             U_PST,             U_RDO,             KC_INS,            KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,            \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              KC_ENT,            KC_BSPC,           KC_DEL,            U_NP,              U_NP

#define MIRYOKU_LAYER_MOUSE \
TD(U_TD_BOOT),     U_NA,              LCTL(KC_F),        U_NA,              KC_BSPC,           U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,             \
KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           KC_ENT,            U_NU,              KC_MS_L,           KC_MS_D,           KC_MS_U,           KC_MS_R,           \
U_UND,             U_CUT,             U_CPY,             U_PST,             U_RDO,             U_NU,              KC_WH_L,           KC_WH_D,           KC_WH_U,           KC_WH_R,           \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              KC_BTN2,           KC_BTN1,           KC_BTN3,           U_NP,              U_NP

#define MIRYOKU_LAYER_MEDIA \
TD(U_TD_BOOT),     U_NA,              LCTL(KC_F),        U_NA,              KC_BSPC,           RGB_TOG,           RGB_MOD,           RGB_HUI,           RGB_SAI,           RGB_VAI,           \
KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           KC_ENT,            U_NU,              KC_MPRV,           KC_VOLD,           KC_VOLU,           KC_MNXT,           \
U_UND,             U_CUT,             U_CPY,             U_PST,             U_RDO,             OU_AUTO,           U_NU,              U_NU,              U_NU,              U_NU,              \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              KC_MSTP,           KC_MPLY,           KC_MUTE,           U_NP,              U_NP
