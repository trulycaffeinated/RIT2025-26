# Communication Electronics Super Condensed Cheat Sheet (2 Columns)

<div style="column-count:2; column-gap:30px;">

## Waves & Antennas
- λ = c / f   (λ = wavelength [m], c = 3×10^8 m/s, f = frequency [Hz])  
- Quarter-wave antenna: L = λ / 4   (L = antenna length [m])  
- Half-wave dipole: L = λ / 2  
- Propagation time: t = d / vp   (t = time [s], d = distance [m], vp = propagation velocity [m/s])  
- Velocity in coax: v = c · VF   (VF = velocity factor < 1)  

## Decibels & Gains
- Voltage gain: Gv(dB) = 20 log10(Vout / Vin)  
- Current gain: Gi(dB) = 20 log10(Iout / Iin)  
- Power gain: Gp(dB) = 10 log10(Pout / Pin)  
- Cascaded: Gtotal = product of An (numeric), GdB = sum of Gn,dB  
- Power in dBm: PdBm = 10 log10(P / 1mW)  
**Tip:** Multiply numeric gains, add dB. Loss = negative dB.  

## RC Filters
- Cutoff freq: fc = 1 / (2πRC)   (R = Ω, C = F)  
- Transfer: H(jω) = ωc / (jω + ωc), with ω = 2πf  
- At fc: |H| = 1/√2 = -3 dB  
- Slope: –20 dB/decade per pole  

## Resonance & RLC
- XL = 2π f L   (L in H, XL in Ω)  
- XC = 1 / (2π f C)   (C in F, XC in Ω)  
- Resonance: f0 = 1 / (2π √(LC))  
- Bandwidth: BW = f0 / Q  
- Quality factor: Q = f0 / BW or Q = XL / Rs  
**Tip:** At resonance XL = XC, tank circuits = high Z  

## Filters
- Butterworth/Chebyshev reference:  
  Lref = R0 / (2π fc),   Cref = 1 / (2π R0 fc)  
- Butterworth = flat passband, Chebyshev = ripple but sharper cutoff  

## Matching Networks
- Q = XL / Rs  
- Rp = (Q^2 + 1) Rs  
- Lp = Ls (1 + 1/Q^2)  
- Cp = 1 / ((2π f)^2 Lp)  
**Tip:** Place shunt element on higher impedance side  

## Oscillators & AM
- Barkhausen condition: |Aβ| ≥ 1, ∠Aβ = 0°  
- AM signal: s(t) = [1 + m cos(ωm t)] cos(ωc t)  
- Modulation index: m = Am / Ac (Am = message amp, Ac = carrier amp)  
- ωm = 2π fm, ωc = 2π fc  
**Tip:** m > 1 → overmodulation distortion  

## Exam Reminders
- Antenna length ↔ frequency: f = c / λ, then L = λ/4 or λ/2  
- Cascaded stages: add dB or multiply numeric  
- Filter cutoff: fc = 1 / (2π RC), slope rules per pole  
- Q-factor: Q = f0 / BW (fast if f0, BW given)  
- Power conversions: PdBm ↔ W with P(W) = 10^(dBm/10) / 1000  

</div>
