vlib work
vcom -93 -work work ../../src/low_pass_filter.vhd
vcom -93 -work work ../src/low_pass_filter_tb.vhd
vsim -voptargs=+acc low_pass_filter_tb
do wave.do
run 18 us