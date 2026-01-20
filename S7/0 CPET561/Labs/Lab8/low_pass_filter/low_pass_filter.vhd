-- Jeff Taylor
-- LPF

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_signed.all;

entity low_pass_filter is
	port(
		clk : in std_logic; -- CLOCK_50
		reset_n : in std_logic; 
		data_in : in std_logic_vector(15 downto 0);
		filter_en : in std_logic;
		--
		data_out : out std_logic_vector(15 downto 0)
	);
end low_pass_filter;

architecture beh of low_pass_filter is 

type array_lpf is array (0 to 16) of std_logic_vector(15 downto 0);
constant coefficients : array_lpf := (
        0  => x"0052",  -- 0.0025 * 2^15
        1  => x"00BB",  -- 0.0057
        2  => x"01E2",  -- 0.0147
        3  => x"0408",  -- 0.0315
        4  => x"071B",  -- 0.0555
        5  => x"0AAD",  -- 0.0834
        6  => x"0E11",  -- 0.1099
        7  => x"1080",  -- 0.1289
        8  => x"1162",  -- 0.1358
        9  => x"1080",  -- 0.1289
        10 => x"0E11",  -- 0.1099
        11 => x"0AAD",  -- 0.0834
        12 => x"071B",  -- 0.0555
        13 => x"0408",  -- 0.0315
        14 => x"01E2",  -- 0.0147
        15 => x"00BB",  -- 0.0057
        16 => x"0052"   -- 0.0025
    );

signal sum : std_logic_vector(31 downto 0);
signal data_in_buffer : array_lpf := (OTHERS => (OTHERS => '0'));
	
component mult is
	port(
		dataa : in std_logic_vector(15 downto 0);
		datab : in std_logic_vector(15 downto 0);
		result : out std_logic_vector(31 downto 0)
	);
end component mult;

--type mult_array is array (0 to 16) of signed(31 downto 0);
type mult_array is array (0 to 16) of std_logic_vector(31 downto 0); -- ACTUAL CODE
signal mult_results : mult_array;

begin

-- generate 16 multipliers
-- SIMULATION CODE ONLY
	--mult_sim : for i in 0 to 16 generate
		--mult_results(i) <= signed(coefficients(i)) * signed(data_in_buffer(i));
	--end generate;
-- ACTUAL CODE
mult_generation : for i in 0 to 16 generate
	mult_inst : mult PORT MAP (
		dataa	 => data_in_buffer(i),
		datab	 => coefficients(i),
		result	 => mult_results(i)
	);
end generate mult_generation;

-- Fill up the input delay (will be passed to the multipler)
process(clk, reset_n)
begin
	if(reset_n = '0') then
		for i in 0 to 16 loop
			-- fill with zeros
			data_in_buffer(i) <= (OTHERS => '0');
		end loop;
	elsif(rising_edge(clk)) then
		if(filter_en = '1') then
			data_in_buffer(0) <= data_in;
			for i in 1 to 16 loop
				data_in_buffer(i) <= data_in_buffer(i - 1);
			end loop;
		end if;
	end if;
end process;

-- do the sum
process(clk, reset_n)
	variable sum_buffer : std_logic_vector(31 downto 0);
begin
	if(reset_n = '0') then
		sum <= (OTHERS => '0');
	elsif(rising_edge(clk)) then
		if(filter_en = '1') then
			sum_buffer := (OTHERS => '0');
			for i in 0 to 16 loop
				sum_buffer := sum_buffer + std_logic_vector(mult_results(i));
			end loop;
			sum <= sum_buffer;
		end if;
	end if;
end process;

-- data out
data_out <= sum(30 downto 15);

end architecture beh;