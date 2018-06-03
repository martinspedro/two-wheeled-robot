/** 
 * \file   IO.c
 * \brief  Input/Output Mapping and configurations C File
 * 
 * \author Pedro Martins
 * \date   Created on June 3, 2018, 11:59 AM
 */
#include "IO.h"

#define CLEAR_LEDS {LATGCLR  = 0x7000;}


void init_IO(void)
{
    TRISGCLR = 0x7000;      // Define LEDS as output 
    CLEAR_LEDS;
}
