-- Jeff Taylor
-- Servo Controller custom IP - Lab 4
-- 10.1.2025 -- happy spooky season
library ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

entity servo_controller is
	PORT(
		-- inputs --
		CLOCK_50					: in std_logic; -- 50 MHz system CLOCK_50
		reset_n 				: in std_logic; -- active low reset
		we						: in std_logic; -- single bit write enable -- active high
		writedata			: in unsigned(31 downto 0); -- writedata in to be stored
		address 				: in std_logic; --only one address bit is needed to choose between two registers
		-- outputs --
		irq_out				: out std_logic; -- interrupt output
		out_wave_export	: out std_logic  -- wave output (single bit?)
	);
end entity servo_controller;

architecture rtl of servo_controller is

-- two signals for angle values
signal min_angle_count 	: unsigned(31 downto 0); -- change this to 45 degrees
signal max_angle_count 	: unsigned(31 downto 0); -- change this to 135 
signal period_counter	: unsigned(31 downto 0);
signal angle_count		: unsigned(31 downto 0) := x"000124F8";

-- state signals
signal current_state : std_logic_vector(3 downto 0);
signal next_state : std_logic_vector(3 downto 0);

constant SWEEP_RIGHT : std_logic_vector(3 downto 0) := "0001";
constant INT_RIGHT : std_logic_vector(3 downto 0) := "0010";
constant SWEEP_LEFT : std_logic_vector(3 downto 0) := "0100";
constant INT_LEFT : std_logic_vector(3 downto 0) := "1000";

begin

-- update min/max angle values
process(CLOCK_50, reset_n)
begin
	if(reset_n = '0') then
		min_angle_count <= x"0000C350";
		max_angle_count <= x"000186A0";
	else
		if(we = '1') then
			if(address = '0') then
				min_angle_count <= writedata;
			elsif(address = '1') then
				max_angle_count <= writedata;
			else 
				-- boken
			end if;
		end if;
	end if;
end process;

-- state prelim stuffs
process(CLOCK_50, reset_n)
begin
	if(reset_n = '0') then
		current_state <= SWEEP_RIGHT;
	elsif(CLOCK_50'event AND CLOCK_50 = '1') then
		current_state <= next_state; -- update state on CLOCK_50
	end if;
end process;

-- period counter increment
process(CLOCK_50, reset_n)
begin
	if reset_n = '0' then
		period_counter <= (OTHERS => '0');
	elsif rising_edge(CLOCK_50) then
		if(period_counter < x"00F4240") then -- 1,000,000
			period_counter <= period_counter + 1;
		else
			period_counter <= (OTHERS => '0');
		end if;
	end if;
end process;

-- change state process
process(CLOCK_50, reset_n)
begin
	if(reset_n = '0') then
		irq_out <= '0';
		out_wave_export <= '0';
	elsif(rising_edge(CLOCK_50)) then
		case current_state is
			when SWEEP_RIGHT =>
				if(angle_count >= max_angle_count) then
					next_state <= INT_RIGHT;
				else
					next_state <= SWEEP_RIGHT;
					angle_count <= angle_count + 6; -- 5.333 Gotten from CHATGPT for sweeping from one side to the next in 1.5 seconds. Times by 100x for sim
				end if;
			when INT_RIGHT =>
				if(we = '1') then
					irq_out <= '0';
					next_state <= SWEEP_LEFT;
				else
					next_state <= INT_RIGHT;
					irq_out <= '1';
				end if;
			when SWEEP_LEFT =>
				if(angle_count <= min_angle_count) then
					next_state <= INT_LEFT;
				else
					next_state <= SWEEP_LEFT;
					angle_count <= angle_count - 6; -- 5.333 Gotten from CHATGPT for sweeping from one side to the next in 1.5 seconds. Times by 1000x for sim
				end if;
			when INT_LEFT =>
				if(we = '1') then
					irq_out <= '0';
					next_state <= SWEEP_RIGHT;
				else
					next_state <= INT_LEFT;
					irq_out <= '1';
				end if;
			when others =>
				-- boken
		end case;
	end if;
	
	-- Output waveform for current period
	if period_counter < angle_count then
		out_wave_export <= '1';
	else
		out_wave_export <= '0';
	end if;

end process;
	

end architecture rtl;