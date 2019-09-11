library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity addressdecoder is
	Port (
		a10 : In std_logic;
		a11 : In std_logic;

		sram_cs : Out std_logic;
		adc_cs  : Out std_logic;
		oled_cs : Out std_logic
	);

	attribute LOC : string;
	attribute LOC of sram_cs : signal is "P19";
	attribute LOC of adc_cs : signal is "P18";
	attribute LOC of oled_cs : signal is "P17";
	attribute LOC of a11 : signal is "P1";
	attribute LOC of a10 : signal is "P2";
end addressdecoder;

architecture behave of addressdecoder is begin
 -- implement the functionality here
	
	sram_cs <= a11;
	adc_cs <= NOT((NOT a11) AND a10);
	oled_cs <= NOT((NOT a11) AND (NOT a10));

end behave;

