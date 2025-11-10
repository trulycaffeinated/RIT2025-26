The overall purpose of Lab 8 is to implement a low-pass and a high pass digital filter

Need to use like six arrays
Put datain into Array_0, move Array_0 to Array_1 and bring in new data in Array_0 from datain
- shifting that data across

Lab provides multiplier coefficients

Use a for loop to instantiate the multiplier

```VHDL
use ieee.std_logic_signed.all;

for i in 0 to 15 generate
uutx : multiplier
-- stuff
end loop;
```

Base-10 Integer Numbers
