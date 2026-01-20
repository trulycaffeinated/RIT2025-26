
module nios_system (
	clk_clk,
	conduit_out_wave,
	hex0_export,
	hex1_export,
	hex2_export,
	hex4_export,
	hex5_export,
	key_export,
	reset_n_reset_n,
	switches_export);	

	input		clk_clk;
	output		conduit_out_wave;
	output	[6:0]	hex0_export;
	output	[6:0]	hex1_export;
	output	[6:0]	hex2_export;
	output	[6:0]	hex4_export;
	output	[6:0]	hex5_export;
	input	[3:0]	key_export;
	input		reset_n_reset_n;
	input	[7:0]	switches_export;
endmodule
