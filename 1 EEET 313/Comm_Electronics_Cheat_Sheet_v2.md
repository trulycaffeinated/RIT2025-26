# Communication Electronics Cheat Sheet (v2)

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

---

## 5. Sallen-Key Filters
- Component relations:  
  $$C_2 = 2C_1$$  
  $$R_1 = R_2 = \frac{1}{2\pi f_c C_1 \sqrt{2}}$$

---

## 6. Oscillators & AM
- Oscillator condition (Barkhausen):  
  $$|A\beta| \geq 1, \quad \angle A\beta = 0^\circ$$
- AM Signal:  
  $$s(t) = [1 + m\cos(\omega_m t)]\cos(\omega_c t)$$
- Modulation index:  
  $$m = A_m / A_c$$
