#ifndef _TOFLIB_H_
#define _TOFLIB_H_
#include <stdint.h>
//
// Copyright (c) 2017 Larry Bank
// email: bitbank@pobox.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

//
// Read the model and revision of the tof sensor
//
int tofGetModel(uint8_t dev_add, int *model, int *revision);

//
// Read the current distance in mm
//
int tofReadDistance(uint8_t dev_add);

//
// Opens a file system handle to the I2C device
// sets the device continous capture mode
//
int initSensor(uint8_t dev_add,int bLongRangeMode);


void setAddress(uint8_t dev_add,uint8_t new_addr);

#endif // _TOFLIB_H
