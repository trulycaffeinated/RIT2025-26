vlib work
vcom -93 -work work ../Lab4.vhd
vcom -93 -work work ../Lab4_tb.vhd
vsim -voptargs=+acc Lab4_tb
do wave.do
run 60000 ns