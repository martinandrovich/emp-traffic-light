#include <stdint.h>
#include <stdbool.h>

#include "spi.h"
#include "chksum.h"

void chksum_test(void)
{

    // construct test frame
    SPI_FRAME	frm1  = {ENC1, 170, 0};
    bool		frm1_is_valid;

    // generate & validate checksums
    frm1.chksum		= chksum.generate(&frm1);
    frm1_is_valid	= chksum.validate(&frm1);

}
