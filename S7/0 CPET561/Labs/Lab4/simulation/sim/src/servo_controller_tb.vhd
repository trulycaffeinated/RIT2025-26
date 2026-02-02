library ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;
USE ieee.numeric_std.ALL;

entity servo_controller_tb is
end entity servo_controller_tb;

architecture beh of servo_controller_tb is

	component servo_controller is
		port(
			-- inputs -----------------------------
			CLOCK_50 			: in std_logic;
			reset_n 		: in std_logic;
			we 				: in std_logic;
			writedata 		: in unsigned(31 downto 0);
			address 		: in std_logic;
			-- outputs -----------------------------
			irq_out 		: out std_logic;
			out_wave_export : out std_logic
		);
	end component;


	signal CLOCK_50 : std_logic := '0';
	signal reset_n : std_logic := '0';
	signal we : std_logic := '0';
	signal writedata : unsigned(31 downto 0) := (OTHERS => '0');
	signal address : std_logic := '0';
	signal irq_out : std_logic := '0';
	signal out_wave_export : std_logic := '0';

	constant TCK : time := 20 ns; -- 50 MHz

begin

-- clock process
clock : process
	begin
		CLOCK_50 <= not CLOCK_50;
		wait for TCK;
	end process;

-- reset process
async_reset : process
	begin
		wait for 2 * TCK;
		reset_n <= '1';
		wait;
end process;

--servo logic
servo_process : process
	begin
		-- sweep to max
		wait until irq_out = '1';

		-- clear irq with write
		address <= '0';
		writedata <= x"0000C350";
		we <= '1';
		wait for 100 ns;
		we <= '0';
		
		-- sweep downto
		wait until irq_out = '1';
		
		--clear
		address <= '1';
		writedata <= x"000186A0";
		we <= '1';
		wait for 100 ns;
		we <= '0';

end process;

uut : servo_controller
	port map
		(
			CLOCK_50 => CLOCK_50,
			reset_n => reset_n,
			we => we,
			writedata => writedata,
			address => address,
			irq_out => irq_out,
			out_wave_export => out_wave_export
		);

end beh;