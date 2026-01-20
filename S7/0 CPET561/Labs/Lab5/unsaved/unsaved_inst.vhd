	component unsaved is
		port (
			clk_clk         : in  std_logic                    := 'X';             -- clk
			hex1_export     : out std_logic_vector(6 downto 0);                    -- export
			hex2_export     : out std_logic_vector(6 downto 0);                    -- export
			hex3_export     : out std_logic_vector(6 downto 0);                    -- export
			hex4_export     : out std_logic_vector(6 downto 0);                    -- export
			hex5_export     : out std_logic_vector(6 downto 0);                    -- export
			key_export      : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
			switches_export : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			export_out_wave : out std_logic                                        -- out_wave
		);
	end component unsaved;

	u0 : component unsaved
		port map (
			clk_clk         => CONNECTED_TO_clk_clk,         --      clk.clk
			hex1_export     => CONNECTED_TO_hex1_export,     --     hex1.export
			hex2_export     => CONNECTED_TO_hex2_export,     --     hex2.export
			hex3_export     => CONNECTED_TO_hex3_export,     --     hex3.export
			hex4_export     => CONNECTED_TO_hex4_export,     --     hex4.export
			hex5_export     => CONNECTED_TO_hex5_export,     --     hex5.export
			key_export      => CONNECTED_TO_key_export,      --      key.export
			switches_export => CONNECTED_TO_switches_export, -- switches.export
			export_out_wave => CONNECTED_TO_export_out_wave  --   export.out_wave
		);

