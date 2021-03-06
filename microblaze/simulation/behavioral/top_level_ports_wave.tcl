#  Simulation Model Generator
#  Xilinx EDK 14.7 EDK_P.20131013
#  Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
#
#  File     top_level_ports_wave.tcl (Sun Nov 19 14:43:04 2017)
#
if { [info exists PathSeparator] } { set ps $PathSeparator } else { set ps "/" }
if { ![info exists tbpath] } { set tbpath "microblaze_tb${ps}dut" }

wave add $tbpath${ps}fpga_0_RS232_RX_pin -into $id 
wave add $tbpath${ps}fpga_0_RS232_TX_pin -into $id 
wave add $tbpath${ps}fpga_0_clk_1_sys_clk_pin -into $id 
wave add $tbpath${ps}fpga_0_rst_1_sys_rst_pin -into $id 
wave add $tbpath${ps}plb_dac_1_S_Data_pin -into $id 
wave add $tbpath${ps}plb_dac_1_S_DCLKIO_pin -into $id 
wave add $tbpath${ps}plb_dac_1_S_Clkout_pin -into $id 
wave add $tbpath${ps}plb_dac_1_S_PinMD_pin -into $id 
wave add $tbpath${ps}plb_dac_1_S_ClkMD_pin -into $id 
wave add $tbpath${ps}plb_dac_1_S_Format_pin -into $id 
wave add $tbpath${ps}plb_dac_1_S_PWRDN_pin -into $id 
wave add $tbpath${ps}plb_dac_1_S_OpEnI_pin -into $id 
wave add $tbpath${ps}plb_dac_1_S_OpEnQ_pin -into $id 
wave add $tbpath${ps}plb_dac_0_S_Data_pin -into $id 
wave add $tbpath${ps}plb_dac_0_S_DCLKIO_pin -into $id 
wave add $tbpath${ps}plb_dac_0_S_Clkout_pin -into $id 
wave add $tbpath${ps}plb_dac_0_S_PinMD_pin -into $id 
wave add $tbpath${ps}plb_dac_0_S_ClkMD_pin -into $id 
wave add $tbpath${ps}plb_dac_0_S_Format_pin -into $id 
wave add $tbpath${ps}plb_dac_0_S_PWRDN_pin -into $id 
wave add $tbpath${ps}plb_dac_0_S_OpEnQ_pin -into $id 
wave add $tbpath${ps}plb_dac_0_S_OpEnI_pin -into $id 

