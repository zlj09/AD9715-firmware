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

#include "plb_dac.h"
#include "xparameters.h"

void print(char *str);
void initDAC(u32 format);
void testDAC();
void printDACTestInfo(u32 wave, u32 channel, u32 delay_time);
void genSowWave(u32 channel, u32 delay_time);
void genSqrWave(u32 channel, u32 delay_time);
void genSinWave(u32 channel, u32 delay_time);
void delayDAC(u32 delay_time);

int main()
{
    init_platform();

    //print("Hello World\n\r");

    initDAC(0);

    testDAC();

    return 0;
}

void initDAC(u32 format)
{
	u32 ctrl_sgn = 0x00000001 | ((format & 0x1) << 1);
	PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET, ctrl_sgn);
}

void testDAC()
{
	//print("**********************DAC test********************\n\r");
	//void (*genWave[])(u32, u32) = {genSowWave, genSqrWave, genSinWave};

	u32 wave = 0, channel = 3, delay_time = 10;

	while(1)
	{
		//printDACTestInfo(wave, channel, delay_time);
		//(*genWave[wave])(channel, delay_time);
		genSowWave(channel, delay_time);
	}
}

void printDACTestInfo(u32 wave, u32 channel, u32 delay_time)
{
	print("DAC Test Information:\n\r");
	switch(wave)
	{
	case 0:
		print("Sawtooth Wave, ");
		break;
	case 1:
		print("Square Wave, ");
		break;
	case 2:
		print("Sinusoidal Wave, ");
		break;
	default:
		print("Wave Form Error, ");
	}
	switch(channel)
	{
	case 0:
		print("Both Q and I Channels Closed");
		break;
	case 1:
		print("I Channel Opened, Q Channel Closed, ");
		break;
	case 2:
		print("Q Channel Opened, I Channel Closed, ");
		break;
	case 3:
		print("Both Q and I Channels Opened, ");
		break;
	default:
		print("Channel Error, ");
	}

	xil_printf("Delay Time %d\r\n", delay_time);
}

void genSowWave(u32 channel, u32 delay_time)
{
	u32 i = 0, dac_data, j, k;

	//PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET, 0x00000011); //010001
	//PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET, 0x00000003); //000011

	PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET, 0x00000001);

    for (k = 0; k < 10; k++)
	{
		dac_data = 0x0ff;
		PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG1_OFFSET, dac_data);
		for (j = 0; j < 10; j++);

		dac_data = 0x2ff;
		PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG1_OFFSET, dac_data);
		for (j = 0; j < 10; j++) ;

		dac_data = 0x0ff;
		PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG1_OFFSET, dac_data);
		for (j = 0; j < 10; j++);

		dac_data = 0x2ff;
		PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG1_OFFSET, dac_data);
		for (j = 0; j < 10; j++) ;
	}
}

void genSqrWave(u32 channel, u32 delay_time)
{
	while(1) ;
}
void genSinWave(u32 channel, u32 delay_time)
{
	while(1) ;
}

void delayDAC(u32 delay_time)
{
	u32 i;
	for (i = delay_time; i > 0; --i) ;
}
