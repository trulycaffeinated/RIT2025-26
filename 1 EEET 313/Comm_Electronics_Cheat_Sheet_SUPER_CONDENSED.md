# Communication Electronics Super Condensed Cheat Sheet

## Waves & Antennas
- $$\lambda = c/f$$ (wavelength, used often in antenna problems)  
- Quarter-wave antenna: $$L = \lambda/4$$  
- Half-wave dipole: $$L = \lambda/2$$  
- Propagation time: $$t = d/v_p$$ (exam problems: Earth-Mars delay, coax velocity factor $$v=c·VF$$)  

## Decibels & Gains
- Voltage gain: $$G_v(dB) = 20 \log_{10}(V_{out}/V_{in})$$  
- Current gain: $$G_i(dB) = 20 \log_{10}(I_{out}/I_{in})$$  
- Power gain: $$G_p(dB) = 10 \log_{10}(P_{out}/P_{in})$$  
- Cascaded: $$G_{tot} = \prod A_n$$, in dB $$G_{dB} = \sum G_{n,dB}$$  
- Power in dBm: $$P_{dBm} = 10 \log_{10}(P/1mW)$$  
**Exam tip:** Gains in series → multiply (num), add (dB). Loss = negative dB.  

## RC Filters
- Corner frequency: $$f_c = 1/(2\pi RC)$$  
- Transfer: $$H(j\omega)=\frac{\omega_c}{j\omega+\omega_c}$$ → at $$f_c$$: -3 dB point.  
- Attenuation slope: -20 dB/decade per pole (exam Qs ask for slope extrapolation).  

## Resonance & RLC
- $$X_L=2\pi fL, \; X_C=1/(2\pi fC)$$  
- Resonance: $$f_0=1/(2\pi\sqrt{LC})$$  
- Bandwidth: $$BW=f_0/Q, \; Q=f_0/BW$$  
**Exam tip:** Identify given L, C, R, then solve for f0, Q, BW quickly.  

## Filters (Butterworth / Chebyshev)
- $$L_{ref}=R_0/(2\pi f_c), \; C_{ref}=1/(2\pi R_0 f_c)$$  
- Butterworth: flat passband, smooth. Chebyshev: ripple but sharper cutoff.  

## Matching Networks
- $$Q=X_L/R_s$$, $$R_p=(Q^2+1)R_s$$  
- Series-to-parallel: $$L_p=L_s(1+1/Q^2)$$  
- $$C_p=1/((2\pi f)^2L_p)$$  
**Exam tip:** Shunt element always on higher impedance side. Match source→load for max power transfer.  

## Oscillators & AM
- Barkhausen: $$|A\beta|\geq1, \angle A\beta=0°$$ (oscillation condition)  
- AM: $$s(t)=[1+m\cos(\omega_m t)]\cos(\omega_c t)$$, modulation index $$m=A_m/A_c$$  
**Exam tip:** If $$m>1$$ → overmodulation distortion. Oscillator generates carrier before modulation.  

---  
### High-Value Exam Problem Reminders:
- **Antenna length ↔ frequency**: Use $$f=c/\lambda$$, then quarter or half λ.  
- **Cascaded stages**: If in dB → add; if numeric → multiply. Convert back/forth as needed.  
- **Filter cutoff**: $$f_c=1/(2πRC)$$ and slope rules (–20 dB/decade per pole).  
- **Q-factor**: $$Q=f_0/BW$$ (fast way if f0 and BW given).  
- **Convert power levels**: $$P_{dBm}$$ ↔ W using $$10^{dBm/10}/1000$$.  
