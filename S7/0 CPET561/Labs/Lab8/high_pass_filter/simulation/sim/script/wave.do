onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /high_pass_filter_tb/clk
add wave -noupdate /high_pass_filter_tb/reset_n
add wave -noupdate /high_pass_filter_tb/filter_en
add wave -noupdate -radix decimal /high_pass_filter_tb/data_in
add wave -noupdate -radix decimal -childformat {{/high_pass_filter_tb/data_out(15) -radix decimal} {/high_pass_filter_tb/data_out(14) -radix decimal} {/high_pass_filter_tb/data_out(13) -radix decimal} {/high_pass_filter_tb/data_out(12) -radix decimal} {/high_pass_filter_tb/data_out(11) -radix decimal} {/high_pass_filter_tb/data_out(10) -radix decimal} {/high_pass_filter_tb/data_out(9) -radix decimal} {/high_pass_filter_tb/data_out(8) -radix decimal} {/high_pass_filter_tb/data_out(7) -radix decimal} {/high_pass_filter_tb/data_out(6) -radix decimal} {/high_pass_filter_tb/data_out(5) -radix decimal} {/high_pass_filter_tb/data_out(4) -radix decimal} {/high_pass_filter_tb/data_out(3) -radix decimal} {/high_pass_filter_tb/data_out(2) -radix decimal} {/high_pass_filter_tb/data_out(1) -radix decimal} {/high_pass_filter_tb/data_out(0) -radix decimal}} -expand -subitemconfig {/high_pass_filter_tb/data_out(15) {-radix decimal} /high_pass_filter_tb/data_out(14) {-radix decimal} /high_pass_filter_tb/data_out(13) {-radix decimal} /high_pass_filter_tb/data_out(12) {-radix decimal} /high_pass_filter_tb/data_out(11) {-radix decimal} /high_pass_filter_tb/data_out(10) {-radix decimal} /high_pass_filter_tb/data_out(9) {-radix decimal} /high_pass_filter_tb/data_out(8) {-radix decimal} /high_pass_filter_tb/data_out(7) {-radix decimal} /high_pass_filter_tb/data_out(6) {-radix decimal} /high_pass_filter_tb/data_out(5) {-radix decimal} /high_pass_filter_tb/data_out(4) {-radix decimal} /high_pass_filter_tb/data_out(3) {-radix decimal} /high_pass_filter_tb/data_out(2) {-radix decimal} /high_pass_filter_tb/data_out(1) {-radix decimal} /high_pass_filter_tb/data_out(0) {-radix decimal}} /high_pass_filter_tb/data_out
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {15620000 ps} 0}
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
WaveRestoreZoom {15543155 ps} {15696845 ps}
