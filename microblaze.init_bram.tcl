cd F:/Programs/Verilog/FPGA_Group/test_br0101/microblaze
if { [ catch { xload xmp microblaze.xmp } result ] } {
  exit 10
}

if { [catch {run init_bram} result] } {
  exit -1
}

exit 0
