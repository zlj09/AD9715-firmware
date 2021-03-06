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
#include "xuartlite.h"

void print(char *str);

int main()
{
	u32 reg_data, i;

    init_platform();

    print("Hello World\r\n");
/*
    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET, 0x00000001);

    //PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x0000049f);
    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00000480);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00008400);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    reg_data = PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET) & 0xff;
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    xil_printf("%d\r\n", reg_data);

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00001200);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00000e3c);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00001210);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    while(1)
    {
    	PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00008f00);
    	while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    	reg_data = PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET) & 0xff;
    	while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    	if (reg_data & 0xC0 == 0xC0)
    		break;

    	for (i = 0; i < 10; i++) ;
    }

    print("Calibration done!\r\n");

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00000bff);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00000c9f);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00008c00);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    reg_data = PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET) & 0xff;
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    xil_printf("%d\n\r", reg_data);

    while(1)
    {
    	//PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG1_OFFSET, 0x00000ff);
    	//PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG2_OFFSET, 0x00000ff);
    	for (i = 0; i < 10; i++) ;

    	//PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG1_OFFSET, 0x00002ff);
    	//PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG2_OFFSET, 0x00002ff);
    	for (i = 0; i < 10; i++) ;
    }

*/
   /* PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET, 0x00000001);

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00000780);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00008700);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    reg_data = PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET) & 0xff;
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    xil_printf("Reg 0x07: %x\r\n", reg_data);

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x000009ff);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00000a9f);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00008900);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    reg_data = PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET) & 0xff;
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    xil_printf("Reg 0x09: %x\r\n", reg_data);

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00008a00);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    reg_data = PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET) & 0xff;
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    xil_printf("Reg 0x0a: %x\r\n", reg_data);

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00001f03);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00009f00);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    reg_data = PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET) & 0xff;
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    xil_printf("DAC 1 - Reg 0x1f: %x\r\n", reg_data);*/

    /*PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET, 0x00000001);

    //PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00000203);
    //while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00009f00);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    reg_data = PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET) & 0xff;
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    xil_printf("DAC 0 - Reg 0x1f: %x\r\n", reg_data);

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET, 0x00000001);

    //PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00000203);
    //while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00009f00);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    reg_data = PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET) & 0xff;
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    xil_printf("DAC 1 - Reg 0x1f: %x\r\n", reg_data);*/
   /* while(1)
    {
    	PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG1_OFFSET, 0x0000155);
    	PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG2_OFFSET, 0x0000155);
    	for (i = 0; i < 10000; i++) ;

    	PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG1_OFFSET, 0x00002aa);
    	PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG2_OFFSET, 0x00002aa);
    	for (i = 0; i < 10000; i++) ;
    }*/

    u8 msg, bit_pos = 9, wave_form = 0;
    u8 reg_addr, reg_val;
    u32 smp_rate = 500, delay_time = 8400, dac_data = 0x00000000;

    XUartLite xuart_1;

    XUartLite_Initialize(&xuart_1, XPAR_UARTLITE_1_DEVICE_ID);

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET, 0x00000001);
    PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET, 0x00000001);

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00000580);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00000880);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00000580);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, 0x00000880);
    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;


    while(1)
    {
    	dac_data = 1 << bit_pos;
    	if (smp_rate == 500)
    		delay_time = 8400;
    	else
    		if (smp_rate == 1000)
    			delay_time = 4200;
    		else
    			if (smp_rate == 2000)
    				delay_time = 2100;
    			else
    				if (smp_rate == 4000)
    					delay_time = 1050;
    				else
    					if (smp_rate == 25000000)
    						delay_time = 10;
    	xil_printf("Change Bit: %d, DAC DATA: 0x%x, Sampling Rate: %d, Delay Time: %d\r\n", bit_pos, dac_data, smp_rate, delay_time);

    	dac_data = 0;
    	while(1)
    	{
    		/*PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG1_OFFSET, 0x0000000);
    		PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG2_OFFSET, 0x0000000);
    		PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG1_OFFSET, 0x0000000);
    		PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG2_OFFSET, 0x0000000);
    		for (i = 0; i < delay_time; i++) ;*/

    		if (++dac_data == (1 << 10))
    			dac_data = 0;

    		PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG1_OFFSET, dac_data);
    		PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG2_OFFSET, dac_data);
    		PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG1_OFFSET, dac_data);
    		PLB_DAC_mWriteReg(XPAR_PLB_DAC_1_BASEADDR, PLB_DAC_SLV_REG2_OFFSET, dac_data);
    		//for (i = 0; i < delay_time; i++) ;

    		msg = '\0';
    		XUartLite_Recv(&xuart_1, &msg, 1);
    		if (msg != '\0')
    			break;
    	}



    	switch(msg)
    	{
    	case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
    		bit_pos = msg - '0';
    		break;
    	case 'Z':
    		smp_rate = 25000000;
    		break;
    	case 'X':
    		smp_rate = 4000;
    		break;
    	case 'E':
    		smp_rate = 2000;
    		break;
    	case 'H':
    		smp_rate = 1000;
    		break;
    	case 'L':
    		smp_rate = 500;
    		break;
    	case 'S':
    		for (i = 0; i < 1000000; i++) ;
    		reg_addr = 0;
    		XUartLite_Recv(&xuart_1, &reg_addr, 1);
    		reg_val = 0;
    		XUartLite_Recv(&xuart_1, &reg_val, 1);
    		reg_data = (reg_addr << 8) + reg_val;
    		xil_printf("SPI DATA: %x\r\n", reg_data);
    		PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, reg_data);
    		while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

    		reg_data = 0x8000 | (reg_addr << 8);
    		xil_printf("SPI DATA: %x\r\n", reg_data);
    		PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET, reg_data);
    		while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;
  		    reg_val = PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG3_OFFSET) & 0xff;
   		    while(PLB_DAC_mReadReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET) & 0x2) ;

   		    xil_printf("DAC 0 - Reg 0x%x: %x\r\n", reg_addr, reg_val);
    		break;
    	default:
    		break;
    	}
    }


    return 0;
}
