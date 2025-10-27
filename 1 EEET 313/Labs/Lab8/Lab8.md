leave r107 and jmp1 out

## Calculations
$$
\begin{aligned}
\text{Bottom transitor calculations} \\
\\
V=\frac{I}{R}\\
R_8 = \frac{V_{ce}}{2ma} \\
R_8 = 500 \ohm \\
\\
V_B = 1.7V \\
I_B = \frac{I_E}{\beta} = \frac{2mA}{80} = 25\mu A \\
R_5 = \frac{V_B}{I_{BB}} = \frac{1.7}{25\mu A \times 50} = 1.36k\ohm \\
R_4 = \frac{V_C - V_B}{I_{BB}+I_B} = \frac{5V-1.7V}{25\mu A * 50 + 25\mu A} = 2.6k\ohm\\
\end{aligned}
$$

$$
\begin{aligned}
\text{Side bias's calculations} \\
I_{E(max)} = 2mA \\
V_E = 2V \\
\\
I_B = \frac{2mA}{80} = 25\mu A \\
V_B = 2.7 V \\
R_3 = \frac{2.7V}{25\mu A \times 50} = 2.16k \ohm \\
R_2 = \frac{5V-2.7V}{25\mu A \times 50 + 25\mu A} = 1.8k\ohm
\end{aligned}
$$

