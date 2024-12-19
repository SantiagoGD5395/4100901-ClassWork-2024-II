/*Incluir librerias */
#include <stdint.h>
#include "systick.h"
#include "gpio.h"
#include "uart.h"
#include "drive.h"

/*Definicion de Pines*/

#define LED_PIN_IN 5
#define LED_PIN_RIGHT 7
#define LED_PIN_LEFT 6
#define BUTTON_PIN_1 13
#define BUTTON_PIN_2 14


int main(void) {
    configure_systick_and_start();// parpadeo
    configure_gpio(BUTTON_PIN_1, BUTTON_PIN_2, LED_PIN_RIGHT, LED_PIN_LEFT, LED_PIN_IN);
    LedToggleTask toggle_task = {0}; 
    while (1) {
        if (systick_GetTick(COUNTER_A) >= 500) {   
            gpio_toggle_led(LED_PIN_IN);
            systick_reset(COUNTER_A);
        }
        if (!toggle_task.active && gpio_button_flag(BUTTON_PIN_1)) {
            start_toggle_task(&toggle_task, LED_PIN_RIGHT);
        }
        if (!toggle_task.active && gpio_button_flag(BUTTON_PIN_2)) {
            start_toggle_task(&toggle_task, LED_PIN_LEFT);
        }
        handle_toggle_task(&toggle_task, systick_GetTick(COUNTER_B)); 
    }
}
