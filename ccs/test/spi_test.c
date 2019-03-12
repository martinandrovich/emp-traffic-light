#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "spi.h"

void spi_test(void)
{
    // init SPI instance @ 8MHz (
    // bps = SYSCLK / (CPSDVSR * (1 + SCR))
    SPI* spi_test = spi.new(2);

    // send value '110' to PWM1
    spi.send(spi_test, PWM1, 110);

    // send value '110' to PWM1 and validate
    if(!spi.send(spi_test, PWM1, 110))
    {
        puts("Error!");
    }

    // request data from ENC1
    uint16_t enc1_dat;
    if(spi.request(spi_test, ENC1, &enc1_dat))
    {
        return true;
    }
}
