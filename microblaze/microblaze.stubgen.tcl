cd F:/Programs/Verilog/FPGA_Group/test_br0101/microblaze/
if { [ catch { xload xmp microblaze.xmp } result ] } {
  exit 10
}
xset hdl verilog
run stubgen
exit 0
