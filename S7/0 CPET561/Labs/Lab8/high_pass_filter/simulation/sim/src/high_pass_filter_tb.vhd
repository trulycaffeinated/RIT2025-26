library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.textio.all;

entity high_pass_filter_tb is
end entity high_pass_filter_tb;

architecture beh of high_pass_filter_tb is
    component high_pass_filter is
        port (
            clk        : in  std_logic;
            reset_n    : in  std_logic;
            data_in    : in  std_logic_vector(15 downto 0);
            filter_en  : in  std_logic;
            data_out   : out std_logic_vector(15 downto 0)
        );
    end component;

    signal clk        : std_logic := '0';
    signal reset_n    : std_logic := '0';
    signal filter_en  : std_logic := '0';
    signal data_in    : std_logic_vector(15 downto 0) := (others => '0');
    signal data_out   : std_logic_vector(15 downto 0);

    constant CLOCK_PERIOD : time := 20 ns;

    type sample_array is array (0 to 39) of std_logic_vector(15 downto 0);
    signal input_samples : sample_array := (others => (others => '0'));

begin

    uut: high_pass_filter
        port map (
            clk       => clk,
            reset_n   => reset_n,
            data_in   => data_in,
            filter_en => filter_en,
            data_out  => data_out
        );

    clk_process: process
    begin
        while now < 5 ms loop
            clk <= '0';
            wait for CLOCK_PERIOD / 2;
            clk <= '1';
            wait for CLOCK_PERIOD / 2;
        end loop;
        wait;
    end process;

    stim_proc: process
        file readFile  : text open read_mode is "../../src/one_cycle_200_8k.csv";
        file outfile : text open write_mode is "../../src/result.csv";
        variable lineIn   : line;
        variable lineOut   : line;
        variable val : integer;
        variable temp_out : integer;
    begin
        reset_n <= '0';
        wait for 40 ns;
        reset_n <= '1';
        wait for 20 ns;

        for i in 0 to 39 loop
            readline(readFile, lineIn);
            read(lineIn, val);
            input_samples(i) <= std_logic_vector(to_signed(val, 16));
        end loop;

        for i in 0 to 10 loop
            for j in 0 to 39 loop
                data_in <= input_samples(j);
                filter_en <= '1';
                wait for CLOCK_PERIOD;
                filter_en <= '0';
                wait for CLOCK_PERIOD;

                temp_out := to_integer(signed(data_out));
                write(lineOut, temp_out);
                writeline(outfile, lineOut);
            end loop;
        end loop;

        file_close(readFile);
        file_close(outfile);
        report "Simulation complete";
        wait;
    end process;
end architecture beh;