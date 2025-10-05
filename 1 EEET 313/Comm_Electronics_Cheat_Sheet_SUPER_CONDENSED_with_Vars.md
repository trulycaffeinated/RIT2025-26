# Communication Electronics Super Condensed Cheat Sheet (with Variable Definitions)

## Waves & Antennas
- $$\lambda = c/f$$ (λ = wavelength [m], c = speed of light ≈ 3×10^8 m/s, f = frequency [Hz])  
- Quarter-wave antenna: $$L = \lambda/4$$ (L = antenna length [m])  
- Half-wave dipole: $$L = \lambda/2$$  
- Propagation time: $$t = d/v_p$$ (t = time [s], d = distance [m], v_p = propagation velocity [m/s])  
- Velocity in coax: $$v = c·VF$$ (VF = velocity factor of coax, unitless fraction <1)  

## Decibels & Gains
- $$G_v(dB) = 20 \log_{10}(V_{out}/V_{in})$$ (Vout, Vin = output/input voltage [V])  
- $$G_i(dB) = 20 \log_{10}(I_{out}/I_{in})$$ (Iout, Iin = current [A])  
- $$G_p(dB) = 10 \log_{10}(P_{out}/P_{in})$$ (Pout, Pin = power [W])  
- Cascaded: $$G_{tot} = \prod A_n$$, in dB $$G_{dB} = \sum G_{n,dB}$$ (A = stage gain, dimensionless)  
- $$P_{dBm} = 10 \log_{10}(P/1mW)$$ (P = power [W])  

**Tip:** Multiply numeric gains, add dB. Loss is negative gain.  

## RC Filters
- $$f_c = 1/(2\pi RC)$$ (fc = cutoff freq [Hz], R = resistance [Ω], C = capacitance [F])  
- $$H(j\omega)=\frac{\omega_c}{j\omega+\omega_c}$$ (ω = angular freq = 2πf [rad/s])  
- At fc: -3 dB point, $$|H(j\omega_c)| = 1/√2$$  
- Slope: –20 dB/decade/pole.  

## Resonance & RLC
- $$X_L=2\pi fL$$ (XL = inductive reactance [Ω], L = inductance [H])  
- $$X_C=1/(2\pi fC)$$ (XC = capacitive reactance [Ω], C = capacitance [F])  
- $$f_0=1/(2\pi\sqrt{LC})$$ (f0 = resonant freq [Hz])  
- $$Q=f_0/BW$$ (Q = quality factor, BW = bandwidth [Hz])  
- $$BW=f_0/Q$$  

**Tip:** At resonance, XL = XC. Tank circuits → high Z at f0.  

## Filters (Butterworth / Chebyshev)
- $$L_{ref}=R_0/(2\pi f_c), \; C_{ref}=1/(2\pi R_0 f_c)$$ (R0 = reference resistance [Ω])  
- Butterworth = flat passband, Chebyshev = ripple but sharper cutoff.  

## Matching Networks
- $$Q=X_L/R_s$$ (Rs = source resistance [Ω])  
- $$R_p=(Q^2+1)R_s$$ (Rp = parallel resistance [Ω])  
- $$L_p=L_s(1+1/Q^2)$$ (Ls = series inductance [H])  
- $$C_p=1/((2\pi f)^2L_p)$$ (Cp = capacitance [F])  

**Tip:** Place shunt on higher impedance side.  

## Oscillators & AM
- Barkhausen: $$|A\beta|\geq1, \angle A\beta=0°$$ (A = amp gain, β = feedback factor)  
- AM: $$s(t)=[1+m\cos(\omega_m t)]\cos(\omega_c t)$$  
  - m = modulation index (Am/Ac), Am = message amplitude, Ac = carrier amplitude  
  - ωm = modulating angular freq (2πfm), ωc = carrier angular freq (2πfc)  

**Tip:** m>1 → overmodulation distortion.  

---  
### High-Value Exam Problem Reminders:
- **Antenna length ↔ frequency**: Use $$f=c/\lambda$$. Then L=λ/4 or λ/2.  
- **Cascaded stages**: If dB → add, if numeric → multiply.  
- **Filter cutoff**: $$f_c=1/(2πRC)$$. Slopes: –20 dB/decade per pole.  
- **Q-factor**: $$Q=f_0/BW$$ (fast if f0, BW given).  
- **Power conversions**: $$P_{dBm}=10\log_{10}(P/1mW)$$ ↔ $$P(W)=10^{(dBm/10)}/1000$$.  
