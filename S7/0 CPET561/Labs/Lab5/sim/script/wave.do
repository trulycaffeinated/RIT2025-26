onerror {resume}
radix define States {
 "00" "SWEEP_LEFT" -color "yellow",
 "01" "SWEEP_RIGHT" -color "yellow",
 "10" "INT_LEFT" -color "yellow",
 "11" "INT_RIGHT" -color "yellow",
 -default default
}
onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /Lab4_tb/CLOCK_50_tb
add wave -noupdate /Lab4_tb/reset_n_tb
add wave -noupdate /Lab4_tb/write_enable_tb
add wave -noupdate /Lab4_tb/write_address_tb
add wave -noupdate -radix Decimal /Lab4_tb/write_data_tb
add wave -noupdate /Lab4_tb/pwm_out_tb
add wave -noupdate /Lab4_tb/irq_signal_tb
add wave -noupdate -radix unsigned /Lab4_tb/uut/period_counter
add wave -noupdate -radix Decimal /Lab4_tb/uut/angle_count
add wave -noupdate /Lab4_tb/uut/state_reg
add wave -noupdate /Lab4_tb/uut/state_next
add wave -noupdate -radix Decimal /Lab4_tb/uut/min_angle_reg
add wave -noupdate -radix Decimal /Lab4_tb/uut/max_angle_reg

radix update 
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {417112 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 177
configure wave -valuecolwidth 40
configure wave -justifyvalue left
configure wave -signalnamewidth 1
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {400250 ps} {505250 ps}
