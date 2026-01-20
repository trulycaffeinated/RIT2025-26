
module unsaved (
	clk_clk,
	hex1_export,
	hex2_export,
	hex3_export,
	hex4_export,
	hex5_export,
	key_export,
	switches_export,
	export_out_wave);	

	input		clk_clk;
	output	[6:0]	hex1_export;
	output	[6:0]	hex2_export;
	output	[6:0]	hex3_export;
	output	[6:0]	hex4_export;
	output	[6:0]	hex5_export;
	input	[3:0]	key_export;
	input	[7:0]	switches_export;
	output		export_out_wave;
endmodule
