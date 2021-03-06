/* Copyright (c) 2020 Cameron Harper
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * */

#include "sx127x.h"
#include "ldl_system.h"
#include "ldl_radio.h"

using namespace LDL;

/* constructors *******************************************************/

SX127X::SX127X(
    enum ldl_radio_type type,
    SPI& spi,
    PinName nss,
    PinName reset,
    PinName dio0,
    PinName dio1,
    PinName dio2,
    PinName dio3,
    PinName dio4,
    PinName dio5,
    enum ldl_sx127x_pa pa,
    int16_t tx_gain,
    enum ldl_radio_xtal xtal,
    Callback<void(enum ldl_chip_mode)> chip_mode_cb
)
    :
    SPIRadio(
        spi,
        nss,
        NC
    ),
    reset(reset, PIN_INPUT, PullNone, 1),
    dio0(dio0),
    dio1(dio1),
    chip_mode_cb(chip_mode_cb)
{
    internal_if = LDL_SX1272_getInterface();

    struct ldl_sx127x_init_arg arg = {};

    arg.pa = pa;
    arg.xtal = xtal;
    arg.tx_gain = tx_gain;

    arg.chip = this;
    arg.chip_write = &SPIRadio::_chip_write;
    arg.chip_read = &SPIRadio::_chip_read;
    arg.chip_set_mode = &SX127X::_chip_set_mode;

    if(type == LDL_RADIO_SX1276){

        LDL_SX1276_init(&radio, &arg);
    }
    else{

        LDL_SX1272_init(&radio, &arg);
    }

    this->dio0.rise(callback(this, &SX127X::dio0_handler));
    this->dio1.rise(callback(this, &SX127X::dio1_handler));

    LDL_Radio_setEventCallback(&radio, (struct ldl_mac *)this, &Radio::_interrupt_handler);
}

/* static protected ***************************************************/

void
SX127X::_chip_set_mode(void *self, enum ldl_chip_mode mode)
{
    static_cast<SX127X *>(self)->chip_set_mode(mode);
}

void
SX127X::chip_set_mode(enum ldl_chip_mode mode)
{
    switch(mode){
    case LDL_CHIP_MODE_RESET:
        reset.output();
        break;
    case LDL_CHIP_MODE_SLEEP:
        reset.input();
        break;
    default:
        break;
    }

    if(chip_mode_cb){

        chip_mode_cb(mode);
    }
}

/* protected **********************************************************/

void
SX127X::dio0_handler()
{
    LDL_Radio_handleInterrupt(&radio, 0);
}

void
SX127X::dio1_handler()
{
    LDL_Radio_handleInterrupt(&radio, 1);
}
