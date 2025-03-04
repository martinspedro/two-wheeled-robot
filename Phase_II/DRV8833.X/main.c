/** 
 * \file   main.c
 * \brief  DRV8833 main test file
 * 
 * \author Pedro Martins
 * \date   Created on May 6, 2018, 2:40 PM
 */

#include "../DEVCFGx_config_bits.h"


#include <stdio.h>
#include <stdlib.h>

#include "DRV8833.h"

void main(void)
{
    configure_DRV8833_interface();
    enable_DRV8833();
    
    forward_fast_decay_left(30);
    forward_fast_decay_right(30);
    
   
    while(1);
}

