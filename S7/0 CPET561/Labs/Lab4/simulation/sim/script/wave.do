onerror {resume}
radix define States {
    "11'b0001" "SWEEP_RIGHT" -color "orange",
    "11'b0010" "INT_RIGHT" -color "blue",
    "11'b0100" "SWEEP_LEFT" -color "yellow",
    "11'b1000" "INT_LEFT" -color "pink",
    -default hexadecimal
    -defaultcolor white
}
quietly WaveActivateNextPane {} 0
add wave -noupdate /servo_controller_tb/clk
add wave -noupdate /servo_controller_tb/reset_n
add wave -noupdate /servo_controller_tb/we
add wave -noupdate -radix hexadecimal /servo_controller_tb/writedata
add wave -noupdate /servo_controller_tb/address
add wave -noupdate /servo_controller_tb/irq_out
add wave -noupdate /servo_controller_tb/out_wave_export
add wave -noupdate -radix States /servo_controller_tb/uut/current_state
add wave -noupdate -radix States /servo_controller_tb/uut/next_state
add wave -noupdate -radix decimal /servo_controller_tb/uut/angle_count
add wave -noupdate -radix decimal /servo_controller_tb/uut/period_counter
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {88 ns} 0}
quietly wave cursor active 1
configure wave -namecolwidth 150
configure wave -valuecolwidth 100
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
WaveRestoreZoom {18139 ns} {20098 ns}
