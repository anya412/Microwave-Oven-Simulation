/***********************************************************************
 *  File name   : clcd.c
 *  Description : CLCD (Character LCD) driver for PIC16F877A microcontroller.
 *                Handles initialization, command, and data transmission
 *                for 4-bit communication mode.
 *
 *                Functions:
 *                - clcd_write()
 *                - init_display_controller()
 *                - init_clcd()
 *                - clcd_putch()
 *                - clcd_print()
 ***********************************************************************/

#include <xc.h>
#include "clcd.h"

/*----------------------------------------------------------------------
 *  Function : clcd_write
 *  Description :
 *      Sends a command or data byte to the CLCD.
 *      Operates in 4-bit mode (nibbles transmitted sequentially).
 *--------------------------------------------------------------------*/
void clcd_write(unsigned char byte, unsigned char mode)
{
    CLCD_RS = mode;

    /* Send higher nibble */
    CLCD_DATA_PORT = byte & 0xF0;
    CLCD_EN = HI;
    __delay_us(100);
    CLCD_EN = LOW;

    /* Send lower nibble */
    CLCD_DATA_PORT = (byte & 0x0F) << 4;
    CLCD_EN = HI;
    __delay_us(100);
    CLCD_EN = LOW;

    __delay_us(4100);  /* Command execution delay */
}

/*----------------------------------------------------------------------
 *  Function : init_display_controller
 *  Description :
 *      Performs the startup and initialization sequence for the CLCD
 *      controller, configuring it for 4-bit, 2-line operation.
 *--------------------------------------------------------------------*/
static void init_display_controller(void)
{
    __delay_ms(30);  /* Startup time for CLCD controller */

    /* Initialization sequence */
    clcd_write(EIGHT_BIT_MODE, INST_MODE);
    __delay_us(4100);
    clcd_write(EIGHT_BIT_MODE, INST_MODE);
    __delay_us(100);
    clcd_write(EIGHT_BIT_MODE, INST_MODE);
    __delay_us(1);
    clcd_write(FOUR_BIT_MODE, INST_MODE);
    __delay_us(100);
    clcd_write(TWO_LINES_5x8_4_BIT_MODE, INST_MODE);
    __delay_us(100);
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    __delay_us(500);
    clcd_write(DISP_ON_AND_CURSOR_OFF, INST_MODE);
    __delay_us(100);
}

/*----------------------------------------------------------------------
 *  Function : init_clcd
 *  Description :
 *      Configures the CLCD data and control pins as output and
 *      initializes the display controller.
 *--------------------------------------------------------------------*/
void init_clcd(void)
{
    /* Configure CLCD data port as output */
    CLCD_DATA_PORT_DDR &= 0x0F;

    /* Configure RS and EN lines as output */
    CLCD_RS_DDR = 0;
    CLCD_EN_DDR = 0;

    init_display_controller();
}

/*----------------------------------------------------------------------
 *  Function : clcd_putch
 *  Description :
 *      Displays a single character at the given LCD address.
 *--------------------------------------------------------------------*/
void clcd_putch(const char data, unsigned char addr)
{
    clcd_write(addr, INST_MODE);
    clcd_write(data, DATA_MODE);
}

/*----------------------------------------------------------------------
 *  Function : clcd_print
 *  Description :
 *      Prints a string on the LCD starting from the specified address.
 *--------------------------------------------------------------------*/
void clcd_print(const char *str, unsigned char addr)
{
    clcd_write(addr, INST_MODE);

    while (*str != '\0')
    {
        clcd_write(*str++, DATA_MODE);
    }
}

