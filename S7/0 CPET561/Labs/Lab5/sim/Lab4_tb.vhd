-------------------------------------------------------------------------
-- Ian Woloshyn
-- CPET 561 Embedded System Design 1
-- Lab 4 Testbench
-- February 19th, 2025
-------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity Lab4_tb is
end entity Lab4_tb;

architecture Behavioral of Lab4_tb is
    -- Component Declaration
    component Lab4
        port (
            CLOCK_50       : in  std_logic;
            reset_n        : in  std_logic;
            write_enable   : in  std_logic;
            write_address  : in  std_logic;
            write_data     : in  unsigned(31 downto 0);
            pwm_out        : out std_logic;
            irq_signal     : out std_logic;
            angle_counter  : out unsigned(31 downto 0)
        );
    end component;

    -- Signals
    signal CLOCK_50       : std_logic := '0';
    signal reset_n        : std_logic := '0';
    signal write_enable   : std_logic := '0';
    signal write_address  : std_logic := '0';
    signal write_data     : unsigned(31 downto 0) := (others => '0');
    signal pwm_out        : std_logic;
    signal irq_signal     : std_logic;
    signal angle_counter  : unsigned(31 downto 0);

    -- Clock process (50 MHz)
    constant CLOCK_PERIOD : time := 20 ns;
    
begin

    -- Lab4 Instantiation
    uut: Lab4
        port map (
            CLOCK_50       => CLOCK_50,
            reset_n        => reset_n,
            write_enable   => write_enable,
            write_address  => write_address,
            write_data     => write_data,
            pwm_out        => pwm_out,
            irq_signal     => irq_signal,
            angle_counter  => angle_counter
        );

    -- Clock process
    clk_process: process
    begin
        while now < 10 ms loop
            CLOCK_50 <= '0';
            wait for CLOCK_PERIOD / 2;
            CLOCK_50 <= '1';
            wait for CLOCK_PERIOD / 2;
        end loop;
        wait;
    end process;

    -- Stimulus process
    stim_proc: process
    begin
        -- Reset sequence
        reset_n <= '0';
        wait for 100 ns;
        reset_n <= '1';
        wait for 100 ns;
        
        -- Write min angle
        write_enable <= '1';
        write_address <= '0';
        write_data <= x"0000C350"; -- 50 000 in hex
        wait for 1000 ns;
        write_enable <= '0';
        wait for 5000 ns;
        
        -- Write max angle
        write_enable <= '1';
        write_address <= '1';
        write_data <= x"000186A0"; -- 100 000 in hex
        wait for 1000 ns;
        write_enable <= '0';
        wait for 5000 ns;

        -- Observe servo movement
		wait for 1000 ns;
		write_enable <= '0';
		wait for 1000 ns;
		write_enable <= '1';
		wait for 1000 ns;
		write_enable <= '0';
		wait for 1000 ns;
		write_enable <= '1';
		wait for 1000 ns;
		write_enable <= '0';
		
        -- Write min angle
        write_enable <= '1';
        write_address <= '0';
        write_data <= x"000124F8"; -- 75 000 in hex
        wait for 1000 ns;
        write_enable <= '0';
        wait for 5000 ns;
		
        -- Observe servo movement
		wait for 1000 ns;
		write_enable <= '0';
		wait for 1000 ns;
		write_enable <= '1';
		wait for 1000 ns;
		write_enable <= '0';
		wait for 1000 ns;
		write_enable <= '1';
		wait for 1000 ns;
		write_enable <= '0';
		
        -- Write max angle
        write_enable <= '1';
        write_address <= '1';
        write_data <= x"00015F90"; -- 90000 in hex
        wait for 1000 ns;
        write_enable <= '0';
        wait for 5000 ns;
		
		-- Observe servo movement
		wait for 1000 ns;
		write_enable <= '0';
		wait for 1000 ns;
		write_enable <= '1';
		wait for 1000 ns;
		write_enable <= '0';
		wait for 1000 ns;
		write_enable <= '1';
		wait for 1000 ns;
		write_enable <= '0';
        
        -- End simulation
        report "Simulation complete";
        wait;
    end process;
end architecture Behavioral;
