
/** @file   gpio.c
 *  @brief  GPIO driver.
 *
 *  This contains the driver definitions for the GPIO module.
 *
 *  @author MikroElektronika
 *  @bug    No known bugs.
 */
 
/* -- Includes -- */

#include "gpio.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** @brief Function sets pin to be digital input
 *
 *  @param pin        Number of pin.
 *  @param pull_mode  Selecting the pin to be pulled down or up.
 *
 *  @return Void.
 */
 
void gpio_set_pin_digital_input(uint8_t pin, PIN_PULL pull_mode) 
{
    GPIO0->PIN_CNF[pin] = (pull_mode << 2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** @brief Function sets pin to be digital output
 *
 *  @param pin        Number of pin.
 *  @param pull_mode  Selecting drive mode of pin.
 *
 *  @return Void.
 */

void gpio_set_pin_digital_output(uint8_t pin, PIN_DRIVE drive_mode) 
{
    GPIO0->PIN_CNF[pin] = (1 | (drive_mode << 8));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** @brief Function connect or disconnect input buffer.
 *
 *  @param pin        Number of pin.
 *
 *  @return Void.
 */

void gpio_disconnect_pin(uint8_t pin) 
{
    GPIO0->PIN_CNF[pin] = 2;  //reset to input, disconnected
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** @brief Function read state of corresponding input pin.
 *
 *  @param pin    Number of pin.
 *
 *  @return Void.
 */

bool gpio_read (uint8_t pin) 
{
    return (GPIO0->IN & (1 << pin)) ? true : false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** @brief Function set state of output pin.
 *
 *  @param pin    Number of pin.
 *  @param value  New state.
 *
 *  @return Void.
 */

void gpio_write (uint8_t pin, bool value) 
{
    *(value ? &(GPIO0->OUTSET) : &(GPIO0->OUTCLR)) = 1 << pin;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
