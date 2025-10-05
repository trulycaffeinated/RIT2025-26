# Communication Electronics Cheat Sheet (Equations + Notes)

## 1. Waves & Antennas
- Wavelength:  
  $$\lambda = \frac{c}{f}$$
- Quarter-wave antenna:  
  $$L = \lambda/4$$
- Half-wave dipole:  
  $$L = \lambda/2$$
- Propagation time:  
  $$t = d/v_p$$
- Velocity in coax:  
  $$v = c \cdot VF$$

**Notes:**  
- Quarter-wave antennas reflect from the ground to appear as half-wave.  
- Coax has velocity factor < 1, reducing propagation speed.  
- Free space propagation delay can be significant for planetary distances (Mars-Earth ~12.5 min).

---

## 2. Decibels & Gains
- Voltage gain (dB):  
  $$G_v(dB) = 20 \log_{10}(V_{out}/V_{in})$$
- Current gain (dB):  
  $$G_i(dB) = 20 \log_{10}(I_{out}/I_{in})$$
- Power gain (dB):  
  $$G_p(dB) = 10 \log_{10}(P_{out}/P_{in})$$
- Cascaded gains:  
  $$G_{tot} = \prod A_n, \quad G_{dB} = \sum G_{n,dB}$$
- Power in dBm:  
  $$P_{dBm} = 10 \log_{10}(P/1mW)$$

**Notes:**  
- Loss is expressed as negative dB gain.  
- Use 20 log for V and I ratios, 10 log for power.  
- Cascaded stages multiply numerically but add in dB.  

---

## 3. RC Filters
- Corner frequency:  
  $$f_c = \frac{1}{2\pi RC}$$
- Attenuation slopes:  
  - Single pole: -20 dB/decade (–6 dB/octave)  
  - Two pole: -40 dB/decade (–12 dB/octave)
- Transfer function:  
  $$H(j\omega) = \frac{\omega_c}{j\omega + \omega_c}$$
- At corner frequency:  
  $$|H(j\omega_c)| = 1/\sqrt{2} = -3dB$$

**Notes:**  
- LPF passes low frequencies, attenuates high.  
- HPF passes high frequencies, attenuates low.  
- Attenuation slope depends on number of poles.  

---

## 4. Resonance & RLC Circuits
- Inductive reactance:  
  $$X_L = 2\pi f L$$
- Capacitive reactance:  
  $$X_C = \frac{1}{2\pi f C}$$
- Resonant frequency:  
  $$f_0 = \frac{1}{2\pi \sqrt{LC}}$$
- Quality factor:  
  $$Q = \frac{X_L}{R_s} = \frac{f_0}{BW}$$
- Bandwidth:  
  $$BW = f_0/Q$$

**Notes:**  
- At resonance, $X_L = X_C$.  
- Tank circuits: high impedance at resonance, block current.  
- Higher Q = narrower bandwidth.  
- Inductor Q: $$Q = X_L / R_s$$  
- Capacitor Q: $$Q = R_p / X_C$$  

---

## 5. LC Filters
- Butterworth (maximally flat):  
  $$L_{ref} = \frac{R_0}{2\pi f_c}, \quad C_{ref} = \frac{1}{2\pi R_0 f_c}$$
- Chebyshev (ripple, sharp cutoff):  
  $$L_{ref} = \frac{R_0}{2\pi f_c}, \quad C_{ref} = \frac{1}{2\pi R_0 f_c}$$

**Notes:**  
- Insertion loss: signal loss even in passband.  
- Transition region: between stopband and passband.  
- Butterworth = smooth response, Chebyshev = sharper roll-off with ripple.  

---

## 6. Sallen-Key Filters
- Component relations:  
  $$C_2 = 2C_1$$  
  $$R_1 = R_2 = \frac{1}{2\pi f_c C_1 \sqrt{2}}$$

**Notes:**  
- Active filter topology for implementing 2nd-order LPF.  

---

## 7. Matching Networks
- Quality factor:  
  $$Q = X_L / R_s$$
- Equivalent parallel resistance:  
  $$R_p = (Q^2 + 1)R_s$$
- Parallel inductance:  
  $$L_p = L_s (1 + 1/Q^2)$$
- Parallel capacitance:  
  $$C_p = 1/((2\pi f)^2 L_p)$$

**Notes:**  
- Shunt component sits on higher impedance side.  
- Matching ensures max power transfer.  
- At design frequency, series vs. parallel equivalents look identical.  

---

## 8. Oscillators & AM
- Oscillator condition (Barkhausen):  
  $$|A\beta| \geq 1, \quad \angle A\beta = 0^\circ$$
- AM Signal:  
  $$s(t) = [1 + m\cos(\omega_m t)]\cos(\omega_c t)$$
- Modulation index:  
  $$m = A_m / A_c$$

**Notes:**  
- AM = amplitude modulation, FM/PM = angle modulation.  
- Need oscillator to generate carrier before modulation.  
- Higher modulation index = deeper modulation, distortion if $m > 1$.  
