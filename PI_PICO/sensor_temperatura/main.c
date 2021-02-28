#include <stdio.h>
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pico/binary_info.h"

const float conv_factor = 3.3f / (1 << 12);

int main()
{
    stdio_init_all();
    uint16_t lectura;
    float lect_conv, temperatura;

    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4); // imput 4 - sensor temperatura

    while (true)
    {
        lectura = adc_read();
        lect_conv = lectura * conv_factor;
        temperatura = 27 - (lect_conv - 0.706) / 0.001721;

        // mostrar temperatura
        printf("%2.1f\n", temperatura);

        sleep_ms(2000);
    }
    return 0;
}