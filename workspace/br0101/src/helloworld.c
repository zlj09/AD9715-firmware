/*
 * Copyright (c) 2009-2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"

#include "xparameters.h"
#include "plb_dac.h"

void print(char *str);

int main()
{
	u32 reg_data;

    init_platform();

    print("Hello World\n\r");

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET, 0x00000001);

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00000480);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00008400);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    reg_data = PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET) & 0xff;

    xil_printf("%d\n\r", reg_data);

    return 0;
}
