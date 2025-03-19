#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "app.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PULSE_PIN1_PORT 0  // GPIO port for PIO0_8
#define PULSE_PIN1_PIN  8  // PIO0_8
#define PULSE_PIN2_PORT 0  // GPIO port for PIO0_9
#define PULSE_PIN2_PIN  9  // PIO0_9

#define PULSE_PIN11_PORT 0  // GPIO port for PIO0_11
#define PULSE_PIN11_PIN  11  // PIO0_11


#define PULSE_DELAY_MS  50  // Delay for pulse in milliseconds

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_systickCounter;

/*******************************************************************************
 * Code
 ******************************************************************************/
void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Define the init structure for the output pulse pins */
    gpio_pin_config_t pulse_config = {
        kGPIO_DigitalOutput,
        0,  // Start with LOW
    };

    /* Board pin, clock, debug console init */
    BOARD_InitHardware();

    /* Initialize the GPIO ports */
    GPIO_PortInit(GPIO, PULSE_PIN1_PORT);
    GPIO_PortInit(GPIO, PULSE_PIN2_PORT);
    GPIO_PortInit(GPIO, PULSE_PIN11_PORT);

    /* Configure PIO0_8 and PIO0_9 as outputs */
    GPIO_PinInit(GPIO, PULSE_PIN1_PORT, PULSE_PIN1_PIN, &pulse_config);
    GPIO_PinInit(GPIO, PULSE_PIN2_PORT, PULSE_PIN2_PIN, &pulse_config);
    GPIO_PinInit(GPIO, PULSE_PIN11_PORT, PULSE_PIN11_PIN, &pulse_config);

    PRINTF("\r\nGPIO Pulse Output Example on PIO0_8 and PIO0_9\r\n");

    GPIO_PortSet(GPIO, PULSE_PIN11_PORT, (0U << PULSE_PIN11_PIN));

    /* Set systick reload value to generate 1ms interrupt */
    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        while (1)
        {
        }
    }

    while (1)
    {
        /* Toggle PIO0_8 and PIO0_9 */
        GPIO_PortToggle(GPIO, PULSE_PIN1_PORT, (1U << PULSE_PIN1_PIN));
        // GPIO_PortToggle(GPIO, PULSE_PIN2_PORT, (1U << PULSE_PIN2_PIN));

        /* Delay */
        SysTick_DelayTicks(PULSE_DELAY_MS);
    }
}
