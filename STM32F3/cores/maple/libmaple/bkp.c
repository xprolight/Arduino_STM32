/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs, LLC.
 * Copyright (c) 2013 OpenMusicKontrollers.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file libmaple/bkp.c
 * @author F3-port by Hanspeter Portner <dev@open-music-kontrollers.ch>
 * @brief Backup register support (STM32F1 & STM32F3 only).
 */

#include <libmaple/pwr.h>
#include <libmaple/bkp.h>
#include <libmaple/bitband.h>

bkp_dev bkp = {
    .regs = BKP_BASE,
};
/** Backup device. */
const bkp_dev *BKP = &bkp;

void bkp_enable_writes(void) {
    *bb_perip(&PWR_BASE->CR, PWR_CR_DBP_BIT) = 1;
}

void bkp_disable_writes(void) {
    *bb_perip(&PWR_BASE->CR, PWR_CR_DBP_BIT) = 0;
}

uint16 bkp_read(uint8 reg) {
    __IO uint32* dr = bkp_data_register(reg);
    if (!dr) {
        ASSERT(0);                  /* nonexistent register */
        return 0;
    }
    return (uint16)*dr;
}

void bkp_write(uint8 reg, uint16 val) {
    __IO uint32* dr = bkp_data_register(reg);
    if (!dr) {
        ASSERT(0);                  /* nonexistent register */
        return;
    }
    *dr = (uint32)val;
}

