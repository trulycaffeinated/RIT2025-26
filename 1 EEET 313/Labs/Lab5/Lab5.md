$$
\begin{aligned}
\text{Assigned Values} \\
R_s = 50\ohm \\
R_L = 200\ohm \\
f = 10MHz \\
\\
\text{Calculate Q for Series Ind and Shunt Cap} \\
Q=\sqrt{\frac{200}{50} -1} = 1.732 \\
\\
X \\
X = Q \times R_S = 1.732 \times 50\ohm = 86.6 \\
\\
\text{Series and Parallel values (Series L)} \\
L_S = \frac{X}{2\pi \times f} = 1.3\mu H \\
L_P = L_S(1 + \frac{1}{Q^2}) = 1.8\mu H \\
C_P = \frac{1}{(2pi \times f)^2 \times L_P} = 137.8pF \\
\\
\text{Series and Parallel Values (Series C)} \\
C_S = \frac{1}{2\pi \times f \times X} = 183.7pF \\
X_{Shunt} = X(1 + \frac{1}{Q^2}) = 115.47 \\
L_P = \frac{X_{Shunt}}{2\pi \times f} = 1.83\mu H
\end{aligned}
$$


