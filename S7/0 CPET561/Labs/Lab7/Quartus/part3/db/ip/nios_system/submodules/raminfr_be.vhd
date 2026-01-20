-----------------------------------------------------------------------
-- Note to past jeff : you're an idiot.
-----------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY raminfr_be IS
PORT(
	clk : IN std_logic;
	reset_n : IN std_logic;
	write_byte_enable_n : IN std_logic_vector(3 downto 0);
	address : IN std_logic_vector(11 DOWNTO 0);
	writedata : IN std_logic_vector(31 DOWNTO 0);
	--
	readdata : OUT std_logic_vector(31 DOWNTO 0)
	);
END ENTITY raminfr_be;

ARCHITECTURE rtl OF raminfr_be IS

-- Overall RAM block
SIGNAL ram_buffer : std_logic_vector(31 downto 0) := (OTHERS => '0');

-- Smaller ram chunks to contribute to big RAM
TYPE ram IS ARRAY (4095 DOWNTO 0) OF std_logic_vector (7 DOWNTO 0);
SIGNAL RAM_0 : ram;
SIGNAL RAM_1 : ram;
SIGNAL RAM_2 : ram;
SIGNAL RAM_3 : ram;
SIGNAL read_addr : std_logic_vector(11 DOWNTO 0);

-- debug/wip signal
signal count : integer := 0;

BEGIN

RamBlock : PROCESS(clk)
BEGIN
	IF (clk'event AND clk = '1') THEN
		IF (reset_n = '0') THEN
			read_addr <= (OTHERS => '0');
			FOR i IN 0 TO 4095 loop
				RAM_0(i) <= (OTHERS => '0');
				RAM_1(i) <= (OTHERS => '0');
				RAM_2(i) <= (OTHERS => '0');
				RAM_3(i) <= (OTHERS => '0');
			END LOOP;
		ELSE
			IF (write_byte_enable_n < "1111") THEN
				-- this is fundamental its the writedata that needs to adapt
				IF(write_byte_enable_n(0) = '0') THEN
					RAM_0(conv_integer(address)) <= writedata(7 downto 0);
				END IF;
				IF(write_byte_enable_n(1) = '0') THEN
					RAM_1(conv_integer(address)) <= writedata(15 downto 8);
				END IF;
				IF(write_byte_enable_n(2) = '0') THEN
					RAM_2(conv_integer(address)) <= writedata(23 downto 16);
				END IF;
				IF(write_byte_enable_n(3) = '0') THEN
					RAM_3(conv_integer(address)) <= writedata(31 downto 24);
				END IF;
			END IF;
		END IF;
		
		-- Send all RAM chunks to a buffer to get put into the big one
		ram_buffer(7 downto 0) <= RAM_0(conv_integer(address));
		ram_buffer(15 downto 8) <= RAM_1(conv_integer(address));
		ram_buffer(23 downto 16) <= RAM_2(conv_integer(address));
		ram_buffer(31 downto 24) <= RAM_3(conv_integer(address));
		
		read_addr <= address;
	END IF;
END PROCESS RamBlock;

readdata <= ram_buffer;

END ARCHITECTURE rtl;