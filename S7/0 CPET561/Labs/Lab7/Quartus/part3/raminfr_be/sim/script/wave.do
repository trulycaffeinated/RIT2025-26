onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /raminfr_be_tb/uut/clk
add wave -noupdate /raminfr_be_tb/uut/reset_n
add wave -noupdate -radix binary /raminfr_be_tb/uut/write_byte_enable_n
add wave -noupdate /raminfr_be_tb/uut/address
add wave -noupdate /raminfr_be_tb/uut/writedata
add wave -noupdate /raminfr_be_tb/uut/readdata
add wave -noupdate /raminfr_be_tb/uut/RAM_0
add wave -noupdate /raminfr_be_tb/uut/RAM_1
add wave -noupdate /raminfr_be_tb/uut/RAM_2
add wave -noupdate /raminfr_be_tb/uut/RAM_3
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {163760 ns} 0}
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
WaveRestoreZoom {163112 ns} {164408 ns}
