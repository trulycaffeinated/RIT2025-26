-----------------------------------------------------------------------
--- Note to future jeff : I think you're overthinking this
--- raminfr_be_tb
--- lab 7 testbench
-----------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;
use ieee.numeric_std.all;
use std.textio.all;

ENTITY raminfr_be_tb IS
END ENTITY raminfr_be_tb;

ARCHITECTURE beh OF raminfr_be_tb IS

COMPONENT raminfr_be IS
	port(
	clk : IN std_logic;
	reset_n : IN std_logic;
	write_byte_enable_n : IN std_logic_vector(3 downto 0);
	address : IN std_logic_vector(11 DOWNTO 0);
	writedata : IN std_logic_vector(31 DOWNTO 0);
	--
	readdata : OUT std_logic_vector(31 DOWNTO 0)
	);
END COMPONENT;

signal clk : std_logic := '0';
signal reset_n : std_logic := '0';
signal write_byte_enable_n : std_logic_vector(3 downto 0) := (OTHERS => '1');
signal address : std_logic_vector(11 downto 0) := (OTHERS => '0');
signal writedata : std_logic_vector(31 downto 0) := (OTHERS => '0');
signal readdata : std_logic_vector(31 downto 0);
signal data_buffer : std_logic_vector(31 downto 0);

CONSTANT TCK : time := 20 ns; -- 50 MHz clock

BEGIN

-- clock process
clock : process
	begin
		clk <= not clk;
		wait for TCK;
	end process;

-- reset process
async_reset : process
	begin
		wait for 2 * TCK;
		reset_n <= '1';
		wait;
end process;

ram_tb : PROCESS
	BEGIN

	wait for 40 ns;

	-- write to all bytes
	for i in 0 to 4095 loop
		write_byte_enable_n <= "0000";
		writedata <= x"AAAAAAAA";
		address <= std_logic_vector(to_unsigned(i, 12));
		wait for 40 ns;
		assert readdata = x"AAAAAAAA" 
			report "Readdata did not match desired output, at i = " & integer'image(i)
			severity error;
	end loop;
	
	-- write to top half word
	for i in 0 to 4095 loop
		write_byte_enable_n <= "0011";
		writedata <= x"BBBBBBBB";
		address <= std_logic_vector(to_unsigned(i, 12));
		wait for 40 ns;
		assert readdata = x"BBBBAAAA" 
			report "Readdata did not match desired output, at i = " & integer'image(i)
			severity error;
	end loop;
	
	-- write to bottom half
	for i in 0 to 4095 loop
		write_byte_enable_n <= "1100";
		writedata <= x"CCCCCCCC";
		address <= std_logic_vector(to_unsigned(i, 12));
		wait for 40 ns;
		assert readdata = x"BBBBCCCC" 
			report "Readdata did not match desired output, at i = " & integer'image(i)
			severity error;
	end loop;
	
	-- byte 0	
	for i in 0 to 4095 loop
		write_byte_enable_n <= "1110";
		writedata <= x"11111111";
		address <= std_logic_vector(to_unsigned(i, 12));
		wait for 40 ns;
		assert readdata = x"BBBBCC11" 
			report "Readdata did not match desired output, at i = " & integer'image(i)
			severity error;
	end loop;
	
	-- byte 1
	for i in 0 to 4095 loop
		write_byte_enable_n <= "1101";
		writedata <= x"22222222";
		address <= std_logic_vector(to_unsigned(i, 12));
		wait for 40 ns;
		assert readdata = x"BBBB2211" 
			report "Readdata did not match desired output, at i = " & integer'image(i)
			severity error;
	end loop;
	
	-- byte 2
	for i in 0 to 4095 loop
		write_byte_enable_n <= "1011";
		writedata <= x"33333333";
		address <= std_logic_vector(to_unsigned(i, 12));
		wait for 40 ns;
		assert readdata = x"BB332211" 
			report "Readdata did not match desired output, at i = " & integer'image(i)
			severity error;
	end loop;
	
	-- byte 3
	for i in 0 to 4095 loop
		write_byte_enable_n <= "0111";
		writedata <= x"44444444";
		address <= std_logic_vector(to_unsigned(i, 12));
		wait for 40 ns;
		assert readdata = x"44332211" 
			report "Readdata did not match desired output, at i = " & integer'image(i)
			severity error;
	end loop;

	wait;
END PROCESS;
	
uut : raminfr_be
port map(
	clk => clk,
	reset_n => reset_n,
	write_byte_enable_n => write_byte_enable_n,
	address => address,
	writedata => writedata,
	readdata => readdata
);

END ARCHITECTURE beh;