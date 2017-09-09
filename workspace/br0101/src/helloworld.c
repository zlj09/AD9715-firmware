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
#include "xintc.h"
#include "xil_exception.h"


void print(char *str);
void uart1_sendhandler(void *CallBackRef, unsigned int EventData);
void uart1_recvhandler(void *CallBackRef, unsigned int EventData);

int main()
{
	u32 reg_data, i;

    init_platform();

    print("Hello World\r\n");

    u8 msg, bit_pos = 9, wave_form = 0;
    u8 reg_addr, reg_val;
    u32 smp_rate = 500, delay_time = 8400, dac_data = 0x00000000;

    XUartLite xuart_1;
    XIntc xintc_0;

    XUartLite_Initialize(&xuart_1, XPAR_UARTLITE_1_DEVICE_ID);

    XIntc_Initialize(&xintc_0, XPAR_XPS_INTC_0_DEVICE_ID);
    XIntc_Connect(&xintc_0,  XPAR_INTC_0_UARTLITE_1_VEC_ID,
    			   (XInterruptHandler)XUartLite_InterruptHandler,
    			   &xuart_1);
    XIntc_Start(&xintc_0, XIN_REAL_MODE);
    XIntc_Enable(&xintc_0, XPAR_INTC_0_UARTLITE_1_VEC_ID);
    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
    			 (Xil_ExceptionHandler)XIntc_InterruptHandler,
    			 &xintc_0);
    Xil_ExceptionEnable();

    XUartLite_SetSendHandler(&xuart_1, uart1_sendhandler, &xuart_1);
    XUartLite_SetRecvHandler(&xuart_1, uart1_recvhandler, &xuart_1);
    XUartLite_EnableInterrupt(&xuart_1);

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

    PLB_DAC_mWriteReg(XPAR_PLB_DAC_0_BASEADDR, PLB_DAC_SLV_REG0_OFFSET, 0x00000021);


    while(1)
    {
    }


    return 0;
}

void uart1_sendhandler(void *CallBackRef, unsigned int EventData)
{
	u8 msg;
	XUartLite_Recv(CallBackRef, &msg, 1);
	xil_printf("%c", msg);
	//xil_printf("Change Bit: %d, DAC DATA: 0x%x, Sampling Rate: %d, Delay Time: %d\r\n", bit_pos, dac_data, smp_rate, delay_time);

	/*switch(msg)
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
	}*/
}

void uart1_recvhandler(void *CallBackRef, unsigned int EventData)
{

}
