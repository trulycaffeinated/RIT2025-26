
module nios_system (
	switches_export,
	pushbuttons_export,
	hex0_export,
	clk_clk,
	reset_reset_n);	

	input	[7:0]	switches_export;
	input	[3:0]	pushbuttons_export;
	output	[6:0]	hex0_export;
	input		clk_clk;
	input		reset_reset_n;
endmodule
