/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#pragma once

#define MATRIX_COL_PINS_RIGHT \
    { B0, B1, B12, B3, B4, B5 }

// #    define BOOTLOADER_RESET_PIN A0
#define DEBUG_LED_PIN C13

#define AUDIO_PIN B7
#define AUDIO_PWM_DRIVER PWMD4
#define AUDIO_PWM_CHANNEL 2
#define AUDIO_PWM_PAL_MODE 2
#define AUDIO_INIT_DELAY
#define AUDIO_ENABLE_TONE_MULTIPLEXING
#define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10

#define SERIAL_USART_SPEED (1 * 1024 * 1024)

#undef POINTING_DEVICE_CS_PIN
#define POINTING_DEVICE_CS_PIN A15 // b14
#define PMW33XX_LIFTOFF_DISTANCE 0b1111

#define RGB_MATRIX_LED_FLUSH_LIMIT 33
#define RGB_MATRIX_LED_PROCESS_LIMIT 29

#undef ROTATIONAL_TRANSFORM_ANGLE
#define ROTATIONAL_TRANSFORM_ANGLE 25
#define POINTING_DEVICE_ROTATION_270

/* RGB Matrix. */
#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150

// Display common config
#define DISPLAY_DC_PIN C15

// 128x128 SSD1351 OLED
#define DISPLAY_CS_PIN_ILI9341 B14
#define DISPLAY_RST_PIN_ILI9341 C14

#define QUANTUM_PAINTER_CONCURRENT_ANIMATIONS 8
#define QUANTUM_PAINTER_LOAD_FONTS_TO_RAM TRUE

#define BACKLIGHT_PIN B6
#define BACKLIGHT_LEVELS 10

#define CHARYBDIS_MINIMUM_DEFAULT_DPI 1200
#define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 400
#define CHARYBDIS_MINIMUM_SNIPING_DPI 200
#define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 100

#define CHARYBDIS_CONFIG_SYNC

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 5
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0
#define BOOTMAGIC_LITE_EEPROM_ROW 1
#define BOOTMAGIC_LITE_EEPROM_COLUMN 0
#define BOOTMAGIC_LITE_EEPROM_ROW_RIGHT 1
#define BOOTMAGIC_LITE_EEPROM_COLUMN_RIGHT 0

#define DEBOUNCE 15

#undef PMW33XX_CS_DIVISOR
#define PMW33XX_CS_DIVISOR 8

#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 8
