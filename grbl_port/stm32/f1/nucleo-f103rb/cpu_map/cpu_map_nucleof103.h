/*
  cpu_map_nucleof103.h - CPU and pin mapping configuration file for NUCLEO F103 board.
  Part of grbl_port_opencm3 project.

  Copyright (c) 2017 Angelo Di Chello

  Grbl_port_opencm3 is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl_port_opencm3 is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl_port_opencm3.  If not, see <http://www.gnu.org/licenses/>.
*/

/* This cpu_map file serves as a central pin mapping settings file for ST Nucleo F103 */

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/flash.h>

//#define BASIC_CPU_SPEED
#ifdef BASIC_CPU_SPEED
#define F_CPU (16000000)
#define PSC_MUL_FACTOR 1
#else
#define F_CPU (48000000)
#define PSC_MUL_FACTOR 3
#endif

#ifdef GRBL_PLATFORM
#error "cpu_map already defined: GRBL_PLATFORM=" GRBL_PLATFORM
#endif

#define GRBL_PLATFORM "NucleoF103"

#define NUCLEO // Nucleo
//#define USE_RX_DMA

#define MAIN_SECTOR 126
#define COPY_SECTOR 127
#define EFLASH_MAIN_BASE_ADDRESS          0x0801F800U
#define EFLASH_COPY_BASE_ADDRESS          0x0801FC00U

// Serial port pins
// #define SERIAL_RX USART0_RX_vect
// #define SERIAL_UDRE USART0_UDRE_vect

// Increase Buffers to make use of extra SRAM
//#define RX_BUFFER_SIZE		256
//#define TX_BUFFER_SIZE		128
//#define BLOCK_BUFFER_SIZE	36
//#define LINE_BUFFER_SIZE	100

// Define step pulse output pins. NOTE: All step bit pins must be on the same port.
#define STEP_X_DDR        GPIOA_CRH
#define STEP_X_PORT       GPIOA_ODR
#define X_STEP_BIT        10 // NucleoF103 Digital PA10
#define X_STEP_BIT_REL    2
#define STEP_MASK_X_DDR   (0x00000001<<(X_STEP_BIT_REL*4 + 2)) // All (step bits*4 + 2) because the direction/mode has 2 bits
#define STEP_X_DDR_RESET_MASK   (0x00000003<<(X_STEP_BIT_REL*4 + 2))
#define STEP_MASK_X       (0x00000001<<X_STEP_BIT)     // X step mask bit

#define STEP_YZ_DDR       GPIOB_CRL
#define STEP_YZ_PORT      GPIOB_ODR
#define Y_STEP_BIT        3 // NucleoF103 Digital PB3
#define Z_STEP_BIT        5 // NucleoF103 Digital PB5
#define STEP_MASK_YZ_DDR  ((0x00000001<<(Y_STEP_BIT*4 + 2))|(0x00000001<<(Z_STEP_BIT*4 + 2))) // All (step bits*4 + 2) because the direction/mode has 2 bits
#define STEP_YZ_DDR_RESET_MASK  ((0x00000003<<(Y_STEP_BIT*4 + 2))|(0x00000003<<(Z_STEP_BIT*4 + 2)))
#define STEP_MASK_YZ      ((0x00000001<<Y_STEP_BIT)|(0x00000001<<Z_STEP_BIT))         // Y-Z step mask bits

// Define step direction output pins. NOTE: All direction pins must be on the same port.
#define DIRECTION_Z_DDR       GPIOA_CRH
#define DIRECTION_Z_PORT      GPIOA_ODR
#define Z_DIRECTION_BIT       8   // NucleoF103 Digital PA8
#define Z_DIRECTION_BIT_REL   0
#define DIRECTION_MASK_Z_DDR  (0x00000001<<(Z_DIRECTION_BIT_REL*4 + 2)) // Z DIR Mask direction bits
#define DIRECTION_Z_DDR_RESET_MASK  (0x00000003<<(Z_DIRECTION_BIT_REL*4 + 2)) // Z DIR Mask direction bits
#define DIRECTION_MASK_Z      (0x00000001<<Z_DIRECTION_BIT) // Z DIR MASK bit

#define DIRECTION_X_DDR       GPIOB_CRL
#define DIRECTION_Y_DDR       GPIOB_CRH
#define DIRECTION_XY_PORT      GPIOB_ODR
#define X_DIRECTION_BIT        4  // NucleoF103 Digital PB4
#define Y_DIRECTION_BIT        10 // NucleoF103 Digital PB10
#define Y_DIRECTION_BIT_REL    2
#define DIRECTION_MASK_XY_DDR  ((0x00000001<<(X_DIRECTION_BIT*4 + 2))|(0x00000001<<(Y_DIRECTION_BIT_REL*4 + 2))) // All direction bits
#define DIRECTION_MASK_X_DDR   (0x00000001<<(X_DIRECTION_BIT*4 + 2)) // All direction bits
#define DIRECTION_MASK_Y_DDR   (0x00000001<<(Y_DIRECTION_BIT_REL*4 + 2)) // All direction bits
#define DIRECTION_XY_DDR_RESET_MASK  ((0x00000003<<(X_DIRECTION_BIT*4 + 2))|(0x00000003<<(Y_DIRECTION_BIT_REL*4 + 2))) // All direction bits
#define DIRECTION_X_DDR_RESET_MASK  (0x00000003<<(X_DIRECTION_BIT*4 + 2)) // All direction bits
#define DIRECTION_Y_DDR_RESET_MASK  (0x00000003<<(Y_DIRECTION_BIT_REL*4 + 2)) // All direction bits
#define DIRECTION_MASK_XY      ((0x00000001<<X_DIRECTION_BIT)|(0x00000001<<Y_DIRECTION_BIT)) // XY DIR MASK bits

// Define stepper driver enable/disable output pin.
#define STEPPERS_DISABLE_DDR        GPIOA_CRH
#define STEPPERS_DISABLE_PORT       GPIOA_ODR
#define STEPPERS_DISABLE_BIT        9                             // NucleoF103 Digital PA9
#define STEPPERS_DISABLE_BIT_REL    1
#define STEPPERS_DISABLE_MASK_DDR   (0x00000001<<(STEPPERS_DISABLE_BIT_REL*4 + 2))
#define STEPPERS_DISABLE_MASK       (0x00000001<<STEPPERS_DISABLE_BIT)

// Define homing/hard limit switch input pins and limit interrupt vectors.
// NOTE: All limit bit pins must be on the same port
#define LIMIT_X_DDR              GPIOC_CRL
#define LIMIT_X_PORT             GPIOC_ODR
#define LIMIT_X_PIN              GPIOC_IDR
#define LIMIT_X_PU               GPIOC_ODR
#define X_LIMIT_BIT               7                     // NucleoF103 Digital PC7
#define LIMIT_X_PU_MASK          (0x00000001<<X_LIMIT_BIT)     // X limit pull-up mask
#define LIMIT_X_PU_RESET_MASK    LIMIT_X_PU_MASK        // X limit pull-up reset mask
#define LIMIT_X_DDR_RESET_MASK   (0x00000003<<(X_LIMIT_BIT*4 + 2)) // X limit dir mask
#define LIMIT_X_MASK             (0x00000001<<X_LIMIT_BIT)       // X limit bits

#define LIMIT_Y_DDR               GPIOB_CRL
#define LIMIT_Y_PORT              GPIOB_ODR
#define LIMIT_Y_PIN               GPIOB_IDR
#define LIMIT_Y_PU                GPIOB_ODR
#define Y_LIMIT_BIT               6                        // NucleoF103 Digital PB6
#define LIMIT_Y_PU_MASK           (0x00000001<<Y_LIMIT_BIT)       // Y limit pull-up mask
#define LIMIT_Y_PU_RESET_MASK     LIMIT_Y_PU_MASK          // Y limit pull-up reset mask
#define LIMIT_Y_DDR_RESET_MASK    ((0x00000003<<(Y_LIMIT_BIT*4 + 2))) // Y limit dir mask
#define LIMIT_Y_MASK              (0x00000001<<Y_LIMIT_BIT)         // Y limit bits

#define LIMIT_Z_DDR               GPIOB_CRL
#define LIMIT_Z_PORT              GPIOB_ODR
#define LIMIT_Z_PIN               GPIOB_IDR
#define LIMIT_Z_PU                GPIOB_ODR
#define Z_LIMIT_BIT               0                        // NucleoF103 Digital PB0
#define LIMIT_Z_PU_MASK           (0x00000001<<Z_LIMIT_BIT)       // Z limit pull-up mask
#define LIMIT_Z_PU_RESET_MASK     LIMIT_Z_PU_MASK          // Z limit pull-up reset mask
#define LIMIT_Z_DDR_RESET_MASK    ((0x00000003<<(Z_LIMIT_BIT*4 + 2))) // Z limit dir mask
#define LIMIT_Z_MASK              (0x00000001<<Z_LIMIT_BIT)         // Z limit bits

#define LIMIT_MASK                (LIMIT_X_MASK | LIMIT_Y_MASK | LIMIT_Z_MASK)
#define INVERT_LIMIT_PIN_MASK     (LIMIT_MASK)

/* Interrupt defines for LIMIT PINS */
#define LIMIT_INT                 NVIC_EXTI9_5_IRQ  // Pin change interrupt enable pin
#define LIMIT_INT_vect            (EXTI6 | EXTI7)
#define LIMIT_PCMSK               NVIC_EXTI9_5_IRQ  // Pin change interrupt register
#define LIMIT_INT_Z               NVIC_EXTI0_IRQ    // Pin change interrupt enable pin
#define LIMIT_INT_vect_Z          (EXTI0)
#define LIMIT_PCMSK_Z             NVIC_EXTI0_IRQ    // Pin change interrupt register


// Define user-control CONTROLs (cycle start, reset, feed hold) input pins.
// NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
#define RESET_CONTROL_DDR               GPIOB_CRL
#define RESET_CONTROL_PORT              GPIOB_ODR
#define RESET_CONTROL_PIN               GPIOB_IDR
#define RESET_CONTROL_PU                GPIOB_ODR
#define RESET_BIT                       2                     // NucleoF103 Digital PB2
#define RESET_CONTROL_PU_MASK           (0x00000001<<RESET_BIT)      // Reset pull-up mask
#define RESET_CONTROL_PU_RESET_MASK     RESET_CONTROL_PU_MASK // Reset dir mask
#define RESET_CONTROL_DDR_RESET_MASK    (0x00000003<<(RESET_BIT*4 + 2))  // Reset dir mask
#define RESET_CONTROL_MASK              (0x00000001<<RESET_BIT)
/* Interrupt defines for RESET CONTROL PIN */
#define RESET_CONTROL_INT               NVIC_EXTI2_IRQ        // Pin change interrupt enable pin
#define RESET_CONTROL_INT_vect          (EXTI2)
#define RESET_CONTROL_PCMSK             NVIC_EXTI2_IRQ        // Pin change interrupt register

#define FEED_HOLD_CONTROL_DDR           GPIOA_CRL
#define FEED_HOLD_CONTROL_PORT          GPIOA_ODR
#define FEED_HOLD_CONTROL_PIN           GPIOA_IDR
#define FEED_HOLD_CONTROL_PU            GPIOA_ODR
#define FEED_HOLD_BIT                   1                        // NucleoF103 Digital PA1
#define FEED_HOLD_PU_MASK               (0x00000001<<FEED_HOLD_BIT)     // Feed Hold pull-up mask
#define FEED_HOLD_PU_RESET_MASK         FEED_HOLD_PU_MASK        // Feed Hold pull-up reset mask
#define FEED_HOLD_DDR_RESET_MASK        (0x00000003<<(FEED_HOLD_BIT*4 + 2)) // Feed Hold DDR reset mask
#define FEED_HOLD_MASK                  (0x00000001<<FEED_HOLD_BIT)
/* Interrupt defines for FEED-HOLD CONTROL PIN */
#define FEED_HOLD_CONTROL_INT           NVIC_EXTI1_IRQ           // Pin change interrupt enable pin
#define FEED_HOLD_CONTROL_INT_vect      (EXTI1)
#define FEED_HOLD_CONTROL_PCMSK         NVIC_EXTI1_IRQ           // Pin change interrupt register

#define CYCLE_START_CONTROL_DDR         GPIOA_CRL
#define CYCLE_START_CONTROL_PORT        GPIOA_ODR
#define CYCLE_START_CONTROL_PIN         GPIOA_IDR
#define CYCLE_START_CONTROL_PU          GPIOA_ODR
#define CYCLE_START_BIT                 4                          // NucleoF103 Digital PA4
#define CYCLE_START_PU_MASK             (0x00000001<<CYCLE_START_BIT)     // CYCLE_START pull-up mask
#define CYCLE_START_PU_RESET_MASK       CYCLE_START_PU_MASK        // CYCLE_START pull-up reset mask
#define CYCLE_START_DDR_RESET_MASK      (0x00000003<<(CYCLE_START_BIT*4 + 2)) // CYCLE_START dir reset mask
#define CYCLE_START_MASK                (0x00000001<<CYCLE_START_BIT)
/* Interrupt defines for CYCLE START CONTROL PIN */
#define CYCLE_START_CONTROL_INT           NVIC_EXTI4_IRQ // Pin change interrupt enable pin
#define CYCLE_START_CONTROL_INT_vect      (EXTI4)
#define CYCLE_START_CONTROL_PCMSK         NVIC_EXTI4_IRQ // Pin change interrupt register

#define SAFETY_DOOR_CONTROL_DDR           GPIOC_CRL
#define SAFETY_DOOR_CONTROL_PORT          GPIOC_ODR
#define SAFETY_DOOR_CONTROL_PIN           GPIOC_IDR
#define SAFETY_DOOR_CONTROL_PU            GPIOC_ODR
#define SAFETY_DOOR_BIT                   3 // NucleoF103 Digital PC3
#define SAFETY_DOOR_PU_MASK               (0x00000001<<SAFETY_DOOR_BIT) // SAFETY_DOOR pull-up mask
#define SAFETY_DOOR_PU_RESET_MASK         SAFETY_DOOR_PU_MASK // SAFETY_DOOR pull-up reset mask
#define SAFETY_DOOR_DDR_RESET_MASK        (0x00000003<<(SAFETY_DOOR_BIT*4 + 2)) // SAFETY_DOOR DDR reset mask
#define SAFETY_DOOR_MASK                  (0x00000001<<SAFETY_DOOR_BIT)
/* Interrupt defines for SAFETY DOOR CONTROL PIN */
#define SAFETY_DOOR_CONTROL_INT           NVIC_EXTI3_IRQ  // Pin change interrupt enable pin
#define SAFETY_DOOR_CONTROL_INT_vect      (EXTI3)
#define SAFETY_DOOR_CONTROL_PCMSK         NVIC_EXTI3_IRQ // Pin change interrupt register



#define CONTROL_INT_vect  (RESET_CONTROL_INT_vect | FEED_HOLD_CONTROL_INT_vect | CYCLE_START_CONTROL_INT_vect | SAFETY_DOOR_CONTROL_INT_vect)

//#define CONTROL_MASK ((0x00000001<<RESET_BIT)|(0x00000001<<FEED_HOLD_BIT)|(0x00000001<<CYCLE_START_BIT)|(0x00000001<<SAFETY_DOOR_BIT))
//#define CONTROL_INVERT_MASK CONTROL_MASK // May be re-defined to only invert certain control pins.


// Define probe switch input pin.
#define PROBE_DDR            GPIOC_CRL
#define PROBE_PIN            GPIOC_IDR
#define PROBE_PORT           GPIOC_ODR
#define PROBE_PU             GPIOC_ODR
#define PROBE_BIT            0                    // NucleoF103 Digital PC0
#define PROBE_PU_MASK        (0x00000001<<PROBE_BIT)     // Probe pull-up mask
#define PROBE_PU_RESET_MASK  PROBE_PU_MASK        // Probe pull-up reset mask
#define PROBE_DDR_RESET_MASK (0x00000003<<(PROBE_BIT*4 + 2)) // Probe dir reset mask
#define PROBE_MASK           (0x00000001<<PROBE_BIT)


// Define spindle enable and spindle direction output pins.
#define SPINDLE_ENABLE_DDR               GPIOA_CRL
#define SPINDLE_ENABLE_PORT              GPIOA_ODR
#define SPINDLE_ENABLE_BIT               6 // NucleoF103 Digital Pin 6
#define SPINDLE_ENABLE_MASK_DDR          (0x00000001<<(SPINDLE_ENABLE_BIT*4 + 2)) // All (step bits*4 + 2) because the direction/mode has 2 bits
#define SPINDLE_ENABLE_DDR_RESET_MASK    (0x00000003<<(SPINDLE_ENABLE_BIT*4 + 2))
#define SPINDLE_ENABLE_MASK              (0x00000001<<SPINDLE_ENABLE_BIT)     // SPINDLE_ENABLE mask bit

#define SPINDLE_DIRECTION_DDR               GPIOA_CRL
#define SPINDLE_DIRECTION_PORT              GPIOA_ODR
#define SPINDLE_DIRECTION_BIT               5 // NucleoF103 Digital Pin 5
#define SPINDLE_DIRECTION_MASK_DDR          (0x00000001<<(SPINDLE_DIRECTION_BIT*4 + 2)) // All (step bits*4 + 2) because the direction/mode has 2 bits
#define SPINDLE_DIRECTION_DDR_RESET_MASK    (0x00000003<<(SPINDLE_DIRECTION_BIT*4 + 2))
#define SPINDLE_DIRECTION_MASK              (0x00000001<<SPINDLE_DIRECTION_BIT)     // SPINDLE_DIRECTION_BIT mask bit

// Start of PWM & Stepper Enabled Spindle
#ifdef VARIABLE_SPINDLE
  // Advanced Configuration Below You should not need to touch these variables
  // Set Timer up to use TIMER4B which is attached to Digital Pin 7
  #define PWM_MAX_VALUE       256.0
  #define TCCRA_REGISTER		TCCR4A
  #define TCCRB_REGISTER		TCCR4B
  #define OCR_REGISTER		OCR4B

  #define COMB_BIT			COM4B1
  #define WAVE0_REGISTER		WGM40
  #define WAVE1_REGISTER		WGM41
  #define WAVE2_REGISTER		WGM42
  #define WAVE3_REGISTER		WGM43

  #define SPINDLE_PWM_DDR               GPIOA_CRL
  #define SPINDLE_PWM_PORT              GPIOA_ODR
  #define SPINDLE_PWM_BIT               6 // NucleoF103 Digital Pin 6
  #define SPINDLE_PWM_MASK_DDR          (0x00000001<<(SPINDLE_PWM_BIT*4 + 2)) // All (step bits*4 + 2) because the direction/mode has 2 bits
  #define SPINDLE_PWM_DDR_RESET_MASK    (0x00000003<<(SPINDLE_PWM_BIT*4 + 2))
  #define SPINDLE_PWM_MASK              (0x00000001<<SPINDLE_PWM_BIT)     // SPINDLE_PWM mask bit
#endif // End of VARIABLE_SPINDLE

// Define flood and mist coolant enable output pins.
#define COOLANT_FLOOD_DDR               GPIOC_CRL
#define COOLANT_FLOOD_PORT              GPIOC_ODR
#define COOLANT_FLOOD_BIT               1 // NucleoF103 Digital Pin 1
#define COOLANT_FLOOD_DDR_MASK          (0x00000001<<(COOLANT_FLOOD_BIT*4 + 2)) // All (step bits*4 + 2) because the direction/mode has 2 bits
#define COOLANT_FLOOD_DDR_RESET_MASK    (0x00000003<<(COOLANT_FLOOD_BIT*4 + 2))
#define COOLANT_FLOOD_MASK              (0x00000001<<COOLANT_FLOOD_BIT)     // COOLANT_FLOOD mask bit
#ifdef ENABLE_M7 // Mist coolant disabled by default. See config.h to enable/disable.
#define COOLANT_MIST_DDR               GPIOC_CRL
#define COOLANT_MIST_PORT              GPIOC_ODR
#define COOLANT_MIST_BIT               2 // NucleoF103 Digital Pin 2
#define COOLANT_MIST_DDR_MASK          (0x00000001<<(COOLANT_MIST_BIT*4 + 2)) // All (step bits*4 + 2) because the direction/mode has 2 bits
#define COOLANT_MIST_DDR_RESET_MASK    (0x00000003<<(COOLANT_MIST_BIT*4 + 2))
#define COOLANT_MIST_MASK              (0x00000001<<COOLANT_MIST_BIT)     // COOLANT_MIST mask bit
#endif

#define SET_STEP_DDR \
  do { \
    STEP_X_DDR &= ~STEP_X_DDR_RESET_MASK; \
    STEP_YZ_DDR &= ~STEP_YZ_DDR_RESET_MASK; \
    STEP_X_DDR |= STEP_MASK_X_DDR; \
    STEP_YZ_DDR |= STEP_MASK_YZ_DDR; \
  } while (0)

#define SET_DIRECTION_DDR \
  do { \
    DIRECTION_X_DDR &= ~DIRECTION_X_DDR_RESET_MASK; \
    DIRECTION_Y_DDR &= ~DIRECTION_Y_DDR_RESET_MASK; \
    DIRECTION_Z_DDR &= ~DIRECTION_Z_DDR_RESET_MASK; \
    DIRECTION_X_DDR |= DIRECTION_MASK_X_DDR; \
    DIRECTION_Y_DDR |= DIRECTION_MASK_Y_DDR; \
    DIRECTION_Z_DDR |= DIRECTION_MASK_Z_DDR; \
  } while (0)

#define SET_STEP_BITS(stepbits) \
  do { \
    STEP_X_PORT = (STEP_X_PORT & ~STEP_MASK_X) | (stepbits & STEP_MASK_X); \
    STEP_YZ_PORT = (STEP_YZ_PORT & ~STEP_MASK_YZ) | (stepbits & STEP_MASK_YZ); \
  } while (0)

#define SET_STEPS(stepbits) \
  do { \
    STEP_X_PORT  = (stepbits & STEP_MASK_X); \
    STEP_YZ_PORT = (stepbits & STEP_MASK_YZ); \
  } while (0)

#define SAVE_STEP_BITS(stepbits) \
  do { st.step_bits = (STEP_X_PORT & ~STEP_MASK_X) | (STEP_YZ_PORT & ~STEP_MASK_YZ) | stepbits;} while (0)

#define SET_DIRECTION_BITS(dirbits) \
  do { \
    DIRECTION_Z_PORT  = (DIRECTION_Z_PORT & ~DIRECTION_MASK_Z) | (dirbits & DIRECTION_MASK_Z); \
    DIRECTION_XY_PORT = (DIRECTION_XY_PORT & ~DIRECTION_MASK_XY) | (dirbits & DIRECTION_MASK_XY); \
  } while (0)

/* set limits pins as inputs */
#define SET_LIMITS_DDR \
  do { \
    LIMIT_X_DDR &= ~LIMIT_X_DDR_RESET_MASK; \
    LIMIT_Y_DDR &= ~LIMIT_Y_DDR_RESET_MASK; \
    LIMIT_Z_DDR &= ~LIMIT_Z_DDR_RESET_MASK; \
  } while (0)

/* unset pull-up for limits pin */
#define UNSET_LIMITS_PU \
  do { \
    LIMIT_X_PU  &= ~LIMIT_X_PU_RESET_MASK; \
    LIMIT_Y_PU  &= ~LIMIT_Y_PU_RESET_MASK; \
    LIMIT_Z_PU  &= ~LIMIT_Z_PU_RESET_MASK; \
    } while (0)

/* set pull-up for limits pin */
#define SET_LIMITS_PU \
  do { \
    LIMIT_X_PU  &= ~LIMIT_X_PU_RESET_MASK; \
    LIMIT_Y_PU  &= ~LIMIT_Y_PU_RESET_MASK; \
    LIMIT_Z_PU  &= ~LIMIT_Z_PU_RESET_MASK; \
    LIMIT_X_PU  |= LIMIT_X_PU_MASK; \
    LIMIT_Y_PU  |= LIMIT_Y_PU_MASK; \
    LIMIT_Z_PU  |= LIMIT_Z_PU_MASK; \
    } while (0)

/* get limits pin status */
#define GET_LIMIT_PIN \
  ((LIMIT_X_PIN & LIMIT_X_MASK) | (LIMIT_Y_PIN & LIMIT_Y_MASK) | (LIMIT_Z_PIN & LIMIT_Z_MASK))

/* set control pins as inputs */
#define SET_CONTROLS_DDR \
  do { \
    RESET_CONTROL_DDR &= ~RESET_CONTROL_DDR_RESET_MASK; \
    FEED_HOLD_CONTROL_DDR  &= ~FEED_HOLD_DDR_RESET_MASK; \
    CYCLE_START_CONTROL_DDR  &= ~CYCLE_START_DDR_RESET_MASK; \
    SAFETY_DOOR_CONTROL_DDR  &= ~SAFETY_DOOR_DDR_RESET_MASK; \
  } while (0)

/* unset pull-up for controls pin */
#define UNSET_CONTROLS_PU \
  do { \
    RESET_CONTROL_PU        &= ~RESET_CONTROL_PU_RESET_MASK; \
    FEED_HOLD_CONTROL_PU    &= ~FEED_HOLD_PU_RESET_MASK; \
    CYCLE_START_CONTROL_PU  &= ~CYCLE_START_PU_RESET_MASK; \
    SAFETY_DOOR_CONTROL_PU  &= ~SAFETY_DOOR_PU_RESET_MASK; \
  } while (0)

/* set pull-up for controls pin */
#define SET_CONTROLS_PU \
  do { \
    RESET_CONTROL_PU        &= ~RESET_CONTROL_PU_RESET_MASK; \
    FEED_HOLD_CONTROL_PU    &= ~FEED_HOLD_PU_RESET_MASK; \
    CYCLE_START_CONTROL_PU  &= ~CYCLE_START_PU_RESET_MASK; \
    SAFETY_DOOR_CONTROL_PU  &= ~SAFETY_DOOR_PU_RESET_MASK; \
    RESET_CONTROL_PU        |= RESET_CONTROL_PU_MASK; \
    FEED_HOLD_CONTROL_PU    |= FEED_HOLD_PU_MASK; \
    CYCLE_START_CONTROL_PU  |= CYCLE_START_PU_MASK; \
    SAFETY_DOOR_CONTROL_PU  |= SAFETY_DOOR_PU_MASK; \
  } while (0)

#define SET_SPINDLE_DIRECTION_DDR \
  do { \
    SPINDLE_DIRECTION_DDR &= ~SPINDLE_DIRECTION_DDR_RESET_MASK; \
    SPINDLE_DIRECTION_DDR |= SPINDLE_DIRECTION_MASK_DDR; \
  } while (0)

#define SET_SPINDLE_DIRECTION_BIT \
  do { \
    SPINDLE_DIRECTION_PORT |= SPINDLE_DIRECTION_MASK; \
  } while (0)

#define UNSET_SPINDLE_DIRECTION_BIT \
  do { \
    SPINDLE_DIRECTION_PORT &= ~(SPINDLE_DIRECTION_MASK); \
  } while (0)

#define SET_SPINDLE_PWM_DDR \
  do { \
    SPINDLE_PWM_DDR &= ~SPINDLE_PWM_DDR_RESET_MASK; \
    SPINDLE_PWM_DDR |= SPINDLE_PWM_MASK_DDR; \
  } while (0)

#define SET_SPINDLE_ENABLE_DDR \
  do { \
    SPINDLE_ENABLE_DDR &= ~SPINDLE_ENABLE_DDR_RESET_MASK; \
    SPINDLE_ENABLE_DDR |= SPINDLE_ENABLE_MASK_DDR; \
  } while (0)

/* Set spindle enable pin */
#define  SET_SPINDLE_ENABLE \
  do { \
    SPINDLE_ENABLE_PORT |= SPINDLE_ENABLE_MASK;  \
  } while (0)

/* Unset spindle enable pin */
#define  UNSET_SPINDLE_ENABLE \
  do { \
    SPINDLE_ENABLE_PORT &= ~SPINDLE_ENABLE_MASK;  \
  } while (0)

/* set probe pin as inputs */
#define SET_PROBE_DDR \
do{ \
	PROBE_DDR &= ~PROBE_DDR_RESET_MASK; \
} while (0)

/* unset pull-up for limits pin */
#define UNSET_PROBE_PU \
do{ \
	PROBE_PU  &= ~PROBE_PU_RESET_MASK; \
} while (0)

/* set pull-up for limits pin */
#define SET_PROBE_PU \
do{ \
	PROBE_PU  &= ~PROBE_PU_RESET_MASK; \
	PROBE_PU  |= PROBE_PU_MASK; \
} while (0)

#define SET_COOLANT_FLOOD_DDR \
  do { \
    COOLANT_FLOOD_DDR &= ~COOLANT_FLOOD_DDR_RESET_MASK; \
    COOLANT_FLOOD_DDR |= COOLANT_FLOOD_DDR_MASK; \
  } while (0)

#define SET_COOLANT_FLOOD_BIT \
  do { \
    COOLANT_FLOOD_PORT |= COOLANT_FLOOD_MASK; \
  } while (0)

#define UNSET_COOLANT_FLOOD_BIT \
  do { \
    COOLANT_FLOOD_PORT &= ~(COOLANT_FLOOD_MASK); \
  } while (0)


#define SET_COOLANT_MIST_DDR \
  do { \
    COOLANT_MIST_DDR &= ~COOLANT_MIST_DDR_RESET_MASK; \
    COOLANT_MIST_DDR |= COOLANT_MIST_DDR_MASK; \
  } while (0)


#define SET_COOLANT_MIST_BIT \
  do { \
    COOLANT_MIST_PORT |= COOLANT_MIST_MASK; \
  } while (0)

#define UNSET_COOLANT_MIST_BIT \
  do { \
    COOLANT_MIST_PORT &= ~(COOLANT_MIST_MASK); \
  } while (0)
