library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

ENTITY lab3 is
	port(
		CLOCK_50 : in std_logic;
		KEY		: in std_logic_vector(3 downto 0);
		SW 		: in std_logic_vector(7 downto 0);
		LEDS 		: out std_logic_vector(7 downto 0);
		hex0		: out std_logic_vector(6 downto 0)
	);
end entity lab3;

architecture arch of lab3 is

	signal reset_n : std_logic;
	signal key0_d1 : std_logic;
	signal key0_d2 : std_logic;
	signal key0_d3 : std_logic;

	component nios_system is
		port (
			clk_clk         : in  std_logic                    := 'X';             -- clk
			reset_reset_n   : in  std_logic                    := 'X';             -- reset_n
			switches_export : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			keys_export     : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
			leds_export     : out std_logic_vector(7 downto 0);                    -- export
			hex0_export     : out std_logic_vector(6 downto 0)                     -- export
		);
	end component nios_system;

begin

	syncUserIn_Proc : process(CLOCK_50) begin
		if(rising_edge(CLOCK_50)) then
			key0_d1 <= KEY(0);
			key0_d2 <= key0_d1;
			key0_d3 <= key0_d2;
		end if;
	end process syncUserIn_Proc;
	reset_n <= key0_d3;

	u0 : component nios_system
		port map (
			clk_clk         => CLOCK_50,         --      clk.clk
			reset_reset_n   => reset_n,   --    reset.reset_n
			switches_export => SW(7 downto 0), -- switches.export
			keys_export     => KEY,     --     keys.export
			leds_export     => LEDS,     --     leds.export
			hex0_export     => HEX0      --     hex0.export
		);

end architecture arch;

