-- Jeff Taylor
-- CPET 561

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Lab5_top is
    port (
	 -- inputs --
      CLOCK_50       : in  std_logic;
      KEY       	   : in std_logic_vector(3 downto 0);
		SW			   	: in std_logic_vector(7 downto 0);
		
	-- outputs
      GPIO_0         : out std_logic_vector(6 downto 0);
		HEX0		   : out std_logic_vector(6 downto 0);
		HEX1		   : out std_logic_vector(6 downto 0);
		HEX2		   : out std_logic_vector(6 downto 0);
		HEX4		   : out std_logic_vector(6 downto 0);
		HEX5		   : out std_logic_vector(6 downto 0)
    );
end entity Lab5_top;

architecture beh of Lab5_top is

signal key0_d1 : std_logic;
signal key0_d2 : std_logic;
signal key0_d3 : std_logic;
signal reset_n		  :  std_logic;

	component nios_system is
		port (
			clk_clk          : in  std_logic                    := 'X';             -- clk
			conduit_out_wave : out std_logic;                                       -- out_wave
			hex0_export      : out std_logic_vector(6 downto 0);                    -- export
			hex1_export      : out std_logic_vector(6 downto 0);                    -- export
			hex2_export      : out std_logic_vector(6 downto 0);                    -- export
			hex4_export      : out std_logic_vector(6 downto 0);                    -- export
			hex5_export      : out std_logic_vector(6 downto 0);                    -- export
			key_export       : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
			reset_n_reset_n  : in  std_logic                    := 'X';             -- reset_n
			switches_export  : in  std_logic_vector(7 downto 0) := (others => 'X')  -- export
		);
	end component nios_system;

begin

	syncResetProc : process(CLOCK_50)
	begin
	if(rising_edge(CLOCK_50))then
		key0_d1 <= key(0);
		key0_d2 <= key0_d2;
		key0_d3 <= key0_d3;
	end if;
	end process;

	reset_n <= key0_d3;
		
	u0 : component nios_system
		port map (
			clk_clk          => CLOCK_50,          --      clk.clk
			key_export       => KEY,       --      key.export
			conduit_out_wave => GPIO_0(0), 				--  conduit.out_wave
			hex0_export      => HEX0,    	  	  --     hex0.export
			hex1_export      => HEX1,    			   --     hex1.export
			hex2_export      => HEX2,      --     hex2.export
			hex4_export      => HEX4,      --     hex4.export
			hex5_export      => HEX5,      --     hex5.export
			reset_n_reset_n  => reset_n,  --  reset_n.reset_n
			switches_export  => SW   		-- switches.export
		);
		
end beh;