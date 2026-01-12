------------------------------------------------------
-- Jeff Taylor
-- 10.22.2025
-- CPET 561 - ESD - Lab 6
------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity lab6_p1 is
	port(
		-- inputs --
		CLOCK_50 : in std_logic;
		KEY		: in std_logic_vector(3 downto 0);
		-- outputs -- 
		LEDR		: out std_logic_vector(7 downto 0)
	);
end entity lab6_p1;

architecture beh of lab6_p1 is

	-- nios component --
		component nios_system is
		port (
			clk_clk       : in  std_logic                    := 'X'; -- clk
			reset_reset_n : in  std_logic                    := 'X'; -- reset_n
			leds_export   : out std_logic_vector(7 downto 0);        -- export
			key_export    : in  std_logic                    := 'X'  -- export
		);
	end component nios_system;

	-- signals --
	signal key0_d1 	: std_logic;
	signal key0_d2 	: std_logic;
	signal key0_d3 	: std_logic;
	signal reset_n	: std_logic;
	
begin

	reset_sync:process(CLOCK_50)
	begin
		if(rising_edge(CLOCK_50)) then
			key0_d1 <= KEY(0);
			key0_d2 <= key0_d1;
			key0_d3 <= key0_d2;
		end if;
	end process;
	
	-- reset
	reset_n <= key0_d3;

	u0 : component nios_system
		port map (
			clk_clk       => CLOCK_50,       --   clk.clk
			reset_reset_n => reset_n, -- reset.reset_n
			leds_export   => ledr,   --  leds.export
			key_export    => key(1)     --   key.export
		);

end beh;